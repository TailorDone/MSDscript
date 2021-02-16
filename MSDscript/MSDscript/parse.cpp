//
//  parse.cpp
//  MSDscript
//
//  Created by Taylor Dunn on 2/10/21.
//

#include "parse.hpp"
#include "catch.h"
#include <stdexcept>

void Parser::consume (std::istream &in, int expect){
   int c = in.get();
   if(c!= expect){
       char c_as_char = (char)c;
       char expect_as_char = (char) expect;
       std::cout << "your c value was " << c_as_char << " but we expected: " << expect_as_char;
       throw std::runtime_error("consume mismatch");
   }
}

void Parser::skip_whitespace(std::istream &in){
   while(1){
       int c = in.peek();
       if(!isspace(c)){
           break;
       }
       consume(in, c);
   }
}

Expr* Parser::parse_num(std::istream &in){
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
   return new Num(n);
}

Expr* Parser::parse_variable(std::istream &in){
   skip_whitespace(in);
   int c = in.peek();
   consume (in, c);
   std::string character;
   character = (char) c;
   return new Variable(character);
}

void Parser::parse_keyword(std::istream &in, std::string keyword){
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

Expr* Parser::parse_let(std::istream &in){
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
    return new Let(lhs, rhs, body);
}

Expr* Parser::parse_expr(std::istream &in){
   Expr *e;
   e = parse_addend(in);
   skip_whitespace(in);
   int c = in.peek();
   if (c=='+'){
       consume(in, '+');
       Expr *rhs = parse_expr(in);
       return new Add(e,rhs);
   } else {
       return e;
   }
}

Expr* Parser::parse_addend(std::istream &in){
   Expr *e;
   e = parse_multicand(in);
   skip_whitespace(in);
   int c = in.peek();
   if(c=='*'){
       consume(in, '*');
       Expr *rhs = parse_addend(in);
       return new Mult(e, rhs);
   } else {
       return e;
   }
}

Expr* Parser::parse_multicand(std::istream &in){
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

Expr* Parser::parse_str(std::string s){
    std::istringstream str(s);
    return parse_expr(str);
}

TEST_CASE ("Parse"){
    CHECK((Parser::parse_str("1")->interp()==1));
    CHECK((Parser::parse_str("0")->interp()==0));
    CHECK((Parser::parse_str("-1")->interp()==-1));
    CHECK((Parser::parse_str("2+4")->interp()==6));
    CHECK((Parser::parse_str("2*4")->interp()==8));
    CHECK((Parser::parse_str("_let x = 2 _in x + 5"))->interp()==7);
    CHECK((Parser::parse_str("_let x = 5 _in _let y = 3 _in x + 5"))->interp()==10);
    CHECK((Parser::parse_str("2+4"))->interp() == 6);
    CHECK((Parser::parse_str("-10+7"))->interp() == -3);
    CHECK((Parser::parse_str("31+-31"))->interp() == 0);
    CHECK((Parser::parse_str("2*5"))->interp() == 10);
    CHECK((Parser::parse_str("2*-5"))->interp() == -10);
    CHECK((Parser::parse_str("_let x = 5 _in x + 1"))->interp() == 6);
    CHECK((Parser::parse_str("_let x = 5 + 2 _in x + 1"))->interp() == 8);
    CHECK_THROWS_WITH((Parser::parse_str("x"))->interp(), "No value for variable" );
    CHECK_THROWS_WITH((Parser::parse_str("&"))->interp(), "No value for variable" );
    CHECK_THROWS_WITH((Parser::parse_str(""))->interp(), "No value for variable" );
    CHECK_THROWS_WITH((Parser::parse_str("b+31"))->interp(), "No value for variable" );
    CHECK_THROWS_WITH((Parser::parse_str("3*t"))->interp(), "No value for variable" );
    CHECK_THROWS_WITH((Parser::parse_str("_let x = t _in x+1"))->interp(), "No value for variable");
    CHECK_THROWS_WITH((Parser::parse_str("_lot x = 3 _in x+1"))->interp(), "unable to parse keyword");
    CHECK_THROWS_WITH((Parser::parse_str("_let x + 3 _in x+1"))->interp(), "equal expected");
    CHECK_THROWS_WITH((Parser::parse_str("_let x = 3 _it x+1"))->interp(), "unable to parse keyword");
    CHECK_THROWS_WITH((Parser::parse_str("(x+4"))->interp(), "missing close parenthesis");
    //CHECK_THROWS_WITH((Parser::parse_str("4+1)"))->interp(), "missing close parenthesis"); Fix This
    CHECK_THROWS_WITH((Parser::parse_str("3+(4+1"))->interp(), "missing close parenthesis");
}
