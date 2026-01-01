#include <iostream>
#include "src/vm/EvalVM.h"
#include "src/Logger.h"


/**
 * Eva VM main executable
 */

 int main (int argc, char const *argv[]){
    EvaVM vm;

   auto result =  vm.exec(R"(

        42

        )");

    log(AS_CPPSTRING(result))
    std::cout << "All done\n";

    return 0;
 }