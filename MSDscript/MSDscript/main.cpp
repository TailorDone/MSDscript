//
//  main.cpp
//  MSDscript
//
//  Created by Taylor Dunn on 1/19/21.
//

#include <iostream>
#include "cmdline.hpp"
#include "parse.hpp"
#include "pointer.h"

int main(int argc, char *argv[]) {
    try{
        use_arguments(argc, argv);
        return 0;
    } catch (std::runtime_error exn){
        std::cerr << exn.what() << "\n";
        return 1;
    }
}
