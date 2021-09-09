/**
 * @Author: Jialiangjun
 * @Description:
 * @Date: Created on 09:32 2021-09-05.
 * @Modify:
 */
#include "graph_store.h"
#include <cstring>
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

MatrixGraph::~MatrixGraph(){
    free(this->pWeight);
    free(this->pVertex);
}

/*!
 * 插入边关系,可以一次插入多条边,比如"A" + "B" "C" "D" 表示插入 "AB" "AC" "AD"
 * @param pVertexA
 * @param pArrayVertexB 数组指针,可以一次插入多条边
 * @return
 */
int MatrixGraph::InsertEdge(const char *pVertexA,const char (*pArrayVertexB)[MAX_NAME_LEN],int sEdgeNum){
    int sVertexA=0;
    int sVertexB=0;
    sVertexA=FindIdxByName(pVertexA);
    CHECK_PARAM(sVertexA>=INVALID_ARRAY_IDX,FAILED);
    for(int i=0;i<sEdgeNum;i++){
        sVertexB=FindIdxByName(pArrayVertexB[i]);
        CHECK_PARAM(sVertexB>=INVALID_ARRAY_IDX,FAILED);
        pWeight[sVertexA*sVertexNum+sVertexB].weight=1;
        pWeight[sVertexB*sVertexNum+sVertexA].weight=1;
    }
    return OK;
}
int MatrixGraph::InsertEdge(const char *pVertexA,const char* pVertexB){
    int sVertexA=0;
    int sVertexB=0;
    sVertexA=FindIdxByName(pVertexA);
    sVertexB=FindIdxByName(pVertexB);
    CHECK_PARAM(sVertexA>=INVALID_ARRAY_IDX||sVertexB>=INVALID_ARRAY_IDX,FAILED);
    pWeight[sVertexA*sVertexNum+sVertexB].weight=1;
    pWeight[sVertexB*sVertexNum+sVertexA].weight=1;
    return OK;
}

