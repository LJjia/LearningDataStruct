/**
 * @Author: JiaLiangJun
 * @Description: 双向生长的栈
 * @Date: Created on 13:42 2021-08-18.
 * @Modify:
 */
#ifndef STACKANDQUE_SEQ_DUL_STACK_H
#define STACKANDQUE_SEQ_DUL_STACK_H


#include "comm.h"
#include "data_type.h"

#define MAX_DUL_STACK_SIZE 10

typedef enum {
    STACK_NUM_ONE,
    STACK_NUM_TWO,
}STACK_SERIAL;

typedef struct {
    ElemType data[MAX_DUL_STACK_SIZE];
    int top1;
    int top2;
}SqDulStackObj;

void SqDulStackTest();


#endif //STACKANDQUE_SEQ_DUL_STACK_H
