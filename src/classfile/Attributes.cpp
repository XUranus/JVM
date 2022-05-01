//
// Created by XUranus on 2019/1/31.
//

#include "Attributes.h"
#include "../common/Exception.h"
#include <memory>

namespace classfile {

    /**
     * Common Type
     */

    // TypePath
    TypePath::PathEntry::PathEntry(BytesReader &reader) {
        typePathKind = reader.readU1();
        typeArgumentIndex = reader.readU2();
    }

    TypePath::TypePath(BytesReader &reader) {
        pathLength = reader.readU1();
        path.reserve(pathLength);
        for (int i = 0; i < pathLength; i++) {
            path.emplace_back(reader);
        }
    }


    // ElementValuePair
    ElementValuePair::ElementValuePair(BytesReader &reader):
        elementNameIndex(reader.readU2()),
        value(new ElementValue(reader)){}

    // Annotation
    Annotation::Annotation(BytesReader &reader) {
        typeIndex = reader.readU2();
        numElementValuePairs = reader.readU2();
        elementValuePairs.reserve(numElementValuePairs);
        for (auto i = 0; i < numElementValuePairs; i++) {
            elementValuePairs.push_back(std::make_unique<ElementValuePair>(reader));
        }
    }



    ElementValue::ElementValue(BytesReader &reader) {
        tag = reader.readU1();
        if(tag == 'B' || tag == 'C' || tag == 'D' || tag == 'F' || tag == 'I' || tag == 'J'
            || tag == 'S' || tag == 'Z' || tag == 's' ) {
            value.constValueIndex = reader.readU2();
        } else if(tag == 'e') {
            value.enumConstValue = { reader.readU2(), reader.readU2()};
        } else if(tag == 'c') {
            value.classInfoIndex = reader.readU2();
        } else if(tag == '@') {
            value.annotationValue = new Annotation(reader);
        } else if(tag == '[') {
            value.arrayValue.numValues = reader.readU2();
            value.arrayValue.values = new ElementValue*[value.arrayValue.numValues];
            for (int i = 0; i < value.arrayValue.numValues; i++) {
                value.arrayValue.values[i] = new ElementValue(reader);
            }
        }
    }

    ElementValue::~ElementValue() noexcept {
        if(tag == '[') {
            for(int i = 0; i < value.arrayValue.numValues; i++) {
                delete value.arrayValue.values[i];
            }
            delete[] value.arrayValue.values;
        } else if(tag == '@') {
            delete value.annotationValue;
        }
    }


    ParameterAnnotation::ParameterAnnotation(BytesReader &reader) {
        numAnnotations = reader.readU2();
        annotations.reserve(numAnnotations);
        for (int i = 0; i < numAnnotations; i++) {
            annotations.emplace_back(std::make_unique<Annotation>(reader));
        }
    }


    // TypeAnnotations
    TypeAnnotations::TypeAnnotations(BytesReader &reader) {
        targetType = reader.readU1();

        if (targetType == 0x00 || targetType == 0x01) {
            targetInfo.typeParameterTarget = {reader.readU1()};
        } else if(targetType == 0x10) {
            targetInfo.supertypeTarget = {reader.readU2()};
        } else if(targetType == 0x11 || targetType == 0x12) {
            targetInfo.typeParameterBoundTarget = {reader.readU1(), reader.readU1()};
        } else if (targetType == 0x13 || targetType == 0x14 || targetType == 0x15) {
            targetInfo.emptyTarget = {};
        } else if(targetType == 0x16) {
            targetInfo.methodFormalParameterTarget = {reader.readU1()};
        } else if(targetType == 0x17) {
            targetInfo.throwsTarget = {reader.readU2()};
        } else if(targetType == 0x40 || targetType == 0x41) {
            u2 num = reader.readU2();
            targetInfo.localVarTarget = {num, new TypeAnnotations::TargetInfo::LocalVarTarget::TableEntry[num]};
            for (int i = 0; i < num; i++) {
                targetInfo.localVarTarget.table[i] = {reader.readU2(), reader.readU2(), reader.readU2()};
            }
        } else if(targetType == 0x42 ) {
            targetInfo.catchTarget = {reader.readU2()};
        } else if(0x43 <= targetType && targetType <= 0x46 ) {
            targetInfo.offsetTarget = {reader.readU2()};
        } else if(0x47 <= targetType && targetType <= 0x4B ) {
            targetInfo.typeArgumentTarget = {reader.readU2(), reader.readU1()};
        }

        targetPath = new TypePath(reader);
        typeIndex = reader.readU2();
        numElementValuePairs = reader.readU2();
        elementValuePairs = new ElementValuePair*[numElementValuePairs];
        for (u2 i = 0; i < numElementValuePairs; i++) {
            elementValuePairs[i] = new ElementValuePair(reader);
        }
    }

