//
// Created by XUranus on 2019/1/31.
//

#ifndef JVM_ATTRIBUTEINFO_H
#define JVM_ATTRIBUTEINFO_H

#include "basicType.h"
#include <string>
#include "CpInfo.h"
#include <vector>

//https://docs.oracle.com/javase/specs/jvms/se8/html/jvms-4.html#jvms-4.7.4
struct ClassReader;


// ---------------------  multiple use inner struction  --------------------------//
struct ElementValue;//declare only

struct TypePath {
    struct PathEntry {
        u1 typePathKind;
        u2 typeArgumentIndex;
        explicit PathEntry(ClassReader& reader);
    };
    u1 pathLength;
    std::vector<PathEntry> path;
    explicit TypePath(ClassReader& reader);
};

struct ElementValuePair {
    u2 elementNameIndex;
    ElementValue* value;
    explicit ElementValuePair(ClassReader& reader);
    ~ElementValuePair();
};

struct Annotation {
    u2 typeIndex;
    u2 numElementValuePairs;
    std::vector<ElementValuePair> elementValuePairs;//numElementValuePairs

    explicit Annotation(ClassReader& reader);
    Annotation();
};

struct ElementValue {
    struct Value { //TODO::union is better!!!
        u2 constValueIndex;
        struct {
            u2 typeNameIndex;
            u2 constNameIndex;
        } enumConstValue;
        u2 classInfoIndex;
        Annotation annotationValue;
        struct {
            u2 numValues;
            std::vector<ElementValue> values;
        } arrayValue;

        Value(u1 tag,ClassReader&reader);
        ~Value(){}
    };

    u1 tag;
    Value value;

    explicit ElementValue(ClassReader& reader);
};


struct ParameterAnnotation {
    u2 numAnnotations;
    std::vector<Annotation> annotations;//numAnnotations
    explicit ParameterAnnotation(ClassReader& reader);
};

struct TypeAnnotations{
    struct TargetInfo{ //TODO::union is better
        struct typeParameterTarget {
            u1 typeParameterIndex;
        } typeParameterTarget;
        struct SupertypeTarget {
            u2 supertypeIndex;
        } supertypeTarget;
        struct TypeParameterBoundTarget {
            u1 typeParameterIndex;
            u1 boundIndex;
        } typeParameterBoundTarget;
        struct EmptyTarget {
            //nothing
        } emptyTarget;
        struct MethodFormalParameterTarget {
            u1 formalParameterIndex;
        } methodFormalParameterTarget;
        struct ThrowsTarget {
            u2 throwsTypeIndex;
        } throwsTarget;
        struct LocalVarTarget {
            struct TableEntry {
                u2 startPc;
                u2 length;
                u2 index;
            };
            u2 tableLength;
            std::vector<TableEntry> table;//tableLength
        } localVarTarget;
        struct CatchTarget {
            u2 exceptionTableIndex;
        } catchTarget;
        struct OffsetTarget {
            u2 offset;
        } offsetTarget;
        struct TypeArgumentTarget {
            u2 offset;
            u1 typeArgumentIndex;
        } typeArgumentTarget;

        TargetInfo(u1 targetType,ClassReader& reader);
        ~TargetInfo(){}
    };

    u1 targetType;
    TargetInfo targetInfo;
    TypePath targetPath;
    u2 typeIndex;
    u2 numElementValuePairs;
    std::vector<ElementValuePair> elementValuePairs;//numElementValuePairs
    explicit TypeAnnotations(ClassReader& reader);
};



// -------------------------------------------------------------------------------//

struct AttributeInfo { //basic class
    u2 attributeNameAndIndex;
    u4 attributeLength;

    CpInfo** constantPool;//for refer
    //u1 *info//[attributeLength];

    AttributeInfo(u2 attributeNameAndIndex,u4 attributeLength,CpInfo** constantPool);
    std::string getAttributeName();
    virtual void debug();
};

//Derived Classes

struct Attribute_ConstantValue:public AttributeInfo {
    u2 constantValueIndex;
    Attribute_ConstantValue(u2 _attributeNameAndIndex,u4 _attributeLength,CpInfo** _constantPool,ClassReader& reader);
};


struct Attribute_Code:public AttributeInfo {
    struct ExceptionTableEntry {
        u2 startPc;
        u2 endPc;
        u2 handlerPc;
        u2 catchType;
        explicit ExceptionTableEntry(ClassReader& reader);
    };

    u2 maxStacks;
    u2 maxLocals;
    u4 codeLength;
    u1 *codes;//[codeLength]
    u2 exceptionTableLength;
    std::vector<ExceptionTableEntry> exceptionTable;//[exceptionTableLength]
    u2 attributesCount;
    std::vector<AttributeInfo*> attributes;//[attributesCount]

    Attribute_Code(u2 _attributeNameAndIndex,u4 _attributeLength,CpInfo** _constantPool,ClassReader& reader);
    ~Attribute_Code();
    void debug() override;
};

