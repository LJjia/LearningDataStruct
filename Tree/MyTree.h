/**
 * @Author: Jialiangjun
 * @Description:
 * @Date: Created on 17:00 2021-08-25.
 * @Modify:
 */
#ifndef TREE_MYTREE_H
#define TREE_MYTREE_H

#include "comm.h"
#include "data_type.h"
#include <string>

#define MAX_ID_LEN 20
struct  TreeChildNode{
    int sPos;    //存放该节点在数组中的哪个位置,相当于指针
    TreeChildNode* pNext;   //存放该节点的右兄弟的结构体的指针,如果没有,置为0
};
struct TreeNode{
    char szId[MAX_ID_LEN]; //以id来单独命名一个独立的节点 如未占用,则会将string清空
    ElemType stData;
    int sParentsIdx;
    bool bUsed;     //该节点是否被占用
    TreeChildNode *pChildList; //孩子链表指针
};



#define MAX_TREE_NODE_NUM 20
#define INVALID_IDX (-1)
class MyTree {
public:
    MyTree();
    ~MyTree();
    int GetExistNodeNum();
    int InsertTreeNode(char *pParentName,char*pNodeName,ElemType*pEle);
    int DeleteTreeNode(char *pName);
    int GetNodeValueByName(char *pName,ElemType*pEle);
    void PtTreeStruct();

private:
    int sNodeNum;
    int sRootIdx;
    TreeNode stTreeArray[MAX_TREE_NODE_NUM]; // 存放所有节点数组指针
    int FindNodeByName(char *pName);
    int FindIdleTreeNode();
    void DeleteTreeNodeByIdx(int sDelIdx);

};


enum BinaryInsertDir{
    INSERT_ROOT,
    INSERT_LEFT,
    INSERT_RIGHT,

};
enum TraverseTreeOrder{
    PREORDER_TRAVERSE,
    POSTORDER_TRAVERSE,
    MIDDLEORDER_TRAVERSE,
    LAYERORDER_TRAVERSE,
};

enum TreePointType{
    TREE_POINT_NODE,        // 指向下一个节点
    TREE_POINT_THREAD,      // 指向下一个线索,循环调用时使用
};

struct BinaryTreeNode{
    ElemType stData;
    char szId[MAX_ID_LEN]; //以id来单独命名一个独立的节点 如未占用,则会将string清空
    TreePointType enLeft;
    TreePointType enRight;
    BinaryTreeNode*pLeft;
    BinaryTreeNode*pRight;
    BinaryTreeNode*pParents;
};

class BinaryTree{
public:
    BinaryTree();
    BinaryTree(char *pStru);
    ~BinaryTree();
    int InsertTreeNode(char *pParentName,char*pNodeName,ElemType*pEle,BinaryInsertDir direct);
    void DeleteTreeNode(char *pName);
    void TraverseTree(TraverseTreeOrder order);
    int InitThread(TraverseTreeOrder order);
    void ThreadPreTraverseTree();
    void ThreadMiddleTraverseTree();


private:
//    int sDepth;
    typedef void (*ProcNodeFunc)(BinaryTreeNode*);

    int sNodeCnt;
    BinaryTreeNode*pRoot;
    BinaryTreeNode* FindNodeByName(char *pName);
    BinaryTreeNode* PreOrderTraverse(BinaryTreeNode*pNode,char *pName);
    void InitTreeByStruct(char **ppChar,BinaryTreeNode**ppNode);
    void RecurFreeNode(BinaryTreeNode*pNode);

    void PreOrderPtTree(BinaryTreeNode*pNode,ProcNodeFunc pFunc);
    void PostOrderPtTree(BinaryTreeNode*pNode,ProcNodeFunc pFunc);
    void MiddleOrderPtTree(BinaryTreeNode*pNode,ProcNodeFunc pFunc);
    int sGenerNodeCnt; //类似sql自增主键一样,插入后自动++.用于字符串类型数据填充
};


#endif //TREE_MYTREE_H