    TypeAnnotations::~TypeAnnotations() {
        if(targetType == 0x40 || targetType == 0x41) {
            delete[] targetInfo.localVarTarget.table;
        }
        delete targetPath;
        for(u2 i = 0; i < numElementValuePairs; i++) {
            delete elementValuePairs[i];
        }
        delete[] elementValuePairs;
    }

}





/**
 * Attribute Info
 */

namespace classfile {

    AttributeInfo *AttributeInfo::from(BytesReader &reader, ConstantsPool* constantsPool) {
        u2 nameIndex = reader.readU2();
        u4 length = reader.readU4();
        std::string attributeName = constantsPool->utf8(nameIndex);

        //todo::
//        std::cout << attributeName << std::endl;

        if(attributeName == "ConstantValue")                              return new AttributeConstantValue(nameIndex,length,constantsPool,reader);
        else if(attributeName == "Code")                                  return new AttributeCode(nameIndex,length,constantsPool,reader);
        else if(attributeName == "Exceptions")                            return new AttributeExceptions(nameIndex,length,constantsPool,reader);
        else if(attributeName == "SourceFile")                            return new AttributeSourceFile(nameIndex,length,constantsPool,reader);
        else if(attributeName == "LineNumberTable")                       return new AttributeLineNumberTable(nameIndex,length,constantsPool,reader);
        else if(attributeName == "LocalVariableTable")                    return new AttributeLocalVariableTable(nameIndex,length,constantsPool,reader);
        else if(attributeName == "InnerClasses")                          return new AttributeInnerClasses(nameIndex,length,constantsPool,reader);
        else if(attributeName == "Synthetic")                             return new AttributeSynthetic(nameIndex,length,constantsPool,reader);
        else if(attributeName == "Deprecated")                            return new AttributeDeprecated(nameIndex,length,constantsPool,reader);
        else if(attributeName == "EnclosingMethod")                       return new AttributeEnclosingMethod(nameIndex,length,constantsPool,reader);
        else if(attributeName == "Signature")                             return new AttributeSignature(nameIndex,length,constantsPool,reader);
        else if(attributeName == "SourceDebugExtension")                  return new AttributeSourceDebugExtension(nameIndex,length,constantsPool,reader);
        else if(attributeName == "LocalVariableTypeTable")                return new AttributeLocalVariableTypeTable(nameIndex,length,constantsPool,reader);
        else if(attributeName == "RuntimeVisibleAnnotations")             return new AttributeRuntimeVisibleAnnotations(nameIndex,length,constantsPool,reader);
        else if(attributeName == "RuntimeInvisibleAnnotations")           return new AttributeRuntimeInvisibleAnnotations(nameIndex,length,constantsPool,reader);
        else if(attributeName == "RuntimeVisibleParameterAnnotations")    return new AttributeRuntimeVisibleParameterAnnotations(nameIndex,length,constantsPool,reader);
        else if(attributeName == "RuntimeInvisibleParameterAnnotations")  return new AttributeRuntimeInvisibleParameterAnnotations(nameIndex,length,constantsPool,reader);
        else if(attributeName == "AnnotationDefault")                     return new AttributeAnnotationDefault(nameIndex,length,constantsPool,reader);
        else if(attributeName == "StackMapTable")                         return new AttributeStackMapTable(nameIndex,length,constantsPool,reader);
        else if(attributeName == "BootstrapMethods")                      return new AttributeBootstrapMethods(nameIndex,length,constantsPool,reader);
        else if(attributeName == "RuntimeVisibleTypeAnnotations")         return new AttributeRuntimeVisibleTypeAnnotations(nameIndex,length,constantsPool,reader);
        else if(attributeName == "RuntimeInvisibleTypeAnnotations")       return new AttributeRuntimeInvisibleTypeAnnotations(nameIndex,length,constantsPool,reader);
        else if(attributeName == "MethodParameters")                      return new AttributeMethodParameters(nameIndex,length,constantsPool,reader);
        else {
            exception::panic("no such attribute: " + attributeName);
        }
        return nullptr;
    }

