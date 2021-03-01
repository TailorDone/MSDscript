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

class Expr{
    
public:
    //Returns whether the calling expression is equal to the parameter expression.
    virtual bool equals(Expr *a) = 0;
    //Returns the value of an expression. If the expression is a variable, throws a runtime error.
    virtual Val* interp() = 0;
    //Returns whether the expression contains a variable.
    virtual bool has_variable() = 0;
    //Returns everywhere that the calling expression contained the parameter string and replaces it with the parameter expression.
    virtual Expr* subst(std::string name, Expr *replacement) = 0;
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
    bool equals(Expr *other);
    Val* interp();
    bool has_variable();
    Expr* subst(std::string name, Expr *replacement);
    void print(std::ostream& output);
    void pretty_print(std::ostream& output);
    void pretty_print_at(std::ostream& output, print_mode_t type, long *position);
};

class AddExpr: public Expr{
public:
    Expr *lhs;
    Expr *rhs;
    
    AddExpr(Expr *lhs, Expr *rhs);
    bool equals(Expr *other);
    Val* interp();
    bool has_variable();
    Expr* subst(std::string name, Expr *replacement);
    void print(std::ostream& output);
    void pretty_print(std::ostream& output);
    void pretty_print_at(std::ostream& output, print_mode_t type, long *position);
};

class MultExpr: public Expr{
public:
    Expr *lhs;
    Expr *rhs;
    
    MultExpr(Expr *lhs, Expr *rhs);
    bool equals(Expr *other);
    Val* interp();
    bool has_variable();
    Expr* subst(std::string name, Expr *replacement);
    void print(std::ostream& output);
    void pretty_print(std::ostream& output);
    void pretty_print_at(std::ostream& output, print_mode_t type, long *position);
};

class VarExpr: public Expr{
public:
    std::string name;
    
    VarExpr(std::string name);
    bool equals(Expr *other);
    Val* interp();
    bool has_variable();
    Expr* subst(std::string name, Expr *replacement);
    void print(std::ostream& output);
    void pretty_print(std::ostream& output);
    void pretty_print_at(std::ostream& output, print_mode_t type, long *position);
};

class LetExpr: public Expr{
public:
    std::string lhs;
    Expr *rhs;
    Expr *body;
    
    LetExpr(std::string lhs, Expr *rhs, Expr *body);
    bool equals (Expr *other);
    Val* interp();
    bool has_variable();
    Expr* subst(std::string name, Expr *replacement);
    void print(std::ostream& output);
    void pretty_print(std::ostream& output);
    void pretty_print_at(std::ostream& output, print_mode_t type, long *position);
};

class BoolExpr: public Expr{
public:
    bool val;
    
    BoolExpr(bool val);
    bool equals(Expr *other);
    Val* interp();
    bool has_variable();
    Expr* subst(std::string name, Expr *replacement);
    void print(std::ostream& output);
    void pretty_print(std::ostream& output);
    void pretty_print_at(std::ostream& output, print_mode_t type, long *position);
};

class IfExpr : public Expr{
public:
    Expr *test_part;
    Expr *then_part;
    Expr *else_part;
    
    IfExpr(Expr *test_part, Expr *then_part, Expr *else_part);
    bool equals(Expr *other);
    Val* interp();
    bool has_variable();
    Expr* subst(std::string name, Expr *replacement);
    void print(std::ostream& output);
    void pretty_print(std::ostream& output);
    void pretty_print_at(std::ostream& output, print_mode_t type, long *position);
};

class EqExpr : public Expr{
public:
    Expr *lhs;
    Expr *rhs;
    
    EqExpr(Expr *lhs, Expr *rhs);
    bool equals(Expr *other);
    Val* interp();
    bool has_variable();
    Expr* subst(std::string name, Expr *replacement);
    void print(std::ostream& output);
    void pretty_print(std::ostream& output);
    void pretty_print_at(std::ostream& output, print_mode_t type, long *position);
};

#endif /* expr_hpp */
