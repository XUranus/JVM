//
// Created by XUranus on 2019/1/31.
//

#ifndef JVM_CLASSFILE_ATTRIBUTES_H
#define JVM_CLASSFILE_ATTRIBUTES_H

#include "../basicType.h"
#include "ClassFile.h"
#include "BytesReader.h"
#include "ConstantsPool.h"
#include <string>

/**
 *  For more about attributes:
 *  https://docs.oracle.com/javase/specs/jvms/se8/html/jvms-4.html#jvms-4.7.4
 */


namespace classfile {
    struct ClassFile;
    struct ElementValue;
    struct AttributeLineNumberTable;

    struct TypePath {
        struct PathEntry {
            u1 typePathKind;
            u2 typeArgumentIndex;

            PathEntry() = default;
            explicit PathEntry(BytesReader &reader);
        };

        u1 pathLength;
        std::vector<PathEntry> path; // [pathLength]

        TypePath() = default;
        explicit TypePath(BytesReader &reader);
    };


    struct ElementValuePair {
        u2 elementNameIndex;
        std::unique_ptr<ElementValue> value; // declare as ptr

        explicit ElementValuePair(BytesReader &reader);
    };

    struct Annotation {
        u2 typeIndex;
        u2 numElementValuePairs;
        std::vector<std::unique_ptr<ElementValuePair>> elementValuePairs; // [numElementValuePairs]

        explicit Annotation(BytesReader &reader);
    };

    struct ElementValue {
        u1 tag;

        union {
            u2 constValueIndex;

            struct {
                u2 typeNameIndex;
                u2 constNameIndex;
            } enumConstValue;

            u2 classInfoIndex;

            Annotation* annotationValue; // union doesn't allow fields with non-trivial constructor

            struct {
                u2 numValues;
                ElementValue** values; // [numValues]
            } arrayValue;

        } value;

        ~ElementValue();
        explicit ElementValue(BytesReader &reader);
    };


    struct ParameterAnnotation {
        u2 numAnnotations;
        std::vector<std::unique_ptr<Annotation>> annotations; // [numAnnotations]

        explicit ParameterAnnotation(BytesReader &reader);
    };

    struct TypeAnnotations {
        u1 targetType;

        union TargetInfo {
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
                u2 tableLength;
                struct TableEntry {
                    u2 startPC;
                    u2 length;
                    u2 index;
                }* table; // [tableLength]
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

        } targetInfo;

        TypePath* targetPath;
        u2 typeIndex;
        u2 numElementValuePairs;
        ElementValuePair** elementValuePairs; // [numElementValuePairs]

        explicit TypeAnnotations(BytesReader &reader);
        ~TypeAnnotations();
    };

}




namespace classfile {

    /**
     * Basic Class
     */
    class AttributeInfo {
        friend ClassFile;
    protected:
        u2 nameIndex;
        u4 length;

        ConstantsPool *constantPool; //for referring, do not delete
    public:
        AttributeInfo();
        virtual ~AttributeInfo();
        AttributeInfo(u2 _nameIndex, u4 _length, ConstantsPool* constantsPool);
        static AttributeInfo* from(BytesReader& reader, ConstantsPool* constantsPool);
        [[nodiscard]] std::string name() const;
    };

    /**
     *   Derived Classes
     */

    struct AttributeConstantValue : public AttributeInfo {
        u2 constantValueIndex;

        AttributeConstantValue(u2 nameIndex, u4 length, ConstantsPool *constantsPool, BytesReader &reader);
    };


    struct AttributeCode : public AttributeInfo {
        struct ExceptionTableEntry {
            u2 startPC;    // from
            u2 endPC;      // to
            u2 handlerPC;  // where to handle
            u2 catchType;  // refer to a class ref in constant pool

            explicit ExceptionTableEntry(BytesReader &reader);
        };

        u2 maxStacks;
        u2 maxLocals;
        u4 codeLength;
        u1* codes; // [codeLength]
        u2 exceptionTableLength;
        std::vector<ExceptionTableEntry> exceptionTable; // [exceptionTableLength]
        u2 attributesCount;
        std::vector<std::unique_ptr<AttributeInfo>> attributes; // [attributesCount]

        ~AttributeCode() override;
        AttributeCode(u2 nameIndex, u4 length, ConstantsPool *constantsPool, BytesReader &reader);
        AttributeLineNumberTable* attributeLineNumberTable();
    };

    struct AttributeExceptions : public AttributeInfo {
        u2 numberOfExceptions;
        std::vector<u2> exceptionIndexTable; // [numberOfException]

        AttributeExceptions(u2 nameIndex, u4 length, ConstantsPool *constantsPool, BytesReader &reader);
    };

