/**
 * @Author: Jialiangjun
 * @Description:
 * @Date: Created on 14:18 2021-09-10.
 * @Modify:
 */
#include "MatrixGraph.h"
#include <iostream>

using namespace std;

MatrixGraph::MatrixGraph(GraphVertex*pVertex,GraphWeight*pWeight,int sVertexNum){
    CHECK_PARAM(!pVertex||!pWeight||sVertexNum>MAX_VERTEX_NUM,);
    this->pVertex=(GraphVertex*)malloc(sizeof(GraphVertex)*sVertexNum);
    this->pWeight=(GraphWeight*)malloc(sizeof(GraphWeight)*sVertexNum*sVertexNum);
    CHECK_PARAM(!this->pWeight||!this->pVertex,);
    memcpy(this->pVertex,pVertex,sVertexNum* sizeof(GraphVertex));
    memcpy(this->pWeight,pWeight,sVertexNum*sVertexNum* sizeof(GraphWeight));
    this->sVertexNum=sVertexNum;
}

MatrixGraph::MatrixGraph(GraphVertex*pVertex,int sVertexNum){
    CHECK_PARAM(!pVertex||sVertexNum>MAX_VERTEX_NUM,);
    this->pVertex=(GraphVertex*)malloc(sizeof(GraphVertex)*sVertexNum);
    this->pWeight=(GraphWeight*)malloc(sizeof(GraphWeight)*sVertexNum*sVertexNum);
    CHECK_PARAM(!this->pWeight||!this->pVertex,);
    memcpy(this->pVertex,pVertex,sVertexNum* sizeof(GraphVertex));
    memset(this->pWeight,0,sVertexNum*sVertexNum* sizeof(GraphWeight));
    this->sVertexNum=sVertexNum;
//    PRINT_MODE(PT_BLUE,"Matrix init Vertex num %d",sVertexNum);
//    for(int i=0;i<sVertexNum;i++){
//        printf("vertex name %s value %d\n",pVertex[i].name,pVertex[i].data);
//    }
//    printf("\n");

}

MatrixGraph::~MatrixGraph(){
    free(this->pWeight);
    free(this->pVertex);
}

/*!
 * 插入单边关系
 * @param pVertexA
 * @param pVertexB
 * @return
 */
int MatrixGraph::InserEdge(const char *pVertexA,const char* pVertexB){
    int sVertexA=0;
    int sVertexB=0;
    sVertexA=FindIdxByName(pVertexA);
    sVertexB=FindIdxByName(pVertexB);
    CHECK_PARAM(sVertexA>=INVALID_ARRAY_IDX||sVertexB>=INVALID_ARRAY_IDX,FAILED);
    pWeight[sVertexA*sVertexNum+sVertexB].weight=1;
    return OK;

}


int MatrixGraph::FindIdxByName(const char *pName) {
    for(int i=0;i<sVertexNum;i++){
        if(!strcmp(pName,pVertex[i].name)){
            return i;
        }
    }
    return INVALID_ARRAY_IDX;
}

/*!
 * 深度优先遍历访问某个顶点的所有路径
 * @param row
 */
void MatrixGraph::dfs(int row,array<bool,MAX_VERTEX_NUM> & visited,ProcMatrixVertexFunc pFunc){
    pFunc(&pVertex[row]);
    visited[row]=true;
    for(int i=0;i<sVertexNum;i++){
        if((pWeight[row*sVertexNum+i].weight==1)&&visited[i]== false){
            dfs(i,visited,pFunc);
        }
    }
}

/*!
 * 深度优先遍历
 * @param pFunc
 */
void MatrixGraph::DfsTraverse(ProcMatrixVertexFunc pFunc){
    array<bool,MAX_VERTEX_NUM> visited{};
    PRINT_MODE(PT_BLUE,"Matrix DfsTraverse vertex num %d",sVertexNum);
    // 防止有的顶点是一个零星的顶点 不连通
    for(int i=0;i<sVertexNum;i++){
        if(visited[i]==false){
            dfs(i,visited,pFunc);
        }
    }

}


int MatrixUndirGraph::InserUndirtEdge(const char *pVertexA,const char* pVertexB){
    int sVertexA=0;
    int sVertexB=0;
    sVertexA=FindIdxByName(pVertexA);
    sVertexB=FindIdxByName(pVertexB);
    CHECK_PARAM(sVertexA>=INVALID_ARRAY_IDX||sVertexB>=INVALID_ARRAY_IDX,FAILED);
    pWeight[sVertexA*sVertexNum+sVertexB].weight=1;
    pWeight[sVertexB*sVertexNum+sVertexA].weight=1;
    return OK;
}

/*!
 * 继承的父类构造方法,有参父类构造方法
 * 会先执行一遍父类的构造方法,然后再执行这个函数定义的内容
 * @param pVertex
 * @param sVertexNum
 */
MatrixUndirGraph::MatrixUndirGraph(GraphVertex*pVertex,int sVertexNum):MatrixGraph(pVertex,sVertexNum){

}

