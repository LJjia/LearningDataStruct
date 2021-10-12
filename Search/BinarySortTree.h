/**
 * @File: BinarySortTree
 * @Author: Jialiangjun
 * @Description:二叉排序树
 * @Date: Created on 15:42 2021-10-08.
 * @Modify:
 */
#ifndef SEARCH_BINARYSORTTREE_H
#define SEARCH_BINARYSORTTREE_H

#include "comm.h"

struct BinaryTreeNode{
    int data;
    int bf; //平衡因子,为左子树的高度-右子树高度
    BinaryTreeNode*pLeft;
    BinaryTreeNode*pRight;
    BinaryTreeNode*pParents; // 双亲节点
};

class BinarySortTree {
public:
    BinarySortTree(){
        sNodeNum=0;
        pRoot= nullptr;
    }
//    ~BinarySortTree();
    int InsertData(int data);
    int AvlInsertData(int data);
    void DeleteData(int data);
    bool SearchData(int data);
    bool SearchData(int data,BinaryTreeNode**pRet);
    bool SearchDataRecursive(int data);
    void PtContent();
    enum BalanceFactor{
        Balance=0,
        LeftHeavy=1,
        RightHeavy=-1,
        LeftUnBalance=2,
        RightUnBalance=-2
    };
protected:
    void AvlProcMinTree(BinaryTreeNode*pNode );
    bool SearchDataRecursiveIn(int data,BinaryTreeNode*pNode,BinaryTreeNode**pOut);
    void PtNodeData(BinaryTreeNode*pNode);
    bool ChangeParents(BinaryTreeNode*pNode,BinaryTreeNode*pDst);
    bool ChangeParentsBf(BinaryTreeNode*pNode);
    int RotateLeft(BinaryTreeNode*pNode);
    int RotateRight(BinaryTreeNode*pNode);
    int sNodeNum;
    BinaryTreeNode*pRoot;
};


#endif //SEARCH_BINARYSORTTREE_H
