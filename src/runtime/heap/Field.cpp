//
// Created by xuranus on 2/16/19.
//

#include "Field.h"



Field::Field(FieldInfo *fieldInfo,Class* classRef)
{
    //copy member info
    accessFlags = fieldInfo->accessFlags;
    name = fieldInfo->getName();
    descriptor = fieldInfo->getDescriptorName();

    _class = classRef;
    slotId = 0;//init


    constValueIndex = 0;
    auto attr = fieldInfo->getConstantValueAttribute();
    if(attr!= nullptr)
        constValueIndex = (unsigned int)attr->constantValueIndex;
}

std::vector<Field*> Field::parseFields(ClassFile *classFile,Class* classRef)
{
    std::vector<Field*> ret;
    for(u2 i=0;i<classFile->fieldsCount;i++)
        ret.emplace_back(new Field(classFile->fields[i],classRef));
    return ret;
}

bool Field::isLongOrDouble()
{
    return descriptor=="J" || descriptor=="D";
}

