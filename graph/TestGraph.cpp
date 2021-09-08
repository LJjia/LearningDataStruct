/**
 * @Author: Jialiangjun
 * @Description:测试文件
 * @Date: Created on 10:12 2021-09-05.
 * @Modify:
 */
#include "graph_store.h"

void TestInitMatrixGraph(){
    GraphVertex aVertex[4] {
        {"v0",0},
        {"v1",1},
        {"v2",2},
        {"v3",3},
    };
    GraphWeight aWeight[4][4] {
            {0,1,1,1},
            {1,0,1,0},
            {1,1,0,1},
            {1,0,1,0}
    };
    PRINT("Init Matrix Graph ");
    auto pGraph=new MatrixGraph(aVertex,&aWeight[0][0],4);
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