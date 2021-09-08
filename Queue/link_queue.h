/**
 * @Author: Jialiangjun
 * @Description:队列的链式存储结构
 * @Description:队列的链式存储结构
 * @Date: Created on 09:51 2021-08-19.
 * @Modify:
 */
#ifndef QUEUE_LINK_QUEUE_H
#define QUEUE_LINK_QUEUE_H
#include "comm.h"
#include "data_type.h"

typedef struct _QNode{
    ElemType data;
    struct _QNode *pNext;
}QNode;

typedef struct {
    QNode*front;
    QNode*rear;
}QNodeObj;

void LinkQueueTest();

#endif //QUEUE_LINK_QUEUE_H
