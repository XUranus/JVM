//
// Created by xuranus on 2/16/19.
//

#ifndef JVM_CLASSMEMBER_H
#define JVM_CLASSMEMBER_H

#include <string>
#include <vector>
#include "../../classfile/ClassFile.h"

struct Class;

struct ClassMember {
    u2 accessFlags;
    std::string name;
    std::string descriptor;
    Class* _class;

    ClassMember();
    bool accessibleTo(Class* d);
};

#endif //JVM_CLASSMEMBER_H
