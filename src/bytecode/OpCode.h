#ifndef _OpCode_h
#define _OpCode_h

// Stops the program
#define OP_HALT 0x00

//Pushes a const into the stack
#define OP_CONST 0x01

//Math opcode
#define OP_ADD 0x02
#define OP_SUB 0x03
#define OP_DIV 0x04
#define OP_MUL 0x05
#define OP_MOD 0x06
#endif