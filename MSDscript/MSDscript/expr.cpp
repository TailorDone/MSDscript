
//
//  expr.cpp
//  MSDscript
//
//  Created by Taylor Dunn on 1/22/21.
//

#include "expr.hpp"
#include "catch.h"
#include "val.hpp"
#include <stdexcept>

/* *********************************************** */

NumExpr::NumExpr(int val){
    this->val = val;
}

bool NumExpr::equals(PTR(Expr)other){
    PTR(NumExpr)other_num = CAST(NumExpr)(other);
    if (other_num == NULL){
        return false;
    } else {
        return (this->val == other_num->val);
    }
}

PTR(Val) NumExpr::interp(PTR(Env) env){
    return NEW(NumVal)(this->val);
}

//PTR(Expr) NumExpr::subst(std::string name, PTR(Expr)replacement){
//    return THIS;
//}

void NumExpr::print(std::ostream& output){
    output << this->val;
}

void NumExpr::pretty_print(std::ostream& output){
    pretty_print_at(output, print_group_none, 0);
}

void NumExpr::pretty_print_at(std::ostream& output, print_mode_t type, long *position){
    output << this->val;
}
/* *********************************************** */

AddExpr::AddExpr(PTR(Expr)lhs, PTR(Expr)rhs){
    this->lhs = lhs;
    this->rhs = rhs;
}

bool AddExpr::equals(PTR(Expr)other){
    PTR(AddExpr)other_num = CAST(AddExpr)(other);
    if (other_num == NULL){
        return false;
    } else {
        return ((this->lhs)->equals(other_num->lhs)) && ((this->rhs)->equals(other_num->rhs));
    }
}

PTR(Val) AddExpr::interp(PTR(Env) env){
    return (this->lhs->interp(env)->add_to(this->rhs->interp(env)));
}

//PTR(Expr) AddExpr::subst(std::string name, PTR(Expr)replacement){
//    PTR(Expr)new_lhs = lhs->subst(name, replacement);
//    PTR(Expr)new_rhs = rhs->subst(name, replacement);
//    return NEW(AddExpr)(new_lhs, new_rhs);
//}

void AddExpr::print(std::ostream& output){
    PTR(Expr)new_lhs = this->lhs;
    PTR(Expr)new_rhs = this->rhs;
    output << "(";
    new_lhs->print(output);
    output << "+";
    new_rhs->print(output);
    output<< ")";
}

void AddExpr::pretty_print(std::ostream& output){
    PTR(Expr)new_lhs = this->lhs;
    PTR(Expr)new_rhs = this->rhs;
    long position = 0;
    long *position_ptr = &position;
    new_lhs->pretty_print_at(output, print_group_add_or_let, position_ptr);
    output << " + ";
    new_rhs->pretty_print_at(output, print_group_add_or_eq, position_ptr);
}

void AddExpr::pretty_print_at(std::ostream& output, print_mode_t type, long *position){
    PTR(Expr)new_lhs = this->lhs;
    PTR(Expr)new_rhs = this->rhs;
    if (type == print_group_add || type == print_group_add_or_let || type == print_group_add_mult_or_let){
        output << "(";
    }
    new_lhs->pretty_print_at(output, print_group_add_or_let, position);
    output << " + ";
    new_rhs->pretty_print_at(output, print_group_add_or_eq, position);
    if (type == print_group_add || type == print_group_add_or_let || type == print_group_add_mult_or_let){
        output << ")";
    }
}
/* *********************************************** */

MultExpr::MultExpr(PTR(Expr)lhs, PTR(Expr)rhs){
    this->lhs = lhs;
    this->rhs = rhs;
}

bool MultExpr::equals(PTR(Expr)other){
    PTR(MultExpr)other_num = CAST(MultExpr)(other);
    if (other_num == NULL){
        return false;
    } else {
        return ((this->lhs)->equals(other_num->lhs)) && ((this->rhs)->equals(other_num->rhs));
    }
}

PTR(Val) MultExpr::interp(PTR(Env) env){
    return (this->lhs->interp(env)->mult_to(this->rhs->interp(env)));
}

//PTR(Expr) MultExpr::subst(std::string name, PTR(Expr)replacement){
//    PTR(Expr)new_lhs = lhs->subst(name, replacement);
//    PTR(Expr)new_rhs = rhs->subst(name, replacement);
//    return NEW(MultExpr)(new_lhs, new_rhs);
//}

void MultExpr::print(std::ostream& output){
    PTR(Expr)new_lhs = this->lhs;
    PTR(Expr)new_rhs = this->rhs;
    output << "(";
    new_lhs->print(output);
    output << "*";
    new_rhs->print(output);
    output<< ")";
}

void MultExpr::pretty_print(std::ostream& output){
    PTR(Expr)new_lhs = this->lhs;
    PTR(Expr)new_rhs = this->rhs;
    long position = 0;
    long *position_ptr = &position;
    new_lhs->pretty_print_at(output, print_group_add_mult_or_let, position_ptr);
    output << " * ";
    new_rhs->pretty_print_at(output, print_group_add, position_ptr);
}

void MultExpr::pretty_print_at(std::ostream& output, print_mode_t type, long *position){
    PTR(Expr)new_lhs = this->lhs;
    PTR(Expr)new_rhs = this->rhs;
    if (type == print_group_add_or_let){
        new_lhs->pretty_print_at(output, print_group_add_mult_or_let, position);
        output << " * ";
        new_rhs->pretty_print_at(output, print_group_add_or_let, position);
    } else {
        if (type == print_group_add_mult_or_let){
            output << "(";
        }
        new_lhs->pretty_print_at(output, print_group_add_mult_or_let, position);
        output << " * ";
        new_rhs->pretty_print_at(output, print_group_add, position);
        if (type == print_group_add_mult_or_let){
            output << ")";
        }
    }
}
/* *********************************************** */

VarExpr::VarExpr(std::string name){
    this->name = name;
}

bool VarExpr::equals(PTR(Expr)other){
    PTR(VarExpr)other_var = CAST(VarExpr)(other);
    if (other_var == NULL){
        return false;
    } else {
        return (this->name == other_var->name);
    }
}

PTR(Val) VarExpr::interp(PTR(Env) env){
    return env->lookup(name);
}

//PTR(Expr) VarExpr::subst(std::string name, PTR(Expr)replacement){
//    if(this->name == name){
//        return replacement;
//    } else {
//        return THIS;
//    }
//}

void VarExpr::print(std::ostream& output){
    output << this->name;
}

void VarExpr::pretty_print(std::ostream& output){
    pretty_print_at(output, print_group_none, 0);
}

void VarExpr::pretty_print_at(std::ostream& output, print_mode_t type, long *position){
    output << this->name;
}
/* *********************************************** */

LetExpr::LetExpr(std::string lhs, PTR(Expr)rhs, PTR(Expr)body){
    this->lhs = lhs;
    this->rhs = rhs;
    this->body = body;
}
    
bool LetExpr::equals(PTR(Expr)other){
    PTR(LetExpr)other_expr = CAST(LetExpr)(other);
    if (other_expr == NULL){
        return false;
    } else {
        return (((this->lhs == other_expr->lhs)) && ((this->rhs)->equals(other_expr->rhs)) && ((this->body)->equals(other_expr->body)));
    }
}
    
PTR(Val) LetExpr::interp(PTR(Env) env){
    PTR(Val) rhs_val = rhs->interp(env);
    PTR(Env) new_env = NEW(ExtendedEnv)(lhs, rhs_val, env);
    return body->interp(new_env);
}

//Always substitute RHS. Body changes iff the variable we are replacing and the bound variable are different
//PTR(Expr) LetExpr::subst(std::string string, PTR(Expr)replacement){
//    std::string new_lhs = this->lhs;
//    //Always substitute on the right, even if it doesn't replace anything
//    PTR(Expr)new_rhs = this->rhs->subst(string, replacement);
//    PTR(Expr)new_body = this->body;
//    if(new_lhs!=(string)){
//        new_body = new_body->subst(string, replacement);
//    }
//    return NEW(LetExpr) (new_lhs, new_rhs, new_body);
//}

