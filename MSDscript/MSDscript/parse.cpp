//
//  parse.cpp
//  MSDscript
//
//  Created by Taylor Dunn on 2/10/21.
//

#include "parse.hpp"
#include "val.hpp"
#include "catch.h"
#include <stdexcept>
#include <cassert>

void consume (std::istream &in, int expect){
    int c = in.get();
    assert(c == expect);
}

void skip_whitespace(std::istream &in){
    while(1){
        int c = in.peek();
        if(!isspace(c)){
            break;
        }
        consume(in, c);
    }
}

Expr* parse_num(std::istream &in){
    int n = 0;
    bool negative = false;
    if (in.peek() == '-'){
        negative = true;
        consume(in, '-');
    }
    while(1) {
        int c = in.peek();
        if (isdigit(c)){
            consume(in, c);
            n = n*10 + (c - '0');
        } else {
            break;
        }
    }
    if (negative){
        n = -n;
    }
    return new NumExpr(n);
}

Expr* parse_variable(std::istream &in){
    skip_whitespace(in);
    int c = in.peek();
    std::string s = "";
    while(isalpha(c)){
        s+=c;
        consume (in, c);
        c = in.peek();
    }
    return new VarExpr(s);
}

std::string parse_keyword(std::istream &in){
    int c = in.peek();
    std::string keyword = "_";
    if(c == '_'){
        consume(in,c);
        c = in.peek();
        while(isalpha(c)){
            keyword+=c;
            consume (in, c);
            c = in.peek();
        }
    }
    skip_whitespace(in);
    return keyword;
}

Expr* parse_let(std::istream &in){
    skip_whitespace(in);
    std::string lhs = parse_variable(in)->to_string_pretty();
    skip_whitespace(in);
    int c = in.peek();
    if (c=='='){
        consume(in, '=');
    } else {
        throw std::runtime_error("equal expected");
    }
    skip_whitespace(in);
    Expr* rhs = parse_expr(in);
    skip_whitespace(in);
    if(parse_keyword(in) != "_in"){
        throw std::runtime_error("in expected");
    }
    skip_whitespace(in);
    Expr* body = parse_expr(in);
    return new LetExpr(lhs, rhs, body);
}

Expr* parse_if(std::istream &in){
    skip_whitespace(in);
    Expr* test_part = parse_expr(in);
    skip_whitespace(in);
    int c = in.peek();
    if(parse_keyword(in) != "_then"){
        throw std::runtime_error("then expected");
    }
    skip_whitespace(in);
    Expr* then_part = parse_expr(in);
    skip_whitespace(in);
    c = in.peek();
    if(parse_keyword(in) != "_else"){
        throw std::runtime_error("else expected");
    }
    Expr* else_part = parse_expr(in);
    return new IfExpr(test_part, then_part, else_part);
}

Expr* parse_expr(std::istream &in){
    Expr *e;
    e = parse_comparg(in);
    skip_whitespace(in);
    int c = in.peek();
    if (c=='='){
        consume(in, '=');
        c=in.peek();
        if (c=='='){
            consume(in, '=');
            Expr *rhs = parse_expr(in);
            return new EqExpr(e,rhs);
        } else{
            throw std::runtime_error("2nd equal sign expected");
        }
    } else {
        return e;
    }
}

Expr* parse_comparg(std::istream &in){
    Expr *e;
    e = parse_addend(in);
    skip_whitespace(in);
    int c = in.peek();
    if (c=='+'){
        consume(in, '+');
        Expr *rhs = parse_comparg(in);
        return new AddExpr(e,rhs);
    } else {
        return e;
    }
}

Expr* parse_addend(std::istream &in){
    Expr *e;
    e = parse_multicand(in);
    skip_whitespace(in);
    int c = in.peek();
    if(c=='*'){
        consume(in, '*');
        Expr *rhs = parse_addend(in);
        return new MultExpr(e, rhs);
    } else {
        return e;
    }
}

Expr* parse_inner(std::istream &in){
    skip_whitespace(in);
    int c = in.peek();
    if((c=='-') || isdigit(c)){
        return parse_num(in);
    } else if (c == '('){
        consume(in, '(');
        Expr *e = parse_expr(in); //recursive function
        skip_whitespace(in);
        c = in.get();
        if (c!= ')'){
            throw std::runtime_error("missing close parenthesis");
        }
        return e;
    } else if (isalpha(c)){
        return parse_variable(in);
    } else if ( c == '_'){
        std::string kw = parse_keyword(in);
        if(kw == "_let"){
            return parse_let(in);
        } else if (kw == "_false"){
            return new BoolExpr(false);
        } else if (kw == "_true"){
            return new BoolExpr(true);
        } else if (kw == "_if"){
            return parse_if(in);
        } else if (kw == "_fun"){
            return parse_function(in);
        }else {
            throw std::runtime_error("Unable to process keyword");
        }
    } else {
        throw std::runtime_error("Unable to process request");
    }}

Expr* parse_multicand(std::istream &in){
    skip_whitespace(in);
    Expr *e;
    e = parse_inner(in);
    skip_whitespace(in);
    while (in.peek() == '('){
        consume(in, '(');
        skip_whitespace(in);
        Expr *actual_arg = parse_expr(in);
        skip_whitespace(in);
        consume(in,')');
        e = new CallExpr(e, actual_arg);
    }
    return e;
}

Expr* parse_function(std::istream &in){
    skip_whitespace(in);
    std::string formal_arg;
    if (in.peek() == '('){
        consume(in, '(');
        skip_whitespace(in);
        formal_arg = parse_variable(in)->to_string_pretty();
        skip_whitespace(in);
        int c = in.get();
        if (c!= ')'){
            throw std::runtime_error("missing close parenthesis");
        }
    }
    skip_whitespace(in);
    Expr *body;
    body = parse_expr(in);
    return new FunExpr(formal_arg, body);
}

