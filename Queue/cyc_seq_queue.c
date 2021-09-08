/**
 * @Author: Jialiangjun
 * @Description: 循环 顺序存储(数组) 的队列
 * @Date: Created on 16:18 2021-08-18.
 * @Modify:
 */
#include "cyc_seq_queue.h"

#define GET_CYCLE_QUEUE_ELEM_NUM(front,rear,size) (front<=rear?(rear-front):(size-front+rear))

CycSeqQueueObj* CycSeqQueueInit(){
    CycSeqQueueObj *pObj=0;
    pObj=malloc(sizeof(CycSeqQueueObj));
    memset(pObj,0, sizeof(CycSeqQueueObj));
    CHECK_PARAM(!pObj,0);
    return pObj;
}

void PtCycSeQueue(CycSeqQueueObj *pObj) {
    int i=0;
    PRINT_MODE(PT_BLUE,"Pt Queue Front %d Rear %d",pObj->front,pObj->rear);
    for(i=0;i<MAX_CYC_SEQ_QUEUE_SIZE;i++)
    {
        printf("index %d data %lld\n",i,pObj->data[i].data);
    }
    printf("\n");
}

void CycSeqQueueDeInit(CycSeqQueueObj *pObj){
    free(pObj);
}

int CycSeqQueueEmpty(CycSeqQueueObj *pObj){
    return 0==GET_CYCLE_QUEUE_ELEM_NUM(pObj->front,pObj->rear,MAX_CYC_SEQ_QUEUE_SIZE)?True:False;
    return OK;
}

/*!
 * 返回队列中元素的个数
 * @param pObj
 * @return
 */
int GetCycSeqQueueEleNum(CycSeqQueueObj *pObj){
    return GET_CYCLE_QUEUE_ELEM_NUM(pObj->front,pObj->rear,MAX_CYC_SEQ_QUEUE_SIZE);
    return OK;
}

/*!
 * 队列清空,仅清空不销毁,不是释放内存
 * @param pObj
 * @return
 */
int ClearCycSeqQueue(CycSeqQueueObj *pObj){
    memset(pObj,0, sizeof(CycSeqQueueObj));
    return OK;
}

/*!
 * 从队头pop出一个元素
 * @param pObj
 * @return
 */
int CycSeqQueuePop(CycSeqQueueObj *pObj,ElemType *pEle){
    int nEleNum=0;
    CHECK_PARAM(!pObj||!pEle,FAILED);
    nEleNum=GET_CYCLE_QUEUE_ELEM_NUM(pObj->front,pObj->rear,MAX_CYC_SEQ_QUEUE_SIZE);
    if(nEleNum<1){
        PRINT("unable pop ele num %u",nEleNum);
        return FAILED;
    }
    memcpy(pEle,&pObj->data[pObj->front],ELEMENT_SIZE);
    memset(&pObj->data[pObj->front],0, ELEMENT_SIZE);
    pObj->front=(pObj->front+1)%MAX_CYC_SEQ_QUEUE_SIZE;
    return OK;
}

/*!
 * 向队尾中插入一个元素
 * @param pObj
 * @param pEle
 * @return
 */
int CycSeqQueuePush(CycSeqQueueObj *pObj,ElemType *pEle){
    int nEleNum=0;
    CHECK_PARAM(!pObj||!pEle,FAILED);
    nEleNum=GET_CYCLE_QUEUE_ELEM_NUM(pObj->front,pObj->rear,MAX_CYC_SEQ_QUEUE_SIZE);
    // 最多插入MAX-1个元素
    if(nEleNum>=MAX_CYC_SEQ_QUEUE_SIZE-1){
        PRINT("unable insert ele num %u",nEleNum);
        return FAILED;
    }
    memcpy(&pObj->data[pObj->rear],pEle,ELEMENT_SIZE);
    pObj->rear=(pObj->rear+1)%MAX_CYC_SEQ_QUEUE_SIZE;
    return OK;

}

void CycSeqQueueTest(){
    int i=0;
    ElemType stEle={0};
    CycSeqQueueObj*pObj=NULL;
    pObj=CycSeqQueueInit();
    for(i=0;i<10;i++){
        stEle.data=i;
        CycSeqQueuePush(pObj,&stEle);
    }
    CycSeqQueuePop(pObj,&stEle);
    CycSeqQueuePop(pObj,&stEle);
    stEle.data=100;
    CycSeqQueuePush(pObj,&stEle);
    stEle.data=100;
    CycSeqQueuePush(pObj,&stEle);
    PtCycSeQueue(pObj);

    CycSeqQueueDeInit(pObj);
}





