/**
 * @Author: Jialiangjun
 * @Description:队列的链式存储结构
 * @Date: Created on 09:51 2021-08-19.
 * @Modify:
 */
#include "link_queue.h"

/*!
 * 不带队列头节点的实现
 * @return
 */
QNodeObj* LinkQueueInit(){
    QNodeObj*pObj=0;
    pObj=malloc(sizeof(QNodeObj));
    CHECK_PARAM(!pObj,NULL);
    memset(pObj,0, sizeof(QNodeObj));
    return pObj;
}


int LinkQueueuPush(QNodeObj *pObj,ElemType*pEle){
    QNode *pNode=0;
    CHECK_PARAM(!pObj||!pEle,FAILED);
    pNode=malloc(sizeof(QNode));
    CHECK_PARAM(!pNode,FAILED);
    memset(pNode,0, sizeof(QNode));
    memcpy(&pNode->data,pEle,sizeof(ElemType));
    if(0==pObj->rear){
        // 队列为空,添加第一个元素时,首尾指针指向同一个节点
        pObj->rear=pObj->front=pNode;
    }
    else{
        pObj->rear->pNext=pNode;
        pObj->rear=pNode;
    }
    return OK;


}

int LinkQueuePop(QNodeObj *pObj,ElemType* pEle){
    QNode *pNode=0;
    CHECK_PARAM(!pObj,FAILED);
    pNode=pObj->front;
    CHECK_PARAM(!pNode,FAILED);
    pObj->front=pNode->pNext;
    // rear和front指针 空队列时需要同时置空
    pObj->rear=0==pObj->front?0:pObj->rear;
    memcpy(pEle,&pNode->data, sizeof(ElemType));
    free(pNode);
    return OK;

}


/*!
 * 和正常的reset不一样,海康工作的时候所有的节点地址都会是记录在obj中
 * pop的时候将节点返回出去,由外部决定这个节点怎么操作,是移动到另一个队列还是释放或不释放
 * 如果不释放,即使节点丢掉,也可以通过reset函数强制释放
 * 这里的实现和海康的有所不同,结点是零散malloc的,不记录地址,所以无法完成reset,只能全部释放
 * @param pObj 节点对象
 * @return
 */
int LinkQueueClear(QNodeObj *pObj){
    ElemType stEle={0};
    while(pObj->front!=0){
        LinkQueuePop(pObj,&stEle);
    }
    pObj->front=pObj->rear=NULL;
    return OK;
}

void LinkQueueDeInit(QNodeObj *pObj){
    LinkQueueClear(pObj);
    free(pObj);
}


int GetLinkQueueNum(QNodeObj *pObj) {
    int cnt = 0;
    QNode *pNode = 0;
    pNode = pObj->front;
    while (pNode != 0){
        pNode=pNode->pNext;
        cnt++;
    }
    return cnt;
}

int bLinkQueueEmpty(QNodeObj *pObj){
    return (pObj->rear==pObj->front==0)?True:False;
}


void PtLinkQueueInfo(QNodeObj *pObj){
    QNode*pNode=0;
    int i=0;
    pNode=pObj->front;
    PRINT_MODE(PT_BLUE,"Pt Queue info node num %u",GetLinkQueueNum(pObj));
    while(pNode!=0){
        printf("index %d data %lld\n",i++,pNode->data.data);
        pNode=pNode->pNext;
    }
}


void LinkQueueTest(){
    QNodeObj *pObj=0;
    int i=0;
    ElemType stEle={0};
    pObj=LinkQueueInit();
    for(i=0;i<10;i++){
        stEle.data=i;
        LinkQueueuPush(pObj,&stEle);
    }
    PRINT("push end node num %d",GetLinkQueueNum(pObj));
    LinkQueuePop(pObj,&stEle);
    LinkQueuePop(pObj,&stEle);
    PtLinkQueueInfo(pObj);
    LinkQueueClear(pObj);
    PtLinkQueueInfo(pObj);
    for(i=0;i<10;i++){
        stEle.data=i;
        LinkQueueuPush(pObj,&stEle);
    }
    PRINT("push end node num %d",GetLinkQueueNum(pObj));
    LinkQueueDeInit(pObj);

}
