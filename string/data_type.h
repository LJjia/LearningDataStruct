/**
 * @Author: JialiangJun
 * @Description: 定义一些基本数据类型
 * @Date: Created on 10:00 2021-08-17.
 * @Modify:
 */
#ifndef LINERATABLE_DATA_TYPE_H
#define LINERATABLE_DATA_TYPE_H
#include "comm.h"

#define MAXSIZE 64

typedef struct {
    char desc[8];
    uint64_t data;

}ElemType;

#define ELEMENT_SIZE sizeof(ElemType)


#endif //LINERATABLE_DATA_TYPE_H
