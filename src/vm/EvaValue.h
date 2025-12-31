#ifndef EvaValue_h
#define EvaValue_h

/**
 * Eva value type.
 */
enum class EvaValueType{
    NUMBER,
};

/**
 *Eva value(tagged union).
 */
struct EvaValue {
    EvaValueType type;
    union {
        double number;
    };
};


//Constructors:
#define NUMBER(v) EvaValue{ .type = EvaValueType::NUMBER, .number = v }
//#define NUMBER(value)(EvaValue)({EvaValueType::NUMBER, .number = value})

//Acessors:
#define AS_NUMBER(evaValue) ((double)(evaValue).number)

#endif
