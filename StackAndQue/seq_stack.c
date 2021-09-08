/**
 * @Author: JialiangJun
 * @Description:栈的顺序存储结构实现
 * @Date: Created on 09:30 2021-08-18.
 * @Modify:
 */
#include "seq_stack.h"

SqStackObj* SqStackInit()
{
    SqStackObj*pObj=NULL;
    pObj=malloc(sizeof(SqStackObj));
    CHECK_PARAM(!pObj,0);
    memset(pObj,0, sizeof(SqStackObj));
    // top为-1表示栈空 0表示有第一个元素
    pObj->top=-1;
    return pObj;
}

void PtStackInfo(SqStackObj*pObj){
    int i=0;
    PRINT_MODE(PT_BLUE,"Pt stack info top %d len %d",pObj->top,pObj->top+1);
    for(i=0;i<=pObj->top;i++){
        printf("top %d data %lld\n",i,pObj->data[i].data);
    }
    printf("\n");
}

int SqStackPush(SqStackObj*pObj,ElemType*pEle)
{
    CHECK_PARAM(!pObj||!pEle,FAILED);
    if(pObj->top>=MAX_STACK_SIZE-1)
    {
        // top为有符号类型
        PRINT_MODE(PT_RED,"ele too much top %d",pObj->top);
        return FAILED;
    }

    memcpy(&pObj->data[pObj->top+1],pEle,ELEMENT_SIZE);
    pObj->top++;
    return OK;
}

int SqStackPop(SqStackObj*pObj,ElemType*pEle){
    CHECK_PARAM(!pObj||!pEle,FAILED);
    if(pObj->top<0){
        PRINT_MODE(PT_RED,"stack is empty top %d",pObj->top);
        return FAILED;
    }
    memcpy(pEle,&pObj->data[pObj->top],ELEMENT_SIZE);
    pObj->top--;
    return OK;
}

void SqStackDeInit(SqStackObj*pObj){
    free(pObj);
}

void SqStackTest(){
    int i=0;
    SqStackObj *pObj=NULL;
    ElemType stEle={0};
    pObj=SqStackInit();
    for(i=0;i<10;i++)
    {
        stEle.data=i;
        SqStackPush(pObj,&stEle);
    }
    SqStackPop(pObj,&stEle);
    PRINT("pop ele %lld",stEle.data);
    SqStackPop(pObj,&stEle);
    PRINT("pop ele %lld",stEle.data);
    PtStackInfo(pObj);
    SqStackDeInit(pObj);

}