void LetExpr::print(std::ostream& output){
    PTR(Expr)new_rhs = this->rhs;
    PTR(Expr)new_body = this->body;
    output << "(_let ";
    output << this->lhs;
    output << "=";
    new_rhs->print(output);
    output << " _in ";
    new_body->print(output);
    output<< ")";
}
void LetExpr::pretty_print(std::ostream& output){
    std::string new_lhs = this->lhs;
    PTR(Expr)new_rhs = this->rhs;
    PTR(Expr)new_body = this->body;
    output << "_let " << new_lhs << " = ";
    long position = 0;
    long *position_ptr = &position;
    new_rhs->pretty_print_at(output, print_group_none, position_ptr);
    output << "\n";
    *position_ptr = output.tellp();
    output << "_in  ";
    new_body->pretty_print_at(output, print_group_none, position_ptr);
}

void LetExpr::pretty_print_at(std::ostream& output, print_mode_t type, long *position){
    std::string new_lhs = this->lhs;
    PTR(Expr)new_rhs = this->rhs;
    PTR(Expr)new_body = this->body;
    if (type == print_group_add_or_let || type == print_group_add_mult_or_let || type == print_group_eq){
        output << "(";
    }
    long curr_let_pos = output.tellp();
    long spaces = curr_let_pos - *position;
    output << "_let " << new_lhs << " = ";
    new_rhs->pretty_print_at(output, print_group_none, position);
    output << "\n";
    *position = output.tellp();
    int space_count = 0;
    while (space_count < spaces){
        output << " ";
        space_count++;
    }
    output << "_in  ";
    new_body->pretty_print_at(output, print_group_none, position);
    if (type == print_group_add_or_let || type == print_group_add_mult_or_let || type == print_group_eq){
        output << ")";
    }
}
/* *********************************************** */

std::string Expr::to_string(){
    std::ostream stream(nullptr);
    std::stringbuf str;
    stream.rdbuf(&str);
    print(stream);
    return str.str();
}

std::string Expr::to_string_pretty(){
    std::ostream stream(nullptr);
    std::stringbuf str;
    stream.rdbuf(&str);
    pretty_print(stream);
    return str.str();
}

/* *********************************************** */

BoolExpr::BoolExpr(bool val){
    this->val = val;
}

bool BoolExpr::equals(PTR(Expr)other){
    PTR(BoolExpr)other_val = CAST(BoolExpr)(other);
    if (other_val == NULL){
        return false;
    } else {
        return (this->val == other_val->val);
    }
}

PTR(Val) BoolExpr::interp(PTR(Env) env){
    return NEW(BoolVal)(this->val);
}

//PTR(Expr) BoolExpr::subst(std::string name, PTR(Expr)replacement){
//    return THIS;
//}

void BoolExpr::print(std::ostream& output){
    if (this->val == true){
        output << "_true";
    } else {
        output << "_false";
    }
}

void BoolExpr::pretty_print(std::ostream& output){
    pretty_print_at(output, print_group_none, 0);
}

void BoolExpr::pretty_print_at(std::ostream& output, print_mode_t type, long *position){
    print(output);
}

/* *********************************************** */

IfExpr::IfExpr(PTR(Expr)test_part, PTR(Expr)then_part, PTR(Expr)else_part){
    this->test_part = test_part;
    this->then_part = then_part;
    this->else_part = else_part;
}

bool IfExpr::equals(PTR(Expr)other){
    PTR(IfExpr)other_num = CAST(IfExpr)(other);
    if (other_num == NULL){
        return false;
    } else {
        return (this->test_part)->equals(other_num->test_part) && (this->then_part)->equals(other_num->then_part) && (this->else_part)->equals(other_num->else_part);
    }
}
PTR(Val) IfExpr::interp(PTR(Env) env){
    if ((test_part->interp(env))->is_true()){
        return then_part->interp(env);
    } else {
        return else_part->interp(env);
    }
}
//
//PTR(Expr) IfExpr::subst(std::string name, PTR(Expr)replacement){
//    PTR(Expr)new_test_part = test_part->subst(name, replacement);
//    PTR(Expr)new_then_part = then_part->subst(name, replacement);
//    PTR(Expr)new_else_part = else_part->subst(name, replacement);
//    return NEW(IfExpr)(new_test_part, new_then_part, new_else_part);
//}

void IfExpr::print(std::ostream& output){
    PTR(Expr)new_test_part = this->test_part;
    PTR(Expr)new_then_part = this->then_part;
    PTR(Expr)new_else_part = this->else_part;
    output << "(_if ";
    new_test_part->print(output);
    output << " _then ";
    new_then_part->print(output);
    output << " _else ";
    new_else_part->print(output);
    output << ")";
}

void IfExpr::pretty_print(std::ostream& output){
    PTR(Expr)new_test = this->test_part;
    PTR(Expr)new_then = this->then_part;
    PTR(Expr)new_else = this->else_part;
    long position = 0;
    long *position_ptr = &position;
    output << "_if ";
    new_test->pretty_print_at(output, print_group_none, position_ptr);
    output << "\n";
    *position_ptr = output.tellp();
    output << "_then ";
    new_then->pretty_print_at(output, print_group_none, position_ptr);
    output << "\n";
    *position_ptr = output.tellp();
    output << "_else ";
    new_else->pretty_print_at(output, print_group_none, position_ptr);
}

void IfExpr::pretty_print_at(std::ostream& output, print_mode_t type, long *position){
    PTR(Expr)new_test = this->test_part;
    PTR(Expr)new_then = this->then_part;
    PTR(Expr)new_else = this->else_part;
    if (type == print_group_add_or_let || type == print_group_add_mult_or_let || type == print_group_eq){
        output << "(";
    }
    long curr_test_pos = output.tellp();
    long spaces = curr_test_pos - *position;
    output << "_if ";
    new_test->pretty_print_at(output, print_group_none, position);
    output << "\n";
    *position = output.tellp();
    int space_count = 0;
    while (space_count < spaces){
        output << " ";
        space_count++;
    }
    output << "_then ";
    new_then->pretty_print_at(output, print_group_none, position);
    output << "\n";
    *position = output.tellp();
    space_count = 0;
    while (space_count < spaces){
        output << " ";
        space_count++;
    }
    output << "_else ";
    new_else->pretty_print_at(output, print_group_none, position);
    if (type == print_group_add_or_let || type == print_group_add_mult_or_let ||  type == print_group_eq){
        output << ")";
    }
}

/* *********************************************** */

EqExpr::EqExpr(PTR(Expr)lhs, PTR(Expr)rhs){
    this->lhs = lhs;
    this->rhs = rhs;
}

bool EqExpr::equals(PTR(Expr)other){
    PTR(EqExpr)other_num = CAST(EqExpr)(other);
    if (other_num == NULL){
        return false;
    } else {
        return ((this->lhs)->equals(other_num->lhs)) && ((this->rhs)->equals(other_num->rhs));
    }
}

PTR(Val) EqExpr::interp(PTR(Env) env){
    return NEW(BoolVal)((this->lhs->interp(env)->equals(this->rhs->interp(env))));
}


//PTR(Expr) EqExpr::subst(std::string name, PTR(Expr)replacement){
//    PTR(Expr)new_lhs = lhs->subst(name, replacement);
//    PTR(Expr)new_rhs = rhs->subst(name, replacement);
//    return NEW(EqExpr)(new_lhs, new_rhs);
//}

void EqExpr::print(std::ostream& output){
    PTR(Expr)new_lhs = this->lhs;
    PTR(Expr)new_rhs = this->rhs;
    output << "(";
    new_lhs->print(output);
    output << "==";
    new_rhs->print(output);
    output<< ")";
}

void EqExpr::pretty_print(std::ostream& output){
    PTR(Expr)new_lhs = this->lhs;
    PTR(Expr)new_rhs = this->rhs;
    long position = 0;
    long *position_ptr = &position;
    new_lhs->pretty_print_at(output, print_group_eq, position_ptr);
    output << " == ";
    new_rhs->pretty_print_at(output, print_group_none, position_ptr);
}

void EqExpr::pretty_print_at(std::ostream& output, print_mode_t type, long *position){
    PTR(Expr)new_lhs = this->lhs;
    PTR(Expr)new_rhs = this->rhs;
    if (type == print_group_none){
        new_lhs->pretty_print_at(output, print_group_eq, position);
        output << " == ";
        new_rhs->pretty_print_at(output, print_group_none, position);
    } else {
        output << "(";
        new_lhs->pretty_print_at(output, print_group_eq, position);
        output << " == ";
        new_rhs->pretty_print_at(output, print_group_none, position);
        output << ")";
    }
}

/* *********************************************** */


FunExpr::FunExpr(std::string formal_arg, PTR(Expr) body){
    this->formal_arg = formal_arg;
    this->body = body;
}

