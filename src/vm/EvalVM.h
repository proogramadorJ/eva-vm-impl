/**
 * Eva Virtual Machine
 */

#ifndef EvaVM_h
#define EvaVM_h


#include <string>
#include <vector>
#include <cstdint>
#include <array>
#include<iostream>
#include<memory>

#include "../bytecode/OpCode.h"
#include "../Logger.h"
#include "./EvaValue.h"
#include "../parser/EvaParser.h"
#include "../compiler/EvaCompiler.h"

using syntax::EvaParser;

/**
 * Reads the current byte in the bytecode
 * and advances ip pointer.
 */
#define READ_BYTE() *ip++

/**
 * Gets a constant from the pool.
 */
#define GET_CONST() co->constants[READ_BYTE()]

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
    EvaVM() : parser(std::make_unique<EvaParser>()),
              compiler(std::make_unique<EvaCompiler>()) {
    }


    /**
     * Pushes a value into the stack
     */
    void push(const EvaValue &value) {
        if ((size_t) (sp - stack.begin()) == STACK_LIMIT) {
            DIE << "push(): Stack overflow.\n";
        }
        *sp = value;
        sp++;
    }

    /**
     * Pops a value from the stack
     */
    EvaValue pop() {
        if (stack.size() == 0) {
            DIE << "pop(): empty stack.\n";
        }
        --sp;
        return *sp;
    }

    /**
    * Execute a program.
    */
    EvaValue exec(const std::string &program) {
        //1. parse the program
        const auto ast = parser->parse(program);
        //log(ast.number);

        //2. Compile program to Eva Bytecode
        // code = compiler->compile(ast);
        //  code = {OP_CONST, 0,OP_CONST, 1, OP_ADD, OP_HALT};
        //  code = compiler->compile(ast);
        co = compiler->compile(ast);


        // Set instruction pointer to the beginning
        ip = &co->code[0];

        //Set the stack pointer to the beginning
        sp = &stack[0];

        return eval();
    }

    /**
     * Main evaluation loop
     */
    EvaValue eval() {
        for (;;) {
            auto opcode = READ_BYTE();
            log_hex(opcode);

            switch (opcode) {
                case OP_HALT:
                    return pop();

                //Constants
                case OP_CONST:
                    push(GET_CONST());
                    break;

                //Math operations
                case OP_ADD: {
                    auto op2 = pop();
                    auto op1 = pop();

                    // Numeric addition
                    if (IS_NUMBER(op1) && IS_NUMBER(op2)) {
                        auto v1 = AS_NUMBER(op1);
                        auto v2 = AS_NUMBER(op2);
                        push(NUMBER(v1 + v2));
                    }

                    //String concatenation
                    else if (IS_STRING(op1) && IS_STRING(op2)) {
                        auto s1 = AS_CPPSTRING(op1);
                        auto s2 = AS_CPPSTRING(op2);
                        push(ALLOC_STRING(s1 + s2));
                    }
                    break;
                }
                case OP_SUB: {
                    BINARY_OP(-);
                    break;
                }
                case OP_DIV: {
                    BINARY_OP(/);
                    break;
                }
                case OP_MUL: {
                    BINARY_OP(*);
                    break;
                }
                default:
                    DIE << "Unknown opcode: " << std::showbase << std::hex << (int) opcode;
            }
        }
    }

    /**
     * Parser
     */
    std::unique_ptr<EvaParser> parser;

    /**
     * Compiler
     */
    std::unique_ptr<EvaCompiler> compiler;

    /**
     *  Instruction point(aka Program counter).
     */
    uint8_t *ip;

    /**
     * Stack pointer.
     */
    EvaValue *sp;

    /**
     * Operands stack;
     */
    std::array<EvaValue, STACK_LIMIT> stack;

    // /**
    //  * Constant pool
    //  */
    // std::vector<EvaValue> constants;
    //
    //
    // /**
    //  * Bytecode.
    //  */
    //
    // std::vector<uint8_t> code;

    CodeObject *co;
};

#endif
