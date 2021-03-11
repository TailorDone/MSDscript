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
    if (other_num == NULL) throw std::runtime_error("addition of non-number");
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

Val* NumVal::call(Val* actual_arg){
    throw std::runtime_error("Calling not allowed on NumVals");
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
    if (other_val == NULL){
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

Val* BoolVal::call(Val* actual_arg){
    throw std::runtime_error("Calling not allowed on BoolVals");
}

/* *********************************************** */
FunVal::FunVal(std::string formal_arg, Expr *body){
    this->formal_arg = formal_arg;
    this->body = body;
}

Expr* FunVal::to_expr(){
    return new FunExpr(this->formal_arg, this->body);
}

bool FunVal::equals(Val* v){
    FunVal *other_val = dynamic_cast<FunVal*>(v);
    if (other_val == NULL){
        return false;
    } else {
        return (this->formal_arg == other_val->formal_arg) && (this->body)->equals(other_val->body);
    }
}

Val* FunVal::add_to(Val* rhs){
    throw std::runtime_error("addition of non-number");
}

Val* FunVal::mult_to(Val* rhs){
    throw std::runtime_error("multiplication of non-number");
}

void FunVal::print (std::ostream& outstream){
    outstream << "(_fun (" << formal_arg << ") ";
    this->body->print(outstream);
    outstream << ")";
}

bool FunVal::is_true(){
    throw std::runtime_error("Test expression is not a boolean");
}

Val* FunVal::call(Val* actual_arg){
    return (body->subst(formal_arg, actual_arg->to_expr()))->interp();
}

/* *********************************************** */

std::string Val::to_string(){
    std::ostream stream(nullptr);
    std::stringbuf str;
    stream.rdbuf(&str);
    print(stream);
    return str.str();
}



