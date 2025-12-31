/**
 * Eva Virtual Machine
 */

 #ifndef EvaVM_h
 #define EvaVM_h


#include <string>
#include <vector>
#include <cstdint>

#include "../bytecode/OpCode.h"
#include "../Logger.h"

/**
 * Reads the current byte in the bytecode
 * and advances ip pointer.
 */
#define READ_BYTE() *ip++

 class EvaVM {

    public:
        EvaVM(){}

    void exec(const std::string &program){
        //1. parse the program
        //auto ast = parser->parse(program);

        //2. Compile program to Eva Bytecode
        // code = compiler->compile(ast);
        code = {OP_HALT};

        // Set instruction pointer to the beginning
        ip = &code[0];

        return eval();
    }

    /**
     * Main evaluation loop
     */
    void eval(){
        for(;;){
            auto opcode = READ_BYTE();
            log_hex(opcode);
            switch (opcode){
                case OP_HALT:
                    return;                           
                default:
                    DIE << "Unknown opcode: " << std::showbase << std::hex << (int)opcode;
            }
        }
    }

    /**
     *  Instruction point(aka Program counter).
     */
    uint8_t* ip;


    /**
     * Bytecode.
     */

     std::vector<uint8_t>code;
     
    
 };

  #endif