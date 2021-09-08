/**
 * @Author: Jialiangjun
 * @Description:链表实现的栈
 * @Date: Created on 14:26 2021-08-18.
 * @Modify:
 */
#ifndef STACKANDQUE_LINK_STACK_H
#define STACKANDQUE_LINK_STACK_H


#include "comm.h"
#include "data_type.h"

typedef struct _LINK_STACK_NODE{
    ElemType data;
    struct _LINK_STACK_NODE *pNext;
}LinkStackNode;

typedef struct {
    LinkStackNode*pTop;
    int cnt;
}LinkStackObj;

#endif //STACKANDQUE_LINK_STACK_H
