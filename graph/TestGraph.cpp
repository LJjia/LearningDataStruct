/**
 * @Author: Jialiangjun
 * @Description:测试文件
 * @Date: Created on 10:12 2021-09-05.
 * @Modify:
 */
#include "graph_store.h"
#include "MatrixGraph.h"

/*!
 * 打印顶点名字
 * @param pVertex
 */
void PtMatrixVetex(GraphVertex*pVertex){
    PRINT("Matrix access Vertex name %s",pVertex->name);
}

void PtSimpleAdjaencyVetex(AdjVertex*pVertex){
    PRINT("Adjaency Vertex name %s",pVertex->name);
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
    pGraph->InserEdge("A","B");
    pGraph->InserEdge("A","F");
    pGraph->InserEdge("B","C");
    pGraph->InserEdge("B","I");
    pGraph->InserEdge("B","G");
    pGraph->InserEdge("C","I");
    pGraph->InserEdge("C","D");
    pGraph->InserEdge("D","I");
    pGraph->InserEdge("D","G");
    pGraph->InserEdge("D","H");
    pGraph->InserEdge("D","E");
    pGraph->InserEdge("E","H");
    pGraph->InserEdge("E","F");
    pGraph->InserEdge("F","G");
    pGraph->InserEdge("F","A");
    pGraph->InserEdge("G","H");
    pGraph->DfsTraverse(PtMatrixVetex);
    delete pGraph;

}


void TestInitUndirMatrixGraph(){
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
    auto pGraph=new MatrixUndirGraph(aVertex,9);
    PRINT("Init Undir Matrix Graph ");
    pGraph->InserUndirtEdge("A","B");
    pGraph->InserUndirtEdge("A","F");
    pGraph->InserUndirtEdge("B","C");
    pGraph->InserUndirtEdge("B","I");
    pGraph->InserUndirtEdge("B","G");
    pGraph->InserUndirtEdge("C","I");
    pGraph->InserUndirtEdge("C","D");
    pGraph->InserUndirtEdge("D","I");
    pGraph->InserUndirtEdge("D","G");
    pGraph->InserUndirtEdge("D","H");
    pGraph->InserUndirtEdge("D","E");
    pGraph->InserUndirtEdge("E","H");
    pGraph->InserUndirtEdge("E","F");
    pGraph->InserUndirtEdge("F","G");
    pGraph->InserUndirtEdge("F","A");
    pGraph->InserUndirtEdge("G","H");
    pGraph->DfsTraverse(PtMatrixVetex);
    delete pGraph;

}

void TestAdjacencyUndirGraph(){
    auto pGraph=new SimpleUndirAdjacencyList();
    pGraph->InsertVertex("A",0);
    pGraph->InsertVertex("B",1);
    pGraph->InsertVertex("C",2);
    pGraph->InsertVertex("D",3);
    pGraph->InsertVertex("E",4);
    pGraph->InsertUndirEdge("A","B");
    pGraph->InsertUndirEdge("B","C");
//    pGraph->InsertUndirEdge("C","D");
    pGraph->InsertUndirEdge("D","A");
    pGraph->InsertUndirEdge("A","E");
    pGraph->DfsTraverse(PtSimpleAdjaencyVetex);
};

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