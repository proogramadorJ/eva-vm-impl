#ifndef EvaValue_h
#define EvaValue_h

#include<string>

/**
 * Eva value type.
 */
enum class EvaValueType{
    NUMBER,
    OBJECT,
};

enum class ObjectType{
    STRING,
};

struct Object{
    Object(ObjectType type) : type(type){}
    ObjectType type;
};

struct StringObject : public Object{
    StringObject(const std::string& str) 
        : Object(ObjectType::STRING), string(str){}
    std::string string;
};

/**
 *Eva value(tagged union).
 */
struct EvaValue {
    EvaValueType type;
    union {
        double number;
        Object* object;
    };
};


//Constructors:
#define NUMBER(v) EvaValue{ .type = EvaValueType::NUMBER, .number = v }
#define ALLOC_STRING(v) EvaValue{ .type = EvaValueType::OBJECT, .object = (Object*)new StringObject(v) }

//#define NUMBER(value)(EvaValue)({EvaValueType::NUMBER, .number = value})

//Acessors:
#define AS_NUMBER(evaValue) ((double)(evaValue).number)

#define AS_STRING(evaValue) ((StringObject*)(evaValue).object)
#define AS_CPPSTRING(evaValue) (AS_STRING(evaValue)->string)
#define AS_OBJECT(evaValue) ((Object*)(evaValue).object)

// Testers:
#define IS_NUMBER(evaValue) ((evaValue).type == EvaValueType::NUMBER)
#define IS_OBJECT(evaValue) ((evaValue).type == EvaValueType::OBJECT)
#define IS_STRING(evaValue) IS_OBJECT_TYPE(evaValue, ObjectType::STRING)

#define IS_OBJECT_TYPE(evaValue, objectType) \
    (IS_OBJECT(evaValue) && AS_OBJECT(evaValue)->type == objectType)

#endif
