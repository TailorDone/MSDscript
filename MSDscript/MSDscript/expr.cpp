//
//  expr.cpp
//  MSDscript
//
//  Created by Taylor Dunn on 1/22/21.
//

#include "expr.hpp"
#include "catch.h"
#include <stdexcept>

Num::Num(int val){
    this->val = val;
}

bool Num::equals(Expr *other){
    Num *other_num = dynamic_cast<Num*>(other);
    if (other_num == NULL){
        return false;
    } else {
        return (this->val == other_num->val);
    }
}

int Num::interp(){
    return this->val;
}

bool Num::has_variable(){
    return false;
}

Expr* Num::subst(std::string string, Expr *a){
    return this;
}

Add::Add(Expr *lhs, Expr *rhs){
    this->lhs = lhs;
    this->rhs = rhs;
}

bool Add::equals(Expr *other){
    Add *other_num = dynamic_cast<Add*>(other);
    if (other_num == NULL){
        return false;
    } else {
        return ((this->lhs)->equals(other_num->lhs)) && ((this->rhs)->equals(other_num->rhs));
    }
}

int Add::interp(){
    return (this->lhs->interp() + this->rhs->interp());
}

bool Add::has_variable(){
    return (this->lhs->has_variable() || this->rhs->has_variable());
}

Expr* Add::subst(std::string string, Expr *a){
    this->lhs = lhs->subst(string, a);
    this->rhs = rhs->subst(string, a);
    return this;
}

Mult::Mult(Expr *lhs, Expr *rhs){
    this->lhs = lhs;
    this->rhs = rhs;
}

bool Mult::equals(Expr *other){
    Mult *other_num = dynamic_cast<Mult*>(other);
    if (other_num == NULL){
        return false;
    } else {
        return ((this->lhs)->equals(other_num->lhs)) && ((this->rhs)->equals(other_num->rhs));
    }
}

int Mult::interp(){
    return (this->lhs->interp() * this->rhs->interp());
}

bool Mult::has_variable(){
    return (this->lhs->has_variable() || this->rhs->has_variable());
}

Expr* Mult::subst(std::string string, Expr *a){
    this->lhs = lhs->subst(string, a);
    this->rhs = rhs->subst(string, a);
    return this;
}

Variable::Variable(std::string val){
    this->val = val;
}

bool Variable::equals(Expr *other){
    Variable *other_var = dynamic_cast<Variable*>(other);
    if (other_var == NULL){
        return false;
    } else {
        return (this->val == other_var->val);
    }
}

int Variable::interp(){
    throw std::runtime_error("No value for variable");
}

bool Variable::has_variable(){
    return true;
}

Expr* Variable::subst(std::string string, Expr *a){
    if(this->val == string){
        return a;
    } else {
        return this;
    }
}

TEST_CASE( "num equals" ){
    CHECK((new Num(0))->equals(new Num(0))==true);
    CHECK((new Num(1))->equals(new Num(1))==true);
    CHECK((new Num(-1))->equals(new Num(-1))==true);
    CHECK((new Num(0))->equals(new Num(1))==false);
    CHECK((new Num(-0))->equals(new Num(0))==true);
    CHECK((new Num(-1))->equals(new Num(1))==false);
    Num *num0 = new Num(0);
    Num *num1 = new Num(1);
    Num *num1b = new Num(1);
    CHECK(num1 ->equals(num1b)==true);
    CHECK(num0 ->equals(num1)==false);
}

TEST_CASE( "add equals" ){
    Num *num0 = new Num(0);
    Num *num1 = new Num(1);
    Num *num1b = new Num(1);
    CHECK((new Add(num0, num1))->equals(new Add(num0, num1)) == true);
    CHECK((new Add(num0, num1))->equals(new Add(num0, num1b)) == true);
    CHECK((new Add(num0, num1))->equals(new Add(num1, num0)) == false);
    CHECK((new Add(new Num(0),new Num(1)))->equals(new Add(new Num(0),new Num(1))) == true);
    CHECK((new Add(new Num(0),new Num(1)))->equals(new Add(new Num(1),new Num(0))) == false);
    CHECK((new Add(new Add(num0, num1),new Num(1)))->equals(new Add(new Add(num0, num1),new Num(1))) == true);
}