    AttributeInfo::AttributeInfo() = default;

    AttributeInfo::~AttributeInfo() noexcept = default;

    AttributeInfo::AttributeInfo(u2 _nameIndex, u4 _length, ConstantsPool* _constantsPool) {
        nameIndex = _nameIndex;
        length = _length;
        constantPool = _constantsPool;
    }

    std::string AttributeInfo::name() const {
        return constantPool->utf8(nameIndex);
    }

    AttributeConstantValue::AttributeConstantValue(u2 nameIndex, u4 length, ConstantsPool *constantsPool, BytesReader &reader):
        AttributeInfo(nameIndex, length, constantsPool) {
        constantValueIndex = reader.readU2();
    }

    AttributeCode::AttributeCode(u2 nameIndex, u4 length, ConstantsPool *constantsPool, BytesReader &reader):
        AttributeInfo(nameIndex, length, constantsPool) {
        maxStacks = reader.readU2();
        maxLocals = reader.readU2();

        //read codes
        codeLength = reader.readU4();
        codes = new u1[codeLength];
        reader.read(codes, codeLength);

        //read exception table
        exceptionTableLength = reader.readU2();
        exceptionTable.reserve(exceptionTableLength);
        for (u2 i = 0; i < exceptionTableLength; i++) {
            exceptionTable[i] = ExceptionTableEntry(reader);
        }

        //read attributes
        attributesCount = reader.readU2();
        attributes.reserve(attributesCount);
        for (u2 i = 0; i < attributesCount; i++) {
            attributes.emplace_back(std::unique_ptr<AttributeInfo>(AttributeInfo::from(reader, constantsPool)));
        }
    }

    AttributeLineNumberTable *AttributeCode::attributeLineNumberTable() {
        for(auto& attributeInfo: attributes) {
            if(attributeInfo->name() == "LineNumberTable") {
                return (AttributeLineNumberTable*)attributeInfo.get();
            }
        }
        return nullptr;
    }


    AttributeCode::ExceptionTableEntry::ExceptionTableEntry(BytesReader &reader) {
        startPC = reader.readU2();
        endPC = reader.readU2();
        handlerPC = reader.readU2();
        catchType = reader.readU2();
    }

    AttributeCode::~AttributeCode() {
        delete[] codes;
    }


    AttributeExceptions::AttributeExceptions(u2 nameIndex, u4 length, ConstantsPool *constantsPool, BytesReader &reader):
        AttributeInfo(nameIndex, length, constantsPool) {
        numberOfExceptions = reader.readU2();
        exceptionIndexTable.reserve(numberOfExceptions);
        for (u2 i = 0; i < numberOfExceptions; i++) {
            exceptionIndexTable[i] = reader.readU2();
        }
    }

    AttributeSourceFile::AttributeSourceFile(u2 nameIndex, u4 length, ConstantsPool *constantsPool,BytesReader &reader):
        AttributeInfo(nameIndex, length, constantsPool) {
        sourceFileIndex = reader.readU2();
    }

