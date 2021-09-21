/**
 * @Author: Jialiangjun
 * @Description:测试文件
 * @Date: Created on 10:12 2021-09-05.
 * @Modify:
 */
#include "graph_store.h"
#include "MatrixGraph.h"
#include "EdgeArray.h"

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

    auto pGraph=new MatrixGraph(aVertex,9);
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
    pGraph->BfsTraverse(PtMatrixVetex);
    delete pGraph;

}


void TestCalcMiniSpanTree(){
    GraphVertex aVertex[9] {
            {"v0",0},
            {"v1",1},
            {"v2",2},
            {"v3",3},
            {"v4",4},
            {"v5",5},
            {"v6",6},
            {"v7",7},
            {"v8",8},
    };
    GraphWeight aWeight[9][9]{};

    auto pGraph=new MatrixUndirGraph(aVertex,9);
    PRINT("Init Undir Matrix Graph ");

    // 一共15条边
    pGraph->InsertUndirEdge("v0","v1",10);
    pGraph->InsertUndirEdge("v0","v5",11);
    pGraph->InsertUndirEdge("v1","v2",18);
    pGraph->InsertUndirEdge("v1","v8",12);
    pGraph->InsertUndirEdge("v1","v6",16);
    pGraph->InsertUndirEdge("v2","v8",8);
    pGraph->InsertUndirEdge("v2","v3",22);
    pGraph->InsertUndirEdge("v3","v8",21);
    pGraph->InsertUndirEdge("v3","v6",24);
    pGraph->InsertUndirEdge("v3","v7",16);
    pGraph->InsertUndirEdge("v3","v4",20);
    pGraph->InsertUndirEdge("v4","v7",7);
    pGraph->InsertUndirEdge("v4","v5",26);
    pGraph->InsertUndirEdge("v5","v6",17);
    pGraph->InsertUndirEdge("v6","v7",19);
    pGraph->CalcMiniSpanTree();
    delete pGraph;
}

/*!
 * 测试最短路径
 */
void TestCalcMinestPath(){
    GraphVertex aVertex[9] {
            {"v0",0},
            {"v1",1},
            {"v2",2},
            {"v3",3},
            {"v4",4},
            {"v5",5},
            {"v6",6},
            {"v7",7},
            {"v8",8},
    };
    GraphWeight aWeight[9][9]{};

    auto pGraph=new MatrixUndirGraph(aVertex,9);
    PRINT("Init Undir Matrix Graph TestMinest Path");

    // 一共15条边
    pGraph->InsertUndirEdge("v0","v1",1);
    pGraph->InsertUndirEdge("v0","v2",5);
    pGraph->InsertUndirEdge("v1","v2",3);
    pGraph->InsertUndirEdge("v1","v4",5);
    pGraph->InsertUndirEdge("v1","v3",7);
    pGraph->InsertUndirEdge("v2","v4",1);
    pGraph->InsertUndirEdge("v2","v5",7);
    pGraph->InsertUndirEdge("v3","v4",2);
    pGraph->InsertUndirEdge("v3","v6",3);
    pGraph->InsertUndirEdge("v4","v6",6);
    pGraph->InsertUndirEdge("v4","v7",9);
    pGraph->InsertUndirEdge("v4","v5",3);
    pGraph->InsertUndirEdge("v5","v7",5);
    pGraph->InsertUndirEdge("v6","v7",2);
    pGraph->InsertUndirEdge("v6","v8",7);
    pGraph->InsertUndirEdge("v7","v8",4);
    pGraph->CalcShortestPathDijkstra("v0","v8");
    pGraph->CalcShortestPathFolyd();
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
    pGraph->InsertUndirEdge("A","B");
    pGraph->InsertUndirEdge("A","F");
    pGraph->InsertUndirEdge("B","C");
    pGraph->InsertUndirEdge("B","I");
    pGraph->InsertUndirEdge("B","G");
    pGraph->InsertUndirEdge("C","I");
    pGraph->InsertUndirEdge("C","D");
    pGraph->InsertUndirEdge("D","I");
    pGraph->InsertUndirEdge("D","G");
    pGraph->InsertUndirEdge("D","H");
    pGraph->InsertUndirEdge("D","E");
    pGraph->InsertUndirEdge("E","H");
    pGraph->InsertUndirEdge("E","F");
    pGraph->InsertUndirEdge("F","G");
    pGraph->InsertUndirEdge("F","A");
    pGraph->InsertUndirEdge("G","H");
    pGraph->DfsTraverse(PtMatrixVetex);
    pGraph->BfsTraverse(PtMatrixVetex);
    delete pGraph;

}



/*!
 * 测试邻接表
 */
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
    pGraph->BfsTraverse(PtSimpleAdjaencyVetex);
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


void TestEdgeArray(){
    using namespace EdgeArraySpace;
    auto pGraph= new EdgeArray();

    //一共9个顶点
    pGraph->InsertVertex("v0",0);
    pGraph->InsertVertex("v1",1);
    pGraph->InsertVertex("v2",2);
    pGraph->InsertVertex("v3",3);
    pGraph->InsertVertex("v4",4);
    pGraph->InsertVertex("v5",5);
    pGraph->InsertVertex("v6",6);
    pGraph->InsertVertex("v7",7);
    pGraph->InsertVertex("v8",8);

    // 一共15条边
    pGraph->InsertEdge("v0","v1",10);
    pGraph->InsertEdge("v0","v5",11);
    pGraph->InsertEdge("v1","v2",18);
    pGraph->InsertEdge("v1","v8",12);
    pGraph->InsertEdge("v1","v6",16);
    pGraph->InsertEdge("v2","v8",8);
    pGraph->InsertEdge("v2","v3",22);
    pGraph->InsertEdge("v3","v8",21);
    pGraph->InsertEdge("v3","v6",24);
    pGraph->InsertEdge("v3","v7",16);
    pGraph->InsertEdge("v3","v4",20);
    pGraph->InsertEdge("v4","v7",7);
    pGraph->InsertEdge("v4","v5",26);
    pGraph->InsertEdge("v5","v6",17);
    pGraph->InsertEdge("v6","v7",19);
//    pGraph->PtStruct();
    pGraph->EdgeSort();
    PRINT("after sort ");
    pGraph->PtStruct();
    pGraph->CalcMiniSpanTree();



}