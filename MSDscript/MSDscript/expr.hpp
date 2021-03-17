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
#include <iostream>
#include <sstream>
#include "pointer.h"

typedef enum {
    print_group_none,
    print_group_add,
    print_group_add_or_mult,
    print_group_add_or_let,
    print_group_add_mult_or_let,
    print_group_eq,
    print_group_add_or_eq
} print_mode_t;

class Val;

CLASS(Expr) {
    
public:
    //Destructor
    virtual ~Expr() {};
    //Returns whether the calling expression is equal to the parameter expression.
    virtual bool equals(PTR(Expr)a) = 0;
    //Returns the value of an expression. If the expression is a variable, throws a runtime error.
    virtual PTR(Val) interp() = 0;
    //Returns everywhere that the calling expression contained the parameter string and replaces it with the parameter expression.
    virtual PTR(Expr) subst(std::string name, PTR(Expr)replacement) = 0;
    //Prints an expression to an output stream
    virtual void print(std::ostream& output) = 0;
    //Prints an expression in a more visually pleasing way
    virtual void pretty_print(std::ostream& output) = 0;
    //Prints an expression based on the given mode and output stream position
    virtual void pretty_print_at(std::ostream& output, print_mode_t type, long *position) = 0;
    //Writes an expression as a string
    std::string to_string();
    //Writes an expression as a prettier string
    std::string to_string_pretty();    
};

class NumExpr: public Expr {
public:
    int val;
    
    NumExpr(int val);
    bool equals(PTR(Expr)other);
    PTR(Val) interp();
    PTR(Expr) subst(std::string name, PTR(Expr)replacement);
    void print(std::ostream& output);
    void pretty_print(std::ostream& output);
    void pretty_print_at(std::ostream& output, print_mode_t type, long *position);
};

class AddExpr: public Expr{
public:
    PTR(Expr)lhs;
    PTR(Expr)rhs;
    
    AddExpr(PTR(Expr)lhs, PTR(Expr)rhs);
    bool equals(PTR(Expr)other);
    PTR(Val) interp();
    PTR(Expr) subst(std::string name, PTR(Expr)replacement);
    void print(std::ostream& output);
    void pretty_print(std::ostream& output);
    void pretty_print_at(std::ostream& output, print_mode_t type, long *position);
};

class MultExpr: public Expr{
public:
    PTR(Expr)lhs;
    PTR(Expr)rhs;
    
    MultExpr(PTR(Expr)lhs, PTR(Expr)rhs);
    bool equals(PTR(Expr)other);
    PTR(Val) interp();
    PTR(Expr) subst(std::string name, PTR(Expr)replacement);
    void print(std::ostream& output);
    void pretty_print(std::ostream& output);
    void pretty_print_at(std::ostream& output, print_mode_t type, long *position);
};

class VarExpr: public Expr{
public:
    std::string name;
    
    VarExpr(std::string name);
    bool equals(PTR(Expr)other);
    PTR(Val) interp();
    PTR(Expr) subst(std::string name, PTR(Expr)replacement);
    void print(std::ostream& output);
    void pretty_print(std::ostream& output);
    void pretty_print_at(std::ostream& output, print_mode_t type, long *position);
};

class LetExpr: public Expr{
public:
    std::string lhs;
    PTR(Expr)rhs;
    PTR(Expr)body;
    
    LetExpr(std::string lhs, PTR(Expr)rhs, PTR(Expr)body);
    bool equals (PTR(Expr)other);
    PTR(Val) interp();
    PTR(Expr) subst(std::string name, PTR(Expr)replacement);
    void print(std::ostream& output);
    void pretty_print(std::ostream& output);
    void pretty_print_at(std::ostream& output, print_mode_t type, long *position);
};

class BoolExpr: public Expr{
public:
    bool val;
    
    BoolExpr(bool val);
    bool equals(PTR(Expr)other);
    PTR(Val) interp();
    PTR(Expr) subst(std::string name, PTR(Expr)replacement);
    void print(std::ostream& output);
    void pretty_print(std::ostream& output);
    void pretty_print_at(std::ostream& output, print_mode_t type, long *position);
};

class IfExpr : public Expr{
public:
    PTR(Expr)test_part;
    PTR(Expr)then_part;
    PTR(Expr)else_part;
    
    IfExpr(PTR(Expr)test_part, PTR(Expr)then_part, PTR(Expr)else_part);
    bool equals(PTR(Expr)other);
    PTR(Val) interp();
    PTR(Expr) subst(std::string name, PTR(Expr)replacement);
    void print(std::ostream& output);
    void pretty_print(std::ostream& output);
    void pretty_print_at(std::ostream& output, print_mode_t type, long *position);
};

class EqExpr : public Expr{
public:
    PTR(Expr)lhs;
    PTR(Expr)rhs;
    
    EqExpr(PTR(Expr)lhs, PTR(Expr)rhs);
    bool equals(PTR(Expr)other);
    PTR(Val) interp();
    PTR(Expr) subst(std::string name, PTR(Expr)replacement);
    void print(std::ostream& output);
    void pretty_print(std::ostream& output);
    void pretty_print_at(std::ostream& output, print_mode_t type, long *position);
};

class FunExpr : public Expr{
public:
    std::string formal_arg;
    PTR(Expr)body;
    
    FunExpr(std::string formal_arg, PTR(Expr)body);
    bool equals(PTR(Expr)other);
    PTR(Val) interp();
    PTR(Expr) subst(std::string name, PTR(Expr)replacement);
    void print(std::ostream& output);
    void pretty_print(std::ostream& output);
    void pretty_print_at(std::ostream& output, print_mode_t type, long *position);
};

class CallExpr : public Expr{
public:
    PTR(Expr)to_be_called;
    PTR(Expr)actual_arg;
    
    CallExpr(PTR(Expr)to_be_called, PTR(Expr)actual_arg);
    bool equals(PTR(Expr)other);
    PTR(Val) interp();
    PTR(Expr) subst(std::string name, PTR(Expr)replacement);
    void print(std::ostream& output);
    void pretty_print(std::ostream& output);
    void pretty_print_at(std::ostream& output, print_mode_t type, long *position);
};

#endif /* expr_hpp */
