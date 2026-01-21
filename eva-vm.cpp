#include <iostream>
#include "src/vm/EvalVM.h"
#include "src/Logger.h"


/**
 * Eva VM main executable
 */

int main(int argc, char const *argv[]) {
    EvaVM vm;

    auto result = vm.exec(R"(

      (+ "hello" " world")

        )");

    log(result)
    std::cout << "All done\n";

    return 0;
}
