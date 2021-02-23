
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

bool NumExpr::equals(Expr *other){
    NumExpr *other_num = dynamic_cast<NumExpr*>(other);
    if (other_num == NULL){
        return false;
    } else {
        return (this->val == other_num->val);
    }
}

Val* NumExpr::interp(){
    return new NumVal(this->val);
}

bool NumExpr::has_variable(){
    return false;
}

Expr* NumExpr::subst(std::string name, Expr *replacement){
    return this;
}

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

AddExpr::AddExpr(Expr *lhs, Expr *rhs){
    this->lhs = lhs;
    this->rhs = rhs;
}

bool AddExpr::equals(Expr *other){
    AddExpr *other_num = dynamic_cast<AddExpr*>(other);
    if (other_num == NULL){
        return false;
    } else {
        return ((this->lhs)->equals(other_num->lhs)) && ((this->rhs)->equals(other_num->rhs));
    }
}

Val* AddExpr::interp(){
    return (this->lhs->interp()->add_to(this->rhs->interp()));
}

bool AddExpr::has_variable(){
    return (this->lhs->has_variable() || this->rhs->has_variable());
}

Expr* AddExpr::subst(std::string name, Expr *replacement){
    Expr *new_lhs = lhs->subst(name, replacement);
    Expr *new_rhs = rhs->subst(name, replacement);
    return new AddExpr(new_lhs, new_rhs);
}

void AddExpr::print(std::ostream& output){
    Expr *new_lhs = this->lhs;
    Expr *new_rhs = this->rhs;
    output << "(";
    new_lhs->print(output);
    output << "+";
    new_rhs->print(output);
    output<< ")";
}

void AddExpr::pretty_print(std::ostream& output){
    Expr *new_lhs = this->lhs;
    Expr *new_rhs = this->rhs;
    long position = 0;
    long *position_ptr = &position;
    new_lhs->pretty_print_at(output, print_group_add_or_let, position_ptr);
    output << " + ";
    new_rhs->pretty_print_at(output, print_group_none, position_ptr);
}

void AddExpr::pretty_print_at(std::ostream& output, print_mode_t type, long *position){
    Expr *new_lhs = this->lhs;
    Expr *new_rhs = this->rhs;
    if (type == print_group_add || type == print_group_add_or_let || type == print_group_add_mult_or_let){
        output << "(";
    }
    new_lhs->pretty_print_at(output, print_group_add_or_let, position);
    output << " + ";
    new_rhs->pretty_print_at(output, print_group_none, position);
    if (type == print_group_add || type == print_group_add_or_let || type == print_group_add_mult_or_let){
        output << ")";
    }
}
/* *********************************************** */

MultExpr::MultExpr(Expr *lhs, Expr *rhs){
    this->lhs = lhs;
    this->rhs = rhs;
}

bool MultExpr::equals(Expr *other){
    MultExpr *other_num = dynamic_cast<MultExpr*>(other);
    if (other_num == NULL){
        return false;
    } else {
        return ((this->lhs)->equals(other_num->lhs)) && ((this->rhs)->equals(other_num->rhs));
    }
}

Val* MultExpr::interp(){
    return (this->lhs->interp()->mult_to(this->rhs->interp()));
}

bool MultExpr::has_variable(){
    return (this->lhs->has_variable() || this->rhs->has_variable());
}

Expr* MultExpr::subst(std::string name, Expr *replacement){
    Expr *new_lhs = lhs->subst(name, replacement);
    Expr *new_rhs = rhs->subst(name, replacement);
    return new MultExpr(new_lhs, new_rhs);
}

void MultExpr::print(std::ostream& output){
    Expr *new_lhs = this->lhs;
    Expr *new_rhs = this->rhs;
    output << "(";
    new_lhs->print(output);
    output << "*";
    new_rhs->print(output);
    output<< ")";
}

void MultExpr::pretty_print(std::ostream& output){
    Expr *new_lhs = this->lhs;
    Expr *new_rhs = this->rhs;
    long position = 0;
    long *position_ptr = &position;
    new_lhs->pretty_print_at(output, print_group_add_mult_or_let, position_ptr);
    output << " * ";
    new_rhs->pretty_print_at(output, print_group_add, position_ptr);
}

