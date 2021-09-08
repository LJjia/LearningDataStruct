/**
 * @Author: JialiangJun
 * @Description: 定义一些基本数据类型
 * @Date: Created on 10:00 2021-08-17.
 * @Modify:
 */

#include "comm.h"
#ifndef LINERATABLE_DATA_TYPE_H
#define LINERATABLE_DATA_TYPE_H

#ifdef __cplusplus
extern "C"{
#endif


#define MAXSIZE 64

typedef struct {
    char desc[8];
    uint64_t data;

}ElemType;

#define ELEMENT_SIZE sizeof(ElemType)


#ifdef __cplusplus
}
#endif


#endif //LINERATABLE_DATA_TYPE_H