    AttributeLineNumberTable::AttributeLineNumberTable(u2 nameIndex, u4 length, ConstantsPool *constantsPool, BytesReader &reader):
        AttributeInfo(nameIndex, length, constantsPool) {
        lineNumberTableLength = reader.readU2();
        lineNumberTable.reserve(lineNumberTableLength);
        for (u2 i = 0; i < lineNumberTableLength; i++) {
            lineNumberTable[i] = LineNumberTableEntry(reader);
        }
    }

    AttributeLineNumberTable::LineNumberTableEntry::LineNumberTableEntry(BytesReader &reader) {
        startPC = reader.readU2();
        lineNumber = reader.readU2();
    }

    AttributeLocalVariableTable::LocalVariableTableEntry::LocalVariableTableEntry(BytesReader &reader) {
        startPC = reader.readU2();
        length = reader.readU2();
        nameIndex = reader.readU2();
        descriptorIndex = reader.readU2();
        index = reader.readU2();
    }

    AttributeLocalVariableTable::AttributeLocalVariableTable(u2 nameIndex, u4 length, ConstantsPool *constantsPool, BytesReader &reader):
        AttributeInfo(nameIndex, length, constantsPool) {
        localVariableTableLength = reader.readU2();
        localVariableTable.reserve(localVariableTableLength);
        for (u2 i = 0; i < localVariableTableLength; i++) {
            localVariableTable[i] = LocalVariableTableEntry(reader);
        }
    }


    AttributeInnerClasses::ClassEntry::ClassEntry(BytesReader &reader) {
        innerClassInfoIndex = reader.readU2();
        outerClassInfoIndex = reader.readU2();
        innerNameIndex = reader.readU2();
        innerClassAccessFlags = reader.readU2();
    }

    AttributeInnerClasses::AttributeInnerClasses(u2 nameIndex, u4 length, ConstantsPool *constantsPool, BytesReader &reader):
        AttributeInfo(nameIndex, length, constantsPool) {
        numberOfClasses = reader.readU2();
        classes.reserve(numberOfClasses);
        for (u2 i = 0; i < numberOfClasses; i++) {
            classes[i] = ClassEntry(reader);
        }
    }


    AttributeSynthetic::AttributeSynthetic(u2 nameIndex, u4 length, ConstantsPool *constantsPool, BytesReader &reader):
            AttributeInfo(nameIndex, length, constantsPool) {}

    AttributeDeprecated::AttributeDeprecated(u2 nameIndex, u4 length, ConstantsPool *constantsPool, BytesReader &reader):
            AttributeInfo(nameIndex, length, constantsPool) {}

    AttributeEnclosingMethod::AttributeEnclosingMethod(u2 nameIndex, u4 length, ConstantsPool *constantsPool, BytesReader &reader):
        AttributeInfo(nameIndex, length, constantsPool) {
        classIndex = reader.readU2();
        methodIndex = reader.readU2();
    }

    AttributeSignature::AttributeSignature(u2 nameIndex, u4 length, ConstantsPool *constantsPool, BytesReader &reader):
        AttributeInfo(nameIndex, length, constantsPool) {
        signatureIndex = reader.readU2();
    }

    AttributeSourceDebugExtension::AttributeSourceDebugExtension(u2 nameIndex, u4 length, ConstantsPool *constantsPool, BytesReader &reader):
        AttributeInfo(nameIndex, length, constantsPool) {
        for (u4 i = 0; i < length; i++) {
            reader.read(debugExtension, length);
        }
    }

    AttributeSourceDebugExtension::~AttributeSourceDebugExtension() {
        delete[] debugExtension;
    }


    AttributeLocalVariableTypeTable::LocalVariableTypeTableEntry::LocalVariableTypeTableEntry(BytesReader &reader) {
        startPC = reader.readU2();
        length = reader.readU2();
        nameIndex = reader.readU2();
        signatureIndex = reader.readU2();
        index = reader.readU2();
    }

