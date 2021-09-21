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
    // 默认元素赋值为-1
    // 但是需要注意,不可使用memset赋值
    // 因为是char类型赋值,所以赋值完后,所以数据为0xff,而不是0x7f
    for(int idx=0;idx<sVertexNum*sVertexNum;idx++){
        this->pWeight[idx].weight=INVALID_WEIGHT;
    }

    for(int i=0;i<sVertexNum;i++){
        // 对角线元素赋值为∞,表示不存在这样的边
        this->pWeight[i*sVertexNum+i].weight=0;
    }
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
int MatrixGraph::InsertEdge(const char *pVertexA,const char* pVertexB,int weight){
    int sVertexA=0;
    int sVertexB=0;
    sVertexA=FindIdxByName(pVertexA);
    sVertexB=FindIdxByName(pVertexB);
    CHECK_PARAM(sVertexA>=INVALID_ARRAY_IDX||sVertexB>=INVALID_ARRAY_IDX,FAILED);
    pWeight[sVertexA*sVertexNum+sVertexB].weight=weight;
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

void MatrixGraph::Disp(){
    printf("disp data %d %x\n",INT_MAX,INT_MAX);
    PRINT_MODE(PT_BLUE,"Disp Matrix graph Vertex num %d",sVertexNum);
    for(int i=0;i<sVertexNum;i++){
        printf("array %d:",i);
        for(int j=0;j<sVertexNum;j++){
            printf(" %4d\t",pWeight[i*sVertexNum+j].weight);
        }
        printf("\n");
    }
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

/*!
 * 计算最小生成树
 */
void MatrixGraph::CalcMiniSpanTree(){
    int aWeight[MAX_VERTEX_NUM]{};
    int i=0;
    int sTotalCost=0;
    Disp();
    for(int i=0;i<sVertexNum;i++){
        aWeight[i]=INVALID_WEIGHT;
    }
    aWeight[0]=0;
    for(i=1;i<sVertexNum;i++){
        // 首先计算第一行 不允许中间有weight=0边存在的情况
        if(pWeight[0+i].weight>0&&pWeight[0+i].weight<INVALID_WEIGHT){
            // 首次记录下到v0最近的距离
            aWeight[i]=pWeight[i].weight;
        }
    }
    PRINT("first use add v0 to set");
    for(int line=1;line<sVertexNum;line++){
        // 寻找最小非0值的索引
        int sMinIdx=-1;
        int sMinValue=INVALID_WEIGHT;
        for(i=0;i<sVertexNum;i++){
            if(aWeight[i]<sMinValue&&aWeight[i]>0){
                sMinValue=aWeight[i];
                sMinIdx=i;
            }
        }
//        for(int tmp=0;tmp<sVertexNum;tmp++){
//            printf("aweight %d\n",aWeight[tmp]);
//        }
        PRINT("next add v%d weight %d",sMinIdx,sMinValue);
        aWeight[sMinIdx]=0;
        sTotalCost+=sMinValue;
        for(i=0;i<sVertexNum;i++){
            if(pWeight[sMinIdx*sVertexNum+i].weight>0&&pWeight[sMinIdx*sVertexNum+i].weight<INVALID_WEIGHT){
                if(pWeight[sMinIdx*sVertexNum+i].weight<aWeight[i]){
                    aWeight[i]=pWeight[sMinIdx*sVertexNum+i].weight;
                }
            }
        }
    }

    PRINT("calc end sTotal cost %d",sTotalCost);

}

/*!
 * 计算v0到某个点的最短路径
 */
void MatrixGraph::CalcShortestPathDijkstra(const char *pStart,const char *pEnd){
    int sStartIdx=0;
    int sEndIdx=0;
    int aMiniCost[MAX_VERTEX_NUM];
    bool bCalc[MAX_VERTEX_NUM];
    int aFront[MAX_VERTEX_NUM];
    int i=0;
    int sCurMinValue=INVALID_WEIGHT;
    int sCurMinIdx=INVALID_ARRAY_IDX;
    sStartIdx=FindIdxByName(pStart);
    sEndIdx=FindIdxByName(pEnd);
    if(sStartIdx>=MAX_VERTEX_NUM||sEndIdx>=MAX_VERTEX_NUM){
        PRINT_ERR("not find start %s %d end %s %d",pStart,sStartIdx,pEnd,sEndIdx);
        return ;
    }
    for(i=0;i<sVertexNum;i++){
        aMiniCost[i]=INVALID_WEIGHT;
        bCalc[i]= false;
        aFront[i]=INVALID_ARRAY_IDX;
    }
    // v0先赋初始值
    bCalc[sStartIdx]=true;
    for(i=0;i<sVertexNum;i++){
        if(i!=sStartIdx&&pWeight[sStartIdx*sVertexNum+i].weight!=INVALID_WEIGHT){
            aMiniCost[i]=pWeight[sStartIdx*sVertexNum+i].weight;
            aFront[i]=sStartIdx;
        }
    }
    aMiniCost[sStartIdx]=0;

    while(1)
    {
        sCurMinValue=INVALID_WEIGHT;
        sCurMinIdx=INVALID_ARRAY_IDX;
        for(int i=0;i<sVertexNum;i++){
            if(!bCalc[i]&&aMiniCost[i]<sCurMinValue){
                sCurMinValue=aMiniCost[i];
                sCurMinIdx=i;
            }

        }
        PRINT("%s next %s min value %d",pVertex[sStartIdx].name,pVertex[sCurMinIdx].name,sCurMinValue);
        if(sCurMinIdx==sEndIdx){
            PRINT("end find minest path cost %d",sCurMinValue);
            break;
        }
        bCalc[sCurMinIdx]=true;
        for(i=0;i<sVertexNum;i++){
            // 每次更新一个顶点的影响,并且更新的这个顶点,不会对之后顶点的更新带来影响,不会产生虚假最小值的顶点
            // (因为这个更新的顶点是当前所有顶点中最小值,如果更新更大的顶点,可能会出现虚假最小值,由最小值顶点带来的影响)
            if(i!=sCurMinIdx&&pWeight[sCurMinIdx*sVertexNum+i].weight!=INVALID_WEIGHT){
                // 如果当前这个节点有连接
                if(pWeight[sCurMinIdx*sVertexNum+i].weight+sCurMinValue<aMiniCost[i]){
                    // 并且链接作用于的作用效果比先前的损失要小
                    // 则更新初始节点到i节点的损失,表示start顶点可以使用aMiniCost[i]的权重走到pVertex[i]顶点
                    aMiniCost[i]=pWeight[sCurMinIdx*sVertexNum+i].weight+sCurMinValue;
                    aFront[i]=sCurMinIdx;
                }
            }
        }
        // 之后再找损失最低的那个顶点
    }
    PRINT("find minest cost %d",aMiniCost[sEndIdx]);
    int sFrontIdx=sEndIdx;

    for(i=0;i<sVertexNum&&sFrontIdx!=INVALID_ARRAY_IDX;i++){
        printf("vertex %d->",sFrontIdx);
        sFrontIdx=aFront[sFrontIdx];
    }
    printf("\n");

}

void MatrixGraph::CalcShortestPathFolyd(){
    int *pTmp=nullptr;
    pTmp=new int[sVertexNum*sVertexNum];
    memcpy(pTmp,pWeight,sVertexNum*sVertexNum* sizeof(int));
    int i,j,k;
    for(i=sVertexNum-1;i>=0;i--){
        for(j=0;j<sVertexNum;j++){
            for(k=0;k<sVertexNum;k++){
                if(pTmp[j*sVertexNum+k]>pTmp[j*sVertexNum+i]+pTmp[i*sVertexNum+k]){
                    pTmp[j*sVertexNum+k]=pTmp[j*sVertexNum+i]+pTmp[i*sVertexNum+k];
                }
            }
        }
    }
    for(i=0;i<sVertexNum;i++){
        printf("array %d:",i);
        for(j=0;j<sVertexNum;j++){
            printf(" %4d\t",pTmp[i*sVertexNum+j]);
        }
        printf("\n");
    }


    delete [] pTmp;
}


int MatrixUndirGraph::InsertUndirEdge(const char *pVertexA,const char* pVertexB,int weight){
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

