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
            Expr* user_input = nullptr;
            user_input = parse_expr(std::cin);
            int value = user_input->interp();
            std::cout << value;
            exit(0);
        } else if (arg == "--print"){
            Expr* user_input = nullptr;
            user_input = parse_expr(std::cin);
            user_input->print(std::cout);
            exit(0);
        } else if (arg == "--pretty-print"){
            Expr* user_input = nullptr;
            user_input = parse_expr(std::cin);
            std::cout << user_input->to_string_pretty();
            exit(0);
        } else {
            std::cerr << "Invalid Argument\n";
            exit(1);
        }
        std::cout << "\n";
    }
}
