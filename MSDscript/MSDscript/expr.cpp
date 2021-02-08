
//
//  expr.cpp
//  MSDscript
//
//  Created by Taylor Dunn on 1/22/21.
//

#include "expr.hpp"
#include "catch.h"
#include <stdexcept>

/* *********************************************** */

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

Expr* Num::subst(std::string name, Expr *replacement){
    return this;
}

void Num::print(std::ostream& output){
    output << this->val;
}

void Num::pretty_print(std::ostream& output){
    pretty_print_at(output, print_group_none, 0);
}

void Num::pretty_print_at(std::ostream& output, print_mode_t type, long position){
    output << this->val;
}

/* *********************************************** */

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

Expr* Add::subst(std::string name, Expr *replacement){
    Expr *new_lhs = lhs->subst(name, replacement);
    Expr *new_rhs = rhs->subst(name, replacement);
    return new Add(new_lhs, new_rhs);
}

void Add::print(std::ostream& output){
    Expr *new_lhs = this->lhs;
    Expr *new_rhs = this->rhs;
    output << "(";
    new_lhs->print(output);
    output << "+";
    new_rhs->print(output);
    output<< ")";
}

void Add::pretty_print(std::ostream& output){
    Expr *new_lhs = this->lhs;
    Expr *new_rhs = this->rhs;
    new_lhs->pretty_print_at(output, print_group_add, 0);
    output << " + ";
    new_rhs->pretty_print_at(output, print_group_none, 0);
}

void Add::pretty_print_at(std::ostream& output, print_mode_t type, long position){
    Expr *new_lhs = this->lhs;
    Expr *new_rhs = this->rhs;
    if (type == print_group_add || type == print_group_add_or_mult){
        output << "(";
    }
    new_lhs->pretty_print_at(output, print_group_add, position);
    output << " + ";
    new_rhs->pretty_print_at(output, print_group_none, position);
    if (type == print_group_add || type == print_group_add_or_mult){
        output << ")";
    }
}
/* *********************************************** */

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

Expr* Mult::subst(std::string name, Expr *replacement){
    Expr *new_lhs = lhs->subst(name, replacement);
    Expr *new_rhs = rhs->subst(name, replacement);
    return new Mult(new_lhs, new_rhs);
}

void Mult::print(std::ostream& output){
    Expr *new_lhs = this->lhs;
    Expr *new_rhs = this->rhs;
    output << "(";
    new_lhs->print(output);
    output << "*";
    new_rhs->print(output);
    output<< ")";
}

void Mult::pretty_print(std::ostream& output){
    Expr *new_lhs = this->lhs;
    Expr *new_rhs = this->rhs;
    new_lhs->pretty_print_at(output, print_group_add_or_mult, 0);
    output << " * ";
    new_rhs->pretty_print_at(output, print_group_add, 0);
}

void Mult::pretty_print_at(std::ostream& output, print_mode_t type, long position){
    Expr *new_lhs = this->lhs;
    Expr *new_rhs = this->rhs;
    if (type == print_group_add_or_mult){
        output << "(";
    }
    new_lhs->pretty_print_at(output, print_group_add_or_mult, position);
    output << " * ";
    new_rhs->pretty_print_at(output, print_group_add, position);
    if (type == print_group_add_or_mult){
        output << ")";
    }
}

/* *********************************************** */

Variable::Variable(std::string name){
    this->name = name;
}

bool Variable::equals(Expr *other){
    Variable *other_var = dynamic_cast<Variable*>(other);
    if (other_var == NULL){
        return false;
    } else {
        return (this->name == other_var->name);
    }
}

int Variable::interp(){
    throw std::runtime_error("No value for variable");
}

bool Variable::has_variable(){
    return true;
}

Expr* Variable::subst(std::string name, Expr *replacement){
    if(this->name == name){
        return replacement;
    } else {
        return this;
    }
}

void Variable::print(std::ostream& output){
    output << this->name;
}

void Variable::pretty_print(std::ostream& output){
    pretty_print_at(output, print_group_none, 0);
}

void Variable::pretty_print_at(std::ostream& output, print_mode_t type, long position){
    output << this->name;
}
/* *********************************************** */

Let::Let(std::string lhs, Expr *rhs, Expr *body){
    this->lhs = lhs;
    this->rhs = rhs;
    this->body = body;
}
    
bool Let::equals(Expr *other){
    Let *other_expr = dynamic_cast<Let*>(other);
    if (other_expr == NULL){
        return false;
    } else {
        return (((this->lhs == other_expr->lhs)) && ((this->rhs)->equals(other_expr->rhs)) && ((this->body)->equals(other_expr->body)));
    }
}
    
