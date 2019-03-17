//
// Created by xuranus on 3/16/19.
//

#include "IO.h"
#include "../NativeRegistry.h"
#include "../../util/Console.h"

void IO::print(Frame *frame) {
    /*auto &stack = frame->operandStack;
    if(descriptor=="(Z)V")
        printf("%d",stack.popInt()!=0);
    else if(descriptor=="(C)V")
        printf("%d",stack.popInt());
    else if(descriptor=="(I)V")
        printf("%d",stack.popInt());
    else if(descriptor=="(F)V")
        printf("%f",stack.popFloat());
    else if(descriptor=="(J)V")
        printf("%ld",stack.popLong());
    else if(descriptor=="(D)V")
        printf("%lf",stack.popDouble());
    else if(descriptor=="(Ljava/lang/String;)V") {
        auto jstr = stack.popRef();
        auto localStr = StringPool::getStringPool()->getlocalString(jstr);
        printf("%s",localStr.c_str());
    } else {
        Console::printlnError("hack error,descriptor"+descriptor);
        exit(1);
    }
    stack.popRef();*/
}

void IO::println(Frame *frame)
{
    /*
    auto &stack = frame->operandStack;
    if(descriptor=="(Z)V")
        printf("%d\n",stack.popInt()!=0);
    else if(descriptor=="(C)V")
        printf("%c\n",stack.popInt());
    else if(descriptor=="(I)V")
        printf("%d\n",stack.popInt());
    else if(descriptor=="(F)V")
        printf("%f\n",stack.popFloat());
    else if(descriptor=="(J)V")
        printf("%ld\n",stack.popLong());
    else if(descriptor=="(D)V")
        printf("%lf\n",stack.popDouble());
    else if(descriptor=="(Ljava/lang/String;)V") {
        auto jstr = stack.popRef();
        auto localStr = StringPool::getStringPool()->getlocalString(jstr);
        printf("%s\n",localStr.c_str());
    } else {
        Console::printlnError("hack error,descriptor"+descriptor);
        exit(1);
    }
    stack.popRef();
     */
}

void IO::init() {
    //NativeRegistry::getNativeRegistery()->setRegister("java/lang/Object","getClass","()Ljava/lang/Class;",(void*)Class_Object::getClass);
}
