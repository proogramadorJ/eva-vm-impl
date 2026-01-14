#ifndef EvaCompiler_h
#define EvaCompiler_h

#include "../vm//EvaValue.h"

class EvaCompiler {
public:
    EvaCompiler() {
    }

    CodeObject *co;

    CodeObject *compile(const Exp &exp) {
        //alloc new code object
        int i = 5;
        int b = i;
        co = AS_CODE(ALLOC_CODE("main"));

        //Generate recursively from top-level
        gen(exp);
        emit(OP_HALT);

        return co;
    }

    //Main compile loop
    void gen(const Exp &exp) {
        switch (exp.type) {
            case ExpType::NUMBER:
                emit(OP_CONST);
                emit(numericConstIdx(exp.number));
                break;
            case ExpType::STRING:
                emit(OP_CONST);
                emit(stringConstIdx(exp.string));
                break;
            case ExpType::LIST:
                DIE << "ExpType::LIST not implemented yet";
                break;
            case ExpType::SYMBOL:
                DIE << "ExpType::SYMBOL not implemented yet";
                break;
        }
    }

private:
    /**
     *Allocates a numeric constant.
     */
    size_t numericConstIdx(double value) {
        for (size_t i = 0; i < co->constants.size(); i++) {
            if (!IS_NUMBER(co->constants[i])) {
                continue;
            }
            if (AS_NUMBER(co->constants[i]) == value) {
                return i;
            }
        }
        co->constants.push_back(NUMBER(value));
        return co->constants.size() - 1;
    }

    /**
     *Allocates a string constant.
     */
    size_t stringConstIdx(const std::string &value) {
        for (auto i = 0; i < co->constants.size(); i++) {
            if (!IS_STRING((co->constants[i]))) {
                continue;
            }
            if (AS_CPPSTRING(co->constants[i]) == value) {
                return i;
            }
        }
        co->constants.push_back(ALLOC_STRING(value));
        return co->constants.size() - 1;
    }

    /**
     *Emits data to the bytecode
     */
    void emit(uint8_t code) { co->code.push_back(code); }
};


#endif
