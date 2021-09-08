/**
 * @Author: JialiangJun
 * @Description:栈的顺序存储结构
 * @Date: Created on 09:30 2021-08-18.
 * @Modify:
 */
#ifndef STACKANDQUE_SEQ_STACK_H
#define STACKANDQUE_SEQ_STACK_H

#include "comm.h"
#include "data_type.h"

#define MAX_STACK_SIZE 100

typedef struct {
    ElemType data[MAX_STACK_SIZE];
    int top;
}SqStackObj;

void SqStackTest();

#endif //STACKANDQUE_SEQ_STACK_H