struct Attribute_Exceptions:public AttributeInfo {
    u2 numberOfExceptions;
    std::vector<u2> exceptionIndexTable;//numberOfException

    Attribute_Exceptions(u2 _attributeNameAndIndex,u4 _attributeLength,CpInfo** _constantPool,ClassReader& reader);
};

struct Attribute_SourceFile:public AttributeInfo {
    u2 sourceFileIndex;
    Attribute_SourceFile(u2 _attributeNameAndIndex,u4 _attributeLength,CpInfo** _constantPool,ClassReader& reader);
};


struct Attribute_LineNumberTable:public AttributeInfo {
    struct LineNumberTableEntry {
        u2 startPc;
        u2 lineNumber;
        LineNumberTableEntry(ClassReader &reader);
    };

    u2 lineNumberTableLength;
    std::vector<LineNumberTableEntry> lineNumberTable;//[lineNumberTableLength]
    Attribute_LineNumberTable(u2 _attributeNameAndIndex,u4 _attributeLength,CpInfo** _constantPool,ClassReader& reader);
};

struct Attribute_LocalVariableTable:public AttributeInfo {
    struct LocalVariableTableEntry {
        u2 startPc;
        u2 length;
        u2 nameIndex;
        u2 descriptorIndex;
        u2 index;

        LocalVariableTableEntry(ClassReader& reader);
        LocalVariableTableEntry();
    };

    u2 localVariableTableLength;
    std::vector<LocalVariableTableEntry> localVariableTable;

    Attribute_LocalVariableTable(u2 _attributeNameAndIndex,u4 _attributeLength,CpInfo** _constantPool,ClassReader& reader);
};

struct Attribute_InnerClasses:public AttributeInfo {
    struct ClassEntry{
        u2 innerClassInfoIndex;
        u2 outerClassInfoIndex;
        u2 innerNameIndex;
        u2 innerClassAccessFlags;

        ClassEntry(ClassReader& reader);
    };

    u2 numberOfClasses;
    std::vector<ClassEntry> classes;//[numberOfClasses]

    Attribute_InnerClasses(u2 _attributeNameAndIndex,u4 _attributeLength,CpInfo** _constantPool,ClassReader& reader);
};

struct Attribute_Synthetic:public AttributeInfo {
    Attribute_Synthetic(u2 _attributeNameAndIndex,u4 _attributeLength,CpInfo** _constantPool,ClassReader& reader);
};

struct Attribute_Deprecated:public AttributeInfo {
    Attribute_Deprecated(u2 _attributeNameAndIndex,u4 _attributeLength,CpInfo** _constantPool,ClassReader& reader);
};

struct Attribute_EnclosingMethod:public AttributeInfo {
    u2 classIndex;
    u2 methodIndex;

    Attribute_EnclosingMethod(u2 _attributeNameAndIndex,u4 _attributeLength,CpInfo** _constantPool,ClassReader& reader);
};

struct Attribute_Signature:public AttributeInfo {
    u2 signatureIndex;

    Attribute_Signature(u2 _attributeNameAndIndex,u4 _attributeLength,CpInfo** _constantPool,ClassReader& reader);
};

struct Attribute_SourceDebugExtension:public AttributeInfo {
    std::vector<u1> debugExtension;//attribute length

    Attribute_SourceDebugExtension(u2 _attributeNameAndIndex,u4 _attributeLength,CpInfo** _constantPool,ClassReader& reader);
};

struct Attribute_LocalVariableTypeTable:public AttributeInfo {
    struct LocalVariableTypeTableEntry {
        u2 startPc;
        u2 length;
        u2 nameIndex;
        u2 signatureIndex;
        u2 index;

        LocalVariableTypeTableEntry(ClassReader& reader);
    };

    u2 localVariableTypeTableLength;
    std::vector<LocalVariableTypeTableEntry> localVariableTypeTable;

    Attribute_LocalVariableTypeTable(u2 _attributeNameAndIndex,u4 _attributeLength,CpInfo** _constantPool,ClassReader& reader);
};

struct Attribute_RuntimeVisibleAnnotations:public AttributeInfo {
    u2 numAnnotations;
    std::vector<Annotation> annoatations;//numAnnoations
    Attribute_RuntimeVisibleAnnotations(u2 _attributeNameAndIndex,u4 _attributeLength,CpInfo** _constantPool,ClassReader& reader);
};

struct Attribute_RuntimeInvisibleAnnotations:public AttributeInfo {
    u2 numAnnotations;
    std::vector<Annotation> annoatations;//numAnnoations
    Attribute_RuntimeInvisibleAnnotations(u2 _attributeNameAndIndex,u4 _attributeLength,CpInfo** _constantPool,ClassReader& reader);
};

struct Attribute_RuntimeVisibleParameterAnnotations:public AttributeInfo {
    u1 numParameters;
    std::vector<ParameterAnnotation> parameterAnnotations;//numParameters
    Attribute_RuntimeVisibleParameterAnnotations(u2 _attributeNameAndIndex,u4 _attributeLength,CpInfo** _constantPool,ClassReader& reader);
};

