//
//  step.hpp
//  MSDscript
//
//  Created by Taylor Dunn on 4/2/21.
//

#ifndef step_hpp
#define step_hpp

#include <stdio.h>
#include "expr.hpp"
#include "env.hpp"
#include "val.hpp"
#include "cont.hpp"

class Expr;
class Env;
class Val;
class Cont;

CLASS (Step){
public:
    typedef enum{
        interp_mode,
        continue_mode
    } mode_t;

static mode_t mode;
static PTR(Expr) expr;
static PTR(Env) env;
static PTR(Val) val;
static PTR(Cont) cont;
    
static PTR(Val) interp_by_steps(PTR(Expr) e);
};




#endif /* step_hpp */