    AttributeLocalVariableTypeTable::AttributeLocalVariableTypeTable(u2 nameIndex, u4 length, ConstantsPool *constantsPool, BytesReader &reader):
        AttributeInfo(nameIndex, length, constantsPool) {
        localVariableTypeTableLength = reader.readU2();
        localVariableTypeTable.reserve(localVariableTypeTableLength);
        for (u2 i = 0; i < localVariableTypeTableLength; i++) {
            localVariableTypeTable[i] = LocalVariableTypeTableEntry(reader);
        }
    }


    AttributeRuntimeVisibleAnnotations::AttributeRuntimeVisibleAnnotations(u2 nameIndex, u4 length, ConstantsPool *constantsPool, BytesReader &reader):
        AttributeInfo(nameIndex, length, constantsPool) {
        numAnnotations = reader.readU2();
        annotations.reserve(numAnnotations);
        for (auto i = 0; i < numAnnotations; i++) {
            annotations.emplace_back(std::make_unique<Annotation>(reader));
        }
    }


    AttributeRuntimeVisibleParameterAnnotations::AttributeRuntimeVisibleParameterAnnotations(u2 nameIndex, u4 length, ConstantsPool *constantsPool, BytesReader &reader):
        AttributeInfo(nameIndex, length, constantsPool) {
        numParameters = reader.readU1();
        parameterAnnotations.reserve(numParameters);
        for (u1 i = 0; i < numParameters; i++) {
            parameterAnnotations.emplace_back(std::make_unique<ParameterAnnotation>(reader));
        }
    }

    AttributeAnnotationDefault::AttributeAnnotationDefault(u2 nameIndex, u4 length, ConstantsPool *constantsPool, BytesReader &reader):
        AttributeInfo(nameIndex, length, constantsPool) {
        defaultValue = new ElementValue(reader);
    }


    AttributeStackMapTable::VerificationTypeInfo::VerificationTypeInfo(BytesReader &reader) {
        u1 tag = reader.readU1();
        if (tag == 0) {
            topVariableInfo.tag = tag;
        } else if (tag == 1) {
            integerVariableInfo.tag = tag;
        } else if (tag == 2) {
            floatVariableInfo.tag = tag;
        } else if (tag == 3) {
            doubleVariableInfo.tag = tag;
        } else if (tag == 4) {
            longVariableInfo.tag = tag;
        } else if (tag == 5) {
            nullVariableInfo.tag = tag;
        } else if (tag == 6) {
            uninitializedThisVariableInfo.tag = tag;
        } else if (tag == 7) {
            objectVariableInfo.tag = tag;
            objectVariableInfo.cPoolIndex = reader.readU2();
        } else if (tag == 8) {
            uninitializedVariableInfo.tag = tag;
            uninitializedVariableInfo.offset = reader.readU2();
        } else {
            exception::panic("VerificationTypeInfo read Error, tag: " + std::to_string(tag));
        }
    }


    AttributeStackMapTable::StackMapFrame::StackMapFrame(BytesReader &reader) {
        u1 frameType = reader.readU1();
        if (frameType >= 0 && frameType <= 63) {
            sameFrame.frameType = frameType;
        } else if (frameType >= 64 && frameType <= 127) {
            sameLocals1StackItemFrame.frameType = frameType;
            sameLocals1StackItemFrame.stack[0] = VerificationTypeInfo(reader);
        } else if (frameType == 247) {
            sameLocals1StackItemFrameExtended.frameType = frameType;
            sameLocals1StackItemFrameExtended.offsetDelta = reader.readU2();
            sameLocals1StackItemFrameExtended.stack[0] = VerificationTypeInfo(reader);
        } else if (frameType >= 248 && frameType <= 250) {
            chopFrame.frameType = frameType;
            chopFrame.offsetDelta = reader.readU2();
        } else if (frameType == 251) {
            sameFrameExtended.frameType = frameType;
            sameFrameExtended.offsetDelta = reader.readU2();
        } else if (frameType >= 252 & frameType <= 254) {
            appendFrame.frameType = frameType;
            appendFrame.offsetDelta = reader.readU2();
            appendFrame.locals = new VerificationTypeInfo[frameType - 251];
            for (u1 i = 0; i < frameType - 251; i++) {
                appendFrame.locals[i] = VerificationTypeInfo(reader);
            }
        } else if (frameType == 255) {
            fullFrame.frameType = frameType;
            fullFrame.offsetDelta = reader.readU2();
            fullFrame.numberOfLocals = reader.readU2();
            fullFrame.locals = new VerificationTypeInfo[fullFrame.numberOfLocals];
            for (u2 i = 0; i < fullFrame.numberOfLocals; i++) {
                fullFrame.locals[i] = VerificationTypeInfo(reader);
            }
            fullFrame.numberOfStackItems = reader.readU2();
            fullFrame.stack = new VerificationTypeInfo[fullFrame.numberOfStackItems];
            for (u2 i = 0; i < fullFrame.numberOfStackItems; i++) {
                fullFrame.stack[i] = VerificationTypeInfo(reader);
            }
        }
    }

