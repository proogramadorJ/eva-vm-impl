//
// Created by pedro on 31/01/2026.
//

#ifndef EVA_VM_IMPL_GLOBAL_H
#define EVA_VM_IMPL_GLOBAL_H

#include <string>
#include <vector>

#include "EvaValue.h"
#include "../Logger.h"

//Global var
struct GlobalVar {
    std::string name;
    EvaValue value;
};

//Global objects
struct Global {
    //Global variables and functions
    std::vector<GlobalVar> globals;

    //Returns a global;
    GlobalVar &get(size_t index) {
        return globals[index];
    }

    //Sets a global
    void set(size_t index, const EvaValue& value) {
        if (index >= globals.size()) {
            DIE << "Global " << index << "does not exist.";
        }
        globals[index].value = value;
    }

    //Gets global index
    int getGlobalIndex(const std::string& name) {
        if (globals.size() > 0) {
            for (auto i = (int)globals.size() - 1; i>=0; i--) {
                if (globals[i].name == name) {
                    return i;
                }
            }
        }
        return -1;
    }

    void define(const std::string& name) {
        auto index = getGlobalIndex(name);

        //already defined
        if (index != -1) {
            return;
        }
        //Set to default number 0.
        globals.push_back({name, NUMBER(0)});
    }

    void addConst(const std::string& name, double value ) {
        if (exists(name)) {
            return;
        }
        globals.push_back({name, NUMBER(value)});
    }


    bool exists(const std::string& name) {
        return getGlobalIndex(name) != -1;
    }
};


#endif //EVA_VM_IMPL_GLOBAL_H
