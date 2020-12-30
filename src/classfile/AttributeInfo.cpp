//
// Created by XUranus on 2019/1/31.
//

#include "AttributeInfo.h"
#include "ClassReader.h"

TypePath::PathEntry::PathEntry(ClassReader& reader){
    typePathKind = reader.readU1();
    typeArgumentIndex = reader.readU2();
}

TypePath::TypePath(ClassReader &reader) {
    pathLength = reader.readU1();
    for(auto i=0;i<pathLength;i++)
        path.emplace_back(PathEntry(reader));
}

ElementValuePair::ElementValuePair(ClassReader &reader) {
    elementNameIndex = reader.readU2();
    value = new ElementValue(reader);
}

ElementValuePair::~ElementValuePair() {
    //delete value;
}

Annotation::Annotation(ClassReader &reader) {
    typeIndex = reader.readU2();
    numElementValuePairs = reader.readU2();
    for(auto i=0;i<numElementValuePairs;i++)
        elementValuePairs.emplace_back(ElementValuePair(reader));
}

Annotation::Annotation() {
    typeIndex = numElementValuePairs = 0;
    elementValuePairs.clear();
}

ElementValue::ElementValue(ClassReader &reader):
        tag(reader.readU1()),value(tag,reader) {}


ElementValue::Value::Value(u1 tag,ClassReader &reader) {
    //TODO::
    constValueIndex = reader.readU2();
}

ParameterAnnotation::ParameterAnnotation(ClassReader &reader) {
    numAnnotations = reader.readU2();
    for(auto i=0;i<numAnnotations;i++)
        annotations.emplace_back(Annotation(reader));
}

TypeAnnotations::TargetInfo::TargetInfo(u1 targetType, ClassReader &reader) {
    //TODO::
    typeParameterTarget.typeParameterIndex = reader.readU1();
}

TypeAnnotations::TypeAnnotations(ClassReader &reader)
    :targetType(reader.readU1()),targetInfo(targetType,reader),targetPath(reader) {
    typeIndex = reader.readU2();
    numElementValuePairs = reader.readU2();
    for(auto i=0;i<numElementValuePairs;i++)
        elementValuePairs.emplace_back(ElementValuePair(reader));
}
//-----------------------------------------------------------------------------------/

AttributeInfo::AttributeInfo(u2 _attributeNameAndIndex, u4 _attributeLength, CpInfo **_constantPool)
{
    attributeNameAndIndex = _attributeNameAndIndex;
    attributeLength = _attributeLength;
    constantPool = _constantPool;
}

std::string AttributeInfo::getAttributeName() {
    return constantPool[attributeNameAndIndex]->getUtf8();
}

void AttributeInfo::debug() {
    printf("[NOT IMPLEMENTED] attributeName: %s, length: %lu\n",getAttributeName().c_str(),attributeLength);
}

Attribute_ConstantValue::Attribute_ConstantValue(u2 _attributeNameAndIndex, u4 _attributeLength, CpInfo **_constantPool,ClassReader &reader):AttributeInfo(_attributeNameAndIndex,_attributeLength,_constantPool) {
    constantValueIndex = reader.readU2();
}

Attribute_Code::Attribute_Code(u2 _attributeNameAndIndex, u4 _attributeLength, CpInfo **_constantPool,ClassReader &reader):AttributeInfo(_attributeNameAndIndex,_attributeLength,_constantPool) {
    maxStacks = reader.readU2();
    maxLocals = reader.readU2();
    codeLength = reader.readU4();
    //read codes
    codes = new u1[codeLength];
    for(u4 i=0;i<codeLength;i++)
        codes[i] = reader.readU1();
    exceptionTableLength = reader.readU2();
    //read exception table
    for(u2 i=0;i<exceptionTableLength;i++)
        exceptionTable.emplace_back(ExceptionTableEntry(reader));
    //read attributes
    attributesCount = reader.readU2();
    for(u2 i=0;i<attributesCount;i++)
        attributes.emplace_back(reader.readAttributeInfo(_constantPool));
}

Attribute_Code::ExceptionTableEntry::ExceptionTableEntry(ClassReader &reader) {
    startPc = reader.readU2();
    endPc = reader.readU2();
    handlerPc = reader.readU2();
    catchType = reader.readU2();
}


void Attribute_Code::debug() {
    printf("attributeName: %s, length: %lu\n",getAttributeName().c_str(),attributeLength);
}

Attribute_Code::~Attribute_Code() {
    delete codes;
}