    struct AttributeSourceFile : public AttributeInfo {
        u2 sourceFileIndex;

        AttributeSourceFile(u2 nameIndex, u4 length, ConstantsPool *constantsPool, BytesReader &reader);
    };


    struct AttributeLineNumberTable : public AttributeInfo {
        struct LineNumberTableEntry {
            u2 startPC;
            u2 lineNumber;
            LineNumberTableEntry() = default;

            explicit LineNumberTableEntry(BytesReader &reader);
        };

        u2 lineNumberTableLength;
        std::vector<LineNumberTableEntry> lineNumberTable; // [lineNumberTableLength]

        AttributeLineNumberTable(u2 nameIndex, u4 length, ConstantsPool *constantsPool, BytesReader &reader);
    };

    struct AttributeLocalVariableTable : public AttributeInfo {
        struct LocalVariableTableEntry {
            u2 startPC;
            u2 length;
            u2 nameIndex;
            u2 descriptorIndex;
            u2 index;

            LocalVariableTableEntry() = default;
            explicit LocalVariableTableEntry(BytesReader &reader);
        };

        u2 localVariableTableLength;
        std::vector<LocalVariableTableEntry> localVariableTable;

        AttributeLocalVariableTable(u2 nameIndex, u4 length, ConstantsPool *constantsPool, BytesReader &reader);
    };

    struct AttributeInnerClasses : public AttributeInfo {
        struct ClassEntry {
            u2 innerClassInfoIndex;
            u2 outerClassInfoIndex;
            u2 innerNameIndex;
            u2 innerClassAccessFlags;

            ClassEntry() = default;
            explicit ClassEntry(BytesReader &reader);
        };

        u2 numberOfClasses;
        std::vector<ClassEntry> classes; // [numberOfClasses]

        AttributeInnerClasses(u2 nameIndex, u4 length, ConstantsPool *constantsPool, BytesReader &reader);
    };

    struct AttributeSynthetic : public AttributeInfo {
        AttributeSynthetic(u2 nameIndex, u4 length, ConstantsPool *constantsPool, BytesReader &reader);
    };

    struct AttributeDeprecated : public AttributeInfo {
        AttributeDeprecated(u2 nameIndex, u4 length, ConstantsPool *constantsPool, BytesReader &reader);
    };

    struct AttributeEnclosingMethod : public AttributeInfo {
        u2 classIndex;
        u2 methodIndex;

        AttributeEnclosingMethod(u2 nameIndex, u4 length, ConstantsPool *constantsPool, BytesReader &reader);
    };

    struct AttributeSignature : public AttributeInfo {
        u2 signatureIndex;

        AttributeSignature(u2 nameIndex, u4 length, ConstantsPool *constantsPool, BytesReader &reader);
    };

    struct AttributeSourceDebugExtension : public AttributeInfo {
        //todo:: complete!
        u1* debugExtension; // [attribute length]

        AttributeSourceDebugExtension(u2 nameIndex, u4 length, ConstantsPool *constantsPool, BytesReader &reader);
        ~AttributeSourceDebugExtension();
    };

    struct AttributeLocalVariableTypeTable : public AttributeInfo {
        struct LocalVariableTypeTableEntry {
            u2 startPC;
            u2 length;
            u2 nameIndex;
            u2 signatureIndex;
            u2 index;

            LocalVariableTypeTableEntry() = default;
            explicit LocalVariableTypeTableEntry(BytesReader &reader);
        };

        u2 localVariableTypeTableLength;
        std::vector<LocalVariableTypeTableEntry> localVariableTypeTable;

        AttributeLocalVariableTypeTable(u2 nameIndex, u4 length, ConstantsPool *constantsPool, BytesReader &reader);
    };

    struct AttributeRuntimeVisibleAnnotations : public AttributeInfo {
        u2 numAnnotations;
        std::vector<std::unique_ptr<Annotation>> annotations; // [numAnnotations]

        AttributeRuntimeVisibleAnnotations(u2 nameIndex, u4 length, ConstantsPool *constantsPool, BytesReader &reader);
    };

    typedef AttributeRuntimeVisibleAnnotations  AttributeRuntimeInvisibleAnnotations;

    struct AttributeRuntimeVisibleParameterAnnotations : public AttributeInfo {
        u1 numParameters;
        std::vector<std::unique_ptr<ParameterAnnotation>> parameterAnnotations; // [numParameters]

        AttributeRuntimeVisibleParameterAnnotations(u2 nameIndex, u4 length, ConstantsPool *constantsPool, BytesReader &reader);
    };

