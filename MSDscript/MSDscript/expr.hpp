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
    //Returns whether the calling expression is equal to the parameter expression.
    virtual bool equals(Expr *a) = 0;
    //Returns the value of an expression. If the expression is a variable, throws a runtime error.
    virtual int interp() = 0;
    //Returns whether the expression contains a variable.
    virtual bool has_variable() = 0;
    //Returns everywhere that the calling expression contained the parameter string and replaces it with the parameter expression.
    virtual Expr* subst(std::string string, Expr *a) = 0;
};

class Num: public Expr {
public:
    int val;
    
    Num(int val);
    bool equals(Expr *other);
    int interp();
    bool has_variable();
    Expr* subst(std::string string, Expr *a);
};

class Add: public Expr{
public:
    Expr *lhs;
    Expr *rhs;
    
    Add(Expr *lhs, Expr *rhs);
    bool equals(Expr *other);
    int interp();
    bool has_variable();
    Expr* subst(std::string string, Expr *a);
};

class Mult: public Expr{
public:
    Expr *lhs;
    Expr *rhs;
    
    Mult(Expr *lhs, Expr *rhs);
    bool equals(Expr *other);
    int interp();
    bool has_variable();
    Expr* subst(std::string string, Expr *a);
};

class Variable: public Expr{
public:
    std::string val;
    
    Variable(std::string val);
    bool equals(Expr *other);
    int interp();
    bool has_variable();
    Expr* subst(std::string string, Expr *a);
};

#endif /* expr_hpp */
