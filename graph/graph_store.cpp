/**
 * @Author: Jialiangjun
 * @Description:
 * @Date: Created on 09:32 2021-09-05.
 * @Modify:
 */
#include "graph_store.h"
#include <cstring>
#include <iostream>
#include <queue>
#include <stack>
#include <array>

using namespace std;


SimpleAdjacencyList::SimpleAdjacencyList(){
    sVertexNum=0;
    memset(stVertexArray,0,sizeof(stVertexArray));
}
SimpleAdjacencyList::~SimpleAdjacencyList(){

}
int SimpleAdjacencyList::InsertVertex(const char *pName,int data){
    int sIdleIdx=0;
    // 检查名称是否存在,存在不插入这个节点
    sIdleIdx=FindVetexIdxByName(pName);
    CHECK_PARAM(sIdleIdx<MAX_VERTEX_NUM,FAILED);
    sIdleIdx=FindNextUnusedVertex();
    CHECK_PARAM(sIdleIdx>=INVALID_ARRAY_IDX,FAILED);
    stVertexArray[sIdleIdx].bUsed=true;
    stVertexArray[sIdleIdx].data=data;
    strncpy(stVertexArray[sIdleIdx].name,pName,MAX_NAME_LEN);
    stVertexArray[sIdleIdx].pFirst= nullptr;
    sVertexNum++;
    return OK;
}

/*!
 * 有向图插入边方向 A->B
 * @param pNameA
 * @param pNameB
 * @return
 */
int SimpleAdjacencyList::InsertEdge(const char *pNameA,const char *pNameB,int weight){
    int sAIdx=0;
    int sBIdx=0;
    AdjSide*pAdjSideA=nullptr;
    sAIdx=FindVetexIdxByName(pNameA);
    sBIdx=FindVetexIdxByName(pNameB);
    CHECK_PARAM(sAIdx>=MAX_VERTEX_NUM||sBIdx>=MAX_VERTEX_NUM,FAILED);
    pAdjSideA=(AdjSide*)malloc(sizeof(AdjSide));
    CHECK_PARAM(!pAdjSideA,FAILED);
    pAdjSideA->adjvex=sBIdx;
    pAdjSideA->pNext=stVertexArray[sAIdx].pFirst;
    stVertexArray[sAIdx].pFirst=pAdjSideA;
    pAdjSideA->weight=weight;
    // B的入度++ ref值为真实值,拓扑排序时可能修改非ref值
    stVertexArray[sBIdx].sInDegreeRef++;
    stVertexArray[sBIdx].sInDegree=stVertexArray[sBIdx].sInDegreeRef;
    return OK;
}

/*!
 * 返回下一个空闲节点的索引idx,没有返回-1
 * @return
 */
