/**
 * @File: EdgeArray
 * @Author: Jialiangjun
 * @Description:
 * @Date: Created on 09:39 2021-09-15.
 * @Modify:
 */
#include <cstdlib>
#include <iostream>
#include "EdgeArray.h"

namespace EdgeArraySpace {
    using std::cout;
    using std::cin;
    using std::endl;

    EdgeArray::EdgeArray() {
        sVertexNum = 0;
        sEdgeNum=0;
        sAllocVertexNum=0;
        sAllocEdgeNum=0;
        pVertex = nullptr;
        pEdge = nullptr;
    }

    EdgeArray::~EdgeArray() {
        free(pVertex);
        free(pEdge);
    }

    int EdgeArray::InsertVertex(const char *pName, int data) {
        VertexDesc *pTmp = nullptr;
        int sIdleIdx = INVALID_ARRAY_IDX;
        CHECK_PARAM(!pName, FAILED);
        sIdleIdx = FindIdleVertex();
        if (sIdleIdx != INVALID_ARRAY_IDX) {
            pVertex[sIdleIdx].data = data;
            strncpy(pVertex[sIdleIdx].name, pName, MAX_NAME_LEN);
            pVertex[sIdleIdx].bValid = true;
        } else {
            pTmp = (VertexDesc *) realloc(pVertex, sizeof(VertexDesc) * (sVertexNum + 1));
            if (pTmp) {
                pVertex = pTmp;
            } else {
                PRINT_ERR("malloc mem err vertex num %d", sVertexNum);
                return FAILED;
            }
            pVertex[sVertexNum].data = data;
            strncpy(pVertex[sVertexNum].name, pName, MAX_NAME_LEN);
            pVertex[sVertexNum].bValid = true;
            sAllocVertexNum++;
        }

        sVertexNum++;
        return OK;
    }

    int EdgeArray::InsertEdge(const char *pTailName, const char *pHeadName, int weight) {
        //TODO:无法检查是否插入了重复的边
        EdgeDesc *pTmp = nullptr;
        int sIdleIdx = INVALID_ARRAY_IDX;
        int sBeginIdx = INVALID_ARRAY_IDX;
        int sEndIdx = INVALID_ARRAY_IDX;

        CHECK_PARAM(!pTailName || !pHeadName, FAILED);
        sBeginIdx = FindVertexByName(pTailName);
        sEndIdx = FindVertexByName(pHeadName);
        if (sBeginIdx == INVALID_ARRAY_IDX || sEndIdx == INVALID_ARRAY_IDX) {
            PRINT_ERR("cannt find pTail %s pHead %s vertex num %d", pTailName, pHeadName, sVertexNum);
            return FAILED;
        }
        sIdleIdx = FindIdleEdge();
        if (sIdleIdx != INVALID_ARRAY_IDX) {
            pEdge[sIdleIdx].begin = sBeginIdx;
            pEdge[sIdleIdx].end = sEndIdx;
            pEdge[sIdleIdx].weight = weight;
            pEdge[sIdleIdx].bValid = true;

        } else {
            pTmp = (EdgeDesc *) realloc(pEdge, sizeof(EdgeDesc) * (sEdgeNum + 1));
            if (pTmp) {
                pEdge = pTmp;
            } else {
                PRINT_ERR("malloc mem err vertex num %d", sEdgeNum);
                return FAILED;
            }
            pEdge[sEdgeNum].begin = sBeginIdx;
            pEdge[sEdgeNum].end = sEndIdx;
            pEdge[sEdgeNum].weight = weight;
            pEdge[sEdgeNum].bValid = true;
            sAllocEdgeNum++;
        }
        sEdgeNum++;
        return OK;
    }

    void EdgeArray::PtStruct() {
        int sVertexCnt=0;
        int sEdgeCnt=0;
        int i=0;
        PRINT_MODE(PT_BLUE,"Pt Edge array struct");
        PRINT_MODE(PT_BLUE,"vertex array ");
        for(i=0;i<sAllocVertexNum;i++){
            if(pVertex[i].bValid){
                printf("vertex %d name %s data %d\n",sVertexCnt,pVertex[i].name,pVertex[i].data);
                sVertexCnt++;
            }
        }
        PRINT_MODE(PT_BLUE,"Edge array ");
        for(i=0;i<sAllocEdgeNum;i++){
            if(pEdge[i].bValid){
                printf("edge %d begin %d end %d weight %d\n",
                        sEdgeCnt,pEdge[i].begin,pEdge[i].end,pEdge[i].weight);
                sEdgeCnt++;
            }
        }
        printf("\n");

    }

