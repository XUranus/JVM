//
// Created by xuranus on 2/11/19.
//

#include "SymRef.h"
#include "ClassLoader.h"
#include "../../common/Exception.h"
#include "ConstantPool.h"

namespace heap {

    SymRef::SymRef(ConstantPool* _constantPool, const std::string& _className):
        className(_className) {
        constantPool = _constantPool;
        klass = nullptr;
    }

    void SymRef::resolveClassRef() {
        if(!klass) {
            Class* d = constantPool->klass;
            Class* c = d->classloader->loadClass(className);
            if (!c->accessibleTo(d)) {
                exception::fatal("java.lang.IllegalAccessError");
            }
            klass = c;
        }
    }

    Class *SymRef::resolvedClass() {
        if (klass == nullptr) {
            resolveClassRef();
        }
        return klass;
    }

    ClassRef::ClassRef(ConstantPool *_constantPool, const std::string &_classname):
        SymRef(_constantPool, _classname) {}

    MemberRef::MemberRef(const std::string &_className,
                         const std::pair <std::string, std::string> &nameAndDescriptor,
                         ConstantPool *_constantPool):
                         SymRef(_constantPool, _className),
                         name(nameAndDescriptor.first),
                         descriptor(nameAndDescriptor.second) {}

    FieldRef::FieldRef(ConstantPool *cp, const std::string& _className, const std::pair<std::string, std::string>& _nameAndDescriptor):
        MemberRef(_className, _nameAndDescriptor, cp) {
        field = nullptr;
    }

    void FieldRef::resolveFieldRef() {
        Class* d = constantPool->klass;
        Class* c = resolvedClass();
        Field* _field = c->lookUpField(name, descriptor);
        if (_field == nullptr) {
            exception::fatal("java.lang.NoSuchFieldError");
        }
        if (!_field->accessibleTo(d)) {
            exception::fatal("java.lang.IllegalAccessError");
        }
        field = _field;
    }

    Field *FieldRef::resolvedField() {
        if (field == nullptr) {
            resolveFieldRef();
        }
        return field;
    }


    MethodRef::MethodRef(ConstantPool *cp, const std::string& _className, const std::pair<std::string, std::string>& nameAndDescriptor):
        MemberRef(_className, nameAndDescriptor, cp) {
        method = nullptr;
    }


    void MethodRef::resolveMethodRef() {
        Class* d = constantPool->klass;
        Class* c = resolvedClass();
        if (c->isInterface()) {
            exception::fatal("java.lang.IncompatibleClassChangeError");
        }
        Method* _method = c->lookUpMethod(name, descriptor);
        if (_method == nullptr) {
            exception::fatal("java.lang.NoSuchMethodError");
        }
        if (!_method->accessibleTo(d)) {
            exception::fatal("java.lang.IllegalAccessError");
        }
        method = _method;
    }

    Method *MethodRef::resolvedMethod() {
        if (method == nullptr) {
            resolveMethodRef();
        }
        return method;
    }

    InterfaceMemberRef::InterfaceMemberRef(ConstantPool *cp, const std::string& _className, const std::pair<std::string, std::string>& nameAndDescriptor):
        MemberRef(_className, nameAndDescriptor, cp) {
        method = nullptr;
    }

    Method *InterfaceMemberRef::resolvedInterfaceMethod() {
        if (method == nullptr) {
            resolveInterfaceMethodRef();
        }
        return method;
    }

    void InterfaceMemberRef::resolveInterfaceMethodRef() {
        Class* d = constantPool->klass;
        Class* c = resolvedClass();
        if (!c->isInterface()) {
            exception::fatal("java.lang.IncompatibleClassChangeError");
        }
        Method* _method = c->lookUpInterfaceMethod(name, descriptor);
        if (_method == nullptr) {
            exception::fatal("java.lang.NoSuchMethodError");
        }
        if (!_method->accessibleTo(d)) {
            exception::fatal("java.lang.IllegalAccessError");
        }
        method = _method;
    }




}