int MatrixGraph::FindIdxByName(const char *pName) {
    for(int i=0;i<sVertexNum;i++){
        if(!strcmp(pName,pVertex->name)){
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




OrthogonalDirGraph::OrthogonalDirGraph(){
    memset(stVertexArray, 0,sizeof(stVertexArray));
    sVertexNum=0;
}
OrthogonalDirGraph::~OrthogonalDirGraph(){
    int sNodeCnt=0;
    OrthSideLink*pSide= nullptr;
    OrthSideLink*pFree= nullptr;
    PRINT_MODE(PT_BLUE,"free Orthogonal Direct Graph")
    for(int i=0;i<MAX_VERTEX_NUM;i++){
        pSide=stVertexArray[i].pFirstOut;
        while(pSide){
            pFree=pSide;
            pSide=pSide->pTail;
            free(pFree);
        }

        sNodeCnt++;
        if(sNodeCnt>=sVertexNum){
            break;
        }
    }
}

int OrthogonalDirGraph::InsertVertex(const char *pName,int data){
    int i=0;
    int sIdleIdx=0;
    sIdleIdx=FindVetexIdxByName(pName);
    if(sIdleIdx<MAX_VERTEX_NUM){
        PRINT_ERR("find same name %s,repect insert node ",pName);
        return FAILED;
    }
    sIdleIdx=FindNextUnusedVertex();
    if(sIdleIdx>=MAX_VERTEX_NUM){
        PRINT_ERR("can not find idle node ");
        return FAILED;
    }
    stVertexArray[sIdleIdx].bUsed=True;
    stVertexArray[sIdleIdx].data=data;
    strncpy(stVertexArray[sIdleIdx].name,pName,MAX_NAME_LEN);
    sVertexNum++;
    return OK;
}


int OrthogonalDirGraph::InsertEdge(const char *pTailName, const char *pHeadName, int weight) {
    int i=0;
    int sTailIdx=0;
    int sHeadIdx=0;
    OrthSideLink *pNewSide= nullptr;
    OrthSideLink *pOriSide= nullptr;
    CHECK_PARAM(!pTailName||!pHeadName,FAILED);
    sTailIdx=FindVetexIdxByName(pTailName);
    sHeadIdx=FindVetexIdxByName(pHeadName);
    if(sTailIdx>=MAX_VERTEX_NUM||sHeadIdx>=MAX_VERTEX_NUM){
        PRINT_ERR("Tail %d Head %d name %s %s",sTailIdx,sHeadIdx,pTailName,pHeadName);
        return FAILED;
    }
    pNewSide=(OrthSideLink *)malloc(sizeof(OrthSideLink));
    CHECK_PARAM(!pNewSide,FAILED);
    memset(pNewSide,0,sizeof(OrthSideLink));
    //一个关系显然只能有一个出度一个入度

    // 出度链表,前插法,完善pTailName的出度关系
    pNewSide->pTail=stVertexArray[sTailIdx].pFirstOut;
    stVertexArray[sTailIdx].pFirstOut=pNewSide;
    pNewSide->weight=weight;
    pNewSide->sTailIdx=sTailIdx;
    pNewSide->sHeadIdx=sHeadIdx;
    // .pFirstIn链表中记录了哪些节点指向当前节点,按pHead遍历即可
    // 下面的作用是将完善指向名为pHeadName的链表,完善pHeadName的入度关系
    if(stVertexArray[sHeadIdx].pFirstIn== nullptr){
        stVertexArray[sHeadIdx].pFirstIn=pNewSide;
    } else {
        pOriSide=stVertexArray[sHeadIdx].pFirstIn;
        // 第一次pOriSide必有值,所以接下来只需要判断pOriSide->pHead有没有值即可
        while(pOriSide->pHead!= nullptr){
            pOriSide=pOriSide->pHead;
        }
        pOriSide->pHead=pNewSide;

    }
    return OK;
}

/*!
 * 删除无向图的一条弧
 * @param pTailName
 * @param pHeadName
 * @return
 */
void OrthogonalDirGraph::DeleteEdge(const char* pTailName,const char* pHeadName){
    int sTailIdx=0,sHeadIdx=0;
    OrthSideLink*pFreSide= nullptr;
    OrthSideLink**ppOriSide= nullptr;   //记录非那顾问的前一个side节点
    OrthSideLink*pHead= nullptr;    // 清理弧头列表
    CHECK_PARAM(!pTailName||!pHeadName,);
    sTailIdx=FindVetexIdxByName(pTailName);
    sHeadIdx=FindVetexIdxByName(pHeadName);
    pFreSide=stVertexArray[sTailIdx].pFirstOut;
    ppOriSide=&stVertexArray[sTailIdx].pFirstOut;
    while(pFreSide&&pFreSide->sHeadIdx!=sHeadIdx){
        ppOriSide=&pFreSide->pTail;
        pFreSide=pFreSide->pTail;
    }
    if(!pFreSide){
        PRINT_ERR("not find corresponse relation %s-%s",pTailName,pHeadName);
        return ;
    }
    *ppOriSide=pFreSide->pTail;
    pHead=stVertexArray[sHeadIdx].pFirstIn;
    ppOriSide=&stVertexArray[sHeadIdx].pFirstIn;
    while(pHead&&pHead!=pFreSide){
        ppOriSide=&pHead->pHead;
        pHead=pHead->pHead;
    }
    if(!pHead){
        PRINT_ERR("not find pHead corresponse relation %s-%s pFreSide %p",pTailName,pHeadName,pFreSide);
        return ;
    }
    // head 链表剪切,此时pHead==pFreSide
    *ppOriSide=pFreSide->pHead;
    free(pFreSide);
    PRINT("delete releation %s->%s ok",pTailName,pHeadName);
}
/*!
 * 删除节点及其对应的弧
 * @param pName
 * @return
 */
void OrthogonalDirGraph::DeleteVertex(const char* pName){
    int sDelIdx=0;
    OrthSideLink*pSide= nullptr;
    OrthSideLink*pOriSide= nullptr;
    CHECK_PARAM(!pName,);
    sDelIdx=FindVetexIdxByName(pName);
    CHECK_PARAM(sDelIdx>=MAX_VERTEX_NUM,);
    // 删除出边
    pSide=stVertexArray[sDelIdx].pFirstOut;
    while (pSide){
        // 先记录变量,再释放,之后再将对应赋值.
        // 循环删除边
        pOriSide=pSide->pTail;
        DeleteEdge(stVertexArray[pSide->sTailIdx].name,stVertexArray[pSide->sHeadIdx].name);
        pSide=pOriSide;
    }
    // 删除入边
    pSide=stVertexArray[sDelIdx].pFirstIn;
    while(pSide){
        pOriSide=pSide->pHead;
        DeleteEdge(stVertexArray[pSide->sTailIdx].name,stVertexArray[pSide->sHeadIdx].name);
        pSide=pOriSide;
    }

    memset(&stVertexArray[sDelIdx],0,sizeof(OrthVertex));
    sVertexNum--;
    PRINT("delete vertex %s ok",pName);
}

/*!
 * 返回下一个空闲节点的索引idx,没有返回-1
 * @return
 */
int OrthogonalDirGraph::FindNextUnusedVertex(){
    int i=0;
    for(;i<MAX_VERTEX_NUM;i++){
        if(!stVertexArray[i].bUsed){
            return i;
        }
    }

    return INVALID_ARRAY_IDX;


}

/*!
 * 寻找是否有同名节点,没有,返回INVALID_ARRAY_IDX,有返回对应索引
 * @param pName
 * @return
 */
int OrthogonalDirGraph::FindVetexIdxByName(const char *pName){
    int i=0;
    int sVertexCnt=0;
    for(;i<MAX_VERTEX_NUM;i++){
        if(stVertexArray[i].bUsed){
            if(!strcmp(pName,stVertexArray[i].name)){
                return i;
            }
            sVertexCnt++;
            if(sVertexCnt>=sVertexNum){
                break;
            }
        }
    }
    return INVALID_ARRAY_IDX;
}

void OrthogonalDirGraph::PtStruct(){
    int i=0;
    int sPtCnt=0;
    OrthSideLink*pSide= nullptr;
    PRINT_MODE(PT_BLUE,"pt graph struct vertex num %d",sVertexNum);
    for(i=0;i<MAX_VERTEX_NUM;i++){
        if(!stVertexArray[i].bUsed){
            continue;
        }
        printf("Vertex name %s data %d first in %p out %p ",
                stVertexArray[i].name,stVertexArray[i].data,
                stVertexArray[i].pFirstIn,stVertexArray[i].pFirstOut);
        pSide=stVertexArray[i].pFirstOut;
        while(pSide){
            printf("[side: tail %d head %d weight %d ",pSide->sTailIdx,pSide->sHeadIdx,pSide->weight);
            printf("Addr %p pHead %p pTail %p ]",pSide,pSide->pHead,pSide->pTail);
            pSide=pSide->pTail;
        }
        printf("\n");
        sPtCnt++;
        if(sPtCnt>=sVertexNum){
            break;
        }
    }

}