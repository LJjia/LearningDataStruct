/**
 * @Author: Jialiangjun
 * @Description: 图的存储结构表示
 * @Date: Created on 09:32 2021-09-05.
 * @Modify:
 */
#ifndef GRAPH_GRAPH_STORE_H
#define GRAPH_GRAPH_STORE_H


#include <array>
#include "graph_common.h"
#include "data_type.h"

struct AdjSide{
    int adjvex;
    int weight;
    AdjSide*pNext;
};
struct AdjVertex{
    char name[MAX_NAME_LEN];
    int data;
    // 计算拓扑排序的时候会修改这个值,增加参考值,修改完复原
    int sInDegree;
    int sInDegreeRef;
    bool bUsed;
    AdjSide *pFirst;

};


typedef void (*pAdjacencyVertexFunc)(AdjVertex*pVertex);

/*!
 * 简单邻接表,有向图
 */
class SimpleAdjacencyList{
public:
    SimpleAdjacencyList();
    ~SimpleAdjacencyList();
    int InsertVertex(const char *pName,int data);
    int InsertEdge(const char *pNameA,const char *pNameB,int weight=1);
    void DfsTraverse(pAdjacencyVertexFunc pFunc);
    void BfsTraverse(pAdjacencyVertexFunc pFunc);
    // 拓扑排序,只有向图才有
    int TopologicalSort();
    void TopologicalResetInDegree();
    int CalcKeyPath();
    void PtStruct();
protected:
    void dfs(int idx,std::array<bool,MAX_VERTEX_NUM> &visited,pAdjacencyVertexFunc pFunc);
    void bfs(int idx,std::array<bool,MAX_VERTEX_NUM> &visited,pAdjacencyVertexFunc pFunc);
    int FindNextUnusedVertex();
    int FindVetexIdxByName(const char *pName);
    int sVertexNum;
    AdjVertex stVertexArray[MAX_VERTEX_NUM];
};

/*!
 * 简单邻接表,无项图
 */
class SimpleUndirAdjacencyList:public SimpleAdjacencyList{
public:
    SimpleUndirAdjacencyList();
    ~SimpleUndirAdjacencyList();
    int InsertUndirEdge(const char *pNameA,const char *pNameB);

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
