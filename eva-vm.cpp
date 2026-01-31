#include <iostream>
#include "src/vm/EvalVM.h"
#include "src/Logger.h"


/**
 * Eva VM main executable
 */

int main(int argc, char const *argv[]) {
    EvaVM vm;

    auto result = vm.exec(R"(

      (if (> 5 10) 1 2)

        )");

    std::cout<<std::endl;
    log(result)
    std::cout << "All done\n";

    return 0;
}
