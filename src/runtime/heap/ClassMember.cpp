//
// Created by xuranus on 2/16/19.
//

#include "ClassMember.h"
#include "Class.h"

/******************************** ClassMember  ***************************/

ClassMember::ClassMember() { //init parent
    accessFlags = 0;
    name = "";
    descriptor = "";
    _class = nullptr;
}

bool ClassMember::accessibleTo(Class *d)
{
    if(accessFlags & ACC_PUBLIC_FLAG)
        return true;
    if(accessFlags & ACC_PROTECTED_FLAG)
        return (d==_class || d->isSubClassOf(_class) || _class->getPackageName()==d->getPackageName());
    if(!(accessFlags & ACC_PRIVATE_FLAG))
        return _class->getPackageName()==d->getPackageName();
    return d == _class;
}