Attribute_Exceptions::Attribute_Exceptions(u2 _attributeNameAndIndex, u4 _attributeLength, CpInfo **_constantPool,ClassReader &reader):AttributeInfo(_attributeNameAndIndex,_attributeLength,_constantPool)
{
    numberOfExceptions = reader.readU2();
    for(auto i=0;i<numberOfExceptions;i++)
        exceptionIndexTable.push_back(reader.readU2());
}


Attribute_SourceFile::Attribute_SourceFile(u2 _attributeNameAndIndex, u4 _attributeLength, CpInfo **_constantPool,ClassReader &reader):AttributeInfo(_attributeNameAndIndex,_attributeLength,_constantPool)
{
    sourceFileIndex = reader.readU2();
}

Attribute_LineNumberTable::Attribute_LineNumberTable(u2 _attributeNameAndIndex, u4 _attributeLength, CpInfo **_constantPool,ClassReader &reader):AttributeInfo(_attributeNameAndIndex,_attributeLength,_constantPool)
{
    lineNumberTableLength = reader.readU2();
    for(u2 i=0;i<lineNumberTableLength;i++)
        lineNumberTable.emplace_back(LineNumberTableEntry(reader));
}

Attribute_LineNumberTable::LineNumberTableEntry::LineNumberTableEntry(ClassReader &reader) {
    startPc = reader.readU2();
    lineNumber = reader.readU2();
}

Attribute_LocalVariableTable::Attribute_LocalVariableTable(u2 _attributeNameAndIndex, u4 _attributeLength, CpInfo **_constantPool,ClassReader &reader):AttributeInfo(_attributeNameAndIndex,_attributeLength,_constantPool)
{
    localVariableTableLength = reader.readU2();
    for(u2 i=0;i<localVariableTableLength;i++)
        localVariableTable.emplace_back(LocalVariableTableEntry(reader));
}

Attribute_LocalVariableTable::LocalVariableTableEntry::LocalVariableTableEntry(ClassReader &reader) {
    startPc = reader.readU2();
    length = reader.readU2();
    nameIndex = reader.readU2();
    descriptorIndex = reader.readU2();
    index = reader.readU2();
}


Attribute_LocalVariableTable::LocalVariableTableEntry::LocalVariableTableEntry() {
    startPc = length = nameIndex = descriptorIndex = index = 0;
}

Attribute_InnerClasses::Attribute_InnerClasses(u2 _attributeNameAndIndex, u4 _attributeLength, CpInfo **_constantPool,ClassReader &reader):AttributeInfo(_attributeNameAndIndex,_attributeLength,_constantPool)
{
    numberOfClasses = reader.readU2();
    //printf("num = %d",numberOfClasses);
    for(auto i=0;i<numberOfClasses;i++)
        classes.emplace_back(ClassEntry(reader));
}


Attribute_InnerClasses::ClassEntry::ClassEntry(ClassReader &reader)
{
    innerClassInfoIndex = reader.readU2();
    outerClassInfoIndex = reader.readU2();
    innerNameIndex = reader.readU2();
    innerClassAccessFlags = reader.readU2();
   // printf("%d %d %d %d",innerNameIndex,outerClassInfoIndex,innerNameIndex,innerClassAccessFlags);
}

Attribute_Synthetic::Attribute_Synthetic(u2 _attributeNameAndIndex, u4 _attributeLength, CpInfo **_constantPool,ClassReader &reader):AttributeInfo(_attributeNameAndIndex,_attributeLength,_constantPool)
{}

Attribute_Deprecated::Attribute_Deprecated(u2 _attributeNameAndIndex, u4 _attributeLength, CpInfo **_constantPool,ClassReader &reader):AttributeInfo(_attributeNameAndIndex,_attributeLength,_constantPool)
{}

Attribute_EnclosingMethod::Attribute_EnclosingMethod(u2 _attributeNameAndIndex, u4 _attributeLength, CpInfo **_constantPool,ClassReader &reader):AttributeInfo(_attributeNameAndIndex,_attributeLength,_constantPool) {
    classIndex = reader.readU2();
    methodIndex = reader.readU2();
}

Attribute_Signature::Attribute_Signature(u2 _attributeNameAndIndex, u4 _attributeLength, CpInfo **_constantPool,ClassReader &reader):AttributeInfo(_attributeNameAndIndex,_attributeLength,_constantPool) {
    signatureIndex = reader.readU2();
}

Attribute_SourceDebugExtension::Attribute_SourceDebugExtension(u2 _attributeNameAndIndex, u4 _attributeLength, CpInfo **_constantPool,ClassReader &reader):AttributeInfo(_attributeNameAndIndex,_attributeLength,_constantPool)
{
    for(auto i=0;i<attributeLength;i++)
        debugExtension.push_back(reader.readU1());
}


