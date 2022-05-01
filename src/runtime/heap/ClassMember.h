//
// Created by xuranus on 2/16/19.
//

#ifndef JVM_CLASSMEMBER_H
#define JVM_CLASSMEMBER_H

#include <string>
#include <vector>
#include "../../basicType.h"

namespace heap {
    class Class;

    struct ClassMember {
        u2 accessFlags;
        std::string name;
        std::string descriptor;
        Class* klass; // for referring, do not release
        std::string signature;
        std::vector<u1> annotationData; // TODO:: init RuntimeVisibleAnnotationsAttribute

        ClassMember(u2 _accessFlags, const std::string& _name, const std::string& _descriptor, Class* _klass);
        virtual ~ClassMember() = default;
        bool accessibleTo(Class *d) const;

        bool isPublic() const;
        bool isPrivate() const;
        bool isProtected() const;
        bool isStatic() const;
        bool isFinal() const;
        bool isSynthetic() const;

        std::vector<u1> getAnnotationData() const;
    };
}

#endif //JVM_CLASSMEMBER_H
