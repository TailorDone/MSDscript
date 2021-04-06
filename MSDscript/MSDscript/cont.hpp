//
//  cont.hpp
//  MSDscript
//
//  Created by Taylor Dunn on 4/2/21.
//

#ifndef cont_hpp
#define cont_hpp

#include <stdio.h>
#include "pointer.h"
#include "expr.hpp"
#include "env.hpp"
#include "step.hpp"

CLASS (Cont){
public:
    virtual void step_continue() = 0;
    static PTR(Cont) done;
};

class Done : public Cont{
public:
    Done();
    void step_continue();
};

class RightThenAddCont : public Cont{
public:
    PTR(Expr) rhs;
    PTR(Env) env;
    PTR(Cont) rest;
    
    void step_continue();
    RightThenAddCont(PTR(Expr) rhs, PTR(Env) env, PTR(Cont) rest);
};

class AddCont : public Cont{
public:
    PTR(Val) lhs_val;
    PTR(Cont) rest;
    
    void step_continue();
    AddCont(PTR(Val) lhs_val, PTR(Cont) rest);
};

class RightThenMultCont: public Cont{
public:
    PTR(Expr) rhs;
    PTR(Env) env;
    PTR(Cont) rest;
    
    void step_continue();
    RightThenMultCont(PTR(Expr) rhs, PTR(Env) env, PTR(Cont) rest);
};

class MultCont: public Cont{
public:
    PTR(Val) lhs_val;
    PTR(Cont) rest;
    
    void step_continue();
    MultCont(PTR(Val) lhs_val, PTR(Cont) rest);
};

#endif /* cont_hpp */
