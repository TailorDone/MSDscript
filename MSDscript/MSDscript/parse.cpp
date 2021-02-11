//
//  parse.cpp
//  MSDscript
//
//  Created by Taylor Dunn on 2/10/21.
//

#include "parse.hpp"

void Parser::consume (std::istream &in, int expect){
   int c = in.get();
   if(c!= expect){
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
       } else {
           //parse let
           throw std::runtime_error("something went wrong");
       }
}
