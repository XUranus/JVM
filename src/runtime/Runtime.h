//
// Created by xuranus on 4/10/22.
//

#ifndef JVM_RUNTIME_H
#define JVM_RUNTIME_H


/**
 * Runtime {
 *      Thread {
 *          pc
 *          JvmStack {
 *              Frame{
 *                  LocalVariable
 *                  OperandStack
 *              }[]
 *          }
 *      }
 *
 *      Heap {
 *          MethodArea {
 *              Class {
 *                  RuntimeConstantsPool
 *                  Fields
 *                  Methods
 *                  Code
 *              }[]
 *          }
 *          Object[]
 *      }
 * }
 */
class Runtime {


};


#endif //JVM_RUNTIME_H
