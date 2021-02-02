extern "C" {
#include "run.h"
};

#define CATCH_CONFIG_RUNNER
#include "../MSDscript/catch.h"
bool run_tests() {
    const char *argv[] = { "arith" };
    return (Catch::Session().run(1, argv) == 0);
}
