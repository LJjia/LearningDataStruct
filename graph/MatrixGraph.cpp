/**
 * @Author: Jialiangjun
 * @Description:
 * @Date: Created on 14:18 2021-09-10.
 * @Modify:
 */
#include "MatrixGraph.h"
#include <iostream>
#include <queue>

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
    if (visited[row]){
        return;
    }
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

/*!
 * 函数外部已经考虑过,不是访问过得节点,不会调用这个函数
 * @param row
 * @param visited
 * @param pFunc
 */
void MatrixGraph::bfs(int row,array<bool,MAX_VERTEX_NUM> & visited,ProcMatrixVertexFunc pFunc){
    if (visited[row]){
        return;
    }
    queue <int > queue1;
    queue1.push(row);
    while(!queue1.empty()){
        int sOutIdx=queue1.front();
        // 如果这个节点没有访问过,则访问,并将对应访问位置1
        // 并且将这个节点关联的节点push进队列
        if(!visited[sOutIdx]){
            pFunc(&pVertex[sOutIdx]);
            visited[sOutIdx]=true;
//            PRINT("pop name %s",pVertex[sOutIdx].name);
            for(int sAddIdx=0;sAddIdx<sVertexNum;sAddIdx++){
                if(pWeight[sOutIdx*sVertexNum+sAddIdx].weight&&!visited[sAddIdx]){
                    queue1.push(sAddIdx);
//                    PRINT("push name %s",pVertex[sAddIdx].name);
                }
            }
        }
        // 不管之前这个节点有没有访问过,都会将这个节点pop走
        queue1.pop();

    }
}



void MatrixGraph::BfsTraverse(ProcMatrixVertexFunc pFunc){
    array<bool,MAX_VERTEX_NUM> visited{};
    PRINT_MODE(PT_BLUE,"Matrix BfsTraverse vertex num %d",sVertexNum);
    // 防止有的顶点是一个零星的顶点 不连通
    for(int i=0;i<sVertexNum;i++){
        if(visited[i]==false){
            bfs(i,visited,pFunc);
        }
    }
}


int MatrixUndirGraph::InserUndirtEdge(const char *pVertexA,const char* pVertexB,int weight){
    int sVertexA=0;
    int sVertexB=0;
    sVertexA=FindIdxByName(pVertexA);
    sVertexB=FindIdxByName(pVertexB);
    CHECK_PARAM(sVertexA>=INVALID_ARRAY_IDX||sVertexB>=INVALID_ARRAY_IDX,FAILED);
    pWeight[sVertexA*sVertexNum+sVertexB].weight=weight;
    pWeight[sVertexB*sVertexNum+sVertexA].weight=weight;
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