TEST_CASE( "mult equals" ){
    Num *num0 = new Num(0);
    Num *num1 = new Num(1);
    Num *num1b = new Num(1);
    CHECK((new Mult(num0, num1))->equals(new Mult(num0, num1)) == true);
    CHECK((new Mult(num0, num1))->equals(new Mult(num0, num1b)) == true);
    CHECK((new Mult(num0, num1))->equals(new Mult(num1, num0)) == false);
    CHECK((new Mult(new Num(0),new Num(1)))->equals(new Mult(new Num(0),new Num(1))) == true);
    CHECK((new Mult(new Num(0),new Num(1)))->equals(new Mult(new Num(1),new Num(0))) == false);
    CHECK((new Mult(new Mult(num0, num1),new Num(1)))->equals(new Mult(new Mult(num0, num1),new Num(1))) == true);
}

TEST_CASE( "variable equals" ){
    Variable *mod = new Variable("%");
    Variable *percent = new Variable("%");
    Variable *one = new Variable("1");
    Num *num1 = new Num(1);
    CHECK(mod->equals(percent) == true);
    CHECK(one->equals(num1) == false);
    CHECK((new Mult(new Variable("*"),new Variable("&")))->equals(new Mult(new Variable("*"),new Variable("&"))) == true);
    CHECK((new Mult(new Variable("*"),new Num(1)))->equals(new Mult(new Variable("*"),new Num(1))) == true);
    CHECK((new Mult(one, num1))->equals(new Mult(one, num1)) == true);
    CHECK((new Mult(num1, one))->equals(new Mult(one, num1)) == false);
}

TEST_CASE ( "Object Comparisions" ){
    CHECK((new Mult(new Num(0),new Num(1)))->equals(new Add(new Num(1),new Num(0))) == false);
    CHECK((new Variable("*"))->equals(new Num(5)) == false);
    CHECK((new Add(new Num(0),new Num(1)))->equals(new Variable("%")) == false);
    CHECK((new Mult(new Num(0),new Num(1)))->equals(new Num(7)) == false);
    CHECK((new Variable("*"))->equals(new Mult(new Num(0),new Num(1))) == false);
}


TEST_CASE ( "Interpret" ){
    CHECK((new Num(5))->interp() == 5);
    CHECK((new Num(-1))->interp() == -1);
    CHECK((new Num(0))->interp() == 0);
    CHECK((new Add(new Num(2),new Num(4)))->interp() == 6);
    CHECK((new Add(new Num(-10),new Num(7)))->interp() == -3);
    CHECK((new Add(new Num(-31),new Num(31)))->interp() == 0);
    CHECK((new Mult(new Num(2),new Num(4)))->interp() == 8);
    CHECK((new Mult(new Num(-5),new Num(-2)))->interp() == 10);
    CHECK((new Mult(new Num(5),new Num(-2)))->interp() == -10);
    CHECK_THROWS_WITH( (new Variable("x"))->interp(), "No value for variable" );
    CHECK_THROWS_WITH( (new Variable("&"))->interp(), "No value for variable" );
    CHECK_THROWS_WITH( (new Variable(""))->interp(), "No value for variable" );
    CHECK_THROWS_WITH( (new Add(new Variable("b"),new Num(31)))->interp(), "No value for variable" );
    CHECK_THROWS_WITH( (new Mult(new Num(3),new Variable("a")))->interp(), "No value for variable" );
}

TEST_CASE ( "Has Variable" ){
    CHECK(((new Num(5))->has_variable() == false));
    CHECK((new Add(new Num(2),new Num(4)))->has_variable()== false);
    CHECK((new Add(new Num(2),new Variable("&")))->has_variable() == true);
    CHECK((new Mult(new Num(2),new Num(4)))->has_variable()== false);
    CHECK((new Mult(new Variable("/"),new Num(4)))->has_variable()== true);
    CHECK((new Variable("*"))->has_variable() == true);
}

TEST_CASE ( "Substitution" ){
    CHECK((new Num(1))->subst("a", new Num(4))->equals(new Num(1)) == true);
    CHECK((new Num(1))->subst("a", new Num(4))->equals(new Num(4)) == false);
    CHECK((new Variable("a"))->subst("a", new Variable("c"))->equals(new Variable("c"))== true);
    CHECK((new Variable("a"))->subst("b", new Variable("c"))->equals(new Variable("a"))== true);
    CHECK((new Mult(new Variable("x"), new Num(7)))->subst("x", new Variable("y"))->equals(new Mult(new Variable("y"), new Num(7)))==true);
    CHECK((new Add(new Variable("x"), new Num(7)))->subst("x", new Variable("y"))->equals(new Add(new Variable("y"), new Num(7)))==true);
}