bool FunExpr::equals(PTR(Expr)other){
    PTR(FunExpr)other_num = CAST(FunExpr)(other);
    if (other_num == NULL){
        return false;
    } else {
        return (this->formal_arg==other_num->formal_arg) && ((this->body)->equals(other_num->body));
    }
}

PTR(Val) FunExpr::interp(PTR(Env) env){
    return NEW(FunVal)(this->formal_arg, this->body, env);
}


//PTR(Expr) FunExpr::subst(std::string name, PTR(Expr)replacement){
//    if (name == formal_arg){
//        return NEW(FunExpr)(formal_arg, body);
//    }
//    return NEW(FunExpr)(formal_arg, body->subst(name, replacement));
//}

void FunExpr::print(std::ostream& output){
    output << "(_fun (" << formal_arg << ") ";
        this->body->print(output);
        output << ")";
}

void FunExpr::pretty_print(std::ostream& output){
  //TODO
}

void FunExpr::pretty_print_at(std::ostream& output, print_mode_t type, long *position){
  //TODO
}


/* *********************************************** */

CallExpr::CallExpr(PTR(Expr)to_be_called, PTR(Expr)actual_arg){
    this->to_be_called = to_be_called;
    this->actual_arg = actual_arg;
}

bool CallExpr::equals(PTR(Expr)other){
    PTR(CallExpr)other_num = CAST(CallExpr)(other);
    if (other_num == NULL){
        return false;
    } else {
        return (this->to_be_called)->equals(other_num->to_be_called) && (this->actual_arg)->equals(other_num->actual_arg);
    }
}

PTR(Val) CallExpr::interp(PTR(Env) env){
    return to_be_called->interp(env)->call(actual_arg->interp(env));
}

//PTR(Expr) CallExpr::subst(std::string name, PTR(Expr)replacement){
//    PTR(Expr)new_TBC = to_be_called->subst(name,replacement);
//    PTR(Expr)new_AA = actual_arg->subst(name, replacement);
//    return NEW(CallExpr)(new_TBC, new_AA);
//}

void CallExpr::print(std::ostream& output){
    this->to_be_called->print(output);
        output << "(";
        this->actual_arg->print(output);
        output << ")";
}

void CallExpr::pretty_print(std::ostream& output){
  //TODO
}

void CallExpr::pretty_print_at(std::ostream& output, print_mode_t type, long *position){
  //TODO
}

/* *********************************************** */
TEST_CASE( "num equals" ){
    CHECK((NEW(NumExpr)(0))->equals(NEW(NumExpr)(0))==true);
    CHECK((NEW(NumExpr)(1))->equals(NEW(NumExpr)(1))==true);
    CHECK((NEW(NumExpr)(-1))->equals(NEW(NumExpr)(-1))==true);
    CHECK((NEW(NumExpr)(0))->equals(NEW(NumExpr)(1))==false);
    CHECK((NEW(NumExpr)(-0))->equals(NEW(NumExpr)(0))==true);
    CHECK((NEW(NumExpr)(-1))->equals(NEW(NumExpr)(1))==false);
    PTR(NumExpr)num0 = NEW(NumExpr)(0);
    PTR(NumExpr)num1 = NEW(NumExpr)(1);
    PTR(NumExpr)num1b = NEW(NumExpr)(1);
    CHECK(num1 ->equals(num1b)==true);
    CHECK(num0 ->equals(num1)==false);
}

TEST_CASE( "add equals" ){
    PTR(NumExpr)num0 = NEW(NumExpr)(0);
    PTR(NumExpr)num1 = NEW(NumExpr)(1);
    PTR(NumExpr)num1b = NEW(NumExpr)(1);
    CHECK((NEW(AddExpr)(num0, num1))->equals(NEW(AddExpr)(num0, num1)) == true);
    CHECK((NEW(AddExpr)(num0, num1))->equals(NEW(AddExpr)(num0, num1b)) == true);
    CHECK((NEW(AddExpr)(num0, num1))->equals(NEW(AddExpr)(num1, num0)) == false);
    CHECK((NEW(AddExpr)(NEW(NumExpr)(0),NEW(NumExpr)(1)))->equals(NEW(AddExpr)(NEW(NumExpr)(0),NEW(NumExpr)(1))) == true);
    CHECK((NEW(AddExpr)(NEW(NumExpr)(0),NEW(NumExpr)(1)))->equals(NEW(AddExpr)(NEW(NumExpr)(1),NEW(NumExpr)(0))) == false);
    CHECK((NEW(AddExpr)(NEW(AddExpr)(num0, num1),NEW(NumExpr)(1)))->equals(NEW(AddExpr)(NEW(AddExpr)(num0, num1),NEW(NumExpr)(1))) == true);
    
}

TEST_CASE( "mult equals" ){
    PTR(NumExpr)num0 = NEW(NumExpr)(0);
    PTR(NumExpr)num1 = NEW(NumExpr)(1);
    PTR(NumExpr)num1b = NEW(NumExpr)(1);
    CHECK((NEW(MultExpr)(num0, num1))->equals(NEW(MultExpr)(num0, num1)) == true);
    CHECK((NEW(MultExpr)(num0, num1))->equals(NEW(MultExpr)(num0, num1b)) == true);
    CHECK((NEW(MultExpr)(num0, num1))->equals(NEW(MultExpr)(num1, num0)) == false);
    CHECK((NEW(MultExpr)(NEW(NumExpr)(0),NEW(NumExpr)(1)))->equals(NEW(MultExpr)(NEW(NumExpr)(0),NEW(NumExpr)(1))) == true);
    CHECK((NEW(MultExpr)(NEW(NumExpr)(0),NEW(NumExpr)(1)))->equals(NEW(MultExpr)(NEW(NumExpr)(1),NEW(NumExpr)(0))) == false);
    CHECK((NEW(MultExpr)(NEW(MultExpr)(num0, num1),NEW(NumExpr)(1)))->equals(NEW(MultExpr)(NEW(MultExpr)(num0, num1),NEW(NumExpr)(1))) == true);
}

TEST_CASE( "variable equals" ){
    PTR(VarExpr)mod = NEW(VarExpr)("%");
    PTR(VarExpr)percent = NEW(VarExpr)("%");
    PTR(VarExpr)one = NEW(VarExpr)("1");
    PTR(VarExpr)word = NEW(VarExpr)("word");
    PTR(VarExpr)word2 = NEW(VarExpr)("word");
    PTR(NumExpr)num1 = NEW(NumExpr)(1);
    CHECK(mod->equals(percent) == true);
    CHECK(one->equals(num1) == false);
    CHECK((NEW(MultExpr)(NEW(VarExpr)("*"),NEW(VarExpr)("&")))->equals(NEW(MultExpr)(NEW(VarExpr)("*"),NEW(VarExpr)("&"))) == true);
    CHECK((NEW(MultExpr)(NEW(VarExpr)("*"),NEW(NumExpr)(1)))->equals(NEW(MultExpr)(NEW(VarExpr)("*"),NEW(NumExpr)(1))) == true);
    CHECK((NEW(MultExpr)(one, num1))->equals(NEW(MultExpr)(one, num1)) == true);
    CHECK((NEW(MultExpr)(num1, one))->equals(NEW(MultExpr)(one, num1)) == false);
    CHECK((word)->equals(word2));
}

TEST_CASE ( "let equals" ){
    std::string name = "x";
    PTR(LetExpr)let1 = NEW(LetExpr)(name, NEW(NumExpr)(5), (NEW(AddExpr) (NEW(VarExpr)("x"), NEW(NumExpr) (4))));
    PTR(LetExpr)sameLet1 = NEW(LetExpr)(name, NEW(NumExpr)(5), (NEW(AddExpr) (NEW(VarExpr)("x"), NEW(NumExpr) (4))));
    PTR(LetExpr)let2 = NEW(LetExpr)(name, NEW(NumExpr)(5), (NEW(AddExpr) (NEW(VarExpr)("y"), NEW(NumExpr) (4))));
    CHECK((let1->equals(sameLet1))==true);
    CHECK((let1->equals(let2))==false);
}

TEST_CASE ("bool equals"){
    PTR(BoolExpr)true_bool = NEW(BoolExpr)(true);
    PTR(BoolExpr)true_bool_2 = NEW(BoolExpr)(true);
    PTR(BoolExpr)false_bool = NEW(BoolExpr)(false);
    PTR(BoolExpr)false_bool_2 = NEW(BoolExpr)(false);
    CHECK(true_bool->equals(true_bool_2));
    CHECK(false_bool->equals(false_bool_2));
}

