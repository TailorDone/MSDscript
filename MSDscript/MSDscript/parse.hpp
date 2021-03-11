//
//  parse.hpp
//  MSDscript
//
//  Created by Taylor Dunn on 2/10/21.
//

#ifndef parse_hpp
#define parse_hpp

#include <stdio.h>
#include "expr.hpp"

    Expr* parse_num(std::istream &in);
    Expr* parse_variable(std::istream &in);
    Expr* parse_multicand(std::istream &in); //parse inner
    Expr* parse_expr(std::istream &in);
    Expr* parse_addend(std::istream &in);
    Expr* parse_let(std::istream &in);
    Expr* parse_comparg(std::istream &in);
    Expr* parse_if(std::istream &in);
    Expr* parse_inner(std::istream &in);
Expr* parse_function(std::istream &in);
    void parse_keyword(std::istream &in, std::string keyword);
    Expr* parse_str(std::string s);
    void consume (std::istream &in, int expect);
    void skip_whitespace(std::istream &in);


#endif /* parse_hpp */