    AttributeStackMapTable::StackMapFrame::~StackMapFrame() {
        int frameType = sameFrame.frameType;
        if(frameType >= 252 & frameType <= 254) { // Append Frame {
            delete[] appendFrame.locals;
        } else if(frameType == 255) { // Full Frame
            delete[] fullFrame.locals;
            delete[] fullFrame.stack;
        }
    }


    AttributeStackMapTable::AttributeStackMapTable(u2 nameIndex, u4 length, ConstantsPool *constantsPool, BytesReader &reader):
        AttributeInfo(nameIndex, length, constantsPool) {
        numbersOfEntries = reader.readU2();
        entries.reserve(numbersOfEntries);
        for (auto i = 0; i < numbersOfEntries; i++) {
            entries.emplace_back(std::make_unique<StackMapFrame>(reader));
        }
    }

    AttributeBootstrapMethods::BootStrapMethodEntry::BootStrapMethodEntry(BytesReader &reader) {
        bootstrapMethodRef = reader.readU2();
        numBootstrapArguments = reader.readU2();
        bootstrapArguments.reserve(numBootstrapArguments);
        for (u2 i = 0; i < numBootstrapArguments; i++) {
            bootstrapArguments[i] = reader.readU2();
        }
    }

    AttributeBootstrapMethods::AttributeBootstrapMethods(u2 nameIndex, u4 length, ConstantsPool *constantsPool, BytesReader &reader):
        AttributeInfo(nameIndex, length, constantsPool) {
        numBootstrapMethods = reader.readU2();
        bootStrapMethods.reserve(numBootstrapMethods);
        for (u2 i = 0; i < numBootstrapMethods; i++) {
            bootStrapMethods.emplace_back(std::make_unique<BootStrapMethodEntry>(reader));
        }
    }

    AttributeRuntimeVisibleTypeAnnotations::AttributeRuntimeVisibleTypeAnnotations(u2 nameIndex, u4 length, ConstantsPool *constantsPool, BytesReader &reader):
        AttributeInfo(nameIndex, length, constantsPool) {
        numAnnotations = reader.readU2();
        annotations.reserve(numAnnotations);
        for (auto i = 0; i > numAnnotations; i++) {
            annotations.emplace_back(std::make_unique<TypeAnnotations>(reader));
        }
    }

    AttributeMethodParameters::ParameterEntry::ParameterEntry(BytesReader &reader) {
        nameIndex = reader.readU2();
        accessFlags = reader.readU2();
    }

    AttributeMethodParameters::AttributeMethodParameters(u2 nameIndex, u4 length, ConstantsPool *constantsPool, BytesReader &reader):
        AttributeInfo(nameIndex, length, constantsPool) {
        parameterCount = reader.readU1();
        parameters.reserve(parameterCount);
        for (u1 i = 0; i < parameterCount; i++) {
            parameters[i] = ParameterEntry(reader);
        }
    }

}