TEST_CASE("if equals"){
    PTR(IfExpr)test = NEW(IfExpr)(NEW(BoolExpr)(true), NEW(NumExpr)(5), NEW(NumExpr)(2));
    PTR(IfExpr)same_test = NEW(IfExpr)(NEW(BoolExpr)(true), NEW(NumExpr)(5), NEW(NumExpr)(2));
    PTR(IfExpr)diff_test = NEW(IfExpr)(NEW(BoolExpr)(true), NEW(NumExpr)(5), NEW(NumExpr)(7));
    CHECK(test->equals(same_test));
    CHECK(test->equals(diff_test) == false);
}

TEST_CASE("equivalence equals"){
    CHECK((NEW(EqExpr)(NEW(NumExpr)(2), NEW(NumExpr)(0)))->equals(NEW(EqExpr)(NEW(NumExpr)(2), NEW(NumExpr)(0))) == true);
    CHECK((NEW(EqExpr)(NEW(NumExpr)(0), NEW(NumExpr)(1)))->equals(NEW(EqExpr)(NEW(NumExpr)(0), NEW(NumExpr)(0))) == false);
}

TEST_CASE("function equals"){
    CHECK((NEW(FunExpr)("x", NEW(NumExpr)(3)))->equals(NEW(FunExpr)("x", NEW(NumExpr)(3))) == true);
}

TEST_CASE("call equals"){
    CHECK((NEW(CallExpr)(NEW(NumExpr)(4), NEW(NumExpr)(3)))->equals(NEW(CallExpr)(NEW(NumExpr)(4), NEW(NumExpr)(3))) == true);
}

TEST_CASE("fun val equal"){
    CHECK((NEW(FunVal)("y", NEW(NumExpr)(5), Env::empty))->equals(NEW(FunVal)("y", NEW(NumExpr)(5), Env::empty))==true);
}

TEST_CASE ( "Object Comparisions" ){
    CHECK((NEW(MultExpr)(NEW(NumExpr)(0),NEW(NumExpr)(1)))->equals(NEW(AddExpr)(NEW(NumExpr)(1),NEW(NumExpr)(0))) == false);
    CHECK((NEW(VarExpr)("*"))->equals(NEW(NumExpr)(5)) == false);
    CHECK((NEW(AddExpr)(NEW(NumExpr)(0),NEW(NumExpr)(1)))->equals(NEW(VarExpr)("%")) == false);
    CHECK((NEW(MultExpr)(NEW(NumExpr)(0),NEW(NumExpr)(1)))->equals(NEW(NumExpr)(7)) == false);
    CHECK((NEW(VarExpr)("*"))->equals(NEW(MultExpr)(NEW(NumExpr)(0),NEW(NumExpr)(1))) == false);
    CHECK(((NEW(LetExpr)("x", NEW(NumExpr)(5), (NEW(AddExpr) (NEW(VarExpr)("x"), NEW(NumExpr) (4)))))->equals(NEW(MultExpr)(NEW(NumExpr)(0),NEW(NumExpr)(1))))==false);
    CHECK((NEW(BoolExpr)(true))->equals(NEW(AddExpr)(NEW(NumExpr)(0), NEW(NumExpr)(2))) == false);
    CHECK((NEW(IfExpr)(NEW(BoolExpr)(true), NEW(NumExpr)(5), NEW(NumExpr)(2)))->equals(NEW(AddExpr)(NEW(NumExpr)(0), NEW(NumExpr)(2))) == false);
    CHECK((NEW(EqExpr)(NEW(NumExpr)(0), NEW(NumExpr)(3)))->equals(NEW(NumExpr)(5)) == false);
    CHECK((NEW(NumVal)(5))->equals(NEW(BoolVal)(true))==false);
    CHECK((NEW(BoolVal)(true))->equals(NEW(NumVal)(-5))==false);
    CHECK((NEW(FunVal)("y", NEW(NumExpr)(5), Env::empty))->equals(NEW(BoolVal)(true))==false);
    CHECK((NEW(FunExpr)("x", NEW(NumExpr)(3)))->equals(NEW(NumExpr)(3)) == false);
    CHECK((NEW(CallExpr)(NEW(NumExpr)(4), NEW(NumExpr)(3)))->equals(NEW(NumExpr)(3)) == false);
}

