//
//  val.cpp
//  MSDscript
//
//  Created by Taylor Dunn on 2/23/21.
//

#include "val.hpp"
#include "expr.hpp"


NumVal::NumVal(int val){
    this->val = val;
}

bool NumVal::equals(Val *other){
    NumVal *other_num = dynamic_cast<NumVal*>(other);
    if (other_num == NULL){
        return false;
    } else {
        return this->val == other_num->val;
    }
}

Expr* NumVal::to_expr(){
    return new NumExpr(this->val);
}

Val *NumVal::add_to(Val *other){
    NumVal *other_num = dynamic_cast<NumVal*>(other);
    if (other_num == NULL) throw std::runtime_error("add of non-number");
    return new NumVal(this->val + other_num->val);
}

Val *NumVal::mult_to(Val *other){
    NumVal *other_num = dynamic_cast<NumVal*>(other);
    if (other_num == NULL) throw std::runtime_error("multiplication of non-number");
    return new NumVal(this->val * other_num->val);
}

void NumVal::print(std::ostream& outstream){
    outstream << this->val;
}

bool NumVal::is_true(){
    throw std::runtime_error("Test expression is not a boolean");
}

/* *********************************************** */
BoolVal::BoolVal(bool val){
    this->val = val;
}

Expr* BoolVal::to_expr(){
    return new BoolExpr(this->val);
}

bool BoolVal::equals(Val* other){
    BoolVal *other_val = dynamic_cast<BoolVal*>(other);
    if (other == NULL){
        return false;
    } else {
        return (this->val == other_val->val);
    }
}

Val* BoolVal::add_to(Val* rhs){
    throw std::runtime_error("addition of non-number");
}

Val* BoolVal::mult_to(Val* rhs){
    throw std::runtime_error("multiplication of non-number");
}

void BoolVal::print (std::ostream& outstream){
    if (this->val == true){
        outstream << "_true";
    } else {
        outstream << "_false";
    }
}

bool BoolVal::is_true(){
    return this->val;
}
