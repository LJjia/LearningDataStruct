/**
 * @Author: Jialiangjun
 * @Description:链表实现的栈 栈顶在列表头
 * @Date: Created on 14:26 2021-08-18.
 * @Modify:
 */
#include "link_stack.h"

LinkStackObj* LinkStackInit(){
    LinkStackObj*pObj=0;
    pObj=malloc(sizeof(LinkStackObj));
    CHECK_PARAM(!pObj,0);
    memset(pObj,0, sizeof(LinkStackObj));
    return pObj;
}

void PtLinkStackInfo(LinkStackObj*pObj)
{
    int i=0;
    LinkStackNode*pNode=0;
    PRINT_MODE(PT_BLUE,"Pt link stack obj num %d",pObj->cnt);
    pNode=pObj->pTop;
    while(pNode!=0)
    {
        printf("index %u data %lld\n",i++,pNode->data.data);
        pNode=pNode->pNext;
    }
    printf("\n");
}

/*!
 * 链表一般不存在元素过多的情况
 * @param pObj
 * @param pEle
 * @return
 */
int LinkStackPush(LinkStackObj*pObj,ElemType*pEle){
    LinkStackNode* pNode=0;
    CHECK_PARAM(!pObj||!pEle,FAILED);
    pNode=malloc(sizeof(LinkStackNode));
    CHECK_PARAM(!pNode,FAILED);
    memcpy(&pNode->data,pEle,ELEMENT_SIZE);
    pNode->pNext=pObj->pTop;
    pObj->pTop=pNode;
    pObj->cnt++;
    return OK;
}

int LinkStackPop(LinkStackObj*pObj,ElemType*pEle){
    LinkStackNode* pNode=0;
    CHECK_PARAM(!pObj||!pEle,FAILED);
    if(pObj->cnt<1)
    {
        PRINT_MODE(PT_RED,"ele num less");
        return FAILED;
    }
    pNode=pObj->pTop;
    pObj->pTop=pObj->pTop->pNext;
    memcpy(pEle,&pNode->data,ELEMENT_SIZE);
    free(pNode);
    pObj->cnt--;
    return OK;
}

void LinkStackDeInit(LinkStackObj*pObj){
    LinkStackNode* pNode=0;
    int nFreeCnt=0;
    CHECK_PARAM(!pObj,);

    while(pObj->pTop!=0)
    {
        pNode=pObj->pTop;
        pObj->pTop=pNode->pNext;
        free(pNode);
        nFreeCnt++;
    }
    PRINT("free cnt %d list cnt %d",nFreeCnt,pObj->cnt);
    free(pObj);
}

void LinkStackTest(){
    LinkStackObj*pObj=0;
    ElemType stEle={0};
    int i=0;
    pObj=LinkStackInit();
    for(i=0;i<8;i++)
    {
        stEle.data=i;
        LinkStackPush(pObj,&stEle);
    }

    LinkStackPop(pObj,&stEle);
    PRINT("pop ele data %d",stEle.data);
    PtLinkStackInfo(pObj);
    LinkStackDeInit(pObj);

}

