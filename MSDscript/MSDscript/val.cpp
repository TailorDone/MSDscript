//
//  val.cpp
//  MSDscript
//
//  Created by Taylor Dunn on 2/23/21.
//

#include "val.hpp"
#include "expr.hpp"
#include "env.hpp"


NumVal::NumVal(int val){
    this->val = val;
}

bool NumVal::equals(PTR(Val) other){
    PTR(NumVal)other_num = CAST(NumVal)(other);
    if (other_num == NULL){
        return false;
    } else {
        return this->val == other_num->val;
    }
}

//PTR(Expr) NumVal::to_expr(){
//    return NEW(NumExpr)(this->val);
//}

PTR(Val)NumVal::add_to(PTR(Val)other){
    PTR(NumVal)other_num = CAST(NumVal)(other);
    if (other_num == NULL) throw std::runtime_error("addition of non-number");
    return NEW(NumVal)(this->val + other_num->val);
}

PTR(Val)NumVal::mult_to(PTR(Val)other){
    PTR(NumVal)other_num = CAST(NumVal)(other);
    if (other_num == NULL) throw std::runtime_error("multiplication of non-number");
    return NEW(NumVal)(this->val * other_num->val);
}

void NumVal::print(std::ostream& outstream){
    outstream << this->val;
}

bool NumVal::is_true(){
    throw std::runtime_error("Test expression is not a boolean");
}

PTR(Val) NumVal::call(PTR(Val) actual_arg){
    throw std::runtime_error("Calling not allowed on NumVals");
}

/* *********************************************** */
BoolVal::BoolVal(bool val){
    this->val = val;
}
//
//PTR(Expr) BoolVal::to_expr(){
//    return NEW(BoolExpr)(this->val);
//}

bool BoolVal::equals(PTR(Val) other){
    PTR(BoolVal)other_val = CAST(BoolVal)(other);
    if (other_val == NULL){
        return false;
    } else {
        return (this->val == other_val->val);
    }
}

PTR(Val) BoolVal::add_to(PTR(Val) rhs){
    throw std::runtime_error("addition of non-number");
}

PTR(Val) BoolVal::mult_to(PTR(Val) rhs){
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

PTR(Val) BoolVal::call(PTR(Val) actual_arg){
    throw std::runtime_error("Calling not allowed on BoolVals");
}

/* *********************************************** */
FunVal::FunVal(std::string formal_arg, PTR(Expr) body, PTR(Env) env){
    this->formal_arg = formal_arg;
    this->body = body;
    this->env = env;
}

//PTR(Expr) FunVal::to_expr(){
//    return NEW(FunExpr)(this->formal_arg, this->body);
//}

bool FunVal::equals(PTR(Val) v){
    PTR(FunVal)other_val = CAST(FunVal)(v);
    if (other_val == NULL){
        return false;
    } else {
        return (this->formal_arg == other_val->formal_arg) && (this->body)->equals(other_val->body);
    }
}

PTR(Val) FunVal::add_to(PTR(Val) rhs){
    throw std::runtime_error("addition of non-number");
}

PTR(Val) FunVal::mult_to(PTR(Val) rhs){
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

PTR(Val) FunVal::call(PTR(Val) actual_arg){
    return body->interp(NEW(ExtendedEnv) (formal_arg, actual_arg, env));
}

/* *********************************************** */

std::string Val::to_string(){
    std::ostream stream(nullptr);
    std::stringbuf str;
    stream.rdbuf(&str);
    print(stream);
    return str.str();
}



