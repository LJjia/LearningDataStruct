/**
 * @Author: JialiangJun
 * @Description:
 * @Date: Created on 16:55 2021-08-17.
 * @Modify:
 */
#ifndef LINERATABLE_CYCLE_DOUBLE_LINK_H
#define LINERATABLE_CYCLE_DOUBLE_LINK_H

#include "comm.h"
#include "data_type.h"

typedef struct _DUL_Node{
    ElemType stData;
    struct _DUL_Node *pNext;
    struct _DUL_Node*pPrior;
}DUL_NODE;

typedef struct {
    DUL_NODE *pHead;
    DUL_NODE *pTail;
    char desc[8];
    int len;
}CYC_DUL_LINK_OBJ;

#define DUL_NODE_SIZE sizeof(DUL_NODE)

void CycDoubleLinkTest();

#endif //LINERATABLE_CYCLE_DOUBLE_LINK_H
