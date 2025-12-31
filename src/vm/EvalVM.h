/**
 * Eva Virtual Machine
 */

 #ifndef EvaVM_h
 #define EvaVM_h


#include <string>
#include <vector>
#include <cstdint>
#include <array>

#include "../bytecode/OpCode.h"
#include "../Logger.h"
#include "./EvaValue.h"

/**
 * Reads the current byte in the bytecode
 * and advances ip pointer.
 */
#define READ_BYTE() *ip++

/**
 * Gets a constant from the pool.
 */
#define GET_CONST() constants[READ_BYTE()]

/*
* Stack top(stack overflow after exceeding).
*/
#define STACK_LIMIT 512

/**
 * Binary operation.
 */
#define BINARY_OP(op) \
    do {\
        auto op2 = AS_NUMBER(pop()); \
        auto op1 = AS_NUMBER(pop()); \
        push(NUMBER(op1 op op2)); \
    } while(false)


 class EvaVM {

    public:
        EvaVM(){}


 /**
  * Pushes a value into the stack
  */
 void push(const EvaValue& value){
   if((size_t) (sp - stack.begin()) == STACK_LIMIT){
        DIE << "push(): Stack overflow.\n"; 
   }
    *sp = value;
    sp++;
 }

 /**
  * Pops a value from the stack
  */
 EvaValue pop(){
    if(stack.size() == 0){
        DIE << "pop(): empty stack.\n";
    }
    --sp;
    return *sp;
 }

  /**
  * Execute a program.
  */
    EvaValue exec(const std::string &program){
        //1. parse the program
        //auto ast = parser->parse(program);

        //2. Compile program to Eva Bytecode
        // code = compiler->compile(ast);
        code = {OP_CONST, 0, OP_CONST, 1, OP_DIV, OP_HALT, 2, OP_ADD, OP_HALT};
        
        constants.push_back(NUMBER(10));
        constants.push_back(NUMBER(5));
        constants.push_back(NUMBER(5));

        // Set instruction pointer to the beginning
        ip = &code[0];

        //Set the stack pointer to the beginning
        sp = &stack[0];

        return eval();
    }

    /**
     * Main evaluation loop
     */
    EvaValue eval(){
        for(;;){
            auto opcode = READ_BYTE();
            log_hex(opcode);

            switch (opcode){
                case OP_HALT:
                    return pop();

                //Constants
                case OP_CONST:
                    push(GET_CONST());
                    break; 

                //Math operations                    
                case OP_ADD:{
                    BINARY_OP(+);
                    break;   
                }
                case OP_SUB:{
                    BINARY_OP(-);
                    break;   
                }
                case OP_DIV:{
                    BINARY_OP(/);
                    break;   
                }  
                case OP_MUL:{
                    BINARY_OP(*);
                    break;   
                }              
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
     * Stack pointer.
     */
    EvaValue* sp;

    /**
     * Operands stack;
     */
    std::array<EvaValue, STACK_LIMIT> stack;

    /**
     * Constant pool
     */
    std::vector<EvaValue> constants;


    /**
     * Bytecode.
     */

     std::vector<uint8_t>code;
     
    
 };

#endif