/**
 * @Author: Jialiangjun
 * @Description:
 * @Date: Created on 14:18 2021-09-10.
 * @Modify:
 */
#ifndef GRAPH_MATRIXGRAPH_H
#define GRAPH_MATRIXGRAPH_H

#include "graph_common.h"
#include <array>
#include "comm.h"

struct GraphVertex{
    char name[MAX_NAME_LEN];
    int data;
};

struct GraphWeight{
    int weight;
};

typedef void (*ProcMatrixVertexFunc)(GraphVertex*pVertex);

/*!
 * 二维矩阵表示图,有向,有项图和无向图表示方法类似
 */
class MatrixGraph {
public:
    MatrixGraph(GraphVertex*pVertex,GraphWeight*pWeight,int sVertexNum);
    // 自动申请权重矩阵
    MatrixGraph(GraphVertex*pVertex,int sVertexNum);
    ~MatrixGraph();
    int InserEdge(const char *pVertexA,const char* pVertexB);
    // 深度优先遍历
    void DfsTraverse(ProcMatrixVertexFunc pFunc);

protected:
    int FindIdxByName(const char *pName);
    void dfs(int row,std::array<bool,MAX_VERTEX_NUM> & visited,ProcMatrixVertexFunc pFunc);
    int sVertexNum;
    GraphVertex* pVertex;
    GraphWeight*pWeight; //应该是一个二维数组指针,但是不确定行数,所以只能采用首地址的方式

};

/*!
 * 二维矩阵表示图,无向图
 */
class MatrixUndirGraph:public MatrixGraph{
public:
    MatrixUndirGraph(GraphVertex*pVertex,int sVertexNum);
    int InserUndirtEdge(const char *pVertexA,const char* pVertexB);

};




#endif //GRAPH_MATRIXGRAPH_H
