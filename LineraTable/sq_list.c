// 线性表使用基本元素
// Created by LJjia on 2021-08-14.
//

#include "sq_list.h"



/*!
 * 初始化有序线性表
 * @return 线性比表结构体指针
 */
SqList *InitSqList() {
    SqList *pSqList = NULL;
    pSqList = malloc(sizeof(SqList));
    memset(pSqList, 0, sizeof(SqList));
    return pSqList;
}

/*!
 * 打印有序列表中的值 方便调试
 * @param pSqList
 */
void PtSqListEle(SqList * pSqList)
{
    int idx=0;
    CHECK_PARAM(!pSqList, );
    PRINT("Pt seq list value ele num %u",pSqList->length)
    for(idx=0;idx<pSqList->length;idx++)
    {
        printf("index %4u data %4llu\n",idx,pSqList->data[idx].data);
    }
    printf("\n");
}

/*!
 * 判断表是否为空
 * @param pSqList
 * @return
 */
int ListEmpty(SqList *pSqList) {
    return pSqList->length == 0 ? True : False;
}

int ListFull(SqList *pSqList) {
    return pSqList->length >= MAXSIZE ? True : False;
}

/*!
 * 交换两个Element
 * @param pSqList
 * @param idxA
 * @param idxB
 * @return
 */
void SwapEle(SqList* pSqList,int idxA,int idxB)
{
    ElemType stEle={0};
    CHECK_PARAM(!pSqList, );
    memcpy(&stEle,&pSqList->data[idxA], sizeof(ElemType));
    memcpy(&pSqList->data[idxA],&pSqList->data[idxB], sizeof(ElemType));
    memcpy(&pSqList->data[idxB],&stEle, sizeof(ElemType));
    return;
}

/*!
 * 设置一个元素的属性
 * @param pSqListEle
 * @param pDst
 */
void SetEle(ElemType * pSqListEle,ElemType * pDst)
{
    CHECK_PARAM(!pSqListEle||! pDst, );
    memcpy(pSqListEle,pDst, sizeof(ElemType));
}

/*!
 * 获取一个元素的属性
 * @param pSqListEle
 * @param pDst
 */
void GetEle(ElemType * pSqListEle,ElemType * pDst)
{
    CHECK_PARAM(!pSqListEle||! pDst, );
    memcpy(pDst,pSqListEle, sizeof(ElemType));
}

/*!
 * 插入元素,插入的元素必须是表尾或者表中间,插入的元素和表之间不可存在空位
 * @param pSqlList 有序表首指针
 * @index 插入结束后元素存在的索引位置
 * @param pEle 插入的元素
 * @return
 */
int ListInsert(SqList *pSqList, int index ,ElemType *pEle) {
    int i=0;
    CHECK_PARAM((!pSqList || !pEle),FAILED);
    if(True==ListFull(pSqList))
    {
        PRINT("list is full num %u",pSqList->length);
        return FAILED;
    }
    if(index>pSqList->length){
        PRINT("insert index error idx %u sqlist len %u",index,pSqList->length);
        return FAILED;
    }

    memmove(&pSqList->data[index+1],&pSqList->data[index], sizeof(ElemType)*(pSqList->length-index));
//    也可以使用下面的交换方法,但是感觉属实效率有点低
//    for(i=pSqList->length;i>index;i--)
//    {
//        SwapEle(pSqList,i,i-1);
//    }
    SetEle(&pSqList->data[index],pEle);
    pSqList->length++;

    return OK;
}

/*!
 * 从有序表中删除索引为index的元素,并且将删除的元素赋值给pEle指针
 * @param pSqList
 * @param index
 * @param pEle 删除的元素,会输出到这个指针中
 * @return
 */
int ListDelete(SqList *pSqList,int index,ElemType *pEle)
{
    int i=0;
    CHECK_PARAM((!pSqList||!pEle),FAILED);
    if(index<0||index>=pSqList->length)
    {
        PRINT("input index error %d",index);
        return FAILED;
    }
    memcpy(pEle,&pSqList->data[index], sizeof(ElemType));
    memmove(&pSqList->data[index],&pSqList->data[index+1], sizeof(ElemType)*(pSqList->length-index));
//    或者可使用下面的交换方法
//    for(i=index;i<pSqList->length-1;i++)
//    {
//        SwapEle(pSqList,i,i+1);
//    }
    pSqList->length--;
    return OK;
}

/*!
 * 销毁顺序数组链表
 * @param pSqList
 * @return
 */
void DestroySqList(SqList *pSqList)
{
    CHECK_PARAM(!pSqList,);
    free(pSqList);
}



/*!
 * demo测试有序列表功能
 */
void SqListTest()
{
    SqList * pSqList=NULL;
    ElemType stEle={0};
    int i=0;
    pSqList=InitSqList();
    PRINT_MODE(PT_RED,"Start Sequence List Test");
    for(i=0;i<10;i++)
    {
        stEle.data=i;
        ListInsert(pSqList,i,&stEle);
    }
    ListDelete(pSqList,2,&stEle);
    ListDelete(pSqList,4,&stEle);
    // 删除后原样插入,顺序也应该相同
    stEle.data=2;
    ListInsert(pSqList,2,&stEle);
    stEle.data=4;
    ListInsert(pSqList,4,&stEle);
    PtSqListEle(pSqList);
    DestroySqList(pSqList);

}