Expr* parse_str(std::string s){
    std::istringstream str(s);
    Expr * e = parse_expr(str);
    skip_whitespace(str);
    if(!str.eof()){
        throw std::runtime_error("Invalid input for an expression");
    }
    return e;
}

TEST_CASE ("Parse"){
    CHECK((parse_str("1")->equals(new NumExpr(1))));
    CHECK((parse_str("0"))->equals(new NumExpr(0)));
    CHECK((parse_str("-1"))->equals(new NumExpr(-1)));
    CHECK((parse_str("taylor"))->equals(new VarExpr("taylor")));
    CHECK((parse_str("0+1"))->equals(new AddExpr(new NumExpr(0), new NumExpr(1))));
    CHECK((parse_str("-1+1"))->equals(new AddExpr(new NumExpr(-1),new NumExpr(1))) == true);
    CHECK((parse_str("(0+1)+1"))->equals(new AddExpr(new AddExpr(new NumExpr(0), new NumExpr(1)),new NumExpr(1))) == true);
    CHECK((parse_str("0*1"))->equals(new MultExpr(new NumExpr(0),new NumExpr(1))) == true);
    CHECK((parse_str("(-2*1)*3"))->equals(new MultExpr(new MultExpr(new NumExpr(-2), new NumExpr(1)),new NumExpr(3))) == true);
    CHECK((parse_str("x*y"))->equals(new MultExpr(new VarExpr("x"),new VarExpr("y"))));
    CHECK((parse_str("w * 1"))->equals(new MultExpr(new VarExpr("w"),new NumExpr(1))));
    std::string name = "x";
    LetExpr *let1 = new LetExpr(name, new NumExpr(5), (new AddExpr (new VarExpr("x"), new NumExpr (4))));
    CHECK((parse_str("_let x=5 _in x+4")->equals(let1)));
    CHECK((parse_str("_let x=5 _in _let x = x+2 _in x + 1")->equals(new LetExpr("x", new NumExpr(5), new LetExpr("x", new AddExpr( new VarExpr("x"), new NumExpr(2)), new AddExpr(new VarExpr("x"), new NumExpr(1)))))));
    CHECK((parse_str("_if _true _then 5 _else 3")->equals (new IfExpr(new BoolExpr(true), new NumExpr(5), new NumExpr(3)))));
    CHECK((parse_str("_let x=5 _in _if _false _then 1 _else _true")->equals(new LetExpr("x", new NumExpr(5), new IfExpr(new BoolExpr(false), new NumExpr(1), new BoolExpr(true))))));
    CHECK((parse_str("5 == 5")->equals(new EqExpr(new NumExpr(5), new NumExpr(5)))));
    CHECK((parse_str("_let f = _fun (x) x+1 _in f(5)")->equals(new LetExpr("f",
                                                                           new FunExpr("x", new AddExpr(new VarExpr("x"), new NumExpr(1))),
                                                                           new CallExpr(new VarExpr("f"), new NumExpr(5))))));
    CHECK((parse_str("_let f = _fun (x) _true _in f(5)")->equals(new LetExpr("f",
                                                                           new FunExpr("x", new BoolExpr(true)),
                                                                           new CallExpr(new VarExpr("f"), new NumExpr(5))))));
    CHECK_THROWS_WITH((parse_str("x"))->interp(), "No value for variable" );
    CHECK_THROWS_WITH((parse_str("variable"))->interp(), "No value for variable" );
    CHECK_THROWS_WITH((parse_str(""))->interp(), "Unable to process request" );
    CHECK_THROWS_WITH((parse_str("b+31"))->interp(), "No value for variable" );
    CHECK_THROWS_WITH((parse_str("3*t"))->interp(), "No value for variable" );
    CHECK_THROWS_WITH((parse_str("_let x = t _in x+1"))->interp(), "No value for variable");
    CHECK_THROWS_WITH((parse_str("_lot x = 3 _in x+1"))->interp(), "Unable to process keyword");
    CHECK_THROWS_WITH((parse_str("_let x + 3 _in x+1"))->interp(), "equal expected");
    CHECK_THROWS_WITH((parse_str("_let x = 3 _it x+1"))->interp(), "in expected");
    CHECK_THROWS_WITH((parse_str("(x+4"))->interp(), "missing close parenthesis");
    CHECK_THROWS_WITH((parse_str("3+(4+1"))->interp(), "missing close parenthesis");
    CHECK_THROWS_WITH((parse_str("5=+7"))->interp(), "2nd equal sign expected");
    CHECK_THROWS_WITH((parse_str("_if 1 _ten 2 _else 5"))->interp(), "then expected");
    CHECK_THROWS_WITH((parse_str("_if 1 _then 2 _els 5"))->interp(), "else expected");
    CHECK_THROWS_WITH((parse_str("_fun (x x-1"))->interp(),"missing close parenthesis");
    CHECK_THROWS_WITH((parse_str("(_fun (x) 5) + 2"))->interp(), "addition of non-number");
    CHECK_THROWS_WITH((parse_str("(_fun (x) 5) * 2"))->interp(), "multiplication of non-number");
}

TEST_CASE("Matthews PDF Quiz Parse"){
    CHECK((parse_str("(1+2)==(3+0)")->interp()->equals((new BoolExpr(true))->interp())));
    CHECK((parse_str("1+2==3+0")->interp()->equals((new BoolExpr(true))->interp())));
    CHECK_THROWS_WITH((parse_str("_true + _false"))->interp(),"addition of non-number");
    }