struct Attribute_RuntimeInvisibleParameterAnnotations:public AttributeInfo {
    //the same as the following!!
    u1 numParameters;
    std::vector<ParameterAnnotation> parameterAnnotations;//numParameters
    Attribute_RuntimeInvisibleParameterAnnotations(u2 _attributeNameAndIndex,u4 _attributeLength,CpInfo** _constantPool,ClassReader& reader);
};

struct Attribute_AnnotationDefault:public AttributeInfo {
    ElementValue defaultValue;
    Attribute_AnnotationDefault(u2 _attributeNameAndIndex,u4 _attributeLength,CpInfo** _constantPool,ClassReader& reader);
};

struct Attribute_StackMapTable:public AttributeInfo {
    union Verification_type_info {
        struct TopVariable_info { u1 tag;} top_variable_info;
        struct Integer_variable_info { u1 tag; } integer_variable_info;
        struct Float_variable_info { u1 tag; } float_variable_info;
        struct Null_variable_info { u1 tag;} null_variable_info;
        struct UninitializedThis_variable_info { u1 tag;} uninitializedThis_variable_info;
        struct Object_variable_info { u1 tag; u2 cpoolIndex;} object_variable_info;
        struct Uninitialized_variable_info { u1 tag;u2 offset;} uninitialized_variable_info;
        struct Long_variable_info { u1 tag;} long_variable_info;
        struct Double_variable_info { u1 tag;} double_variable_info;

        Verification_type_info(ClassReader& reader);
        Verification_type_info(){}
    };

    union StackMapFrame {
        struct Same_frame {
            u1 frame_type;
        } same_frame;
        struct Same_locals_1_stack_item_frame {
            u1 frame_type;
            Verification_type_info stack[1];
        } same_locals_1_stack_item_frame;
        struct Same_locals_1_stack_item_frame_extended {
            u1 frame_type;
            u2 offset_delta;
            Verification_type_info stack[1];
        } same_locals_1_stack_item_frame_extended;
        struct Chop_frame {
            u1 frame_type;
            u2 offset_delta;
        } chop_frame;
        struct Same_frame_extended {
            u1 frame_type;
            u2 offset_delta;
        } same_frame_extended;
        struct Append_frame {
            u1 frame_type;
            u2 offset_delta;
            Verification_type_info* locals;//[frame_type-251]
        } append_frame;
        struct Full_frame {
            u1 frame_type;
            u2 offset_delta;
            u2 number_of_locals;
            Verification_type_info *locals;//[number_of_locals]
            u2 number_of_stack_items;
            Verification_type_info *stack;//[number_of_stack_items]
        } full_frame;

        StackMapFrame(ClassReader& reader);//construction
        StackMapFrame(){};
    };

    u2 numbersOfEntries;
    StackMapFrame *entries;//[numbersOfEntries]

    Attribute_StackMapTable(u2 _attributeNameAndIndex,u4 _attributeLength,CpInfo** _constantPool,ClassReader& reader);
};

struct Attribute_BootstrapMethods:public AttributeInfo {
    struct BootStrapMethodEntry {
        u2 bootstrapMethodRef;
        u2 numBootstrapArguments;
        std::vector<u2> bootstrapArguments;//numBootstrapArguments

        BootStrapMethodEntry(ClassReader& reader);
    } ;

    u2 numBootstrapMethods;
    std::vector<BootStrapMethodEntry> bootStrapMethod;//numBootStrapMethod

    Attribute_BootstrapMethods(u2 _attributeNameAndIndex,u4 _attributeLength,CpInfo** _constantPool,ClassReader& reader);
};

struct Attribute_RuntimeVisibleTypeAnnotations:public AttributeInfo {
    u2 numAnnotations;
    std::vector<TypeAnnotations> annotations;//numAnnotations
    Attribute_RuntimeVisibleTypeAnnotations(u2 _attributeNameAndIndex,u4 _attributeLength,CpInfo** _constantPool,ClassReader& reader);
};

struct Attribute_RuntimeInvisibleTypeAnnotations:public AttributeInfo {
    u2 numAnnotations;
    std::vector<TypeAnnotations> annotations;//numAnnotations
    Attribute_RuntimeInvisibleTypeAnnotations(u2 _attributeNameAndIndex,u4 _attributeLength,CpInfo** _constantPool,ClassReader& reader);
};


struct Attribute_MethodParameters:public AttributeInfo {
    struct ParameterEntry {
        u2 nameIndex;
        u2 accessFlags;
        ParameterEntry(ClassReader& reader);
    };

    u1 parameterCount;
    std::vector<ParameterEntry> parameters;//parameterCount

    Attribute_MethodParameters(u2 _attributeNameAndIndex,u4 _attributeLength,CpInfo** _constantPool,ClassReader& reader);
};





#endif //JVM_ATTRIBUTEINFO_H
