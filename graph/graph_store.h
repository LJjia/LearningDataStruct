/**
 * @Author: Jialiangjun
 * @Description: 图的存储结构表示
 * @Date: Created on 09:32 2021-09-05.
 * @Modify:
 */
#ifndef GRAPH_GRAPH_STORE_H
#define GRAPH_GRAPH_STORE_H

#include <limits.h>

#include "data_type.h"

#define INVALID_WEIGHT INT INT_MAX
#define MAX_VERTEX_NUM 100
#define MAX_NAME_LEN 16
#define INVALID_ARRAY_IDX INT_MAX


struct GraphVertex{
    char name[16];
    int data;
};

struct GraphWeight{
    int weight;
};

/*!
 * 二维矩阵表示图
 */
class MatrixGraph {
public:
    MatrixGraph(GraphVertex*pVertex,GraphWeight*pWeight,int sVertexNum);
    ~MatrixGraph();

private:
    int sVertexNum;
    GraphVertex* pVertex;
    GraphWeight*pWeight; //应该是一个二维数组指针,但是不确定行数,所以只能采用首地址的方式

};

struct OrthSideLink{
    int sTailIdx;
    int sHeadIdx;
    int weight;
    OrthSideLink*pHead; //当前顶点做表头,后面链接当前节点入度
    OrthSideLink*pTail; //当前顶点做表尾,后面链接的是当前节点出度
};

struct OrthVertex{
    char name[16];
    int data;
    OrthSideLink*pFirstIn;
    OrthSideLink*pFirstOut;
    bool bUsed;

};
/*!
 * 十字邻接表,类似数组+链表.十字链表在于可以前后遍历链表,采用有向链表
 * 图中没有根节点的概念,基本上每个节点都可以视作根节点
 */
class OrthogonalDirGraph{
public:
    OrthogonalDirGraph();
    ~OrthogonalDirGraph();
    // 将插入边和插入节点分为两个函数,通过给出节点的名字来插入边,节点名字必须要是可打印字符串
    int InsertEdge(const char* pTailName,const char* pHeadName,int weight);
    void DeleteEdge(const char* pTailName,const char* pHeadName);
    int InsertVertex(const char *pName,int data);
    void DeleteVertex(const char* pName);
    void PtStruct();

private:
    int FindNextUnusedVertex();

    int FindVetexIdxByName(const char *pName);
    OrthVertex stVertexArray[MAX_VERTEX_NUM];
    int sVertexNum;


};




#endif //GRAPH_GRAPH_STORE_H
