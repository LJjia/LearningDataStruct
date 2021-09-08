/**
 * @Author: Jialiangjun
 * @Description: 循环 顺序存储(数组) 的队列
 * @Date: Created on 16:18 2021-08-18.
 * @Modify:
 */
#ifndef QUEUE_CYC_SEQ_QUEUE_H
#define QUEUE_CYC_SEQ_QUEUE_H

#include "comm.h"
#include "data_type.h"


#define MAX_CYC_SEQ_QUEUE_SIZE 10
typedef struct {
    ElemType data[MAX_CYC_SEQ_QUEUE_SIZE];
    int front;  //队头索引,队头的索引填充元素
    int rear;   //队尾索引,指向队尾空位的元素的索引,当前该索引中不会添加元素 因此队列实际元素最大max-1
}CycSeqQueueObj;

void CycSeqQueueTest();

#endif //QUEUE_CYC_SEQ_QUEUE_H