    int EdgeArray::FindVertexByName(const char *pName) {
        CHECK_PARAM(!pName, FAILED);
        for (int i = 0; i < sVertexNum; i++) {
            if (pVertex[i].bValid && !strcmp(pName, pVertex[i].name)) {
                return i;
            }
        }
        return INVALID_ARRAY_IDX;
    }

    int EdgeArray::FindIdleVertex() {
        if(sVertexNum==0){
            return INVALID_ARRAY_IDX;
        }
        for (int i = 0; i < sVertexNum; i++) {
            if (!pVertex[i].bValid) {
                return i;
            }
        }
        return INVALID_ARRAY_IDX;
    }

    int EdgeArray::FindIdleEdge() {
        if(sEdgeNum==0){
            return INVALID_ARRAY_IDX;
        }
        for (int i = 0; i < sEdgeNum; i++) {
            if (!pEdge[i].bValid) {
                return i;
            }
        }
        return INVALID_ARRAY_IDX;
    }

    /*!
     * 删除一条边,需要区分有项图和无向图
     * @param pTailName
     * @param pHeadName
     * @return
     */
    int EdgeArray::DeleteEdge(const char *pTailName, const char *pHeadName){
        //TODO:注意节点和边的数据结构
        return OK;
    }

    /*!
     * 删除一个节点及其对应的边
     * @param pName
     * @return
     */
    int EdgeArray::DeleteVertex(const char *pName){
        //TODO:注意节点和边的数据结构
        return OK;
    }

    /*!
     * 按照边的权重对边数组进行排序,当前仅从大到小排序
     * @return
     */
    void EdgeArray::EdgeSort(SortOrder enOrder){
        PRINT_MODE(PT_BLUE,"sort Edge num %d",sEdgeNum);
        EdgeArrayQuickSort(0,sEdgeNum-1);
    }

    /*!
     * 交换两个边的数据
     * @param a
     * @param b
     */
    void EdgeArray::SwapEdge(EdgeDesc &a,EdgeDesc &b){
        EdgeDesc tmp;
        memcpy(&tmp,&a,sizeof(EdgeDesc));
        memcpy(&a,&b,sizeof(EdgeDesc));
        memcpy(&b,&tmp,sizeof(EdgeDesc));
    }

    /*!
     * 边集数组对边权重进行快速排序
     * @param left 最左边元素索引
     * @param right 最右边元素索引 双闭区间[]
     * @return
     */
    void EdgeArray::EdgeArrayQuickSort(int left,int right){
        //TODO:删除边的操作无法在排序中实现,因为排序要求数据分布都是连续的
        EdgeDesc stEdgeTmp{};
        int sLeft=left;
        int sRight=right;
//        PRINT("loop start left %d right %d",left,right);
        if(sEdgeNum<=1){
            return ;
        }
        if(left>=right){
            // 最小可能遇到两个元素的情况,一个元素直接退出
            return ;
        }
        memcpy(&stEdgeTmp,&pEdge[left], sizeof(EdgeDesc));
        while(1){
            while(sLeft!=sRight&&pEdge[sRight].weight>=stEdgeTmp.weight){
                sRight--;
            }
            if(sLeft==sRight){
                break;
            }
//            PRINT("1 swap %d %d",pEdge[sLeft].weight,pEdge[sRight].weight);
            memcpy(&pEdge[sLeft],&pEdge[sRight],sizeof(EdgeDesc));
            // 拷贝完后,sRight的位置相当于一个空的占位符,
            // 需要对应左边的数据来填充他,或者由一开始的stEdgeTmp来填充
            sLeft++;
            while(sLeft!=sRight && pEdge[sLeft].weight<=stEdgeTmp.weight){
                sLeft++;
            }
            if(sLeft==sRight){
                break;
            }
//            PRINT("2 swap %d %d",pEdge[sLeft].weight,pEdge[sRight].weight);
            // 拷贝完后 sLeft的位置相当于一个空的占位符,
            // 需要对应右边的数据来填充,或者由一开始的stEdgeTmp来填充
            memcpy(&pEdge[sRight],&pEdge[sLeft], sizeof(EdgeDesc));
            sRight--;
        }
        memcpy(&pEdge[sLeft],&stEdgeTmp, sizeof(EdgeDesc));
//        PRINT("cur loop end left %d right %d empty %d",left,right,sLeft);
        EdgeArrayQuickSort(left,sLeft-1);
        EdgeArrayQuickSort(sLeft+1,right);
    }