TEST_CASE ( "Interpret" ){
    CHECK((NEW(NumExpr)(5))->interp(Env::empty)->equals(NEW(NumVal)(5)));
    CHECK((NEW(NumExpr)(-1))->interp(Env::empty)->equals(NEW(NumVal)(-1)));
    CHECK((NEW(NumExpr)(0))->interp(Env::empty)->equals(NEW(NumVal)(0)));
    CHECK((NEW(AddExpr)(NEW(NumExpr)(2),NEW(NumExpr)(4)))->interp(Env::empty)->equals(NEW(NumVal)(6)));
    CHECK((NEW(AddExpr)(NEW(NumExpr)(-10),NEW(NumExpr)(7)))->interp(Env::empty)->equals(NEW(NumVal)(-3)));
    CHECK((NEW(AddExpr)(NEW(NumExpr)(-31),NEW(NumExpr)(31)))->interp(Env::empty)->equals(NEW(NumVal)(0)));
    CHECK((NEW(MultExpr)(NEW(NumExpr)(2),NEW(NumExpr)(4)))->interp(Env::empty)->equals(NEW(NumVal)(8)));
    CHECK((NEW(MultExpr)(NEW(NumExpr)(-5),NEW(NumExpr)(-2)))->interp(Env::empty)->equals(NEW(NumVal)(10)));
    CHECK((NEW(MultExpr)(NEW(NumExpr)(5),NEW(NumExpr)(-2)))->interp(Env::empty)->equals(NEW(NumVal)(-10)));
    CHECK((NEW(LetExpr)("x", NEW(NumExpr)(5), NEW(AddExpr)(NEW(VarExpr)("x"), NEW(NumExpr)(1))))->interp(Env::empty)->equals(NEW(NumVal)(6)));
    CHECK((NEW(LetExpr)("x", NEW(AddExpr)( NEW(NumExpr)(5), NEW(NumExpr) (2)), NEW(AddExpr)(NEW(VarExpr)("x"), NEW(NumExpr)(1))))->interp(Env::empty)->equals(NEW(NumVal)(8)));
    CHECK((NEW(LetExpr)("x", NEW(NumExpr)(5), NEW(AddExpr)(NEW(LetExpr)("y", NEW(NumExpr)(3), NEW(AddExpr)(NEW(VarExpr)("y"), NEW(NumExpr)(2))), NEW(VarExpr)("x"))))->interp(Env::empty)->equals(NEW(NumVal)(10)));
    CHECK((NEW(LetExpr)("x", NEW(NumExpr)(5), NEW(LetExpr)("x", NEW(AddExpr)( NEW(VarExpr)("x"), NEW(NumExpr)(2)), NEW(AddExpr)(NEW(VarExpr)("x"), NEW(NumExpr)(1)))))->interp(Env::empty)->equals(NEW(NumVal)(8)));
    CHECK((NEW(AddExpr)(NEW(MultExpr)(NEW(NumExpr)(5), NEW(LetExpr)("x", NEW(NumExpr)(5), NEW(VarExpr)("x"))), NEW(NumExpr) (1)))->interp(Env::empty)->equals(NEW(NumVal)(26)));
    CHECK((NEW(MultExpr)( NEW(NumExpr)(5), NEW(AddExpr)(NEW(LetExpr)("x", NEW(NumExpr)(5), NEW(VarExpr)("x")), NEW(NumExpr) (1))))->interp(Env::empty)->equals(NEW(NumVal)(30)));
    CHECK_THROWS_WITH((NEW(VarExpr)("x"))->interp(Env::empty), "free variable: x" );
    CHECK_THROWS_WITH((NEW(VarExpr)("&"))->interp(Env::empty), "free variable: &" );
    CHECK_THROWS_WITH((NEW(VarExpr)(""))->interp(Env::empty), "free variable: " );
    CHECK_THROWS_WITH((NEW(AddExpr)(NEW(VarExpr)("b"),NEW(NumExpr)(31)))->interp(Env::empty), "free variable: b" );
    CHECK_THROWS_WITH((NEW(MultExpr)(NEW(NumExpr)(3),NEW(VarExpr)("a")))->interp(Env::empty), "free variable: a" );
    CHECK_THROWS_WITH((NEW(LetExpr)("x", NEW(VarExpr)("t"), NEW(AddExpr)(NEW(VarExpr)("x"), NEW(NumExpr)(1))))->interp(Env::empty), "free variable: t");
    CHECK(((NEW(BoolExpr)(true))->interp(Env::empty)->equals(NEW(BoolVal)(true))));
    CHECK(((NEW(BoolExpr)(false))->interp(Env::empty)->equals(NEW(BoolVal)(false))));
    CHECK(((NEW(IfExpr)(NEW(BoolExpr)(true), NEW(NumExpr)(5), NEW(VarExpr)("x")))->interp(Env::empty)->equals(NEW(NumVal)(5))));
    CHECK(((NEW(IfExpr)(NEW(BoolExpr)(false), NEW(NumExpr)(5), NEW(NumExpr)(6)))->interp(Env::empty)->equals(NEW(NumVal)(6))));
    CHECK_THROWS_WITH((NEW(IfExpr)(NEW(BoolExpr)(false), NEW(NumExpr)(5), NEW(VarExpr)("x")))->interp(Env::empty), "free variable: x");
    CHECK((NEW(EqExpr)(NEW(AddExpr)(NEW(NumExpr)(5), NEW(NumExpr)(3)), NEW(AddExpr)(NEW(NumExpr)(3), NEW(NumExpr)(5))))->interp(Env::empty)->equals(NEW(BoolVal)(true)));
    CHECK((NEW(EqExpr)(NEW(MultExpr)(NEW(NumExpr)(2), NEW(NumExpr)(3)), NEW(MultExpr)(NEW(NumExpr)(3), NEW(NumExpr)(2))))->interp(Env::empty)->equals(NEW(BoolVal)(true)));
    CHECK((NEW(EqExpr)(NEW(MultExpr)(NEW(NumExpr)(2), NEW(NumExpr)(3)), NEW(NumExpr)(6)))->interp(Env::empty)->equals(NEW(BoolVal)(true)));
    CHECK((NEW(EqExpr)(NEW(MultExpr)(NEW(NumExpr)(2), NEW(NumExpr)(3)), NEW(NumExpr)(5)))->interp(Env::empty)->equals(NEW(BoolVal)(false)));
    CHECK((NEW(EqExpr)(
                       NEW(LetExpr)("x",
                                   NEW(NumExpr)(5),
                                   NEW(AddExpr) ( NEW(VarExpr)("x"), NEW(NumExpr)(3))),
                      NEW(LetExpr)( "x",
                                   NEW(NumExpr)(3),
                                   NEW(AddExpr) ( NEW(VarExpr)("x"), NEW(NumExpr)(5)))
                      ))
                      ->interp(Env::empty)->equals(NEW(BoolVal)(true)));
    CHECK((NEW(LetExpr)("x",
                NEW(EqExpr)(NEW(NumExpr)(3), NEW(NumExpr)(4)),
                NEW(VarExpr)("x")))
          ->interp(Env::empty)->equals(NEW(BoolVal)(false)));
    CHECK((NEW(LetExpr)(("same"),
           NEW(EqExpr)(NEW(NumExpr)(1), NEW(NumExpr)(2)),
           NEW(IfExpr)(
                      NEW(EqExpr) (NEW(NumExpr)(1), NEW(NumExpr)(2)),
                      NEW(AddExpr)( NEW(BoolExpr)(false), NEW(NumExpr)(5)),
                      NEW(NumExpr)(88))
           ))->interp(Env::empty)->equals(NEW(NumVal)(88)));
    CHECK_THROWS_WITH((NEW(IfExpr)(NEW(AddExpr)(NEW(NumExpr)(4), NEW(NumExpr)(1)),
                              NEW(AddExpr)(NEW(BoolExpr)(false), NEW(NumExpr)(5)),
                              NEW(NumExpr)(3)))->interp(Env::empty), "Test expression is not a boolean");
    CHECK_THROWS_WITH((NEW(AddExpr)(NEW(NumExpr)(4), NEW(BoolExpr)(true)))->interp(Env::empty), "addition of non-number");
    CHECK_THROWS_WITH((NEW(MultExpr)(NEW(NumExpr)(-4), NEW(BoolExpr)(true)))->interp(Env::empty), "multiplication of non-number");
    CHECK_THROWS_WITH((NEW(AddExpr)(NEW(BoolExpr)(true), NEW(NumExpr)(5)))->interp(Env::empty), "addition of non-number");
    CHECK_THROWS_WITH((NEW(MultExpr)(NEW(BoolExpr)(false), NEW(NumExpr)(-5)))->interp(Env::empty), "multiplication of non-number");
}

//TEST_CASE ( "Substitution" ){
//    CHECK ((NEW(NumExpr)(1))->subst("a", NEW(NumExpr)(4))->equals(NEW(NumExpr)(1)) == true);
//    CHECK ((NEW(NumExpr)(1))->subst("a", NEW(NumExpr)(4))->equals(NEW(NumExpr)(4)) == false);
//    CHECK ((NEW(VarExpr)("a"))->subst("a", NEW(VarExpr)("c"))->equals(NEW(VarExpr)("c"))== true);
//    CHECK ((NEW(VarExpr)("a"))->subst("b", NEW(VarExpr)("c"))->equals(NEW(VarExpr)("a"))== true);
//    CHECK ((NEW(MultExpr)(NEW(VarExpr)("x"), NEW(NumExpr)(7)))->subst("x", NEW(VarExpr)("y"))->equals(NEW(MultExpr)(NEW(VarExpr)("y"), NEW(NumExpr)(7)))==true);
//    CHECK ((NEW(AddExpr)(NEW(VarExpr)("x"), NEW(NumExpr)(7)))->subst("x", NEW(VarExpr)("y"))->equals(NEW(AddExpr)(NEW(VarExpr)("y"), NEW(NumExpr)(7)))==true);
//    //Always substitue RHS. Body changes iff the variable we are replacing and the bound variable are different
//    //
//    //No Change
//    //_let x = 1
//    //_in x + 2 ->subst(x, y+3)
//    PTR(Expr)let1 = NEW(LetExpr)("x",
//                         NEW(NumExpr)(1),
//                         NEW(AddExpr)(NEW(VarExpr)("x"), NEW(NumExpr)(2)));
//    CHECK ((let1)->subst("x", NEW(AddExpr)(NEW(VarExpr)("y"), NEW(NumExpr)(3)))->equals(let1));
//    //Only change RHS
//    //_let x = x
//    //_in x + 2 ->subst(x, 5)
//    //=
//    //_let x = 5
//    //_in x + 2
//    PTR(Expr)let2 = NEW(LetExpr)("x",
//                         NEW(VarExpr)("x"),
//                         NEW(AddExpr)(NEW(VarExpr)("x"), NEW(NumExpr)(2)));
//    CHECK ((let2->subst("x", NEW(NumExpr)(5))
//           ->equals(NEW(LetExpr)("x",
//                            NEW(NumExpr)(5),
//                            NEW(AddExpr) (NEW(VarExpr)("x"), NEW(NumExpr)(2))))));
//    //Only change Body
//    //_let x = 8
//    //_in x+y-> subst("y", 9)
//    // =
//    //_let x = 8
//    //_in x+9
//    PTR(Expr)let3 = NEW(LetExpr) ("x",
//                          NEW(NumExpr)(8),
//                          NEW(AddExpr) (NEW(VarExpr)("x"), NEW(VarExpr)("y")));
//    CHECK ((let3-> subst("y", NEW(NumExpr)(9)))
//          ->equals(NEW(LetExpr) ("x",
//                            NEW(NumExpr)(8),
//                            NEW(AddExpr) (NEW(VarExpr)("x"), NEW(NumExpr)(9)))));
//    //Change RHS and Body
//    //_let x = y
//    //_in x+y-> subst("y", 9)
//    // =
//    //_let x = 9
//    //_in x+9
//    PTR(Expr)let4 = NEW(LetExpr) ("x",
//                          NEW(VarExpr) ("y"),
//                          NEW(AddExpr) (NEW(VarExpr)("x"), NEW(VarExpr)("y")));
//    CHECK ((let4-> subst("y", NEW(NumExpr)(9)))
//          ->equals(NEW(LetExpr) ("x",
//                            NEW(NumExpr)(9),
//                            NEW(AddExpr) (NEW(VarExpr)("x"), NEW(NumExpr)(9)))));
//    CHECK ((NEW(IfExpr)(NEW(VarExpr)("x"), NEW(NumExpr)(5), NEW(NumExpr)(3)))->subst("x", NEW(VarExpr)("y"))->equals(NEW(IfExpr)(NEW(VarExpr)("y"), NEW(NumExpr)(5), NEW(NumExpr)(3))));
//    CHECK ((NEW(IfExpr)(NEW(NumExpr)(5), NEW(VarExpr)("x"), NEW(NumExpr)(3)))->subst("x", NEW(VarExpr)("y"))->equals(NEW(IfExpr)(NEW(NumExpr)(5), NEW(VarExpr)("y"), NEW(NumExpr)(3))));
//    CHECK ((NEW(IfExpr)(NEW(NumExpr)(5), NEW(NumExpr)(3), NEW(VarExpr)("x")))->subst("x", NEW(VarExpr)("y"))->equals(NEW(IfExpr)(NEW(NumExpr)(5), NEW(NumExpr)(3), NEW(VarExpr)("y"))));
//    CHECK ((NEW(BoolExpr)(true))->subst("y", NEW(NumExpr)(5))->equals(NEW(BoolExpr)(true)));
//    CHECK ((NEW(EqExpr)(NEW(AddExpr) (NEW(VarExpr)("x"), NEW(NumExpr)(3)), NEW(AddExpr)(NEW(VarExpr)("x"), NEW(NumExpr)(3))))->subst("x", NEW(NumExpr)(4))->equals( NEW(EqExpr)(NEW(AddExpr) (NEW(NumExpr)(4), NEW(NumExpr)(3)), NEW(AddExpr)(NEW(NumExpr)(4), NEW(NumExpr)(3)))));
//    CHECK((NEW(FunExpr)("x", NEW(AddExpr)(NEW(NumExpr)(4), NEW(VarExpr)("x"))))->subst("x", NEW(VarExpr)("y"))->equals(NEW(FunExpr)("x", NEW(AddExpr)(NEW(NumExpr)(4), NEW(VarExpr)("x")))));
//    CHECK((NEW(CallExpr)(NEW(VarExpr)("x"), NEW(AddExpr)(NEW(NumExpr)(1), NEW(VarExpr)("x"))))->subst("x", NEW(NumExpr)(13))->equals(NEW(CallExpr)(NEW(NumExpr)(13), NEW(AddExpr)(NEW(NumExpr)(1), NEW(NumExpr)(13)))));
//}

