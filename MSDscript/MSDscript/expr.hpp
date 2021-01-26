//
//  expr.hpp
//  MSDscript
//
//  Created by Taylor Dunn on 1/22/21.
//

#ifndef expr_hpp
#define expr_hpp

#include <stdio.h>
#include <string>

class Expr{
public:
    virtual bool equals(Expr *a) = 0;
};

class Num: public Expr {
public:
    int val;
    
    Num(int val);
    bool equals(Expr *other);
};

class Add: public Expr{
public:
    Expr *lhs;
    Expr *rhs;
    
    Add(Expr *lhs, Expr *rhs);
    bool equals(Expr *other);
};

class Mult: public Expr{
public:
    Expr *lhs;
    Expr *rhs;
    
    Mult(Expr *lhs, Expr *rhs);
    bool equals(Expr *other);
};

class Variable: public Expr{
public:
    std::string val;
    
    Variable(std::string val);
    bool equals(Expr *other);
};

#endif /* expr_hpp */
