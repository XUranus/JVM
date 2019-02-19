//
// Created by xuranus on 2/11/19.
//

#include "SymRef.h"
#include "ClassLoader.h"
#include "../../util/Console.h"

SymRef::SymRef() {
    constantPool = nullptr;
    className = "";
    _class = nullptr;
};

void SymRef::resolveClassRef()
{
    auto d = constantPool->_class;
    auto c = d->classloader->loadClass(className);
    if(!c->accessibleTo(d))
    {
        Console::printlnError("java.lang.IllegalAccessError");
        exit(1);
    }
    _class = c;
}

Class* SymRef::resolvedClass()
{
    if(_class== nullptr)
        resolveClassRef();
    return _class;
}

MemberRef::MemberRef(CpInfo *constantMemberRef)
{
    className = constantMemberRef->getClassName();
    auto ret = constantMemberRef->getNameAndDescriptor();
    name = ret.first;
    descriptor = ret.second;
}

FieldRef::FieldRef(ConstantPool *cp, CONSTANT_Fieldref *constantFieldrefInfo):MemberRef(constantFieldrefInfo)
{
    constantPool = cp;
    field = nullptr;
}

void FieldRef::resolveFieldRef()
{
    auto d = constantPool->_class;
    auto c = resolvedClass();
    auto _field = c->lookUpField(name,descriptor);
    if(_field== nullptr)
    {
        Console::printlnError("java.lang.NoSuchFieldError");
        exit(1);
    }
    if(!_field->accessibleTo(d))
    {
        Console::printlnError("java.lang.IllegalAccessError");
        exit(1);

    }
    field = _field;
}

Field* FieldRef::resolvedField()
{
    if(field== nullptr)
        resolveFieldRef();
    return field;
}

MethodRef::MethodRef(ConstantPool *cp, CONSTANT_Methodref *constantMethodRefInfo) :MemberRef(constantMethodRefInfo)
{
    constantPool = cp;
    method = nullptr;
}


void MethodRef::resolveMethodRef()
{
   auto d = constantPool->_class;
   auto c = resolvedClass();
   if(c->accessFlags & ACC_INTERFACE_FLAG)
   {
       Console::printlnError("java.lang.IncompatibleClassChangeError");
       exit(1);
   }
   auto _method = c->lookUpMethod(name,descriptor);
   if(_method== nullptr)
   {
       Console::printlnError("java.lang.NoSuchMethodError");
       exit(1);
   }
   if(!_method->accessibleTo(d))
   {
       Console::printlnError("java.lang.IllegalAccessError");
       exit(1);
   }
   method = _method;
   //method->debug();
}

Method* MethodRef::resolvedMethod()
{
    if(method == nullptr)
        resolveMethodRef();
    return method;
}

InterfaceMemberRef::InterfaceMemberRef(ConstantPool *cp, CONSTANT_InterfaceMethodref *constantInterfaceMethodRefInfo) :MemberRef(constantInterfaceMethodRefInfo)
{
    constantPool = cp;
}

Method* InterfaceMemberRef::resolvedInterfaceMethod()
{
    if(method==nullptr)
        resolveInterfaceMethodRef();
    return method;
}

void InterfaceMemberRef::resolveInterfaceMethodRef()
{
    auto d = constantPool->_class;
    auto c = resolvedClass();
    if(c->accessFlags & ACC_INTERFACE_FLAG)
    {
        Console::printlnError("java.lang.IncompatibleClassChangeError");
        exit(1);
    }
    auto _method = c->lookUpInterfaceMethod(name,descriptor);
    if(_method== nullptr)
    {
        Console::printlnError("java.lang.NoSuchMethodError");
        exit(1);
    }
    if(!_method->accessibleTo(d))
    {
        Console::printlnError("java.lang.IllegalAccessError");
        exit(1);
    }
    method = _method;
}

ClassRef::ClassRef(ConstantPool *cp, CONSTANT_Class *classInfo)
{
    constantPool = cp;
    className = classInfo->getClassName();
}