int Let::interp(){
    std::string new_lhs = this->lhs;
    Expr* new_rhs = this->rhs;
    Expr* new_body = this->body;
    int simp_rhs = new_rhs->interp();
    new_body = new_body->subst(new_lhs, new Num(simp_rhs));
    return new_body->interp();
}

bool Let::has_variable(){
    return ((this->rhs->has_variable()) || this->body->has_variable());
}
Expr* Let::subst(std::string string, Expr *replacement){
    Expr *new_body = this->body;
    std::string new_lhs = this->lhs;
    Expr *new_rhs = rhs->subst(string, replacement);
    return new_body->subst(new_lhs, new_rhs);
}

void Let::print(std::ostream& output){
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
void Let::pretty_print(std::ostream& output){
    std::string new_lhs = this->lhs;
    Expr *new_rhs = this->rhs;
    Expr *new_body = this->body;
    output << "_let " << new_lhs << " = ";
    new_rhs->pretty_print_at(output, print_group_let, 0);
    output << "\n";
    long new_line_pos = output.tellp();
    output << "_in  ";
    new_body->pretty_print_at(output, print_group_let, new_line_pos);
}

void Let::pretty_print_at(std::ostream& output, print_mode_t type, long position){
    std::string new_lhs = this->lhs;
    Expr *new_rhs = this->rhs;
    Expr *new_body = this->body;
    if (type == print_group_add || type == print_group_add_or_mult){
        output << "(";
    }
    long curr_let_pos = output.tellp();
    output << "_let " << new_lhs << " = ";
    new_rhs->pretty_print_at(output, print_group_let, position);
    output << "\n";
    long new_line_pos = output.tellp();
    long spaces = curr_let_pos - position;
    int space_count = 0;
    while (space_count < spaces){
        output << " ";
        space_count++;
    }
    output << "_in  ";
    new_body->pretty_print_at(output, print_group_let, new_line_pos);
    if (type == print_group_add || type == print_group_add_or_mult){
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

TEST_CASE ( "let equals" ){
    std::string name = "x";
    Let *let1 = new Let(name, new Num(5), (new Add (new Variable("x"), new Num (4))));
    Let *sameLet1 = new Let(name, new Num(5), (new Add (new Variable("x"), new Num (4))));
    Let *let2 = new Let(name, new Num(5), (new Add (new Variable("y"), new Num (4))));
    CHECK((let1->equals(sameLet1))==true);
    CHECK((let1->equals(let2))==false);
}

TEST_CASE ( "Object Comparisions" ){
    CHECK((new Mult(new Num(0),new Num(1)))->equals(new Add(new Num(1),new Num(0))) == false);
    CHECK((new Variable("*"))->equals(new Num(5)) == false);
    CHECK((new Add(new Num(0),new Num(1)))->equals(new Variable("%")) == false);
    CHECK((new Mult(new Num(0),new Num(1)))->equals(new Num(7)) == false);
    CHECK((new Variable("*"))->equals(new Mult(new Num(0),new Num(1))) == false);
    CHECK(((new Let("x", new Num(5), (new Add (new Variable("x"), new Num (4)))))->equals(new Mult(new Num(0),new Num(1))))==false);
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
    CHECK((new Let("x", new Num(5), new Add(new Variable("x"), new Num(1))))->interp() == 6);
    CHECK((new Let("x", new Add( new Num(5), new Num (2)), new Add(new Variable("x"), new Num(1))))->interp() == 8);
    CHECK((new Let("x", new Num(5), new Add(new Let("y", new Num(3), new Add(new Variable("y"), new Num(2))), new Variable("x"))))->interp() == 10);
    CHECK((new Let("x", new Num(5), new Let("x", new Add( new Variable("x"), new Num(2)), new Add(new Variable("x"), new Num(1)))))->interp() == 8);
    CHECK((new Add(new Mult(new Num(5), new Let("x", new Num(5), new Variable("x"))), new Num (1)))->interp() == 26);
    CHECK((new Mult( new Num(5), new Add(new Let("x", new Num(5), new Variable("x")), new Num (1))))->interp() == 30);
    CHECK_THROWS_WITH((new Variable("x"))->interp(), "No value for variable" );
    CHECK_THROWS_WITH((new Variable("&"))->interp(), "No value for variable" );
    CHECK_THROWS_WITH((new Variable(""))->interp(), "No value for variable" );
    CHECK_THROWS_WITH((new Add(new Variable("b"),new Num(31)))->interp(), "No value for variable" );
    CHECK_THROWS_WITH((new Mult(new Num(3),new Variable("a")))->interp(), "No value for variable" );
    CHECK_THROWS_WITH((new Let("x", new Variable("t"), new Add(new Variable("x"), new Num(1))))->interp(), "No value for variable");
}

TEST_CASE ( "Has Variable" ){
    CHECK(((new Num(5))->has_variable() == false));
    CHECK((new Add(new Num(2),new Num(4)))->has_variable() == false);
    CHECK((new Add(new Num(2),new Variable("&")))->has_variable() == true);
    CHECK((new Mult(new Num(2),new Num(4)))->has_variable() == false);
    CHECK((new Mult(new Variable("/"),new Num(4)))->has_variable() == true);
    CHECK((new Variable("*"))->has_variable() == true);
    CHECK((new Let("x", new Num(5), (new Add (new Variable("x"), new Num (4)))))->has_variable() == true);
    CHECK((new Let("x", new Add (new Variable("x"), new Num (4)), new Num (4)))->has_variable() == true);
    CHECK((new Let("x", new Num (5), new Num (4)))->has_variable() == false);
}

TEST_CASE ( "Substitution" ){
    CHECK((new Num(1))->subst("a", new Num(4))->equals(new Num(1)) == true);
    CHECK((new Num(1))->subst("a", new Num(4))->equals(new Num(4)) == false);
    CHECK((new Variable("a"))->subst("a", new Variable("c"))->equals(new Variable("c"))== true);
    CHECK((new Variable("a"))->subst("b", new Variable("c"))->equals(new Variable("a"))== true);
    CHECK((new Mult(new Variable("x"), new Num(7)))->subst("x", new Variable("y"))->equals(new Mult(new Variable("y"), new Num(7)))==true);
    CHECK((new Add(new Variable("x"), new Num(7)))->subst("x", new Variable("y"))->equals(new Add(new Variable("y"), new Num(7)))==true);
}

TEST_CASE ( "Print" ){
    CHECK ((new Num(5))->to_string() == "5");
    CHECK ((new Variable("x"))->to_string() == "x");
    CHECK ((new Add(new Num(5), new Num(4)))->to_string() == "(5+4)");
    CHECK (((new Add(new Variable("x"), (new Mult(new Num(2),new Num(4)))))->to_string())=="(x+(2*4))");
    CHECK ((new Add( new Mult(new Num(3), new Num(2)), new Mult( new Num(5), new Num(6))))->to_string() == "((3*2)+(5*6))");
    CHECK ((new Let("x", new Num(5), new Add(new Variable("x"), new Num(1))))->to_string() == "(_let x=5 _in (x+1))");
    CHECK ((new Let("x", new Num(5), new Add(new Let("y", new Num(3), new Add(new Variable("y"), new Num(2))), new Variable("x"))))->to_string() == "(_let x=5 _in ((_let y=3 _in (y+2))+x))");
}

TEST_CASE ( "Pretty Print Basic" ){
    CHECK ((new Num(5))->to_string_pretty() == "5");
    CHECK ((new Variable("x"))->to_string_pretty() == "x");
    CHECK ((new Add(new Num(5), new Num(4)))->to_string_pretty() == "5 + 4");
    CHECK ((new Mult(new Num(5), new Num(4)))->to_string_pretty() == "5 * 4");
    CHECK ((new Add(new Variable("a"), new Variable("b")))->to_string_pretty() == "a + b");
    CHECK ((new Mult(new Variable("a"), new Variable("b")))->to_string_pretty() == "a * b");
}

TEST_CASE ( "Pretty Print Moderate" ){
    CHECK ((new Add(new Add( new Num(3), new Num(4)), new Variable("a")))->to_string_pretty() == "(3 + 4) + a");
    CHECK ((new Add(new Num(3), new Add( new Num(4), new Num(5))))->to_string_pretty() == "3 + 4 + 5");
    CHECK ((new Add(new Num(3), new Mult( new Num(4), new Variable("b"))))->to_string_pretty() == "3 + 4 * b");
    CHECK ((new Add(new Mult( new Num(3), new Num(4)), new Num(5)))->to_string_pretty() == "3 * 4 + 5");
    CHECK ((new Mult(new Add( new Num(3), new Variable("a")), new Num(5)))->to_string_pretty() == "(3 + a) * 5");
    CHECK ((new Mult(new Variable("b"), new Add( new Num(4), new Num(5))))->to_string_pretty() == "b * (4 + 5)");
    CHECK ((new Mult(new Num(3), new Mult( new Num(4), new Num(5))))->to_string_pretty() == "3 * 4 * 5");
    CHECK ((new Mult(new Mult( new Variable("a"), new Num(4)), new Num(5)))->to_string_pretty() == "(a * 4) * 5");
}

TEST_CASE ( "Pretty Print Advanced" ){
       CHECK ((new Add(new Add( new Num(3), new Num(4)), new Add( new Num(5), new Variable("a"))))->to_string_pretty() == "(3 + 4) + 5 + a");
       CHECK ((new Add(new Mult( new Variable("a"), new Num(4)), new Mult( new Num(5), new Num(6))))->to_string_pretty() == "a * 4 + 5 * 6");
       CHECK ((new Add(new Add( new Num(3), new Variable("a")), new Mult( new Num(5), new Num(6))))->to_string_pretty() == "(3 + a) + 5 * 6");
       CHECK ((new Add(new Mult( new Variable("b"), new Variable("a")), new Add( new Num(5), new Num(6))))->to_string_pretty() == "b * a + 5 + 6");
       CHECK ((new Mult(new Add( new Num(3), new Num(4)), new Add( new Num(5), new Variable("b"))))->to_string_pretty() == "(3 + 4) * (5 + b)");
       CHECK ((new Mult(new Mult( new Num(3), new Num(4)), new Mult( new Num(5), new Num(6))))->to_string_pretty() == "(3 * 4) * 5 * 6");
       CHECK ((new Mult(new Add( new Num(3), new Variable("b")), new Mult( new Variable("a"), new Num(6))))->to_string_pretty() == "(3 + b) * a * 6");
       CHECK ((new Mult(new Mult( new Num(3), new Num(4)), new Add( new Num(5), new Variable("a"))))->to_string_pretty() == "(3 * 4) * (5 + a)");
}

TEST_CASE ( "Pretty Print Extreme" ){
    CHECK ((new Mult (new Add (new Variable ("a"), new Variable ("b")), new Num (7)))->to_string_pretty() == "(a + b) * 7");
    CHECK ((new Mult (new Mult (new Add (new Variable ("a"), new Variable ("b")), new Num (7)), new Num (6)))->to_string_pretty() == "((a + b) * 7) * 6");
    CHECK ((new Mult (new Mult (new Mult (new Add (new Variable ("a"), new Variable ("b")), new Num (7)), new Num (6)), new Variable ("c")))->to_string_pretty() == "(((a + b) * 7) * 6) * c");
    CHECK ((new Mult(new Mult(new Mult( new Num(3), new Num(4)), new Mult( new Num(5), new Num(6))), new Variable ("b")))->to_string_pretty()=="((3 * 4) * 5 * 6) * b");
    CHECK ((new Mult(new Mult( new Mult( new Num(3), new Num(4)), new Mult( new Num(5), new Num(6))), new Add( new Num(7), new Num(8))))->to_string_pretty() == "((3 * 4) * 5 * 6) * (7 + 8)");
    CHECK ((new Mult(new Mult( new Add( new Variable("a"), new Variable("b")), new Num(7)), new Mult( new Num(6), new Variable("c"))))->to_string_pretty() == "((a + b) * 7) * 6 * c");
}

TEST_CASE ( "Let Pretty Print" ){
    CHECK ((new Let("x", new Num(5), new Add(new Variable("x"), new Num(1))))->to_string_pretty() == "_let x = 5\n_in  x + 1");
    CHECK ((new Let("x", new Num(5), new Let("x", new Num(1), new Add( new Variable("x"), new Num(3)))))->to_string_pretty() == "_let x = 5\n_in  _let x = 1\n     _in  x + 3");
    CHECK ((new Let("x", new Num(5), new Add(new Let("y", new Num(3), new Add(new Variable("y"), new Num(2))), new Variable("x"))))->to_string_pretty() == "_let x = 5\n_in  (_let y = 3\n      _in  y + 2) + x");
    CHECK ((new Let("x", new Num(5), new Let("y", new Num(3), new Let( "z", new Num(1), new Add (new Variable("z"), new Num(4))))))->to_string_pretty() == "_let x = 5\n_in  _let y = 3\n     _in  _let z = 1\n          _in  z + 4");
    CHECK((new Mult(new Let("x", new Num(5), new Add(new Variable("x"), new Num(1))), new Num (5)))->to_string_pretty() == "(_let x = 5\n _in  x + 1) * 5");
    CHECK((new Add( new Num (5), new Let("x", new Num(5), new Add(new Variable("x"), new Num(1)))))->to_string_pretty() == "5 + _let x = 5\n    _in  x + 1");
    CHECK((new Add(new Let("x", new Num(5), new Add(new Variable("x"), new Num(1))), new Num (5)))->to_string_pretty() == "(_let x = 5\n _in  x + 1) + 5");
    CHECK((new Mult( new Num(5), new Add(new Let("x", new Num(5), new Variable("x")), new Num (1))))->to_string_pretty() == "5 * ((_let x = 5\n      _in  x) + 1)");
    CHECK((new Add(new Mult(new Num(5), new Let("x", new Num(5), new Variable("x"))), new Num (1)))->to_string_pretty() == "5 * (_let x = 5\n     _in  x) + 1");
    CHECK((new Mult(new Num(5), new Add(new Let("x", new Num(5), new Variable("x")), new Num (1))))->to_string_pretty() == "5 * ((_let x = 5\n      _in  x) + 1)");
}