    typedef AttributeRuntimeVisibleParameterAnnotations AttributeRuntimeInvisibleParameterAnnotations;

    struct AttributeAnnotationDefault : public AttributeInfo {
        ElementValue* defaultValue;

        AttributeAnnotationDefault(u2 nameIndex, u4 length, ConstantsPool *constantsPool, BytesReader &reader);
    };

    struct AttributeStackMapTable : public AttributeInfo {
        u2 numbersOfEntries;

        union VerificationTypeInfo {
            struct TopVariableInfo {
                u1 tag;
            } topVariableInfo{};
            struct IntegerVariableInfo {
                u1 tag;
            } integerVariableInfo;
            struct FloatVariableInfo {
                u1 tag;
            } floatVariableInfo;
            struct NullVariableInfo {
                u1 tag;
            } nullVariableInfo;
            struct UninitializedThisVariableInfo {
                u1 tag;
            } uninitializedThisVariableInfo;
            struct ObjectVariableInfo {
                u1 tag;
                u2 cPoolIndex;
            } objectVariableInfo;
            struct UninitializedVariableInfo {
                u1 tag;
                u2 offset;
            } uninitializedVariableInfo;
            struct LongVariableInfo {
                u1 tag;
            } longVariableInfo;
            struct DoubleVariableInfo {
                u1 tag;
            } doubleVariableInfo;

            VerificationTypeInfo() = default;
            explicit VerificationTypeInfo(BytesReader &reader);
        };

        union StackMapFrame {
            struct SameFrame {
                u1 frameType;
            } sameFrame;

            struct SameLocals1StackItemFrame {
                u1 frameType;
                VerificationTypeInfo stack[1];
            } sameLocals1StackItemFrame;

            struct SameLocals1StackItemFrameExtended {
                u1 frameType;
                u2 offsetDelta;
                VerificationTypeInfo stack[1];
            } sameLocals1StackItemFrameExtended;

            struct ChopFrame {
                u1 frameType;
                u2 offsetDelta;
            } chopFrame;

            struct SameFrameExtended {
                u1 frameType;
                u2 offsetDelta;
            } sameFrameExtended;

            struct AppendFrame {
                u1 frameType;
                u2 offsetDelta;
                VerificationTypeInfo *locals; // [frameType - 251]
            } appendFrame;

            struct FullFrame {
                u1 frameType;
                u2 offsetDelta;
                u2 numberOfLocals;
                VerificationTypeInfo *locals; // [numberOfLocals]
                u2 numberOfStackItems;
                VerificationTypeInfo *stack; // [numberOfStackItems]
            } fullFrame;

            StackMapFrame() = default;
            explicit StackMapFrame(BytesReader &reader);
            ~StackMapFrame();
        };


        std::vector<std::unique_ptr<StackMapFrame>> entries; // [numbersOfEntries]

        AttributeStackMapTable(u2 nameIndex, u4 length, ConstantsPool *constantsPool, BytesReader &reader);
    };

    struct AttributeBootstrapMethods : public AttributeInfo {
        struct BootStrapMethodEntry {
            u2 bootstrapMethodRef;
            u2 numBootstrapArguments;
            std::vector<u2> bootstrapArguments; // [numBootstrapArguments]

            BootStrapMethodEntry() = default;
            explicit BootStrapMethodEntry(BytesReader &reader);
        };

        u2 numBootstrapMethods;
        std::vector<std::unique_ptr<BootStrapMethodEntry>> bootStrapMethods; // [numBootStrapMethod]

        AttributeBootstrapMethods(u2 nameIndex, u4 length, ConstantsPool *constantsPool, BytesReader &reader);
    };

    struct AttributeRuntimeVisibleTypeAnnotations : public AttributeInfo {
        u2 numAnnotations;
        std::vector<std::unique_ptr<TypeAnnotations>> annotations; // [numAnnotations]

        AttributeRuntimeVisibleTypeAnnotations(u2 nameIndex, u4 length, ConstantsPool *constantsPool, BytesReader &reader);
    };

    typedef AttributeRuntimeVisibleTypeAnnotations  AttributeRuntimeInvisibleTypeAnnotations;

    struct AttributeMethodParameters : public AttributeInfo {
        struct ParameterEntry {
            u2 nameIndex;
            u2 accessFlags;

            ParameterEntry() = default;
            explicit ParameterEntry(BytesReader &reader);
        };

        u1 parameterCount;
        std::vector<ParameterEntry> parameters; // [parameterCount]

        AttributeMethodParameters(u2 nameIndex, u4 length, ConstantsPool *constantsPool, BytesReader &reader);
    };


}


#endif //JVM_CLASSFILE_ATTRIBUTES_H