TEST_CASE ( "Print" ){
    CHECK ((NEW(NumExpr)(5))->to_string() == "5");
    CHECK ((NEW(VarExpr)("x"))->to_string() == "x");
    CHECK ((NEW(AddExpr)(NEW(NumExpr)(5), NEW(NumExpr)(4)))->to_string() == "(5+4)");
    CHECK (((NEW(AddExpr)(NEW(VarExpr)("x"), (NEW(MultExpr)(NEW(NumExpr)(2),NEW(NumExpr)(4)))))->to_string())=="(x+(2*4))");
    CHECK ((NEW(AddExpr)( NEW(MultExpr)(NEW(NumExpr)(3), NEW(NumExpr)(2)), NEW(MultExpr)( NEW(NumExpr)(5), NEW(NumExpr)(6))))->to_string() == "((3*2)+(5*6))");
    CHECK ((NEW(LetExpr)("x", NEW(NumExpr)(5), NEW(AddExpr)(NEW(VarExpr)("x"), NEW(NumExpr)(1))))->to_string() == "(_let x=5 _in (x+1))");
    CHECK ((NEW(LetExpr)("x", NEW(NumExpr)(5), NEW(AddExpr)(NEW(LetExpr)("y", NEW(NumExpr)(3), NEW(AddExpr)(NEW(VarExpr)("y"), NEW(NumExpr)(2))), NEW(VarExpr)("x"))))->to_string() == "(_let x=5 _in ((_let y=3 _in (y+2))+x))");
    CHECK ((NEW(BoolExpr)(true))->to_string() == "_true");
    CHECK ((NEW(BoolExpr)(false))->to_string() == "_false");
    CHECK ((NEW(EqExpr)(NEW(AddExpr) (NEW(NumExpr)(4), NEW(NumExpr)(3)), NEW(AddExpr)(NEW(NumExpr)(4), NEW(NumExpr)(3))))->to_string() == "((4+3)==(4+3))");
    CHECK ((NEW(EqExpr)(NEW(NumExpr)(4), NEW(NumExpr)(7)))->to_string() == "(4==7)");
    CHECK ((NEW(IfExpr)(NEW(BoolExpr)(true), NEW(NumExpr)(5), NEW(NumExpr)(0)))->to_string() == "(_if _true _then 5 _else 0)");
    CHECK ((NEW(IfExpr)(NEW(AddExpr)(NEW(NumExpr)(6), NEW(VarExpr)("y")), NEW(NumExpr)(5), NEW(NumExpr)(0)))->to_string() == "(_if (6+y) _then 5 _else 0)");
    CHECK((NEW(NumVal)(8))->to_string()== "8");
    CHECK((NEW(BoolVal)(true))->to_string() == "_true");
    CHECK((NEW(BoolVal)(false))->to_string() == "_false");
    CHECK((NEW(FunExpr)("x", NEW(AddExpr) (NEW(NumExpr)(3), NEW(VarExpr)("x"))))->to_string() == "(_fun (x) (3+x))");
    CHECK((NEW(CallExpr)(NEW(VarExpr)("f"), NEW(NumExpr)(3)))->to_string() == "f(3)");
    CHECK((NEW(CallExpr)(NEW(VarExpr)("f"), NEW(AddExpr)(NEW(NumExpr)(3), NEW(VarExpr)("x"))))->to_string() == "f((3+x))");
}

TEST_CASE ( "Pretty Print Basic" ){
    CHECK ((NEW(NumExpr)(5))->to_string_pretty() == "5");
    CHECK ((NEW(VarExpr)("x"))->to_string_pretty() == "x");
    CHECK ((NEW(AddExpr)(NEW(NumExpr)(5), NEW(NumExpr)(4)))->to_string_pretty() == "5 + 4");
    CHECK ((NEW(MultExpr)(NEW(NumExpr)(5), NEW(NumExpr)(4)))->to_string_pretty() == "5 * 4");
    CHECK ((NEW(AddExpr)(NEW(VarExpr)("a"), NEW(VarExpr)("b")))->to_string_pretty() == "a + b");
    CHECK ((NEW(MultExpr)(NEW(VarExpr)("a"), NEW(VarExpr)("b")))->to_string_pretty() == "a * b");
    CHECK ((NEW(BoolExpr)(true))->to_string_pretty() == "_true");
    CHECK ((NEW(BoolExpr)(false))->to_string_pretty() == "_false");
}

TEST_CASE ( "Pretty Print Moderate" ){
    CHECK ((NEW(AddExpr)(NEW(AddExpr)( NEW(NumExpr)(3), NEW(NumExpr)(4)), NEW(VarExpr)("a")))->to_string_pretty() == "(3 + 4) + a");
    CHECK ((NEW(AddExpr)(NEW(NumExpr)(3), NEW(AddExpr)( NEW(NumExpr)(4), NEW(NumExpr)(5))))->to_string_pretty() == "3 + 4 + 5");
    CHECK ((NEW(AddExpr)(NEW(NumExpr)(3), NEW(MultExpr)( NEW(NumExpr)(4), NEW(VarExpr)("b"))))->to_string_pretty() == "3 + 4 * b");
    CHECK ((NEW(AddExpr)(NEW(MultExpr)( NEW(NumExpr)(3), NEW(NumExpr)(4)), NEW(NumExpr)(5)))->to_string_pretty() == "3 * 4 + 5");
    CHECK ((NEW(MultExpr)(NEW(AddExpr)( NEW(NumExpr)(3), NEW(VarExpr)("a")), NEW(NumExpr)(5)))->to_string_pretty() == "(3 + a) * 5");
    CHECK ((NEW(MultExpr)(NEW(VarExpr)("b"), NEW(AddExpr)( NEW(NumExpr)(4), NEW(NumExpr)(5))))->to_string_pretty() == "b * (4 + 5)");
    CHECK ((NEW(MultExpr)(NEW(NumExpr)(3), NEW(MultExpr)( NEW(NumExpr)(4), NEW(NumExpr)(5))))->to_string_pretty() == "3 * 4 * 5");
    CHECK ((NEW(MultExpr)(NEW(MultExpr)( NEW(VarExpr)("a"), NEW(NumExpr)(4)), NEW(NumExpr)(5)))->to_string_pretty() == "(a * 4) * 5");
}

