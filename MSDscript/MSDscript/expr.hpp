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
    print_group_add_mult_or_let
} print_mode_t;

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

class Num: public Expr {
public:
    int val;
    
    Num(int val);
    bool equals(Expr *other);
    int interp();
    bool has_variable();
    Expr* subst(std::string string, Expr *a);
    void print(std::ostream& output);
    void pretty_print(std::ostream& output);
    void pretty_print_at(std::ostream& output, print_mode_t type, long *position);
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
    void print(std::ostream& output);
    void pretty_print(std::ostream& output);
    void pretty_print_at(std::ostream& output, print_mode_t type, long *position);
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
    void print(std::ostream& output);
    void pretty_print(std::ostream& output);
    void pretty_print_at(std::ostream& output, print_mode_t type, long *position);
};

class Variable: public Expr{
public:
    std::string name;
    
    Variable(std::string name);
    bool equals(Expr *other);
    int interp();
    bool has_variable();
    Expr* subst(std::string string, Expr *replacement);
    void print(std::ostream& output);
    void pretty_print(std::ostream& output);
    void pretty_print_at(std::ostream& output, print_mode_t type, long *position);
};

class Let: public Expr{
public:
    std::string lhs;
    Expr *rhs;
    Expr *body;
    
    Let(std::string lhs, Expr *rhs, Expr *body);
    bool equals (Expr *other);
    int interp();
    bool has_variable();
    Expr* subst(std::string string, Expr *replacement);
    void print(std::ostream& output);
    void pretty_print(std::ostream& output);
    void pretty_print_at(std::ostream& output, print_mode_t type, long *position);
};

#endif /* expr_hpp */
