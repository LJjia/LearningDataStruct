#include <iostream>
#include <set>

void TestInitMatrixGraph();
void TestInitUndirMatrixGraph();
void TestOrthogonalDirGraph();
void TestAdjacencyUndirGraph();
void TestEdgeArray();
void TestCalcMiniSpanTree();
void TestCalcMinestPath();

using namespace std;
struct StSizeof{
    int a;
    int b;
    char sz[100];
};
int main() {
    std::cout << "Hello, World!" << std::endl;
//    TestInitMatrixGraph();
//    TestInitUndirMatrixGraph();
//    TestOrthogonalDirGraph();
//    TestAdjacencyUndirGraph();
//    TestEdgeArray();
//    TestCalcMiniSpanTree();
    TestCalcMinestPath();

    return 0;
}