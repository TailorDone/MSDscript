//
//  main.cpp
//  MSDscriptTest
//
//  Created by Taylor Dunn on 2/19/21.
//
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "exec.hpp"

static std::string random_expr_string();

int main (int argc, char **argv) {
    srand(clock());
    const char * const interp_argv[] = { argv[1], "--interp" };
    const char * const print_argv[] = { argv[1], "--print" };
    const char * const prettyprint_argv[] = { argv[1], "--pretty-print" };
    for (int i = 0; i < 100; i++) {
        std::string in = random_expr_string();
        std::cout << "Trying " << in << "\n";
        ExecResult interp_result = exec_program(2, interp_argv, in);
        ExecResult print_result = exec_program(2, print_argv, in);
        if (argc == 2){
            ExecResult interp_again_result = exec_program(2, interp_argv, print_result.out);
            if (interp_again_result.out != interp_result.out){
                throw std::runtime_error("different result for printed");
            }
        } else if(argc == 3){
            const char * const interp2_argv[] = { argv[2], "--interp" };
            const char * const print2_argv[] = { argv[2], "--print" };
            const char * const prettyprint2_argv[] = { argv[2], "--pretty-print" };
            ExecResult interp2_result = exec_program(2, interp2_argv, in);
            ExecResult print2_result = exec_program(2, print2_argv, in);
            ExecResult prettyprint_result = exec_program(2, prettyprint_argv, in);
            ExecResult prettyprint2_result = exec_program(2, prettyprint2_argv, in);
            if (interp_result.out != interp2_result.out){
                std::cout << "result 1: " << interp_result.out << "\n";
                std::cout << "result 2: " << interp2_result.out << "\n";
                throw std::runtime_error("different interp results");
            }
            if (print_result.out != print2_result.out){
                std::cout << "result 1: " << print_result.out << "\n";
                std::cout << "result 2: " << print2_result.out << "\n";
                throw std::runtime_error("different print results");
            }
            if (prettyprint_result.out != prettyprint2_result.out){
                std::cout << "result 1: " << prettyprint_result.out << "\n";
                std::cout << "result 2: " << prettyprint2_result.out << "\n";
                throw std::runtime_error("different pretty print results");
            }
        } else {
            throw std::runtime_error("too many aruments");
        }
    }
    return 0;
}

std::string random_expr_string() {
    int n = (rand() % 23);
    if (n < 10)
        return std::to_string(rand());
    else if (n < 16){
        if (n==10) {
            return "(" + random_expr_string() + "+" + random_expr_string() + ")"; // (expr + expr)
        } else if (n==11) {
            return random_expr_string() + "+" + random_expr_string(); // expr + expr
        } else if (n == 12) {
            return "x + " + random_expr_string(); // x + expr
        } else if (n == 13) {
            return random_expr_string() + " + x"; // expr + x
        } else if (n == 14) {
            return "(x + " + random_expr_string() + ")"; // (x + expr)
        } else{
            return "(" + random_expr_string() + " + x)"; // (expr + x)
        }
    }
    else if (n < 22){
        if (n==16) {
            return "(" + random_expr_string() + "*" + random_expr_string() + ")"; // (expr * expr)
        } else if (n==17) {
            return random_expr_string() + "*" + random_expr_string(); // expr * expr
        } else if (n == 18) {
            return "x * " + random_expr_string(); // x * expr
        } else if (n == 19) {
            return random_expr_string() + " * x"; // expr * x
        } else if (n == 20) {
            return "(x * " + random_expr_string() + ")"; // (x * expr)
        } else{
            return "(" + random_expr_string() + " * x)"; // (expr * x)
        }
    }
    else{
        if (n == 21){
        return "_let x = " + random_expr_string() + " _in " + random_expr_string(); // single let
        } else {
        return "_let x = " + random_expr_string() + " _in _let x = " + random_expr_string() + " _in " + random_expr_string(); // nested let
        }
    }
}
