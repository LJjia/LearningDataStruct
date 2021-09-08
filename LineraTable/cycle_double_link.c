/**
 * @Author: JialiangJun
 * @Description:循环双向链表
 * @Date: Created on 16:55 2021-08-17.
 * @Modify:
 */
#include "cycle_double_link.h"


CYC_DUL_LINK_OBJ * CycDulLinkInit() {
    CYC_DUL_LINK_OBJ *pCycDulLinkObj = NULL;
    pCycDulLinkObj = malloc(sizeof(CYC_DUL_LINK_OBJ));
    memset(pCycDulLinkObj, 0, sizeof(CYC_DUL_LINK_OBJ));
    return pCycDulLinkObj;
}

/*!
 * 打印元素的值
 * @param pCycDulLinkObj
 * @param negative 为True 表示倒序,为False表示正序
 */
void PtCycDulLink(CYC_DUL_LINK_OBJ *pCycDulLinkObj,int negative){
    int i=0;
    DUL_NODE* pOriNode=0;
    DUL_NODE* pHead=0;
    pHead=pCycDulLinkObj->pHead;
    pOriNode=pHead;
    char szOrder[32]={0};
    strcpy(szOrder,negative==True?"negative":"positive");
    PRINT("Pt Cyc double Link list order %s len %d Head %p Tail %p",
            szOrder,pCycDulLinkObj->len,pCycDulLinkObj->pHead,pCycDulLinkObj->pTail);
    if(negative==False)
    {
        while(pOriNode->pNext!=pHead)
        {
            //正序遍历
            printf("Addr %p index %d data %lld\n",pOriNode,i++,pOriNode->stData.data);
            pOriNode=pOriNode->pNext;
        }
    }
    else
    {
        //按照反方向遍历list
        while(pOriNode->pPrior!=pHead)
        {
            printf("index %d data %lld\n",i++,pOriNode->stData.data);
            pOriNode=pOriNode->pPrior;
        }

    }
    //和之前不同,最后一个节点已经是循环退出条件了,但仍需要打印
    printf("Addr %p index %d data %lld\n",pOriNode,i++,pOriNode->stData.data);
    printf("\n");

}

/*!
 * 把元素插入到双向列表中,插入后元素索引为index
 * @param pCycDulLinkObj
 * @param index
 * @param pEle
 * @return
 */
int CycDulLinkInsert(CYC_DUL_LINK_OBJ *pCycDulLinkObj,int index,ElemType*pEle) {
    DUL_NODE* pOriNode=0;
    DUL_NODE*pNewNode=0;
    int i=0;

    CHECK_PARAM(!pCycDulLinkObj||!pEle,FAILED);
    if(index>pCycDulLinkObj->len)
    {
        PRINT_MODE(PT_RED,"insert idx %d len %d",index,pCycDulLinkObj->len);
        return FAILED;
    }
    if (0==index)
    {
        pNewNode=malloc(DUL_NODE_SIZE);
        CHECK_PARAM(!pNewNode,FAILED);
        memcpy(&pNewNode->stData,pEle,ELEMENT_SIZE);
        // 未初始化时,头尾节点都为新添加的节点
        pNewNode->pNext=pCycDulLinkObj->pHead?pCycDulLinkObj->pHead:pNewNode;
        pNewNode->pPrior=pCycDulLinkObj->pTail?pCycDulLinkObj->pTail:pNewNode;
        pCycDulLinkObj->pHead=pNewNode;
        pCycDulLinkObj->pTail=pCycDulLinkObj->pTail?pCycDulLinkObj->pTail:pNewNode;
    }else{
        pOriNode=pCycDulLinkObj->pHead;
        while (pOriNode->pNext!=pCycDulLinkObj->pHead && i<index-1)
        {
            i++;
            pOriNode=pOriNode->pNext;
        }
        if(i!=index-1)
        {
            PRINT_MODE(PT_RED,"maybe some error happened ,check insert idx %u,i %u",index,i);
            return FAILED;
        }
        pNewNode=malloc(DUL_NODE_SIZE);
        CHECK_PARAM(!pNewNode,FAILED);
        memcpy(&pNewNode->stData,pEle,ELEMENT_SIZE);
        // 明早来看一下顺序
        pNewNode->pNext=pOriNode->pNext;
        pNewNode->pPrior=pOriNode;
        pOriNode->pNext=pNewNode;
        pNewNode->pNext->pPrior=pNewNode;
        pCycDulLinkObj->pTail=index==pCycDulLinkObj->len?pNewNode:pCycDulLinkObj->pTail;
    }
    pCycDulLinkObj->len++;
    return OK;

}

int CycDulLinkAppend(){
    return OK;
}

/*!
 * 将B的列表追加到A列表后面,将释放B列表头
 * @param pObjA
 * @param pObjB
 * @return
 */