int SimpleAdjacencyList::FindNextUnusedVertex(){
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
int SimpleAdjacencyList::FindVetexIdxByName(const char *pName){
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

void SimpleAdjacencyList::dfs(int idx,array<bool,MAX_VERTEX_NUM> &visited,pAdjacencyVertexFunc pFunc){
    AdjSide*pSide= nullptr;
    if(visited[idx]){
        return ;
    }
    pFunc(&stVertexArray[idx]);
    visited[idx]=true;
    pSide=stVertexArray[idx].pFirst;
//    PRINT("access node %s idx %d",stVertexArray[idx].name,idx)
    while (pSide!=0){
        if(visited[pSide->adjvex]== false){
//            PRINT("visited side %d",pSide->adjvex);
            dfs(pSide->adjvex,visited,pFunc);
        }
        pSide=pSide->pNext;
    }

}

void SimpleAdjacencyList::DfsTraverse(pAdjacencyVertexFunc pFunc){
    array<bool,MAX_VERTEX_NUM> visited{};
    PRINT_MODE(PT_BLUE,"SimpleAdjacencyList dfs vertex num %d",sVertexNum);
    for(int i=0;i<sVertexNum;i++){
        if(visited[i]== false){
            dfs(i,visited,pFunc);
        }

    }
}


void SimpleAdjacencyList::bfs(int idx,array<bool,MAX_VERTEX_NUM> &visited,pAdjacencyVertexFunc pFunc){
    AdjSide *pAdjVertex= nullptr;
    if(visited[idx]){
        return ;
    }
    queue <int> queue1;
    queue1.push(idx);
    while(!queue1.empty()){
        int sOutIdx=queue1.front();
        if(!visited[sOutIdx]){
            pFunc(&stVertexArray[sOutIdx]);
            visited[sOutIdx]=true;
            pAdjVertex=stVertexArray[sOutIdx].pFirst;
            while (pAdjVertex!=nullptr){
                if(!visited[pAdjVertex->adjvex]){
//                    PRINT("push node name %s",stVertexArray[pAdjVertex->adjvex].name);
                    queue1.push(pAdjVertex->adjvex);
                }
                pAdjVertex=pAdjVertex->pNext;
            }
        }
//        PRINT("pop node name %s",stVertexArray[sOutIdx].name);
        queue1.pop();
    }

}

void SimpleAdjacencyList::BfsTraverse(pAdjacencyVertexFunc pFunc){
    array<bool,MAX_VERTEX_NUM> visited{};
    PRINT_MODE(PT_BLUE,"SimpleAdjacencyList bfs vertex num %d",sVertexNum);
    for(int i=0;i<sVertexNum;i++){
        if(visited[i]== false){
            bfs(i,visited,pFunc);
        }

    }
}

/*!
 * 计算拓扑排序
 * @return
 */
int SimpleAdjacencyList::TopologicalSort(){
    int i=0;
    int sPopIdx=0;
    int sLoopCnt=0;
    std::stack<int > s;
    AdjSide*pSide=nullptr;
    PtStruct();
    // 需要了解的一点是,不存在删除边导致空位的情况
    for(i=0;i<sVertexNum;i++){
        if(stVertexArray[i].sInDegree==0){
            s.push(i);
        }
    }
    while(!s.empty()){

        sPopIdx=s.top();
        s.pop();
        printf("Vertex %s\tdata %d\n",stVertexArray[sPopIdx].name,stVertexArray[sPopIdx].data);
        pSide=stVertexArray[sPopIdx].pFirst;
        while(pSide){
            /*下面的代码块在有环时可以防止isIndeDegree产生-1这样的无意义值
            if(stVertexArray[pSide->adjvex].sInDegree==1){
                s.push(pSide->adjvex);
            }
            if(stVertexArray[pSide->adjvex].sInDegree>0){
                stVertexArray[pSide->adjvex].sInDegree--;
            }*/
            // 有环情况下可能产生-1这样的无效值
            stVertexArray[pSide->adjvex].sInDegree--;
            if(stVertexArray[pSide->adjvex].sInDegree==0){
                s.push(pSide->adjvex);
            }
            pSide=pSide->pNext;
        }
        sLoopCnt++;
    }
    TopologicalResetInDegree();

    if(sLoopCnt<sVertexNum){
        // 证明其中可能有环,对于所有能成环边上的顶点,将无法找到入度为0的顶点,因此环无法消除
        // 可能存在大量无法消除的顶点
        PRINT_ERR("maybe has circle sVertexNum %d loopcnts %d",sVertexNum,sLoopCnt);
        return FAILED;
    }else{
        PRINT_ERR("topologic end times %d",sLoopCnt)
        return OK;
    }

}

/*!
 * 复位入度值,求拓扑排序时会修改入度值
 * @return
 */
void SimpleAdjacencyList::TopologicalResetInDegree(){
    for(int i=0;i<sVertexNum;i++){
        if(stVertexArray[i].bUsed){
            stVertexArray[i].sInDegree=stVertexArray[i].sInDegreeRef;
        }
    }
}

/*!
 * 计算拓扑排序
 * @return
 */
int SimpleAdjacencyList::CalcKeyPath(){
    int i=0;
    int sPopIdx=0;
    int sLoopCnt=0;
    std::stack<int > s;
    std::stack<int > ToplogicStack; //存放拓扑排序序列
    AdjSide*pSide=nullptr;
    std::array <int ,MAX_VERTEX_NUM> aEarly{};
    std::array <int ,MAX_VERTEX_NUM> aLate{};

    // 计算拓扑排序 代码和拓扑排序代码基本类似,增加栈临时存放拓扑序列
    // 增加存放到达各个顶点最大损失的数组
    for(i=0;i<sVertexNum;i++){
        if(stVertexArray[i].sInDegree==0){
            s.push(i);
        }
    }

    while(!s.empty()){
        sPopIdx=s.top();
        s.pop();
        ToplogicStack.push(sPopIdx);
        printf("Vertex %s\tdata %d\n",stVertexArray[sPopIdx].name,stVertexArray[sPopIdx].data);
        pSide=stVertexArray[sPopIdx].pFirst;
        while(pSide){
            // 不管关联的节点入度是否为0,都需要进行损失更新
            if(aEarly[sPopIdx]+pSide->weight>aEarly[pSide->adjvex]){
                aEarly[pSide->adjvex]=aEarly[sPopIdx]+pSide->weight;
            }

            stVertexArray[pSide->adjvex].sInDegree--;
            if(stVertexArray[pSide->adjvex].sInDegree==0){
                s.push(pSide->adjvex);
            }
            pSide=pSide->pNext;
        }
        sLoopCnt++;
    }
    TopologicalResetInDegree();
    if(sLoopCnt<sVertexNum){
        // 证明其中可能有环,对于所有能成环边上的顶点,将无法找到入度为0的顶点,因此环无法消除
        // 可能存在大量无法消除的顶点
        PRINT_ERR("maybe has circle sVertexNum %d loopcnts %d",sVertexNum,sLoopCnt);
        return FAILED;
    }else{
        PRINT("topologic OK end times %d",sLoopCnt)
    }

    for(i=0;i<sVertexNum;i++){
        printf("early idx %d value %d\n",i,aEarly[i]);
    }

    // 计算最迟开工时间
    for(i=0;i<sVertexNum;i++){
        aLate[i]=aEarly[sVertexNum-1];
    }
    // 需要求n顶点到终点路径的最大值,即 终点工时-路径损失的最小值
    while(!ToplogicStack.empty()){
        sPopIdx=ToplogicStack.top();
        ToplogicStack.pop();
        pSide=stVertexArray[sPopIdx].pFirst;
        while(pSide){
            // 不管关联的节点入度是否为0,都需要进行损失更新
            // 求n节点到终点的最大值,即 终点工时-路径损失的最小值
            // 如果当前节点的后继节点late值-边权值,小于本节点late值,则更新本节点late值更小
            if(aLate[pSide->adjvex]-pSide->weight<aLate[sPopIdx]){
                //如果后继节点的损失-路径损失<当前节点损失
                aLate[sPopIdx]=aLate[pSide->adjvex]-pSide->weight;
            }
            pSide=pSide->pNext;
        }
    }
    for(i=0;i<sVertexNum;i++){
        printf("late idx %d value %d\n",i,aLate[i]);
    }

    for(i=0;i<sVertexNum;i++){
        pSide=stVertexArray[i].pFirst;
        while(pSide){
            // 仅根据求解最早完成时间,然后计算哪个节点最后更新路径的更新
            if(aEarly[i]+pSide->weight==aLate[pSide->adjvex]){
                // 满足条件说明这条边卡的很紧凑,前后两个事件之间没有余量
                // 前节点到来后,要立刻做这条边的事情,才能按时完成后节点的工期要求(这样才能满足整个项目的工期要求)
                PRINT("path %s %s w %d keypath",
                      stVertexArray[i].name,stVertexArray[pSide->adjvex].name,pSide->weight);
            }
            /*大话数据结构书上 为什么要用这种很奇怪的写法?*/
            /*sEarlyTime=aEarly[i];
            sLateTime=aLate[pSide->adjvex]-pSide->weight;
            if(sEarlyTime==sLateTime){
                PRINT("path %s %s w %d keypath",
                        stVertexArray[i].name,stVertexArray[pSide->adjvex].name,pSide->weight);
            }*/
            pSide=pSide->pNext;
        }
    }


    return OK;
}


void SimpleAdjacencyList::PtStruct(){
    AdjSide*pSide= nullptr;
    int sValidCnt=0;
    PRINT("print Adjacency list struct vertex num %d",sVertexNum);
    for(int i=0;i<MAX_VERTEX_NUM;i++){
        if(stVertexArray[i].bUsed){
            pSide=stVertexArray[i].pFirst;
            printf("vertex idx %d\tname %s \tdata%d\t",i,stVertexArray[i].name,stVertexArray[i].data);
            while(pSide){
                printf("->idx %d\t",pSide->adjvex);
                pSide=pSide->pNext;
            }
            printf("\n");

            sValidCnt++;
            if(sValidCnt>=sVertexNum){
                break;
            }
        }
    }
}



SimpleUndirAdjacencyList::SimpleUndirAdjacencyList():SimpleAdjacencyList(){

}
SimpleUndirAdjacencyList::~SimpleUndirAdjacencyList(){

}

int SimpleUndirAdjacencyList::InsertUndirEdge(const char *pNameA, const char *pNameB) {
    int sAIdx=0;
    int sBIdx=0;
    AdjSide*pAdjSideA=nullptr;
    AdjSide*pAdjSideB=nullptr;
    sAIdx=FindVetexIdxByName(pNameA);
    sBIdx=FindVetexIdxByName(pNameB);
    CHECK_PARAM(sAIdx>=MAX_VERTEX_NUM||sBIdx>=MAX_VERTEX_NUM,FAILED);
    pAdjSideA=(AdjSide*)malloc(sizeof(AdjSide));
    pAdjSideB=(AdjSide*)malloc(sizeof(AdjSide));
    CHECK_PARAM(!pAdjSideA||!pAdjSideB,FAILED);
    pAdjSideA->adjvex=sBIdx;
    pAdjSideA->pNext=stVertexArray[sAIdx].pFirst;
    stVertexArray[sAIdx].pFirst=pAdjSideA;
    pAdjSideB->adjvex=sAIdx;
    pAdjSideB->pNext=stVertexArray[sBIdx].pFirst;
    stVertexArray[sBIdx].pFirst=pAdjSideB;
    return OK;
}






OrthogonalDirGraph::OrthogonalDirGraph(){
    memset(stVertexArray, 0,sizeof(stVertexArray));
    sVertexNum=0;
}
OrthogonalDirGraph::~OrthogonalDirGraph(){
    int sNodeCnt=0;
    OrthSideLink*pSide= nullptr;
    OrthSideLink*pFree= nullptr;
    PRINT_MODE(PT_BLUE,"free Orthogonal Direct Graph");
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