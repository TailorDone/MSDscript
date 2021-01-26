//
//  expr.cpp
//  MSDscript
//
//  Created by Taylor Dunn on 1/22/21.
//

#include "expr.hpp"
#include "catch.h"

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