int CycDulLinkExtend(CYC_DUL_LINK_OBJ*pObjA,CYC_DUL_LINK_OBJ*pObjB){
    CHECK_PARAM(!pObjA||!pObjB,FAILED);
    pObjA->pTail->pNext=pObjB->pHead;
    pObjB->pHead->pPrior=pObjB->pTail;
    pObjA->pTail=pObjB->pTail;
    pObjB->pTail->pNext=pObjA->pHead;
    pObjA->len+=pObjB->len;
    free(pObjB);
    return OK;
}

/*!
 * 删除索引为index的元素
 * @param pObj
 * @param index
 * @param pEle
 * @return
 */
int CycDulLinkDelete(CYC_DUL_LINK_OBJ*pObj,int index,ElemType*pOutEle) {
    int i=0;
//    DUL_NODE*pDelNode=0;
    DUL_NODE*pOriNode=0;
    CHECK_PARAM(!pObj||!pOutEle,FAILED);
    if(index>=pObj->len)
    {
        PRINT_MODE(PT_RED,"insert idx %d len %d",index,pObj->len);
        return FAILED;
    }
    //增加优化方法,根据索引值发生前后遍历
    if(index>=pObj->len/2)
    {
        pOriNode=pObj->pTail;
        //negative
        for(i=pObj->len-1;i>index;i--)
        {
            pOriNode=pOriNode->pPrior;
        }

    }
    else
    {
        pOriNode=pObj->pHead;
        //positive
        for(i=0;i<index;i++)
        {
            pOriNode=pOriNode->pNext;
        }
    }
//    pDelNode=pOriNode;
    pOriNode->pPrior->pNext=pOriNode->pNext;
    pOriNode->pNext->pPrior=pOriNode->pPrior;
    if(index==0)
    {
        pObj->pHead=pObj->len==1?0:pOriNode->pNext;
    }
    if(index==pObj->len-1)
    {
        pObj->pTail=pObj->len==1?0:pOriNode->pPrior;
    }
    memcpy(pOutEle,&pOriNode->stData,ELEMENT_SIZE);
    free(pOriNode);
    pObj->len--;
    return OK;
}

void CycDulLinkDeInit(CYC_DUL_LINK_OBJ*pObj){
    DUL_NODE*pDelNode=0;
    DUL_NODE*pTmpNode=0;
    int nFreeCnt=0;
    CHECK_PARAM(!pObj,);
    pTmpNode=pObj->pHead;
    while(pTmpNode->pNext!=pObj->pHead)
    {
        //先拿到后一个节点,再销毁当前节点
        pDelNode=pTmpNode;
        pTmpNode=pTmpNode->pNext;
        free(pDelNode);
        nFreeCnt++;
//        PRINT("free Node cnt %u",nFreeCnt);
    }
    free(pTmpNode);
    nFreeCnt++;
    if(nFreeCnt!=pObj->len)
    {
        PRINT_MODE(PT_RED,"some error ,len %u freecnt %u",pObj->len,nFreeCnt);
    }
    PRINT("Total Free %u Node",nFreeCnt);
    free(pObj);

}


void CycDoubleLinkTest() {
    int i=0;
    ElemType stEle={0};
    CYC_DUL_LINK_OBJ*pObj=NULL;
    pObj=CycDulLinkInit();
    for(i=0;i<8;i++)
    {
        stEle.data=i;
        CycDulLinkInsert(pObj,i,&stEle);
    }
    stEle.data=50;
    CycDulLinkInsert(pObj,50,&stEle);
    CycDulLinkInsert(pObj,3,&stEle);
    CycDulLinkInsert(pObj,6,&stEle);
    PtCycDulLink(pObj,True);
    PtCycDulLink(pObj,False);

    CycDulLinkDelete(pObj,1,&stEle);
    PRINT("del data value %lld",stEle.data);
    CycDulLinkDelete(pObj,1,&stEle);
    PRINT("del data value %lld",stEle.data);
    PtCycDulLink(pObj,False);
    CycDulLinkDelete(pObj,0,&stEle);
    PRINT("del data value %lld",stEle.data);
    CycDulLinkDelete(pObj,0,&stEle);
    PRINT("del data value %lld",stEle.data);
    CycDulLinkDelete(pObj,0,&stEle);
    PtCycDulLink(pObj,False);
    PRINT("del data value %lld",stEle.data);
    CycDulLinkDelete(pObj,pObj->len-1,&stEle);
    PRINT("del data value %lld",stEle.data);
    CycDulLinkDelete(pObj,pObj->len-1,&stEle);
    PRINT("del data value %lld",stEle.data);
    PtCycDulLink(pObj,False);
    PRINT_MODE(PT_BLUE,"Test extend list");
    CYC_DUL_LINK_OBJ*pObjExt=NULL;
    pObjExt=CycDulLinkInit();
    for(i=0;i<5;i++)
    {
        stEle.data=i;
        CycDulLinkInsert(pObjExt,i,&stEle);
    }
    PtCycDulLink(pObjExt,False);

    CycDulLinkExtend(pObj,pObjExt);
    PRINT_MODE(PT_BLUE,"PT extend list");
    PtCycDulLink(pObj,False);
    CycDulLinkDeInit(pObj);

}
