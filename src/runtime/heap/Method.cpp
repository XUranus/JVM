//
// Created by xuranus on 2/16/19.
//

#include "Method.h"
#include "../Thread.h"
#include "../../instructions/instruction.h"
#include "../../util/Console.h"
#include "ClassLoader.h"
#include "StringPool.h"
#include "ObjectPool.h"

void MethodDescriptor::addParameterType(std::string type)
{
    parameterTypes.push_back(type);
}

MethodDescriptor* MethodDescriptorParser::parse(std::string& descriptor)
{
    offset = 0;
    raw = descriptor;
    parsed = new MethodDescriptor();
    startParams();
    parseParamTypes();
    endParams();
    parseReturnType();
    finish();
    return parsed;
}

void MethodDescriptorParser::startParams()
{
    if(readUint8()!='(')
        causeError();
}

void MethodDescriptorParser::endParams()
{
    if(readUint8()!=')')
        causeError();
}

void MethodDescriptorParser::finish()
{
    if(offset!=raw.length())
        causeError();
}

void MethodDescriptorParser::causeError()
{
    //Console::printlnError("BAD descriptor: "+raw);
    //exit(1);
}

uint8 MethodDescriptorParser::readUint8()
{
    auto b = raw[offset];
    offset++;
    return (uint8)b;
}

void MethodDescriptorParser::unreadUint8()
{
    offset--;
}

void MethodDescriptorParser::parseParamTypes()
{
    while (true)
    {
        auto t = parseFieldType();
        if(!t.empty())
            parsed->addParameterType(t);
        else
            break;
    }
}

void MethodDescriptorParser::parseReturnType()
{
    if(readUint8() == 'V')
    {
        parsed->returnType = "V";
        return;
    }
    unreadUint8();
    auto t = parseFieldType();
    if(!t.empty())
    {
        parsed->returnType = t;
        return;
    }
    causeError();
}

std::string MethodDescriptorParser::parseFieldType()
{
    switch (readUint8()) {
        case 'B': return "B";
        case 'C': return "C";
        case 'D': return "D";
        case 'F': return "F";
        case 'I': return "I";
        case 'J': return "J";
        case 'S': return "S";
        case 'Z': return "Z";
        case 'L': return parseObjectType();
        case '[': return parseArrayType();
        default: {
            unreadUint8();
            return "";
        }
    }
}

std::string MethodDescriptorParser::parseObjectType()
{
    auto unread = raw.substr(0,offset);
    auto semicolonIndex = unread.find(';');
    if(semicolonIndex == -1)
    {
        causeError();
        return "";
    } else {
        auto objStart = offset - 1;
        auto objEnd = offset + semicolonIndex + 1;
        offset = objEnd;
        auto descriptor = raw.substr(objStart,objEnd);
        return descriptor;
    }

}

std::string MethodDescriptorParser::parseArrayType()
{
    auto arrStart = offset - 1;
    parseFieldType();
    auto arrEnd = offset;
    auto descriptor = raw.substr(arrStart,arrStart);
    return descriptor;
}

//-------------------------------------------------------------------------------


Method::Method(MethodInfo *methodInfo, Class *classRef)
{
    accessFlags = methodInfo->accessFlags;
    name = methodInfo->getName();
    descriptor = methodInfo->getDescriptorName();

    _class = classRef;

    auto codeAttr = methodInfo->getCodeAttribute();
    if(codeAttr!= nullptr)
    {
        maxLocals = codeAttr->maxLocals;
        maxStack = codeAttr->maxStacks;
        code = std::vector<u1>(codeAttr->codeLength);
        for(auto i=0;i<codeAttr->codeLength;i++)
        {
            code[i] = codeAttr->codes[i];
        }
    } else {
        maxLocals = maxStack = 0;
        code.clear();
    }
    //calculate args slots
    argSlotCount = 0;
    MethodDescriptorParser parser;
    auto parsedDescriptor = parser.parse(descriptor);
    for(const auto& paramType:parsedDescriptor->parameterTypes)
    {
        argSlotCount++;
        if(paramType == "J" || paramType == "D")//double or long
            argSlotCount++;
    }
    if(!(accessFlags & ACC_STATIC_FLAG))
        argSlotCount++;//non static method has "this" ref param

}

std::vector<Method*> Method::parseMethods(ClassFile *classFile, Class *classRef)
{
    std::vector<Method*> ret;
    for(u2 i=0;i<classFile->methodsCount;i++)
    {
        ret.emplace_back(new Method(classFile->methods[i], classRef));
    }
    return ret;
}

void Method::debug()
{
    printf("[Debug Method]\n");
    printf("accessFlags:%d\n",accessFlags);
    printf("name:%s\n",name.c_str());
    printf("descriptor:%s\n",descriptor.c_str());
    printf("Class:%s\n",_class->name.c_str());
    printf("maxLocals:%u\n",maxLocals);
    printf("maxStacks:%u\n",maxStack);
    printf("argSlotsCount:%d\n",argSlotCount);
    printf("Code:");
    for(auto c:code)
        printf("%02x ",c);
    printf("\n");
}


void loop(Thread* thread,bool verboseInst)
{
    BytesReader reader;
    int i = 0;
    while (true)
    {
        auto frame = thread->currentFrame();
        int pc = frame->nextPc;
        thread->pc = pc;

        reader.reset(frame->method->code.data(),pc);
        auto opCode = reader.readUint8();

        auto inst = Instruction::createInstruction(opCode);
        inst->fetchOperands(reader);

        if(verboseInst)
            Console::printlnYellow("[INST]:"+inst->toString());
        //frame->debug();
        //ObjectPool::getObjectPool()->debug();

        //printf("[%d] <%s> starkSize=%d \n",i++,inst->toString().c_str(),frame->thread->stack.size);
        //StringPool::getStringPool()->debug();

        frame->nextPc = reader.pc;
        inst->excute(frame);
        //frame->method->_class->constantPool->debug();printf("\n");
        if(thread->stackEmpty())
        {
            break;
        }
    }
}

void Method::interpret(Method *method,bool verboseInst,std::vector<std::string> args)
{
    auto thread = new Thread(2048);
    auto frame = new Frame(method);
    thread->pushFrame(frame);

    //set command args
    auto jArgs = method->_class->classloader->createArgsArrayObject(args);
    frame->localVars.setRef(0,jArgs);

    loop(thread,verboseInst);
    delete(frame);
    delete(thread);
}
