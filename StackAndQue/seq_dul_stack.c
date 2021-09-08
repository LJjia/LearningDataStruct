/**
 * @Author: Jialiangjun
 * @Description: 双向生长的栈,类似程序的栈和堆
 * @Date: Created on 13:42 2021-08-18.
 * @Modify:
 */
#include "seq_dul_stack.h"


SqDulStackObj* SqDulStackInit()
{
    SqDulStackObj*pObj=NULL;
    pObj=malloc(sizeof(SqDulStackObj));
    CHECK_PARAM(!pObj,0);
    memset(pObj,0, sizeof(SqDulStackObj));
    // top为-1表示栈空 0表示有第一个元素
    pObj->top1=-1;
    pObj->top2=MAX_DUL_STACK_SIZE;
    return pObj;
}

void PtDulStackInfo(SqDulStackObj*pObj){
    int i=0;
    PRINT_MODE(PT_BLUE,"Pt stack info top1 %d  top1 %d len %d",
            pObj->top1,pObj->top2,pObj->top1+1+MAX_DUL_STACK_SIZE-pObj->top2);
    for(i=0;i<MAX_DUL_STACK_SIZE;i++){
        printf("Index %d data %lld\n",i,pObj->data[i].data);
    }
    printf("\n");
}

int SqDulStackPush(SqDulStackObj*pObj,ElemType*pEle,int nStackSerialNum)
{
    CHECK_PARAM(!pObj||!pEle,FAILED);
    if(pObj->top2-pObj->top1<=1)
    {
        // 两个top之间差小于1证明栈满
        PRINT_MODE(PT_RED,"ele too much top1 %d top2 %d",pObj->top1,pObj->top2);
        return FAILED;
    }

    if(nStackSerialNum==STACK_NUM_ONE)
    {
        memcpy(&pObj->data[pObj->top1+1],pEle,ELEMENT_SIZE);
        pObj->top1++;
    }
    else if(nStackSerialNum==STACK_NUM_TWO)
    {
        memcpy(&pObj->data[pObj->top2-1],pEle,ELEMENT_SIZE);
        pObj->top2--;
    }

    return OK;
}

int SqDulStackPop(SqDulStackObj*pObj,ElemType*pEle,int nStackSerialNum){
    CHECK_PARAM(!pObj||!pEle,FAILED);
    if(nStackSerialNum==STACK_NUM_ONE){
        if(pObj->top1<0){
            PRINT_MODE(PT_RED,"stack is empty top1 %d",pObj->top1);
            return FAILED;
        }
        memcpy(pEle,&pObj->data[pObj->top1],ELEMENT_SIZE);
        memset(&pObj->data[pObj->top1],0,ELEMENT_SIZE);
        pObj->top1--;
    }
    else if(nStackSerialNum==STACK_NUM_TWO)
    {
        if(pObj->top2>=MAX_DUL_STACK_SIZE){
            PRINT_MODE(PT_RED,"stack is empty top2 %d",pObj->top2);
            return FAILED;
        }
        memcpy(pEle,&pObj->data[pObj->top2],ELEMENT_SIZE);
        memset(&pObj->data[pObj->top2],0,ELEMENT_SIZE);
        pObj->top2++;
    }

    return OK;
}

void SqDulStackDeInit(SqDulStackObj*pObj){
    free(pObj);
}

void SqDulStackTest(){
    int i=0;
    SqDulStackObj *pObj=NULL;
    ElemType stEle={0};
    pObj=SqDulStackInit();
    for(i=0;i<10;i++)
    {
        stEle.data=i;
        SqDulStackPush(pObj,&stEle,STACK_NUM_ONE);
    }
    PRINT("Test Push too ele ",stEle.data);
    SqDulStackPush(pObj,&stEle,STACK_NUM_ONE);
    SqDulStackPush(pObj,&stEle,STACK_NUM_ONE);

    stEle.data=200;
    SqDulStackPop(pObj,&stEle,STACK_NUM_ONE);
    PRINT("Test Push ele %d",stEle.data);

    stEle.data=200;
    SqDulStackPop(pObj,&stEle,STACK_NUM_TWO);
    PRINT("Test Push ele %d",stEle.data);

    stEle.data=20;
    SqDulStackPush(pObj,&stEle,STACK_NUM_TWO);
    PRINT("Test Push ele %d",stEle.data);

    stEle.data=30;
    SqDulStackPush(pObj,&stEle,STACK_NUM_TWO);
    PRINT("Test Push ele %d",stEle.data);

    PtDulStackInfo(pObj);
    SqDulStackDeInit(pObj);

}