TEST_CASE ( "Pretty Print Advanced" ){
    CHECK ((NEW(AddExpr)(NEW(AddExpr)( NEW(NumExpr)(3), NEW(NumExpr)(4)), NEW(AddExpr)( NEW(NumExpr)(5), NEW(VarExpr)("a"))))->to_string_pretty() == "(3 + 4) + 5 + a");
    CHECK ((NEW(AddExpr)(NEW(MultExpr)( NEW(VarExpr)("a"), NEW(NumExpr)(4)), NEW(MultExpr)( NEW(NumExpr)(5), NEW(NumExpr)(6))))->to_string_pretty() == "a * 4 + 5 * 6");
    CHECK ((NEW(AddExpr)(NEW(AddExpr)( NEW(NumExpr)(3), NEW(VarExpr)("a")), NEW(MultExpr)( NEW(NumExpr)(5), NEW(NumExpr)(6))))->to_string_pretty() == "(3 + a) + 5 * 6");
    CHECK ((NEW(AddExpr)(NEW(MultExpr)( NEW(VarExpr)("b"), NEW(VarExpr)("a")), NEW(AddExpr)( NEW(NumExpr)(5), NEW(NumExpr)(6))))->to_string_pretty() == "b * a + 5 + 6");
    CHECK ((NEW(MultExpr)(NEW(AddExpr)( NEW(NumExpr)(3), NEW(NumExpr)(4)), NEW(AddExpr)( NEW(NumExpr)(5), NEW(VarExpr)("b"))))->to_string_pretty() == "(3 + 4) * (5 + b)");
    CHECK ((NEW(MultExpr)(NEW(MultExpr)( NEW(NumExpr)(3), NEW(NumExpr)(4)), NEW(MultExpr)( NEW(NumExpr)(5), NEW(NumExpr)(6))))->to_string_pretty() == "(3 * 4) * 5 * 6");
    CHECK ((NEW(MultExpr)(NEW(AddExpr)( NEW(NumExpr)(3), NEW(VarExpr)("b")), NEW(MultExpr)( NEW(VarExpr)("a"), NEW(NumExpr)(6))))->to_string_pretty() == "(3 + b) * a * 6");
    CHECK ((NEW(MultExpr)(NEW(MultExpr)( NEW(NumExpr)(3), NEW(NumExpr)(4)), NEW(AddExpr)( NEW(NumExpr)(5), NEW(VarExpr)("a"))))->to_string_pretty() == "(3 * 4) * (5 + a)");
}

TEST_CASE ( "Pretty Print Extreme" ){
    CHECK ((NEW(MultExpr) (NEW(AddExpr) (NEW(VarExpr) ("a"), NEW(VarExpr) ("b")), NEW(NumExpr) (7)))->to_string_pretty() == "(a + b) * 7");
    CHECK ((NEW(MultExpr) (NEW(MultExpr) (NEW(AddExpr) (NEW(VarExpr) ("a"), NEW(VarExpr) ("b")), NEW(NumExpr) (7)), NEW(NumExpr) (6)))->to_string_pretty() == "((a + b) * 7) * 6");
    CHECK ((NEW(MultExpr) (NEW(MultExpr) (NEW(MultExpr) (NEW(AddExpr) (NEW(VarExpr) ("a"), NEW(VarExpr) ("b")), NEW(NumExpr) (7)), NEW(NumExpr) (6)), NEW(VarExpr) ("c")))->to_string_pretty() == "(((a + b) * 7) * 6) * c");
    CHECK ((NEW(MultExpr)(NEW(MultExpr)(NEW(MultExpr)( NEW(NumExpr)(3), NEW(NumExpr)(4)), NEW(MultExpr)( NEW(NumExpr)(5), NEW(NumExpr)(6))), NEW(VarExpr) ("b")))->to_string_pretty()=="((3 * 4) * 5 * 6) * b");
    CHECK ((NEW(MultExpr)(NEW(MultExpr)( NEW(MultExpr)( NEW(NumExpr)(3), NEW(NumExpr)(4)), NEW(MultExpr)( NEW(NumExpr)(5), NEW(NumExpr)(6))), NEW(AddExpr)( NEW(NumExpr)(7), NEW(NumExpr)(8))))->to_string_pretty() == "((3 * 4) * 5 * 6) * (7 + 8)");
    CHECK ((NEW(MultExpr)(NEW(MultExpr)( NEW(AddExpr)( NEW(VarExpr)("a"), NEW(VarExpr)("b")), NEW(NumExpr)(7)), NEW(MultExpr)( NEW(NumExpr)(6), NEW(VarExpr)("c"))))->to_string_pretty() == "((a + b) * 7) * 6 * c");
}

TEST_CASE ( "Let Pretty Print" ){
    CHECK ((NEW(LetExpr)("x", NEW(NumExpr)(5), NEW(AddExpr)(NEW(VarExpr)("x"), NEW(NumExpr)(1))))->to_string_pretty() == "_let x = 5\n_in  x + 1");
    CHECK ((NEW(LetExpr)("x", NEW(NumExpr)(5), NEW(LetExpr)("x", NEW(NumExpr)(1), NEW(AddExpr)( NEW(VarExpr)("x"), NEW(NumExpr)(3)))))->to_string_pretty() == "_let x = 5\n_in  _let x = 1\n     _in  x + 3");
    CHECK ((NEW(LetExpr)("x", NEW(NumExpr)(5), NEW(AddExpr)(NEW(LetExpr)("y", NEW(NumExpr)(3), NEW(AddExpr)(NEW(VarExpr)("y"), NEW(NumExpr)(2))), NEW(VarExpr)("x"))))->to_string_pretty() == "_let x = 5\n_in  (_let y = 3\n      _in  y + 2) + x");
    CHECK ((NEW(LetExpr)("x", NEW(NumExpr)(5), NEW(LetExpr)("y", NEW(NumExpr)(3), NEW(LetExpr)( "z", NEW(NumExpr)(1), NEW(AddExpr) (NEW(VarExpr)("z"), NEW(NumExpr)(4))))))->to_string_pretty() == "_let x = 5\n_in  _let y = 3\n     _in  _let z = 1\n          _in  z + 4");
    CHECK((NEW(MultExpr)(NEW(LetExpr)("x", NEW(NumExpr)(5), NEW(AddExpr)(NEW(VarExpr)("x"), NEW(NumExpr)(1))), NEW(NumExpr) (5)))->to_string_pretty() == "(_let x = 5\n _in  x + 1) * 5");
    CHECK((NEW(AddExpr)( NEW(NumExpr) (5), NEW(LetExpr)("x", NEW(NumExpr)(5), NEW(AddExpr)(NEW(VarExpr)("x"), NEW(NumExpr)(1)))))->to_string_pretty() == "5 + _let x = 5\n    _in  x + 1");
    CHECK((NEW(AddExpr)(NEW(LetExpr)("x", NEW(NumExpr)(5), NEW(AddExpr)(NEW(VarExpr)("x"), NEW(NumExpr)(1))), NEW(NumExpr) (5)))->to_string_pretty() == "(_let x = 5\n _in  x + 1) + 5");
    CHECK((NEW(MultExpr)( NEW(NumExpr)(5), NEW(AddExpr)(NEW(LetExpr)("x", NEW(NumExpr)(5), NEW(VarExpr)("x")), NEW(NumExpr) (1))))->to_string_pretty() == "5 * ((_let x = 5\n      _in  x) + 1)");
    CHECK((NEW(AddExpr)(NEW(MultExpr)(NEW(NumExpr)(5), NEW(LetExpr)("x", NEW(NumExpr)(5), NEW(VarExpr)("x"))), NEW(NumExpr) (1)))->to_string_pretty() == "5 * (_let x = 5\n     _in  x) + 1");
    CHECK((NEW(MultExpr)(NEW(NumExpr)(5), NEW(AddExpr)(NEW(LetExpr)("x", NEW(NumExpr)(5), NEW(VarExpr)("x")), NEW(NumExpr) (1))))->to_string_pretty() == "5 * ((_let x = 5\n      _in  x) + 1)");
    CHECK((NEW(AddExpr)( NEW(LetExpr)( "x", NEW(NumExpr)(1), NEW(AddExpr)( NEW(VarExpr)("x"), NEW(NumExpr)(2))), NEW(LetExpr)( "y", NEW(NumExpr)(3), NEW(AddExpr)( NEW(VarExpr)("y"), NEW(NumExpr)(4)))))->to_string_pretty() == "(_let x = 1\n _in  x + 2) + _let y = 3\n               _in  y + 4");
    CHECK ((NEW(MultExpr)( NEW(NumExpr) (5), (NEW(LetExpr)("x", NEW(NumExpr)(5), NEW(LetExpr)("y", NEW(NumExpr)(3), NEW(LetExpr)( "z", NEW(NumExpr)(1), NEW(AddExpr) (NEW(VarExpr)("z"), NEW(NumExpr)(4))))))))->to_string_pretty() == "5 * _let x = 5\n    _in  _let y = 3\n         _in  _let z = 1\n              _in  z + 4");
    CHECK((NEW(MultExpr)( NEW(NumExpr) (5), NEW(LetExpr)("x", NEW(NumExpr)(5), NEW(AddExpr)(NEW(VarExpr)("x"), NEW(NumExpr)(1)))))->to_string_pretty() == "5 * _let x = 5\n    _in  x + 1");
}

