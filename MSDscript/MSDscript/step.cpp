//
//  step.cpp
//  MSDscript
//
//  Created by Taylor Dunn on 4/2/21.
//

#include "step.hpp"
#include "catch.h"

PTR(Expr) Step::expr;
PTR(Env) Step::env;
PTR(Val) Step::val;
PTR(Cont) Step::cont;
Step::mode_t Step::mode;

PTR(Val) Step::interp_by_steps(PTR(Expr) e){
    Step::mode = Step::interp_mode;
    Step::expr = e;
    Step::env = Env::empty;
    Step::val = nullptr;
    Step::cont = Cont::done;
    
    while(1){
        if (Step::mode == Step::interp_mode)
            Step::expr->step_interp();
        else {
            if (Step::cont == Cont::done)
                return Step::val;
            else
                Step::cont->step_continue();
        }
    }
}

TEST_CASE("Num Expr"){
    CHECK(Step::interp_by_steps(NEW(NumExpr)(13))->equals(NEW(NumVal)(13)));
    CHECK(Step::interp_by_steps(NEW(NumExpr)(0))->equals(NEW(NumVal)(0)));
    CHECK(Step::interp_by_steps(NEW(NumExpr)(-31))->equals(NEW(NumVal)(-31)));
}

TEST_CASE("Add Expr"){
    CHECK(Step::interp_by_steps(NEW(AddExpr)(NEW(NumExpr)(5), NEW(NumExpr)(4)))->equals(NEW(NumVal)(9)));
    CHECK(Step::interp_by_steps(NEW(AddExpr)(NEW(NumExpr)(-4), NEW(NumExpr)(4)))->equals(NEW(NumVal)(0)));
}

TEST_CASE("Mult Expr"){
    CHECK(Step::interp_by_steps(NEW(MultExpr)(NEW(NumExpr)(5), NEW(NumExpr)(4)))->equals(NEW(NumVal)(20)));
    CHECK(Step::interp_by_steps(NEW(MultExpr)(NEW(NumExpr)(-4), NEW(NumExpr)(4)))->equals(NEW(NumVal)(-16)));
}

TEST_CASE("Let Expr"){
    CHECK(Step::interp_by_steps(NEW(LetExpr)("x", NEW(NumExpr)(5), NEW(AddExpr)(NEW(VarExpr)("x"), NEW(NumExpr)(1))))->equals(NEW(NumVal)(6)));
    CHECK(Step::interp_by_steps(NEW(LetExpr)("x", NEW(NumExpr)(5), NEW(MultExpr)(NEW(VarExpr)("x"), NEW(VarExpr)("x"))))->equals(NEW(NumVal)(25)));
}

TEST_CASE("Bool Expr"){
    CHECK(Step::interp_by_steps(NEW(BoolExpr)(true))->equals(NEW(BoolVal)(true)));
    CHECK(Step::interp_by_steps(NEW(BoolExpr)(false))->equals(NEW(BoolVal)(false)));
}

TEST_CASE("If Expr"){
    CHECK(Step::interp_by_steps(NEW(IfExpr)(NEW(BoolExpr)(false), NEW(NumExpr)(5), NEW(NumExpr)(3)))->equals(NEW(NumVal)(3)));
    CHECK(Step::interp_by_steps(NEW(IfExpr)(NEW(BoolExpr)(true), NEW(NumExpr)(5), NEW(NumExpr)(3)))->equals(NEW(NumVal)(5)));
}

TEST_CASE("Eq Expr"){
    CHECK(Step::interp_by_steps((NEW(EqExpr)(NEW(NumExpr)(2), NEW(NumExpr)(0))))->equals(NEW(BoolVal)(false)));
    CHECK(Step::interp_by_steps((NEW(EqExpr)(NEW(NumExpr)(0), NEW(NumExpr)(0))))->equals(NEW(BoolVal)(true)));
}

TEST_CASE("Fun Expr"){
    CHECK((Step::interp_by_steps(NEW(FunExpr)("x", NEW(NumExpr)(1))))->equals(NEW(FunVal)("x", NEW(NumExpr)(1), NEW(EmptyEnv)())));
    CHECK((Step::interp_by_steps(NEW(FunExpr)("x", NEW(AddExpr)(NEW(NumExpr)(5), NEW(NumExpr)(4)))))->equals(NEW(FunVal)("x", NEW(AddExpr)(NEW(NumExpr)(5), NEW(NumExpr)(4)), NEW(EmptyEnv)())));
}

TEST_CASE("Call Expr"){
    CHECK_THROWS((Step::interp_by_steps(NEW(CallExpr)(NEW(NumExpr)(7),(NEW(NumExpr)(3))))), "Call_step not allowed on NumVals");
}