    /*!
     * 判断两条边是否成环
     * 依据根判断,,每次把end所在的树挂到begin所在树的根上,运气不好可能会生成线性表的树,复杂度较高
     * 有优化空间
     * @param aParents
     * @param begin
     * @param end
     * @return
     */
    bool EdgeArray::bNotCycle(int* aParents,int begin,int end){
        int sBeginIdx=begin;
        int sEndIdx=end;

        while(aParents[sBeginIdx]!=-1){
            sBeginIdx=aParents[sBeginIdx];
        }
        while (aParents[sEndIdx]!=-1){
            sEndIdx=aParents[sEndIdx];
        }
        if(sEndIdx!=sBeginIdx){
            // 证明end的根和begin的根不是同一个根,这个时候把end的根挂在begin根上
            aParents[sEndIdx]=sBeginIdx;
        }
        for(int i=0;i<10;i++){
            printf("idx %d pare %d\n",i,aParents[i]);
        }
        // 如果两条边遇上同一个根,则说明形成环
        return sEndIdx==sBeginIdx?false:true;
    }


    /*!
     * 计算最小生成树 克鲁斯卡尔算法
     * 每次都寻找最优边,遇到成环的边,则舍弃
     * @return
     */
    int EdgeArray::CalcMiniSpanTree(){
        int aParents[MAX_VERTEX_NUM];
        int i=0;
        int sEdgeCnt=0;
        int sTotalCost=0;
        bool bOk;
        memset(aParents,-1,sizeof(aParents));
        for(i=0;i<sEdgeNum;i++){
            bOk=bNotCycle(aParents,pEdge[i].begin,pEdge[i].end);
            if(bOk){
                sEdgeCnt++;
                sTotalCost+=pEdge[i].weight;
                PRINT("Add edge begin %d end %d weight %d",pEdge[i].begin,pEdge[i].end,pEdge[i].weight);
                if(sEdgeCnt>=sVertexNum-1){
                    break;
                }
            }
        }
        PRINT("total cost %d",sTotalCost);
        return OK;

    }

    MySet::MySet(){
        memset(aSetArray,0, sizeof(aSetArray));
        sSetNum=0;
    }
    MySet::~MySet(){
        memset(aSetArray,0, sizeof(aSetArray));
        sSetNum=0;
    }

    /*!
     * 简单增加,不进行排序,新插入的元素放在最后
     * @return
     */
    int MySet::Add(int data){
        int idx=0;
        idx=FindByData(data);
        if(idx!=INVALID_ARRAY_IDX){
            return FAILED;
        }
        aSetArray[sSetNum]=data;
        sSetNum++;
        return OK;
    }

    /*!
     * 删除,删除之后移动元素,让中间没有空位
     * @return
     */
    int MySet::Delete(int data){
        int idx=0;
        idx=FindByData(data);
        if(idx==INVALID_ARRAY_IDX){
            return FAILED;
        }
        memmove(&aSetArray[idx],&aSetArray[idx+1],(sSetNum-1-idx)*sizeof(int));
        sSetNum--;
        return OK;
    }

    int MySet::In(int data){
        int idx=0;
        idx=FindByData(data);
        if(idx==INVALID_ARRAY_IDX){
            return FAILED;
        }
        return OK;
    }

    void MySet::Disp(){
        int idx=0;
        PRINT("set has %d ele",sSetNum);
        for(idx=0;idx<sSetNum;idx++){
            printf(" idx %d data %d\n",idx,aSetArray[idx]);
        }

    }

    int MySet::FindByData(int data){
        for(int i=0;i<sSetNum;i++){
            if(aSetArray[i]==data){
                return i;
            }
        }
        return INVALID_ARRAY_IDX;
    }
}


