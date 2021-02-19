#ifndef exec_hpp
#define exec_hpp

#include <string>
#include <iostream>
#include <cassert>

#include <unistd.h>
#include <fcntl.h>
#include <poll.h>
#include <errno.h>


class ExecResult {
public:
  int exit_code;
  std::string out;
  std::string err;
  ExecResult() {
    exit_code = 0;
    out = "";
    err = "";
  }
};

extern ExecResult exec_program(int argc, const char * const *argv, std::string input);

#endif /* exec_hpp */
