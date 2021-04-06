//
//  cmdline.cpp
//  MSDscript
//
//  Created by Taylor Dunn on 1/19/21.
//

#define CATCH_CONFIG_RUNNER
#include "cmdline.hpp"
#include "catch.h"
#include "parse.hpp"
#include "val.hpp"
#include "env.hpp"
#include "pointer.h"
#include "step.hpp"


void use_arguments(int argc, char *argv[]){
    //No argument provided
    if (argc == 1){
        exit(0);
    }
    bool testSeen = false; 
    //Additional argument options
    for (int i = 1; i < argc; i++){
        std::string arg = argv[i];
        if (arg == "--help"){
            std::cout << "Allowed Arguments: --help, --interp, --print, --pretty-print, --test\n";
            exit(0);
        } else if (arg == "--test"){
            if(testSeen == false){
                if (Catch::Session().run(1,argv) != 0){
                    exit(1);
                }
                testSeen = true;
            } else {
                std::cerr << "Tests already seen\n";
                exit(1);
            }
        } else if (arg == "--interp"){
            PTR(Expr) user_input = parse_expr(std::cin);
            PTR(Val) value = user_input->interp(Env::empty);
            value->print(std::cout);
        } else if (arg == "--print"){
            PTR(Expr) user_input = parse_expr(std::cin);
            user_input->print(std::cout);
        } else if (arg == "--pretty-print"){
            PTR(Expr) user_input = parse_expr(std::cin);
            std::cout << user_input->to_string_pretty();
        } else if (arg == "--step"){
            PTR(Expr) user_input = parse_expr(std::cin);
            std::cout << Step::interp_by_steps(user_input)->to_string();
        } else {
            std::cerr << "Invalid Argument\n";
            exit(1);
        }
        std::cout << "\n";
    }
}
