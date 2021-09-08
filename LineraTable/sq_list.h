//
// Created by LJjia on 2021-08-14.
//

#ifndef LINERATABLE_SQ_LIST_H
#define LINERATABLE_SQ_LIST_H

#include "comm.h"
#include "data_type.h"


typedef struct {
    ElemType data[MAXSIZE];
    int32_t length;
}SqList;

void SqListTest();




#endif //LINERATABLE_SQ_LIST_H
