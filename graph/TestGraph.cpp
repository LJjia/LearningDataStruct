/**
 * @Author: Jialiangjun
 * @Description:测试文件
 * @Date: Created on 10:12 2021-09-05.
 * @Modify:
 */
#include "graph_store.h"

/*!
 * 打印顶点名字
 * @param pVertex
 */
void PtMatrixVetex(GraphVertex*pVertex){
    PRINT("Matrix access Vertex name %s",pVertex->name);
}


void TestInitMatrixGraph(){
    GraphVertex aVertex[9] {
        {"A",0},
        {"B",1},
        {"C",2},
        {"D",3},
        {"E",4},
        {"F",5},
        {"G",6},
        {"H",7},
        {"I",8},
    };
    GraphWeight aWeight[9][9]{};

    auto pGraph=new MatrixGraph(aVertex,&aWeight[0][0],9);
    PRINT("Init Matrix Graph ");
    pGraph->InsertEdge("A","B");
    pGraph->InsertEdge("A","F");
    pGraph->InsertEdge("B","C");
    pGraph->InsertEdge("B","I");
    pGraph->InsertEdge("B","G");
    pGraph->InsertEdge("C","I");
    pGraph->InsertEdge("C","D");
    pGraph->InsertEdge("D","I");
    pGraph->InsertEdge("D","G");
    pGraph->InsertEdge("D","H");
    pGraph->InsertEdge("D","E");
    pGraph->InsertEdge("E","H");
    pGraph->InsertEdge("E","F");
    pGraph->InsertEdge("F","G");
    pGraph->InsertEdge("F","A");
    pGraph->InsertEdge("G","H");
    pGraph->DfsTraverse(PtMatrixVetex);
    delete pGraph;

}

void TestOrthogonalDirGraph(){
    auto pGraph=new OrthogonalDirGraph();
    pGraph->InsertVertex("v0",0);
    pGraph->InsertVertex("v1",1);
    pGraph->InsertVertex("v2",2);
    pGraph->InsertVertex("v3",3);
    pGraph->InsertEdge("v0","v3",1);
    pGraph->InsertEdge("v1","v0",1);
    pGraph->InsertEdge("v1","v2",1);
    pGraph->InsertEdge("v2","v1",1);
    pGraph->InsertEdge("v2","v0",1);
    pGraph->PtStruct();
    pGraph->InsertVertex("v4",4);
    pGraph->InsertEdge("v3","v4",1);
    pGraph->InsertEdge("v4","v3",1);
    pGraph->InsertEdge("v0","v4",1);
    pGraph->DeleteEdge("v0","v4");
    pGraph->DeleteVertex("v4");
    pGraph->PtStruct();
    delete pGraph;
}