Attribute_LocalVariableTypeTable::Attribute_LocalVariableTypeTable(u2 _attributeNameAndIndex, u4 _attributeLength, CpInfo **_constantPool,ClassReader &reader):AttributeInfo(_attributeNameAndIndex,_attributeLength,_constantPool) {
    localVariableTypeTableLength = reader.readU2();
    for(auto i=0;i<localVariableTypeTableLength;i++)
        localVariableTypeTable.emplace_back(LocalVariableTypeTableEntry(reader));
}

Attribute_LocalVariableTypeTable::LocalVariableTypeTableEntry::LocalVariableTypeTableEntry(ClassReader &reader) {
    startPc = reader.readU2();
    length = reader.readU2();
    nameIndex = reader.readU2();
    signatureIndex = reader.readU2();
    index = reader.readU2();
}


Attribute_RuntimeVisibleAnnotations::Attribute_RuntimeVisibleAnnotations(u2 _attributeNameAndIndex, u4 _attributeLength, CpInfo **_constantPool,ClassReader &reader):AttributeInfo(_attributeNameAndIndex,_attributeLength,_constantPool) {
    numAnnotations = reader.readU2();
    for(auto i=0;i<numAnnotations;i++)
        annoatations.emplace_back(Annotation(reader));
}

Attribute_RuntimeInvisibleAnnotations::Attribute_RuntimeInvisibleAnnotations(u2 _attributeNameAndIndex, u4 _attributeLength, CpInfo **_constantPool,ClassReader &reader):AttributeInfo(_attributeNameAndIndex,_attributeLength,_constantPool) {
    numAnnotations = reader.readU2();
    for(auto i=0;i<numAnnotations;i++)
        annoatations.emplace_back(Annotation(reader));
}

Attribute_RuntimeVisibleParameterAnnotations::Attribute_RuntimeVisibleParameterAnnotations(u2 _attributeNameAndIndex, u4 _attributeLength, CpInfo **_constantPool,ClassReader &reader):AttributeInfo(_attributeNameAndIndex,_attributeLength,_constantPool) {
    numParameters = reader.readU1();
    for(auto i=0;i<numParameters;i++)
        parameterAnnotations.emplace_back(ParameterAnnotation(reader));
}

Attribute_RuntimeInvisibleParameterAnnotations::Attribute_RuntimeInvisibleParameterAnnotations(u2 _attributeNameAndIndex, u4 _attributeLength, CpInfo **_constantPool,ClassReader &reader):AttributeInfo(_attributeNameAndIndex,_attributeLength,_constantPool) {
    numParameters = reader.readU1();
    for(auto i=0;i<numParameters;i++)
        parameterAnnotations.emplace_back(ParameterAnnotation(reader));
}

Attribute_AnnotationDefault::Attribute_AnnotationDefault(u2 _attributeNameAndIndex, u4 _attributeLength, CpInfo **_constantPool,ClassReader &reader):AttributeInfo(_attributeNameAndIndex,_attributeLength,_constantPool),defaultValue(reader) {
}

Attribute_StackMapTable::Attribute_StackMapTable(u2 _attributeNameAndIndex, u4 _attributeLength, CpInfo **_constantPool,ClassReader &reader):AttributeInfo(_attributeNameAndIndex,_attributeLength,_constantPool)
{
    numbersOfEntries = reader.readU2();
    entries = new StackMapFrame[numbersOfEntries];
    for(auto i=0;i<numbersOfEntries;i++) {
        entries[i] = StackMapFrame(reader);
    }
}

