/**
 * @Author: JialiangJun
 * @Description:单链表的基本元素
 * @Date: Created on 10:09 2021-08-17.
 * @Modify:
 */
#include "link_list.h"

/*!
 * 初始化单链表
 * @return
 */
LINK_LIST_OBJ *InitLinkList() {
    void *pVoid = NULL;
    PRINT("Init Link List");
    pVoid = malloc(sizeof(LINK_LIST_OBJ));
    CHECK_PARAM(!pVoid, 0);
    memset(pVoid, 0, sizeof(LINK_LIST_OBJ));
    return (LINK_LIST_OBJ *) pVoid;
}

/*!
 * 打印链表中所有元素的值
 * @param pLinkListObj
 */
void PtLinkListEle(LINK_LIST_OBJ *pLinkListObj) {
    int len = 0;
    int i = 0;
    NODE *pNode = NULL;
    CHECK_PARAM(!pLinkListObj,);
    pNode = pLinkListObj->pHead;
    len = pLinkListObj->len;
    PRINT("Pt Link element");
    while (i < len) {
        printf("idx %4u data %4llu\n", i, pNode->stData.data);
        pNode = pNode->pNext;
        i++;
    }
    printf("\n");
    if (NULL != pNode) {
        PRINT("Check data vaild failed last Node have point");
    }

}

/*!
 * 向单链表后面追加元素,注意是特定向最后添加,和insert和del有区别
 * @param pEle
 * @return
 */
int LinkListAppend(LINK_LIST_OBJ *pLinkListObj, ElemType *pEle) {
    NODE *pOriNode = NULL;
    NODE *pNewNode = NULL;
    int CheckCnt = 0;
    CHECK_PARAM(!pLinkListObj || !pEle, FAILED);
    //申请表头
    if (NULL == pLinkListObj->pHead) {
        if (0 != pLinkListObj->len) {
            //数据校验
            PRINT_MODE(PT_RED, "data check error len %d check %d", pLinkListObj->len, CheckCnt);
            return FAILED;
        }
        pNewNode = malloc(sizeof(NODE));
        if (0 == pNewNode) {
            PRINT_MODE(PT_RED, "malloc failed")
            return FAILED;
        }
        memcpy(&pNewNode->stData, pEle, ELEMENT_SIZE);
        pLinkListObj->pHead = pNewNode;
        pNewNode->pNext = NULL;
        pLinkListObj->len = 1;

    } else {
        // 处理append 元素
        pOriNode = pLinkListObj->pHead;
        CheckCnt = 1;
        while (0 != pOriNode->pNext) {
            pOriNode = pOriNode->pNext;
            CheckCnt++;
        }
        if (pLinkListObj->len != CheckCnt) {
            PRINT_MODE(PT_RED, "data check error len %d check %d", pLinkListObj->len, CheckCnt);
            return FAILED;
        }
        pNewNode = malloc(sizeof(NODE));
        if (0 == pNewNode) {
            PRINT_MODE(PT_RED, "malloc failed")
            return FAILED;
        }
        memcpy(&pNewNode->stData, pEle, ELEMENT_SIZE);
        pOriNode->pNext = pNewNode;
        pNewNode->pNext = NULL;
        pLinkListObj->len++;
    }
    return OK;
}

/*!
 * 获取link list 中的元素
 * @param pLinkListObj
 * @param pOutData 输出指针
 * @return
 */
int GetLinkListEle(LINK_LIST_OBJ *pLinkListObj, int index, ElemType *pOutData) {
    int i = 0;
    NODE *pNode = NULL;
    CHECK_PARAM(!pLinkListObj || !pOutData, FAILED);
    pNode = pLinkListObj->pHead;
    while (i < index && pNode) {
        pNode = pNode->pNext;
        i++;
    }
    if ((i != index ) || 0 == pNode) {
        //可能是i比index-1要小 说明这中间出现列表指针为空的情况
        // 也有可能出现最后两个节点之间没连接上,导致指针为空
        PRINT_MODE(PT_RED, "Maybe point is null List len %u index %u pNode %p",
                pLinkListObj->len, index, pNode);
        return FAILED;
    }
    memcpy(pOutData, &pNode->stData, ELEMENT_SIZE);
    return OK;

}

/*!
 * 链表插入元素,传入的index为插入完成后元素所在的位置
 * @param pLinkListObj
 * @param index
 * @param pSrcEle
 * @return
 */
