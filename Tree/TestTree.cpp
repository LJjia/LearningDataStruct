/**
 * @Author: Jialiangjun
 * @Description: 测试自己写的树结构
 * @Date: Created on 19:53 2021-08-25.
 * @Modify:
 */
#include "MyTree.h"


void TestChildTree(){
    auto pMyTree=new MyTree();
    ElemType stEle{};
    stEle.data=0;
    pMyTree->InsertTreeNode(nullptr,(char*)"root",&stEle);
    stEle.data=1;
    pMyTree->InsertTreeNode((char*)"root",(char*)"B",&stEle);
    stEle.data=2;
    pMyTree->InsertTreeNode((char*)"root",(char*)"C",&stEle);
    stEle.data=3;
    pMyTree->InsertTreeNode((char*)"B",(char*)"D",&stEle);
    stEle.data=4;
    pMyTree->InsertTreeNode((char*)"C",(char*)"E",&stEle);
    stEle.data=5;
    pMyTree->InsertTreeNode((char*)"C",(char*)"F",&stEle);
    stEle.data=6;
    pMyTree->InsertTreeNode((char*)"D",(char*)"G",&stEle);
    stEle.data=7;
    pMyTree->InsertTreeNode((char*)"D",(char*)"H",&stEle);
    stEle.data=8;
    pMyTree->InsertTreeNode((char*)"D",(char*)"I",&stEle);
    stEle.data=9;
    pMyTree->InsertTreeNode((char*)"E",(char*)"J",&stEle);

    pMyTree->PtTreeStruct();
    delete(pMyTree);
}

/*!
 * 测试二叉链表树
 */
void TestBinaryLinkTree(){
    auto pBinTree=new BinaryTree;
    ElemType stEle{};
    stEle.data=0;
    pBinTree->InsertTreeNode(nullptr,"root",&stEle,INSERT_ROOT);
    stEle.data=1;
    pBinTree->InsertTreeNode("root","B",&stEle,INSERT_LEFT);
    stEle.data=2;
    pBinTree->InsertTreeNode("root","C",&stEle,INSERT_RIGHT);
    stEle.data=3;
    pBinTree->InsertTreeNode("B","D",&stEle,INSERT_LEFT);
    stEle.data=4;
    pBinTree->InsertTreeNode("C","E",&stEle,INSERT_LEFT);
    stEle.data=5;
    pBinTree->InsertTreeNode("C","F",&stEle,INSERT_RIGHT);
    stEle.data=6;
    pBinTree->InsertTreeNode("D","G",&stEle,INSERT_LEFT);
    stEle.data=7;
    pBinTree->InsertTreeNode("D","H",&stEle,INSERT_RIGHT);
    stEle.data=8;
    pBinTree->InsertTreeNode("E","I",&stEle,INSERT_RIGHT);

//    pBinTree->DeleteTreeNode("root");
    PRINT("---------------------------");
    pBinTree->TraverseTree(PREORDER_TRAVERSE);
    pBinTree->TraverseTree(POSTORDER_TRAVERSE);
    pBinTree->TraverseTree(MIDDLEORDER_TRAVERSE);
    delete pBinTree;
}

void TestBinaryLinkTreeStrStruct(){
    auto pBinTree=new BinaryTree("ABDH##I##EJ###CF##G##");

//    pBinTree->DeleteTreeNode("root");

//    pBinTree->TraverseTree(PREORDER_TRAVERSE);
//    pBinTree->TraverseTree(POSTORDER_TRAVERSE);
//    pBinTree->TraverseTree(MIDDLEORDER_TRAVERSE);
    pBinTree->InitThread(MIDDLEORDER_TRAVERSE);
    PRINT("---------------------------");
    pBinTree->TraverseTree(MIDDLEORDER_TRAVERSE);
    PRINT("---------------------------");
//    pBinTree->ThreadPreTra verseTree();
    pBinTree->ThreadMiddleTraverseTree();
    delete pBinTree;
}