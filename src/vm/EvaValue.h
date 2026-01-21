#ifndef EvaValue_h
#define EvaValue_h

#include<string>

/**
 * Eva value type.
 */
enum class EvaValueType {
    NUMBER,
    OBJECT,
    BOOLEAN,
    CODE
};

enum class ObjectType {
    STRING,
    CODE
};

struct Object {
    Object(ObjectType type) : type(type) {

    }

    ObjectType type;
};

/**
 *Eva value(tagged union).
 */
struct EvaValue {
    EvaValueType type;

    union {
        double number;
        bool boolean;
        Object *object;
    };
};

struct StringObject : public Object {
    StringObject(const std::string &str)
        : Object(ObjectType::STRING), string(str) {
    }

    std::string string;
};

struct CodeObject : public Object {
    CodeObject (const std::string& name) : Object(ObjectType::CODE), name(name){}

    /**
     * Name of the unit(usually function name)
     */
    std::string name;

    /**
   * Constant pool
   */
    std::vector<EvaValue> constants;

    /**
     * Bytecode.
     */
    std::vector<uint8_t> code;
};

//Constructors:
#define NUMBER(v) EvaValue{ .type = EvaValueType::NUMBER, .number = v }
#define BOOLEAN(v) EvaValue{ .type = EvaValueType::BOOLEAN, .boolean = v }

#define ALLOC_STRING(v) EvaValue{ .type = EvaValueType::OBJECT, .object = (Object*)new StringObject(v) }
#define ALLOC_CODE(name) EvaValue{ .type = EvaValueType::CODE, .object = (Object*)new CodeObject(name) }

//#define NUMBER(value)(EvaValue)({EvaValueType::NUMBER, .number = value})

//Acessors:
#define AS_NUMBER(evaValue) ((double)(evaValue).number)
#define AS_BOOLEAN(evaValue) ((bool)(evaValue).boolean)

#define AS_STRING(evaValue) ((StringObject*)(evaValue).object)
#define AS_CPPSTRING(evaValue) (AS_STRING(evaValue)->string)
#define AS_OBJECT(evaValue) ((Object*)(evaValue).object)
#define AS_CODE(evaValue) ((CodeObject*)(evaValue).object)

// Testers:
#define IS_NUMBER(evaValue) ((evaValue).type == EvaValueType::NUMBER)
#define IS_BOOLEAN(evaValue) ((evaValue).type == EvaValueType::BOOLEAN)
#define IS_OBJECT(evaValue) ((evaValue).type == EvaValueType::OBJECT)
#define IS_STRING(evaValue) IS_OBJECT_TYPE(evaValue, ObjectType::STRING)
#define IS_CODE(evaValue) IS_OBJECT_TYPE(evaValue, ObjectType::CODE)

#define IS_OBJECT_TYPE(evaValue, objectType) \
    (IS_OBJECT(evaValue) && AS_OBJECT(evaValue)->type == objectType)

//String representation used in constants for debug.
std::string evaValueToTypeString(const EvaValue &evaValue) {
    if (IS_NUMBER(evaValue)) {
        return "NUMBER";
    }
    if (IS_BOOLEAN(evaValue)){
        return "BOOLEAN";
    }
    if (IS_STRING(evaValue)) {
        return "STRING";
    }
    if (IS_CODE(evaValue)) {
        return "CODE";
    }
    DIE << "evaValueToTypeString: unknow type " << (int)evaValue.type;
    return "";
}

//String representation used in constants for debug.
std::string evaValueToConstantString(const EvaValue &evaValue) {
    std::stringstream ss;
    if (IS_NUMBER(evaValue)) {
        ss << evaValue.number;
    }else if (IS_BOOLEAN(evaValue)) {
        ss << (evaValue.boolean == true ? "true" : "false");
    }else if (IS_STRING(evaValue)) {
        ss << '"' << AS_CPPSTRING(evaValue) << '"';
    }else if (IS_CODE(evaValue)) {
        auto code = AS_CODE(evaValue);
        ss << "code " << code << ": " << code->name;
    }else {
        DIE << "evaValueToConstantString: unknow type " << (int)evaValue.type;
    }
    return ss.str();
}

// Output stream
std::ostream &operator<<(std::ostream &os, const EvaValue &evaValue) {
    return os << "EvaValue(" << evaValueToTypeString(evaValue)
                << "): " << evaValueToConstantString(evaValue);
}

#endif