int LinkListInsert(LINK_LIST_OBJ *pLinkListObj, int index, ElemType *pSrcEle) {
    int i = 0;
    NODE *pNewNode = 0;
    NODE *pOriNode = 0;
    CHECK_PARAM(!pLinkListObj || !pSrcEle, FAILED)
    if (index > pLinkListObj->len) {
        PRINT_MODE(PT_RED, "insert index error,len %u index %u", pLinkListObj->len, index);
        return FAILED;
    }
    if (0 == index) {
        //对于头特殊处理
        pNewNode = malloc(NODE_SIZE);
        CHECK_PARAM(!pNewNode, FAILED);
        memcpy(&pNewNode->stData, pSrcEle, ELEMENT_SIZE);
        pNewNode->pNext = pLinkListObj->pHead;
        pLinkListObj->pHead = pNewNode;
    } else {
        pOriNode=pLinkListObj->pHead;
        while (i < index-1 && pOriNode) {
            pOriNode = pOriNode->pNext;
            i++;
        }
        if(i!=index-1||!pOriNode)
        {
            PRINT("check maybe some error happen point %p i %u",pOriNode,i);
            return FAILED;
        }
        pNewNode=malloc(NODE_SIZE);
        CHECK_PARAM(!pNewNode,FAILED);
        memcpy(&pNewNode->stData,pSrcEle,ELEMENT_SIZE);
        // 常规操作,pNew->pNext=pOri->pNext; pOri->pNext=pNew;
        pNewNode->pNext=pOriNode->pNext;
        pOriNode->pNext=pNewNode;

    }
    pLinkListObj->len++;
    return OK;
}

/*!
 * 删除索引为i的元素,因此需要注意实际可以传入的idx要比元素长度小1
 * @param pLinkListObj
 * @param index
 * @param pDelEle
 * @return
 */
int LinkListDelete(LINK_LIST_OBJ*pLinkListObj,int index,ElemType*pDelEle)
{
    int i=0;
    NODE* pNode=0;
    NODE* pDelNode=0;
//    NODE* pPreNode=0;
    CHECK_PARAM(!pLinkListObj||!pDelEle,FAILED);

    if (index>pLinkListObj->len-1){
        PRINT_MODE(PT_RED,"del idx %u len %u",index,pLinkListObj->len);
        return FAILED;
    }
    if(0==index)
    {
        pDelNode=pLinkListObj->pHead;
        pLinkListObj->pHead=pLinkListObj->pHead->pNext;

    } else{
        pNode=pLinkListObj->pHead;
        while(i<index-1&&pNode)
        {
            i++;
            pNode=pNode->pNext;
        }
        if(i!=index-1)
        {
            PRINT("check maybe some error happen point %p i %u",pNode,i);
            return FAILED;
        }
        // 删除元素索引为i,实际操作的节点索引为i-1
        // 常规删除操作 pDel=pNode->pNext;pNode->pNext=pDel->pNext;free(pDel);
        pDelNode=pNode->pNext;
        pNode->pNext=pDelNode->pNext;

    }
    free(pDelNode);
    pLinkListObj->len--;
    return OK;
}

/*!
 * 整表销毁,从头开始往后销毁
 * @param pLinkListObj
 * @return
 */
void LinkListDeInit(LINK_LIST_OBJ*pLinkListObj)
{
    NODE*pDelNode=0;
    NODE*pTmpNode=0;
    int nFreeCnt=0;
    CHECK_PARAM(!pLinkListObj,);
    pTmpNode=pLinkListObj->pHead;
    while(pTmpNode!=0)
    {
        //先拿到后一个节点,再销毁当前节点
        pDelNode=pTmpNode;
        pTmpNode=pTmpNode->pNext;
        // 检查free(0)为什么不会出问题
        free(pDelNode);
        nFreeCnt++;
    }
    if(nFreeCnt!=pLinkListObj->len)
    {
        PRINT_MODE(PT_RED,"some error ,len %u freecnt %u",pLinkListObj->len,nFreeCnt);
    }
    PRINT("Total Free %u Node",nFreeCnt);
    free(pLinkListObj);
}

/*!
 * 链表功能简单测试
 */
void LinkListTest() {
    LINK_LIST_OBJ *pLinkListObj = NULL;
    ElemType stEle = {0};
    int i = 0;
    PRINT_MODE(PT_RED, "Start Link List Test");
    pLinkListObj = InitLinkList();
    stEle.data=100;
    LinkListInsert(pLinkListObj,0,&stEle);
    for (i = 0; i < 10; i++) {
        stEle.data = i;
        LinkListAppend(pLinkListObj, &stEle);
    }
    stEle.data=90;
    LinkListInsert(pLinkListObj,0,&stEle);
    LinkListInsert(pLinkListObj,10,&stEle);
    LinkListInsert(pLinkListObj,11,&stEle);
    LinkListInsert(pLinkListObj,12,&stEle);
    LinkListDelete(pLinkListObj,20,&stEle);
    PRINT("del ele data %llu",stEle.data);
//    LinkListDelete(pLinkListObj,0,&stEle);
//    PRINT("del ele data %llu",stEle.data);
    PtLinkListEle(pLinkListObj);
    LinkListDeInit(pLinkListObj);
}
