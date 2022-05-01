//
// Created by xuranus on 2/16/19.
//

#include "ClassMember.h"
#include "Class.h"

namespace heap {

    ClassMember::ClassMember(u2 _accessFlags,
                             const std::string &_name,
                             const std::string &_descriptor,
                             Class *_klass):
                             name(_name),
                             descriptor(_descriptor) {
        accessFlags = _accessFlags;
        klass = _klass;
    }

    // if class d can access this member
    bool ClassMember::accessibleTo(Class *d) const {
        if (isPublic()) {
            return true;
        } else if (isProtected()) {
            return (d == klass || d->isSubClassOf(klass) || klass->packageName() == d->packageName());
        } else if (!isPrivate()) { // is default
            return klass->packageName() == d->packageName();
        } else {
            return d == klass;
        }
    }

    bool ClassMember::isPublic() const { return accessFlags & ACC_PUBLIC_FLAG; }

    bool ClassMember::isPrivate() const { return accessFlags & ACC_PRIVATE_FLAG; }

    bool ClassMember::isProtected() const { return accessFlags & ACC_PROTECTED_FLAG; }

    bool ClassMember::isStatic() const { return accessFlags & ACC_STATIC_FLAG; }

    bool ClassMember::isFinal() const { return accessFlags & ACC_FINAL_FLAG; }

    bool ClassMember::isSynthetic() const { return accessFlags & ACC_SYNTHETIC_FLAG; }

    std::vector<u1> ClassMember::getAnnotationData() const {
        return annotationData;
    }

}