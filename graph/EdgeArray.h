/**
 * @File: EdgeArray
 * @Author: Jialiangjun
 * @Description:边集数组
 * @Date: Created on 09:39 2021-09-15.
 * @Modify:
 */
#ifndef GRAPH_EDGEARRAY_H
#define GRAPH_EDGEARRAY_H

#include "graph_common.h"
#include "comm.h"

namespace EdgeArraySpace {

    enum SortOrder{
        SORT_SMALL_TO_BIG,
        SORT_BIG_TO_SMALL,
    };

    struct EdgeDesc {
        int begin;
        int end;
        int weight;
        bool bValid;
    };
    struct VertexDesc {
        char name[MAX_NAME_LEN];
        int data;
        bool bValid;
    };

/*!
 * 有向图边集数组结构,无向图类似
 */
    class EdgeArray {
    public:
        EdgeArray();

        ~EdgeArray();

        int InsertVertex(const char *pName,int data);

        int InsertEdge(const char *pTailName, const char *pHeadName, int weight=1);

        int DeleteEdge(const char *pTailName, const char *pHeadName);

        int DeleteVertex(const char *pName);

        void EdgeSort(SortOrder enOrder=SORT_SMALL_TO_BIG);

        void PtStruct();

        int CalcMiniSpanTree();

    protected:
        int sVertexNum;
        int sEdgeNum;
        VertexDesc *pVertex;
        EdgeDesc *pEdge;
        int sAllocVertexNum;
        int sAllocEdgeNum;
        int FindVertexByName(const char *pName);
        int FindIdleVertex();
        int FindIdleEdge();
        bool bNotCycle(int* aParents,int begin,int end);

        void SwapEdge(EdgeDesc &a,EdgeDesc &b);
        void EdgeArrayQuickSort(int left,int right);

    };

#define MAX_VERTEX_NUM 100

    /*!
     * 专门为顶点设计的集合,其中不含重复元素,c++stl中其实也有集合,自己先写一个实现简单功能
     * 使用集合发现对于克鲁斯卡尔算法来说没有用处是一种错误的思想
     */
    class MySet{
    public:
        MySet();
        ~MySet();
        int Add(int data);
        int Delete(int data);
        int In(int data);
        void Disp();
        inline int GetEleNum(){
            return sSetNum;
        }
    protected:
        int sSetNum;
        int aSetArray[MAX_VERTEX_NUM];
        int FindByData(int data);
    };

}
#endif //GRAPH_EDGEARRAY_H
