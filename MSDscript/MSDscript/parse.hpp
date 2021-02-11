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

class Parser{
    
public:
    static Expr* parse_num(std::istream &in);
    static Expr* parse_variable(std::istream &in);
    static Expr* parse_multicand(std::istream &in);
    static Expr* parse_expr(std::istream &in);
    static Expr* parse_addend(std::istream &in);
    static void consume (std::istream &in, int expect);
    static void skip_whitespace(std::istream &in);
    static Expr* parse_let(std::istream &in);
    static void parse_keyword(std::istream &in, std::string keyword);
};

#endif /* parse_hpp */
