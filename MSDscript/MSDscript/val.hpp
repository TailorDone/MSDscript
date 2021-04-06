//
//  val.hpp
//  MSDscript
//
//  Created by Taylor Dunn on 2/23/21.
//

#ifndef val_hpp
#define val_hpp

#include <stdio.h>
#include <iostream>
#include "pointer.h"
#include "env.hpp"
#include "cont.hpp"
#include "expr.hpp"

class Expr;
class Cont;
class Env;

CLASS(Val){
public:
    //Destructor
    virtual ~Val() {};
    //virtual PTR(Expr) to_expr() = 0;
    virtual bool equals(PTR(Val) v) = 0;
    virtual PTR(Val) add_to(PTR(Val) rhs) = 0;
    virtual PTR(Val) mult_to(PTR(Val) rhs) = 0;
    virtual void print(std::ostream& outstream) = 0;
    virtual bool is_true() = 0;
    virtual PTR(Val) call(PTR(Val) actual_arg) = 0;
    virtual void call_step(PTR(Val) actual_arg, PTR(Cont) rest) = 0;
    std::string to_string();
};

class NumVal: public Val {
public:
    int val;
    
    NumVal(int val);
    //PTR(Expr) to_expr();
    bool equals(PTR(Val) v);
    PTR(Val) add_to(PTR(Val) rhs);
    PTR(Val) mult_to(PTR(Val) rhs);
    void print (std::ostream& outstream);
    bool is_true();
    PTR(Val) call(PTR(Val) actual_arg);
    void call_step(PTR(Val) actual_arg, PTR(Cont) rest);
};

class BoolVal: public Val {
public:
    bool val;
    
    BoolVal(bool val);
    //PTR(Expr) to_expr();
    bool equals(PTR(Val) v);
    PTR(Val) add_to(PTR(Val) rhs);
    PTR(Val) mult_to(PTR(Val) rhs);
    void print (std::ostream& outstream);
    bool is_true();
    PTR(Val) call(PTR(Val) actual_arg);
    void call_step(PTR(Val) actual_arg, PTR(Cont) rest);
};

class FunVal: public Val {
public:
    std::string formal_arg;
    PTR(Expr) body;
    PTR(Env) env;
    
    FunVal(std::string formal_arg, PTR(Expr)body, PTR(Env) env);
    //PTR(Expr) to_expr();
    bool equals(PTR(Val) v);
    PTR(Val) add_to(PTR(Val) rhs);
    PTR(Val) mult_to(PTR(Val) rhs);
    void print (std::ostream& outstream);
    bool is_true();
    PTR(Val) call(PTR(Val) actual_arg);
    void call_step(PTR(Val) actual_arg, PTR(Cont) rest);
};


#endif /* val_hpp */