TEST_CASE ("EqExpr Pretty Print"){
    CHECK((NEW(EqExpr)(NEW(NumExpr)(-9), NEW(NumExpr)(-7)))->to_string_pretty() == "-9 == -7");
    CHECK((NEW(AddExpr) (NEW(EqExpr)(NEW(NumExpr)(7), NEW(NumExpr)(4)), NEW(NumExpr)(6)))->to_string_pretty() == "(7 == 4) + 6");
    CHECK((NEW(AddExpr) (NEW(NumExpr)(6), NEW(EqExpr)(NEW(NumExpr)(0), NEW(NumExpr)(3))))->to_string_pretty() == "6 + (0 == 3)");
    CHECK((NEW(MultExpr) (NEW(EqExpr)(NEW(NumExpr)(7), NEW(NumExpr)(4)), NEW(NumExpr)(6)))->to_string_pretty() == "(7 == 4) * 6");
    CHECK((NEW(MultExpr) (NEW(NumExpr)(6), NEW(EqExpr)(NEW(NumExpr)(0), NEW(NumExpr)(3))))->to_string_pretty() == "6 * (0 == 3)");
    CHECK((NEW(EqExpr)(NEW(EqExpr)(NEW(NumExpr)(1), NEW(NumExpr)(2)), NEW(EqExpr)(NEW(NumExpr)(3), NEW(NumExpr)(4))))->to_string_pretty() == "(1 == 2) == 3 == 4");
    CHECK((NEW(EqExpr)(
                       NEW(LetExpr)("x",
                                   NEW(NumExpr)(5),
                                   NEW(AddExpr) ( NEW(VarExpr)("x"), NEW(NumExpr)(3))),
                      NEW(LetExpr)( "x",
                                   NEW(NumExpr)(3),
                                   NEW(AddExpr) ( NEW(VarExpr)("x"), NEW(NumExpr)(5)))
                      ))
                      ->to_string_pretty() ==
                      "(_let x = 5\n _in  x + 3) == _let x = 3\n                _in  x + 5");
    CHECK((NEW(EqExpr) (
                       NEW(LetExpr)("x",
                                   NEW(NumExpr)(5),
                                   NEW(VarExpr)("x")),
                       NEW(LetExpr)("x",
                                   NEW(NumExpr)(5),
                                   NEW(VarExpr)("x"))))
          ->to_string_pretty()==
          "(_let x = 5\n _in  x) == _let x = 5\n            _in  x");
    CHECK((NEW(LetExpr)("x",
                NEW(EqExpr)(NEW(NumExpr)(3), NEW(NumExpr)(4)),
                NEW(VarExpr)("x")))
    ->to_string_pretty() ==
     "_let x = 3 == 4\n_in  x");
    CHECK((NEW(LetExpr)("y",
                NEW(NumExpr)(7),
                       NEW(EqExpr)(NEW(VarExpr)("y"), NEW(NumExpr) (6))))
    ->to_string_pretty() ==
     "_let y = 7\n_in  y == 6");
}

TEST_CASE("IfExpr Pretty Print"){
    CHECK((NEW(IfExpr)(NEW(BoolExpr)(true), NEW(NumExpr)(3), NEW(BoolExpr)(false)))->to_string_pretty() == "_if _true\n_then 3\n_else _false");
    CHECK((NEW(LetExpr)("y",
                       NEW(NumExpr)(3),
                       NEW(IfExpr)(NEW(BoolExpr)(true),
                                  NEW(NumExpr)(5),
                                  NEW(NumExpr)(-5))
                       )
           )->to_string_pretty() == "_let y = 3\n_in  _if _true\n     _then 5\n     _else -5");
    CHECK((NEW(EqExpr)(NEW(IfExpr)(NEW(BoolExpr)(true),
                      NEW(NumExpr)(5),
                      NEW(NumExpr)(-5)), NEW(IfExpr)(NEW(BoolExpr)(true),
                                                   NEW(NumExpr)(5),
                                                   NEW(NumExpr)(-5))))->to_string_pretty()== "(_if _true\n _then 5\n _else -5) == _if _true\n              _then 5\n              _else -5");
    
}

TEST_CASE("Matthews PDF Quiz"){
    CHECK((NEW(IfExpr)(NEW(EqExpr)(NEW(NumExpr)(1), NEW(NumExpr)(2)),
                      NEW(NumExpr)(5),
                      NEW(NumExpr)(6)))->interp(Env::empty)->equals(NEW(NumVal)(6)));
    CHECK((NEW(EqExpr)(NEW(NumExpr)(1), NEW(NumExpr)(2)))->interp(Env::empty)->equals(NEW(BoolVal)(false)));
    CHECK((NEW(EqExpr)(NEW(NumExpr)(1), NEW(NumExpr)(1)))->interp(Env::empty)->equals(NEW(BoolVal)(true)));
    CHECK((NEW(EqExpr)(NEW(AddExpr)(NEW(NumExpr)(1), NEW(NumExpr)(2)), NEW(AddExpr)(NEW(NumExpr)(3), NEW(NumExpr)(0))))->interp(Env::empty)->equals(NEW(BoolVal)(true)));
}

TEST_CASE("Nested HW Example"){
    CHECK((NEW(LetExpr)("factrl",
                       NEW(FunExpr)("factrl",
                                   NEW(FunExpr)("x",
                                               NEW(IfExpr)(
                                                          NEW(EqExpr)(
                                                                     NEW(VarExpr)("x"),
                                                                     NEW(NumExpr)(1)),
                                                          NEW(NumExpr)(1),
                                                          NEW(MultExpr)(
                                                                       NEW(VarExpr)("x"),
                                                                       NEW(CallExpr)(
                                                                                    NEW(CallExpr)(
                                                                                                 NEW(VarExpr)("factrl"),
                                                                                                 NEW(VarExpr)("factrl")
                                                                                                 ),
                                                                                    NEW(AddExpr)(
                                                                                                NEW(VarExpr)("x"),
                                                                                                NEW(NumExpr)(-1)
                                                                                                )
                                                                                    )
                                                                       )
                                                          )
                                               )
                                   ),
                       NEW(CallExpr)(
                                    NEW(CallExpr)(
                                                 NEW(VarExpr)("factrl"),
                                                 NEW(VarExpr)("factrl")
                                                 ),
                                    NEW(NumExpr)(10))))->interp(Env::empty)->equals(NEW(NumVal)(3628800)));
}

TEST_CASE("Val Tests"){
    CHECK_THROWS_WITH((NEW(BoolVal)(true))->call(NULL),"Calling not allowed on BoolVals");
    CHECK_THROWS_WITH((NEW(NumVal)(5))->call(NULL), "Calling not allowed on NumVals");
    CHECK_THROWS_WITH((NEW(FunVal)("y", NEW(NumExpr)(5), Env::empty))->is_true(), "Test expression is not a boolean");
    CHECK((NEW(FunVal)("y", NEW(NumExpr)(5), Env::empty))->to_string() == "(_fun (y) 5)");
    CHECK((NEW(FunVal)("x",NEW(NumExpr)(3), Env::empty))->call(NEW(NumVal)(7))->equals(NEW(NumVal)(3)));
    CHECK((NEW(FunVal)("x",NEW(AddExpr)(NEW(NumExpr)(1),NEW(VarExpr)("x")), Env::empty)->call(NEW(NumVal)(3)))->equals(NEW(NumVal)(4)));
    CHECK_THROWS_WITH((NEW(FunVal)("y", NEW(AddExpr)(NEW(NumExpr)(1), NEW(VarExpr)("x")), Env::empty)->call(NEW(NumVal)(3))), "free variable: x");
}