Attribute_StackMapTable::StackMapFrame::StackMapFrame(ClassReader &reader) {
    u1 frame_type = reader.readU1();
    if(frame_type >= 0 && frame_type <= 63) {
        same_frame.frame_type = frame_type;
    } else if(frame_type >=64 && frame_type <= 127) {
        same_locals_1_stack_item_frame.frame_type = frame_type;
        same_locals_1_stack_item_frame.stack[0] = Verification_type_info(reader);
    } else if(frame_type==247) {
        same_locals_1_stack_item_frame_extended.frame_type = frame_type;
        same_locals_1_stack_item_frame_extended.offset_delta = reader.readU2();
        same_locals_1_stack_item_frame_extended.stack[0] = Verification_type_info(reader);
    } else if(frame_type >= 248 && frame_type <= 250) {
        chop_frame.frame_type = frame_type;
        chop_frame.offset_delta = reader.readU2();
    } else if(frame_type == 251) {
        same_frame_extended.frame_type = frame_type;
        same_frame_extended.offset_delta = reader.readU2();
    } else if(frame_type >= 252 & frame_type <= 254) {
        append_frame.frame_type = frame_type;
        append_frame.offset_delta = reader.readU2();
        append_frame.locals = new Verification_type_info[frame_type-251];
        for(auto i=0;i<frame_type-251;i++)
            append_frame.locals[i] = Verification_type_info(reader);
    } else if(frame_type == 255) {
        full_frame.frame_type = frame_type;
        full_frame.offset_delta = reader.readU2();
        full_frame.number_of_locals = reader.readU2();
        full_frame.locals = new Verification_type_info[full_frame.number_of_locals];
        for(auto i=0;i<full_frame.number_of_locals;i++)
            full_frame.locals[i] = Verification_type_info(reader);
        full_frame.number_of_stack_items = reader.readU2();
        full_frame.stack = new Verification_type_info[full_frame.number_of_stack_items];
        for(auto i=0;i<full_frame.number_of_stack_items;i++)
            full_frame.stack[i] = Verification_type_info(reader);
    }
}

Attribute_StackMapTable::Verification_type_info::Verification_type_info(ClassReader &reader) {
    u1 tag = reader.readU1();
    if(tag==0) {
        top_variable_info.tag = tag;
    } else if(tag==1) {
        integer_variable_info.tag = tag;
    } else if(tag == 2) {
        float_variable_info.tag = tag;
    } else if(tag == 3) {
        double_variable_info.tag = tag;
    } else if(tag == 4) {
        long_variable_info.tag = tag;
    } else if(tag == 5) {
        null_variable_info.tag = tag;
    } else if(tag == 6) {
        uninitializedThis_variable_info.tag = tag;
    } else if(tag == 7) {
        object_variable_info.tag = tag;
        object_variable_info.cpoolIndex = reader.readU2();
    } else if(tag == 8) {
        uninitialized_variable_info.tag = tag;
        uninitialized_variable_info.offset = reader.readU2();
    } else {
        printf("Verification_type_info read Error, tag:0x%02x\n",tag);
        exit(1);
    }

}

Attribute_BootstrapMethods::Attribute_BootstrapMethods(u2 _attributeNameAndIndex, u4 _attributeLength, CpInfo **_constantPool,ClassReader &reader):AttributeInfo(_attributeNameAndIndex,_attributeLength,_constantPool) {
    numBootstrapMethods = reader.readU2();
    for(auto i=0;i<numBootstrapMethods;i++)
        bootStrapMethod.emplace_back(BootStrapMethodEntry(reader));
}

Attribute_BootstrapMethods::BootStrapMethodEntry::BootStrapMethodEntry(ClassReader &reader) {
    bootstrapMethodRef = reader.readU2();
    numBootstrapArguments = reader.readU2();
    bootstrapArguments.resize(numBootstrapArguments);
    for(auto i=0;i<numBootstrapArguments;i++)
        bootstrapArguments[i] = reader.readU2();
}

Attribute_RuntimeVisibleTypeAnnotations::Attribute_RuntimeVisibleTypeAnnotations(u2 _attributeNameAndIndex, u4 _attributeLength, CpInfo **_constantPool,ClassReader &reader):AttributeInfo(_attributeNameAndIndex,_attributeLength,_constantPool) {
    numAnnotations = reader.readU2();
    for(auto i=0;i>numAnnotations;i++)
        annotations.emplace_back(TypeAnnotations(reader));
}

Attribute_RuntimeInvisibleTypeAnnotations::Attribute_RuntimeInvisibleTypeAnnotations(u2 _attributeNameAndIndex, u4 _attributeLength, CpInfo **_constantPool,ClassReader &reader):AttributeInfo(_attributeNameAndIndex,_attributeLength,_constantPool) {
    numAnnotations = reader.readU2();
    for(auto i=0;i>numAnnotations;i++)
        annotations.emplace_back(TypeAnnotations(reader));
}

Attribute_MethodParameters::Attribute_MethodParameters(u2 _attributeNameAndIndex, u4 _attributeLength, CpInfo **_constantPool,ClassReader &reader):AttributeInfo(_attributeNameAndIndex,_attributeLength,_constantPool) {
    parameterCount = reader.readU1();
    for(auto i=0;i<parameterCount;i++)
        parameters.emplace_back(ParameterEntry(reader));
}

Attribute_MethodParameters::ParameterEntry::ParameterEntry(ClassReader &reader) {
    nameIndex = reader.readU2();
    accessFlags = reader.readU2();
}
