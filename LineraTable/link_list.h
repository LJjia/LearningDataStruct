/**
 * @Author: JialiangJun
 * @Description:
 * @Date: Created on 10:09 2021-08-17.
 * @Modify:
 */
#ifndef LINERATABLE_LINK_LIST_H
#define LINERATABLE_LINK_LIST_H

#include "comm.h"
#include "data_type.h"

typedef struct _Node{
    ElemType stData;
    struct _Node *pNext;
}NODE;

typedef struct {
        NODE *pHead;
        char desc[8];
        int len;
}LINK_LIST_OBJ;

#define NODE_SIZE sizeof(NODE)


LINK_LIST_OBJ * InitLinkList();
void LinkListTest();

#endif //LINERATABLE_LINK_LIST_H
