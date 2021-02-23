//
//  parse.cpp
//  MSDscript
//
//  Created by Taylor Dunn on 2/10/21.
//

#include "parse.hpp"
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

void parse_keyword(std::istream &in, std::string keyword){
    std::string keyword_check = "";
    for (int i = 0; i < keyword.size(); i++){
        keyword_check += in.get();
    }
    if (keyword_check == keyword){
        return;
    } else {
        throw std::runtime_error("unable to parse keyword");
    }
}

Expr* parse_let(std::istream &in){
    skip_whitespace(in);
    int c = in.peek();
    consume(in, '_');
    parse_keyword(in, "let");
    skip_whitespace(in);
    std::string lhs = parse_variable(in)->to_string_pretty();
    skip_whitespace(in);
    c = in.peek();
    if (c=='='){
        consume(in, '=');
    } else {
        throw std::runtime_error("equal expected");
    }
    skip_whitespace(in);
    Expr* rhs = parse_expr(in);
    skip_whitespace(in);
    c = in.peek();
    consume(in, '_');
    parse_keyword(in, "in");
    Expr* body = parse_expr(in);
    return new LetExpr(lhs, rhs, body);
}

Expr* parse_expr(std::istream &in){
    Expr *e;
    e = parse_addend(in);
    skip_whitespace(in);
    int c = in.peek();
    if (c=='+'){
        consume(in, '+');
        Expr *rhs = parse_expr(in);
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

Expr* parse_multicand(std::istream &in){
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
    } else if (c != '_'){
        return parse_variable(in);
    } else if ( c == '_'){
        return parse_let(in);
    } else {
        throw std::runtime_error("unable to process request");
    }
}

Expr* parse_str(std::string s){
    std::istringstream str(s);
    return parse_expr(str);
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
    CHECK_THROWS_WITH((parse_str("x"))->interp(), "No value for variable" );
    CHECK_THROWS_WITH((parse_str("&"))->interp(), "No value for variable" );
    CHECK_THROWS_WITH((parse_str(""))->interp(), "No value for variable" );
    CHECK_THROWS_WITH((parse_str("b+31"))->interp(), "No value for variable" );
    CHECK_THROWS_WITH((parse_str("3*t"))->interp(), "No value for variable" );
    CHECK_THROWS_WITH((parse_str("_let x = t _in x+1"))->interp(), "No value for variable");
    CHECK_THROWS_WITH((parse_str("_lot x = 3 _in x+1"))->interp(), "unable to parse keyword");
    CHECK_THROWS_WITH((parse_str("_let x + 3 _in x+1"))->interp(), "equal expected");
    CHECK_THROWS_WITH((parse_str("_let x = 3 _it x+1"))->interp(), "unable to parse keyword");
    CHECK_THROWS_WITH((parse_str("(x+4"))->interp(), "missing close parenthesis");
    CHECK_THROWS_WITH((parse_str("3+(4+1"))->interp(), "missing close parenthesis");
}
