//
// Created by xuranus on 4/23/22.
//

#include "ExceptionHandler.h"
#include "Class.h"

namespace heap {
    ExceptionHandler::ExceptionHandler() {
        catchType = nullptr;
    }

    ExceptionHandler::ExceptionHandler(u2 _startPC, u2 _endPC, u2 _handlerPC, ClassRef* _catchTypeRef) {
        startPC = _startPC;
        endPC = _endPC;
        handlerPC = _handlerPC;
        catchType = _catchTypeRef;
    }


    ExceptionTable::ExceptionTable(ConstantPool *constantPool, classfile::AttributeCode *attributeCode) {
        for(auto& exceptionEntry: attributeCode->exceptionTable) {
            ClassRef* catchTypeRef = nullptr;
            if(exceptionEntry.catchType != 0) {
                catchTypeRef = constantPool->classRefValue(exceptionEntry.catchType);
            }
            handlers.emplace_back(ExceptionHandler(
                exceptionEntry.startPC,
                exceptionEntry.endPC,
                exceptionEntry.handlerPC,
                catchTypeRef));
        }
    }

    ExceptionHandler* ExceptionTable::findHandler(Class *exceptionClass, int pc) {
        for(auto &handler: handlers) {
            if(pc >= handler.startPC && pc < handler.endPC) {
                if(handler.catchType == nullptr) { // means 'catch all'
                    return &handler;
                }
                Class* catchClass = handler.catchType->resolvedClass();
                if(catchClass == exceptionClass || catchClass->isSuperClassOf(exceptionClass)) {
                    return &handler;
                }
            }
        }
        return nullptr;
    }

    std::vector<Class *> ExceptionTable::exceptionTypes() const {
        std::vector<Class*> types;
        for(auto& handler: handlers) {
            types.emplace_back(handler.catchType->resolvedClass());
        }
        return types;
    }
}