void MultExpr::pretty_print_at(std::ostream& output, print_mode_t type, long *position){
    Expr *new_lhs = this->lhs;
    Expr *new_rhs = this->rhs;
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

bool VarExpr::equals(Expr *other){
    VarExpr *other_var = dynamic_cast<VarExpr*>(other);
    if (other_var == NULL){
        return false;
    } else {
        return (this->name == other_var->name);
    }
}

Val* VarExpr::interp(){
    throw std::runtime_error("No value for variable");
}

bool VarExpr::has_variable(){
    return true;
}

Expr* VarExpr::subst(std::string name, Expr *replacement){
    if(this->name == name){
        return replacement;
    } else {
        return this;
    }
}

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

LetExpr::LetExpr(std::string lhs, Expr *rhs, Expr *body){
    this->lhs = lhs;
    this->rhs = rhs;
    this->body = body;
}
    
bool LetExpr::equals(Expr *other){
    LetExpr *other_expr = dynamic_cast<LetExpr*>(other);
    if (other_expr == NULL){
        return false;
    } else {
        return (((this->lhs == other_expr->lhs)) && ((this->rhs)->equals(other_expr->rhs)) && ((this->body)->equals(other_expr->body)));
    }
}
    
Val* LetExpr::interp(){
    std::string new_lhs = this->lhs;
    Expr* new_rhs = this->rhs;
    Expr* new_body = this->body;
    Val* simp_rhs = new_rhs->interp();
    return new_body->subst(new_lhs, simp_rhs->to_expr())->interp();
}

bool LetExpr::has_variable(){
    return ((this->rhs->has_variable()) || this->body->has_variable());
}

//Always substitute RHS. Body changes iff the variable we are replacing and the bound variable are different
Expr* LetExpr::subst(std::string string, Expr *replacement){
    std::string new_lhs = this->lhs;
    //Always substitute on the right, even if it doesn't replace anything
    Expr *new_rhs = this->rhs->subst(string, replacement);
    Expr *new_body = this->body;
    if(new_lhs!=(string)){
        new_body = new_body->subst(string, replacement);
    }
    return new LetExpr (new_lhs, new_rhs, new_body);
}

void LetExpr::print(std::ostream& output){
    Expr *new_rhs = this->rhs;
    Expr *new_body = this->body;
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
    Expr *new_rhs = this->rhs;
    Expr *new_body = this->body;
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
    Expr *new_rhs = this->rhs;
    Expr *new_body = this->body;
    if (type == print_group_add_or_let || type == print_group_add_mult_or_let){
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
    if (type == print_group_add_or_let || type == print_group_add_mult_or_let){
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

TEST_CASE( "num equals" ){
    CHECK((new NumExpr(0))->equals(new NumExpr(0))==true);
    CHECK((new NumExpr(1))->equals(new NumExpr(1))==true);
    CHECK((new NumExpr(-1))->equals(new NumExpr(-1))==true);
    CHECK((new NumExpr(0))->equals(new NumExpr(1))==false);
    CHECK((new NumExpr(-0))->equals(new NumExpr(0))==true);
    CHECK((new NumExpr(-1))->equals(new NumExpr(1))==false);
    NumExpr *num0 = new NumExpr(0);
    NumExpr *num1 = new NumExpr(1);
    NumExpr *num1b = new NumExpr(1);
    CHECK(num1 ->equals(num1b)==true);
    CHECK(num0 ->equals(num1)==false);
}

TEST_CASE( "add equals" ){
    NumExpr *num0 = new NumExpr(0);
    NumExpr *num1 = new NumExpr(1);
    NumExpr *num1b = new NumExpr(1);
    CHECK((new AddExpr(num0, num1))->equals(new AddExpr(num0, num1)) == true);
    CHECK((new AddExpr(num0, num1))->equals(new AddExpr(num0, num1b)) == true);
    CHECK((new AddExpr(num0, num1))->equals(new AddExpr(num1, num0)) == false);
    CHECK((new AddExpr(new NumExpr(0),new NumExpr(1)))->equals(new AddExpr(new NumExpr(0),new NumExpr(1))) == true);
    CHECK((new AddExpr(new NumExpr(0),new NumExpr(1)))->equals(new AddExpr(new NumExpr(1),new NumExpr(0))) == false);
    CHECK((new AddExpr(new AddExpr(num0, num1),new NumExpr(1)))->equals(new AddExpr(new AddExpr(num0, num1),new NumExpr(1))) == true);
}

TEST_CASE( "mult equals" ){
    NumExpr *num0 = new NumExpr(0);
    NumExpr *num1 = new NumExpr(1);
    NumExpr *num1b = new NumExpr(1);
    CHECK((new MultExpr(num0, num1))->equals(new MultExpr(num0, num1)) == true);
    CHECK((new MultExpr(num0, num1))->equals(new MultExpr(num0, num1b)) == true);
    CHECK((new MultExpr(num0, num1))->equals(new MultExpr(num1, num0)) == false);
    CHECK((new MultExpr(new NumExpr(0),new NumExpr(1)))->equals(new MultExpr(new NumExpr(0),new NumExpr(1))) == true);
    CHECK((new MultExpr(new NumExpr(0),new NumExpr(1)))->equals(new MultExpr(new NumExpr(1),new NumExpr(0))) == false);
    CHECK((new MultExpr(new MultExpr(num0, num1),new NumExpr(1)))->equals(new MultExpr(new MultExpr(num0, num1),new NumExpr(1))) == true);
}

TEST_CASE( "variable equals" ){
    VarExpr *mod = new VarExpr("%");
    VarExpr *percent = new VarExpr("%");
    VarExpr *one = new VarExpr("1");
    VarExpr *word = new VarExpr("word");
    VarExpr *word2 = new VarExpr("word");
    NumExpr *num1 = new NumExpr(1);
    CHECK(mod->equals(percent) == true);
    CHECK(one->equals(num1) == false);
    CHECK((new MultExpr(new VarExpr("*"),new VarExpr("&")))->equals(new MultExpr(new VarExpr("*"),new VarExpr("&"))) == true);
    CHECK((new MultExpr(new VarExpr("*"),new NumExpr(1)))->equals(new MultExpr(new VarExpr("*"),new NumExpr(1))) == true);
    CHECK((new MultExpr(one, num1))->equals(new MultExpr(one, num1)) == true);
    CHECK((new MultExpr(num1, one))->equals(new MultExpr(one, num1)) == false);
    CHECK((word)->equals(word2));
}

TEST_CASE ( "let equals" ){
    std::string name = "x";
    LetExpr *let1 = new LetExpr(name, new NumExpr(5), (new AddExpr (new VarExpr("x"), new NumExpr (4))));
    LetExpr *sameLet1 = new LetExpr(name, new NumExpr(5), (new AddExpr (new VarExpr("x"), new NumExpr (4))));
    LetExpr *let2 = new LetExpr(name, new NumExpr(5), (new AddExpr (new VarExpr("y"), new NumExpr (4))));
    CHECK((let1->equals(sameLet1))==true);
    CHECK((let1->equals(let2))==false);
}

TEST_CASE ( "Object Comparisions" ){
    CHECK((new MultExpr(new NumExpr(0),new NumExpr(1)))->equals(new AddExpr(new NumExpr(1),new NumExpr(0))) == false);
    CHECK((new VarExpr("*"))->equals(new NumExpr(5)) == false);
    CHECK((new AddExpr(new NumExpr(0),new NumExpr(1)))->equals(new VarExpr("%")) == false);
    CHECK((new MultExpr(new NumExpr(0),new NumExpr(1)))->equals(new NumExpr(7)) == false);
    CHECK((new VarExpr("*"))->equals(new MultExpr(new NumExpr(0),new NumExpr(1))) == false);
    CHECK(((new LetExpr("x", new NumExpr(5), (new AddExpr (new VarExpr("x"), new NumExpr (4)))))->equals(new MultExpr(new NumExpr(0),new NumExpr(1))))==false);
}

TEST_CASE ( "Interpret" ){
    CHECK((new NumExpr(5))->interp()->equals(new NumVal(5)));
    CHECK((new NumExpr(-1))->interp()->equals(new NumVal(-1)));
    CHECK((new NumExpr(0))->interp()->equals(new NumVal(0)));
    CHECK((new AddExpr(new NumExpr(2),new NumExpr(4)))->interp()->equals(new NumVal(6)));
    CHECK((new AddExpr(new NumExpr(-10),new NumExpr(7)))->interp()->equals(new NumVal(-3)));
    CHECK((new AddExpr(new NumExpr(-31),new NumExpr(31)))->interp()->equals(new NumVal(0)));
    CHECK((new MultExpr(new NumExpr(2),new NumExpr(4)))->interp()->equals(new NumVal(8)));
    CHECK((new MultExpr(new NumExpr(-5),new NumExpr(-2)))->interp()->equals(new NumVal(10)));
    CHECK((new MultExpr(new NumExpr(5),new NumExpr(-2)))->interp()->equals(new NumVal(-10)));
    CHECK((new LetExpr("x", new NumExpr(5), new AddExpr(new VarExpr("x"), new NumExpr(1))))->interp()->equals(new NumVal(6)));
    CHECK((new LetExpr("x", new AddExpr( new NumExpr(5), new NumExpr (2)), new AddExpr(new VarExpr("x"), new NumExpr(1))))->interp()->equals(new NumVal(8)));
    CHECK((new LetExpr("x", new NumExpr(5), new AddExpr(new LetExpr("y", new NumExpr(3), new AddExpr(new VarExpr("y"), new NumExpr(2))), new VarExpr("x"))))->interp()->equals(new NumVal(10)));
    CHECK((new LetExpr("x", new NumExpr(5), new LetExpr("x", new AddExpr( new VarExpr("x"), new NumExpr(2)), new AddExpr(new VarExpr("x"), new NumExpr(1)))))->interp()->equals(new NumVal(8)));
    CHECK((new AddExpr(new MultExpr(new NumExpr(5), new LetExpr("x", new NumExpr(5), new VarExpr("x"))), new NumExpr (1)))->interp()->equals(new NumVal(26)));
    CHECK((new MultExpr( new NumExpr(5), new AddExpr(new LetExpr("x", new NumExpr(5), new VarExpr("x")), new NumExpr (1))))->interp()->equals(new NumVal(30)));
    CHECK_THROWS_WITH((new VarExpr("x"))->interp(), "No value for variable" );
    CHECK_THROWS_WITH((new VarExpr("&"))->interp(), "No value for variable" );
    CHECK_THROWS_WITH((new VarExpr(""))->interp(), "No value for variable" );
    CHECK_THROWS_WITH((new AddExpr(new VarExpr("b"),new NumExpr(31)))->interp(), "No value for variable" );
    CHECK_THROWS_WITH((new MultExpr(new NumExpr(3),new VarExpr("a")))->interp(), "No value for variable" );
    CHECK_THROWS_WITH((new LetExpr("x", new VarExpr("t"), new AddExpr(new VarExpr("x"), new NumExpr(1))))->interp(), "No value for variable");
}

TEST_CASE ( "Has Variable" ){
    CHECK(((new NumExpr(5))->has_variable() == false));
    CHECK((new AddExpr(new NumExpr(2),new NumExpr(4)))->has_variable() == false);
    CHECK((new AddExpr(new NumExpr(2),new VarExpr("&")))->has_variable() == true);
    CHECK((new MultExpr(new NumExpr(2),new NumExpr(4)))->has_variable() == false);
    CHECK((new MultExpr(new VarExpr("/"),new NumExpr(4)))->has_variable() == true);
    CHECK((new VarExpr("*"))->has_variable() == true);
    CHECK((new LetExpr("x", new NumExpr(5), (new AddExpr (new VarExpr("x"), new NumExpr (4)))))->has_variable() == true);
    CHECK((new LetExpr("x", new AddExpr (new VarExpr("x"), new NumExpr (4)), new NumExpr (4)))->has_variable() == true);
    CHECK((new LetExpr("x", new NumExpr (5), new NumExpr (4)))->has_variable() == false);
}

TEST_CASE ( "Substitution" ){
    CHECK((new NumExpr(1))->subst("a", new NumExpr(4))->equals(new NumExpr(1)) == true);
    CHECK((new NumExpr(1))->subst("a", new NumExpr(4))->equals(new NumExpr(4)) == false);
    CHECK((new VarExpr("a"))->subst("a", new VarExpr("c"))->equals(new VarExpr("c"))== true);
    CHECK((new VarExpr("a"))->subst("b", new VarExpr("c"))->equals(new VarExpr("a"))== true);
    CHECK((new MultExpr(new VarExpr("x"), new NumExpr(7)))->subst("x", new VarExpr("y"))->equals(new MultExpr(new VarExpr("y"), new NumExpr(7)))==true);
    CHECK((new AddExpr(new VarExpr("x"), new NumExpr(7)))->subst("x", new VarExpr("y"))->equals(new AddExpr(new VarExpr("y"), new NumExpr(7)))==true);
    //Always substitue RHS. Body changes iff the variable we are replacing and the bound variable are different
    //
    //No Change
    //_let x = 1
    //_in x + 2 ->subst(x, y+3)
    Expr *let1 = new LetExpr("x",
                         new NumExpr(1),
                         new AddExpr(new VarExpr("x"), new NumExpr(2)));
    CHECK((let1)->subst("x", new AddExpr(new VarExpr("y"), new NumExpr(3)))->equals(let1));
    //Only change RHS
    //_let x = x
    //_in x + 2 ->subst(x, 5)
    //=
    //_let x = 5
    //_in x + 2
    Expr *let2 = new LetExpr("x",
                         new VarExpr("x"),
                         new AddExpr(new VarExpr("x"), new NumExpr(2)));
    CHECK((let2->subst("x", new NumExpr(5))
           ->equals(new LetExpr("x",
                            new NumExpr(5),
                            new AddExpr (new VarExpr("x"), new NumExpr(2))))));
    //Only change Body
    //_let x = 8
    //_in x+y-> subst("y", 9)
    // =
    //_let x = 8
    //_in x+9
    Expr *let3 = new LetExpr ("x",
                          new NumExpr(8),
                          new AddExpr (new VarExpr("x"), new VarExpr("y")));
    CHECK((let3-> subst("y", new NumExpr(9)))
          ->equals(new LetExpr ("x",
                            new NumExpr(8),
                            new AddExpr (new VarExpr("x"), new NumExpr(9)))));
    //Change RHS and Body
    //_let x = y
    //_in x+y-> subst("y", 9)
    // =
    //_let x = 9
    //_in x+9
    Expr *let4 = new LetExpr ("x",
                          new VarExpr ("y"),
                          new AddExpr (new VarExpr("x"), new VarExpr("y")));
    CHECK((let4-> subst("y", new NumExpr(9)))
          ->equals(new LetExpr ("x",
                            new NumExpr(9),
                            new AddExpr (new VarExpr("x"), new NumExpr(9)))));
}

TEST_CASE ( "Print" ){
    CHECK ((new NumExpr(5))->to_string() == "5");
    CHECK ((new VarExpr("x"))->to_string() == "x");
    CHECK ((new AddExpr(new NumExpr(5), new NumExpr(4)))->to_string() == "(5+4)");
    CHECK (((new AddExpr(new VarExpr("x"), (new MultExpr(new NumExpr(2),new NumExpr(4)))))->to_string())=="(x+(2*4))");
    CHECK ((new AddExpr( new MultExpr(new NumExpr(3), new NumExpr(2)), new MultExpr( new NumExpr(5), new NumExpr(6))))->to_string() == "((3*2)+(5*6))");
    CHECK ((new LetExpr("x", new NumExpr(5), new AddExpr(new VarExpr("x"), new NumExpr(1))))->to_string() == "(_let x=5 _in (x+1))");
    CHECK ((new LetExpr("x", new NumExpr(5), new AddExpr(new LetExpr("y", new NumExpr(3), new AddExpr(new VarExpr("y"), new NumExpr(2))), new VarExpr("x"))))->to_string() == "(_let x=5 _in ((_let y=3 _in (y+2))+x))");
}

TEST_CASE ( "Pretty Print Basic" ){
    CHECK ((new NumExpr(5))->to_string_pretty() == "5");
    CHECK ((new VarExpr("x"))->to_string_pretty() == "x");
    CHECK ((new AddExpr(new NumExpr(5), new NumExpr(4)))->to_string_pretty() == "5 + 4");
    CHECK ((new MultExpr(new NumExpr(5), new NumExpr(4)))->to_string_pretty() == "5 * 4");
    CHECK ((new AddExpr(new VarExpr("a"), new VarExpr("b")))->to_string_pretty() == "a + b");
    CHECK ((new MultExpr(new VarExpr("a"), new VarExpr("b")))->to_string_pretty() == "a * b");
}

TEST_CASE ( "Pretty Print Moderate" ){
    CHECK ((new AddExpr(new AddExpr( new NumExpr(3), new NumExpr(4)), new VarExpr("a")))->to_string_pretty() == "(3 + 4) + a");
    CHECK ((new AddExpr(new NumExpr(3), new AddExpr( new NumExpr(4), new NumExpr(5))))->to_string_pretty() == "3 + 4 + 5");
    CHECK ((new AddExpr(new NumExpr(3), new MultExpr( new NumExpr(4), new VarExpr("b"))))->to_string_pretty() == "3 + 4 * b");
    CHECK ((new AddExpr(new MultExpr( new NumExpr(3), new NumExpr(4)), new NumExpr(5)))->to_string_pretty() == "3 * 4 + 5");
    CHECK ((new MultExpr(new AddExpr( new NumExpr(3), new VarExpr("a")), new NumExpr(5)))->to_string_pretty() == "(3 + a) * 5");
    CHECK ((new MultExpr(new VarExpr("b"), new AddExpr( new NumExpr(4), new NumExpr(5))))->to_string_pretty() == "b * (4 + 5)");
    CHECK ((new MultExpr(new NumExpr(3), new MultExpr( new NumExpr(4), new NumExpr(5))))->to_string_pretty() == "3 * 4 * 5");
    CHECK ((new MultExpr(new MultExpr( new VarExpr("a"), new NumExpr(4)), new NumExpr(5)))->to_string_pretty() == "(a * 4) * 5");
}

TEST_CASE ( "Pretty Print Advanced" ){
    CHECK ((new AddExpr(new AddExpr( new NumExpr(3), new NumExpr(4)), new AddExpr( new NumExpr(5), new VarExpr("a"))))->to_string_pretty() == "(3 + 4) + 5 + a");
    CHECK ((new AddExpr(new MultExpr( new VarExpr("a"), new NumExpr(4)), new MultExpr( new NumExpr(5), new NumExpr(6))))->to_string_pretty() == "a * 4 + 5 * 6");
    CHECK ((new AddExpr(new AddExpr( new NumExpr(3), new VarExpr("a")), new MultExpr( new NumExpr(5), new NumExpr(6))))->to_string_pretty() == "(3 + a) + 5 * 6");
    CHECK ((new AddExpr(new MultExpr( new VarExpr("b"), new VarExpr("a")), new AddExpr( new NumExpr(5), new NumExpr(6))))->to_string_pretty() == "b * a + 5 + 6");
    CHECK ((new MultExpr(new AddExpr( new NumExpr(3), new NumExpr(4)), new AddExpr( new NumExpr(5), new VarExpr("b"))))->to_string_pretty() == "(3 + 4) * (5 + b)");
    CHECK ((new MultExpr(new MultExpr( new NumExpr(3), new NumExpr(4)), new MultExpr( new NumExpr(5), new NumExpr(6))))->to_string_pretty() == "(3 * 4) * 5 * 6");
    CHECK ((new MultExpr(new AddExpr( new NumExpr(3), new VarExpr("b")), new MultExpr( new VarExpr("a"), new NumExpr(6))))->to_string_pretty() == "(3 + b) * a * 6");
    CHECK ((new MultExpr(new MultExpr( new NumExpr(3), new NumExpr(4)), new AddExpr( new NumExpr(5), new VarExpr("a"))))->to_string_pretty() == "(3 * 4) * (5 + a)");
}

TEST_CASE ( "Pretty Print Extreme" ){
    CHECK ((new MultExpr (new AddExpr (new VarExpr ("a"), new VarExpr ("b")), new NumExpr (7)))->to_string_pretty() == "(a + b) * 7");
    CHECK ((new MultExpr (new MultExpr (new AddExpr (new VarExpr ("a"), new VarExpr ("b")), new NumExpr (7)), new NumExpr (6)))->to_string_pretty() == "((a + b) * 7) * 6");
    CHECK ((new MultExpr (new MultExpr (new MultExpr (new AddExpr (new VarExpr ("a"), new VarExpr ("b")), new NumExpr (7)), new NumExpr (6)), new VarExpr ("c")))->to_string_pretty() == "(((a + b) * 7) * 6) * c");
    CHECK ((new MultExpr(new MultExpr(new MultExpr( new NumExpr(3), new NumExpr(4)), new MultExpr( new NumExpr(5), new NumExpr(6))), new VarExpr ("b")))->to_string_pretty()=="((3 * 4) * 5 * 6) * b");
    CHECK ((new MultExpr(new MultExpr( new MultExpr( new NumExpr(3), new NumExpr(4)), new MultExpr( new NumExpr(5), new NumExpr(6))), new AddExpr( new NumExpr(7), new NumExpr(8))))->to_string_pretty() == "((3 * 4) * 5 * 6) * (7 + 8)");
    CHECK ((new MultExpr(new MultExpr( new AddExpr( new VarExpr("a"), new VarExpr("b")), new NumExpr(7)), new MultExpr( new NumExpr(6), new VarExpr("c"))))->to_string_pretty() == "((a + b) * 7) * 6 * c");
}

TEST_CASE ( "Let Pretty Print" ){
    CHECK ((new LetExpr("x", new NumExpr(5), new AddExpr(new VarExpr("x"), new NumExpr(1))))->to_string_pretty() == "_let x = 5\n_in  x + 1");
    CHECK ((new LetExpr("x", new NumExpr(5), new LetExpr("x", new NumExpr(1), new AddExpr( new VarExpr("x"), new NumExpr(3)))))->to_string_pretty() == "_let x = 5\n_in  _let x = 1\n     _in  x + 3");
    CHECK ((new LetExpr("x", new NumExpr(5), new AddExpr(new LetExpr("y", new NumExpr(3), new AddExpr(new VarExpr("y"), new NumExpr(2))), new VarExpr("x"))))->to_string_pretty() == "_let x = 5\n_in  (_let y = 3\n      _in  y + 2) + x");
    CHECK ((new LetExpr("x", new NumExpr(5), new LetExpr("y", new NumExpr(3), new LetExpr( "z", new NumExpr(1), new AddExpr (new VarExpr("z"), new NumExpr(4))))))->to_string_pretty() == "_let x = 5\n_in  _let y = 3\n     _in  _let z = 1\n          _in  z + 4");
    CHECK((new MultExpr(new LetExpr("x", new NumExpr(5), new AddExpr(new VarExpr("x"), new NumExpr(1))), new NumExpr (5)))->to_string_pretty() == "(_let x = 5\n _in  x + 1) * 5");
    CHECK((new AddExpr( new NumExpr (5), new LetExpr("x", new NumExpr(5), new AddExpr(new VarExpr("x"), new NumExpr(1)))))->to_string_pretty() == "5 + _let x = 5\n    _in  x + 1");
    CHECK((new AddExpr(new LetExpr("x", new NumExpr(5), new AddExpr(new VarExpr("x"), new NumExpr(1))), new NumExpr (5)))->to_string_pretty() == "(_let x = 5\n _in  x + 1) + 5");
    CHECK((new MultExpr( new NumExpr(5), new AddExpr(new LetExpr("x", new NumExpr(5), new VarExpr("x")), new NumExpr (1))))->to_string_pretty() == "5 * ((_let x = 5\n      _in  x) + 1)");
    CHECK((new AddExpr(new MultExpr(new NumExpr(5), new LetExpr("x", new NumExpr(5), new VarExpr("x"))), new NumExpr (1)))->to_string_pretty() == "5 * (_let x = 5\n     _in  x) + 1");
    CHECK((new MultExpr(new NumExpr(5), new AddExpr(new LetExpr("x", new NumExpr(5), new VarExpr("x")), new NumExpr (1))))->to_string_pretty() == "5 * ((_let x = 5\n      _in  x) + 1)");
    CHECK((new AddExpr( new LetExpr( "x", new NumExpr(1), new AddExpr( new VarExpr("x"), new NumExpr(2))), new LetExpr( "y", new NumExpr(3), new AddExpr( new VarExpr("y"), new NumExpr(4)))))->to_string_pretty() == "(_let x = 1\n _in  x + 2) + _let y = 3\n               _in  y + 4");
    CHECK ((new MultExpr( new NumExpr (5), (new LetExpr("x", new NumExpr(5), new LetExpr("y", new NumExpr(3), new LetExpr( "z", new NumExpr(1), new AddExpr (new VarExpr("z"), new NumExpr(4))))))))->to_string_pretty() == "5 * _let x = 5\n    _in  _let y = 3\n         _in  _let z = 1\n              _in  z + 4");
    CHECK((new MultExpr( new NumExpr (5), new LetExpr("x", new NumExpr(5), new AddExpr(new VarExpr("x"), new NumExpr(1)))))->to_string_pretty() == "5 * _let x = 5\n    _in  x + 1");
}
