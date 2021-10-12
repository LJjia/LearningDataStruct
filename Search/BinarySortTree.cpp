/**
 * @File: BinarySortTree
 * @Author: Jialiangjun
 * @Description:
 * @Date: Created on 15:42 2021-10-08.
 * @Modify:
 */
#include "BinarySortTree.h"
#include <iostream>
#include <cstdlib>
using namespace std;

/*!
 * 不考虑平衡树的插入方法
 */
int BinarySortTree::InsertData(int data) {
    BinaryTreeNode*pNew=nullptr;
    BinaryTreeNode**pOri=&pRoot;
    BinaryTreeNode*pParents= nullptr;
    // 插入根节点
    if(nullptr==pRoot){
        pNew=(BinaryTreeNode*)malloc(sizeof(BinaryTreeNode));
        memset(pNew,0,sizeof(BinaryTreeNode));
        pNew->data=data;
        pNew->pParents=nullptr;
        pRoot=pNew;
        sNodeNum++;
        return OK;
    }
    // 根据二叉排序顺序插入节点 对于同等大小的节点,默认插入在左边
    // 根据大小找到一个空的节点,然后新申请一个节点, 再插入
    pOri=&pRoot;
    while(*pOri!=nullptr){
        // 记录双亲节点,便于新申请节点记录
        pParents=pOri[0];
        if(data>pOri[0]->data){
            pOri=&(pOri[0]->pRight);
        } else{
            pOri=&(pOri[0]->pLeft);
        }
    }
    pNew=(BinaryTreeNode*)malloc(sizeof(BinaryTreeNode));
    memset(pNew,0,sizeof(BinaryTreeNode));
    pNew->data=data;
    // 新申请的节点记录双亲地址
    pNew->pParents=pParents;
    // 修改双亲节点的left right指针
    *pOri=pNew;
    // 双亲的平衡因子修改
    // 当新加入导致平衡因子为0 证明添加的节点不影响深度,因此不需要再向上修改
    while(pNew->pParents!= nullptr&&pNew->pParents->bf!=0){
        ChangeParentsBf(pNew);
        pNew=pNew->pParents;
    }

    sNodeNum++;
    return OK;
}

/*!
 * 平衡树插入方法
 * @param data
 * @return
 */
int BinarySortTree::AvlInsertData(int data) {
    BinaryTreeNode*pNew=nullptr;
    BinaryTreeNode**pOri=&pRoot;
    BinaryTreeNode*pParents= nullptr;
    BinaryTreeNode*pMinAvlRoot= nullptr; //最小平衡子树的根节点
    // 插入根节点
    if(nullptr==pRoot){
        pNew=(BinaryTreeNode*)malloc(sizeof(BinaryTreeNode));
        memset(pNew,0,sizeof(BinaryTreeNode));
        pNew->data=data;
        pNew->pParents=nullptr;
        pRoot=pNew;
        sNodeNum++;
        return OK;
    }
    // 根据二叉排序顺序插入节点 对于同等大小的节点,默认插入在左边
    // 根据大小找到一个空的节点,然后新申请一个节点, 再插入
    pOri=&pRoot;
    while(*pOri!=nullptr){
        // 记录双亲节点,便于新申请节点记录
        pParents=pOri[0];
        if(data>pOri[0]->data){
            pOri=&(pOri[0]->pRight);
        } else{
            pOri=&(pOri[0]->pLeft);
        }
    }
    pNew=(BinaryTreeNode*)malloc(sizeof(BinaryTreeNode));
    memset(pNew,0,sizeof(BinaryTreeNode));
    pNew->data=data;
    // 新申请的节点记录双亲地址
    pNew->pParents=pParents;
    // 修改双亲节点的left right指针
    *pOri=pNew;

    ChangeParentsBf(pNew);
    // 双亲的平衡因子修改
    // 当新加入导致平衡因子为0 证明添加的节点不影响深度,因此不需要再向上修改
    while(pNew->pParents!= nullptr&&abs(pNew->pParents->bf)==1){
        pNew=pNew->pParents;
        ChangeParentsBf(pNew);
    }
    if(pNew->pParents== nullptr || (pNew->pParents&&pNew->pParents->bf==0)){
        // 遍历到根节点 或者 遍历出现bf=0的情况 ,则证明当前的添加没有对子树深度造成影响,返回
        PRINT("data %d not effect tree balance",data);
        return OK;
    }

    // avl算法,需要旋转子树
    // 先找到最小子树
    pMinAvlRoot=pNew->pParents;
    PRINT("avl proc data %d bf %d",pMinAvlRoot->data,pMinAvlRoot->bf);
    AvlProcMinTree(pMinAvlRoot);
    return OK;
}

/*!
 * 当前节点左旋就是让当前节点跑到父节点的左下方(左孩子)
 * @param pNode
 * @return
 */
int BinarySortTree::RotateLeft(BinaryTreeNode *pNode) {
    BinaryTreeNode*pRight=nullptr;
    bool bRoot=false;
    if(!pNode||!pNode->pRight){
        PRINT_MODE(PT_RED,"nullptr ");
        return FAILED;
    }
    if(pRoot==pNode){
        bRoot=true;
    }
    pRight=pNode->pRight;

    ChangeParents(pNode,pRight);
    pRight->pParents=pNode->pParents;

    // 一定要赋值是因为如果节点为空,则旋转之后,对应节点也置为空
    pNode->pRight=pRight->pLeft;
    if(pRight->pLeft){
        pNode->pRight->pParents=pNode->pRight;
    }

    pRight->pLeft=pNode;
    pNode->pParents=pRight;

    // 检查是否替换了根节点
    if(bRoot){
        pRoot=pRight;
    }
    return OK;

}

/*!
 * 当前节点左旋就是让当前节点成为左孩子节点的右孩子
 * @param pNode
 * @return
 */
int BinarySortTree::RotateRight(BinaryTreeNode *pNode) {
    BinaryTreeNode*pLeft=nullptr;
    bool bRoot=false;
    if(!pNode||!pNode->pLeft){
        PRINT_MODE(PT_RED,"nullptr ");
        return FAILED;
    }
    if(pRoot==pNode){
        bRoot=true;
    }
    pLeft=pNode->pLeft;

    ChangeParents(pNode,pLeft);
    pLeft->pParents=pNode->pParents;

    // 一定要赋值是因为如果节点为空,则旋转之后,对应节点也置为空
    pNode->pLeft=pLeft->pRight;
    if(pLeft->pRight){
        pNode->pRight->pParents=pNode->pRight;
    }

    pLeft->pRight=pNode;
    pNode->pParents=pLeft;

    // 检查是否替换了根节点
    if(bRoot){
        pRoot=pLeft;
    }
    return OK;

}

/*!
 * 处理avl最小生成树
 * @param pRoot
 */
void BinarySortTree::AvlProcMinTree(BinaryTreeNode*pNode){
    if(!pNode){
        PRINT_MODE(PT_RED,"error nullptr ");
        return ;
    }
    BinaryTreeNode**ppNodePos= nullptr;
    // 记录父节点指向该指针的地址,方便后续修改bf值
    if(pNode->pParents){
        ppNodePos=pNode->pParents->pLeft==pNode?&pNode->pParents->pLeft:&pNode->pParents->pRight;
    }

    switch (pNode->bf){
        case LeftUnBalance:
            if(!pNode->pRight){
                // 值为1 的节点 没有右节点的情况 根节点右旋
                RotateRight(pNode);
                pNode=ppNodePos?*ppNodePos:pRoot;
                pNode->bf=0;
                pNode->pLeft->bf=0;
                pNode->pRight->bf=0;
            } else if(pNode->pLeft->bf==LeftHeavy){
                // /型
                RotateRight(pNode);
                pNode=ppNodePos?*ppNodePos:pRoot;
                pNode->bf=0;
                pNode->pLeft->bf=1;
                pNode->pRight->bf=0;
            }else if(pNode->pLeft->bf==RightHeavy&&pNode->pLeft->pRight->bf==RightHeavy){
                // <型
                RotateLeft(pNode->pLeft);
                RotateRight(pNode);
                pNode=ppNodePos?*ppNodePos:pRoot;
                pNode->bf=0;
                pNode->pLeft->bf=1;
                pNode->pRight->bf=0;
            } else if(pNode->pLeft->bf==RightHeavy&&pNode->pLeft->pRight->bf==LeftHeavy){
                // 闪电1型
                RotateLeft(pNode->pLeft);
                RotateRight(pNode);
                pNode=ppNodePos?*ppNodePos:pRoot;
                pNode->bf=0;
                pNode->pLeft->bf=0;
                pNode->pRight->bf=-1;
            }
            else if(pNode->pLeft->bf==RightHeavy&&pNode->pLeft->pRight->bf==Balance){
                // 闪电2型
                RotateLeft(pNode->pLeft);
                RotateRight(pNode);
                pNode=ppNodePos?*ppNodePos:pRoot;
                pNode->bf=0;
                pNode->pLeft->bf=0;
                pNode->pRight->bf=0;
            }
            else{
                PRINT_MODE(PT_RED,"RightUnBalance maybe some err happened");
            }
            break;
        case RightUnBalance:
            if(!pNode->pLeft){
                // 简单/
                RotateLeft(pNode);
                pNode=ppNodePos?*ppNodePos:pRoot;
                pNode->bf=0;
                pNode->pLeft->bf=0;
                pNode->pRight->bf=0;
            } else if(pNode->pRight->bf==RightHeavy){
                // /型
                RotateLeft(pNode);
                pNode=ppNodePos?*ppNodePos:pRoot;
                pNode->bf=0;
                pNode->pLeft->bf=0;
                pNode->pRight->bf=1;
            }else if(pNode->pRight->bf==LeftHeavy&&pNode->pRight->pLeft->bf==LeftHeavy){
                // >型
                RotateRight(pNode->pRight);
                RotateLeft(pNode);
                pNode=ppNodePos?*ppNodePos:pRoot;
                pNode->bf=0;
                pNode->pLeft->bf=0;
                pNode->pRight->bf=-1;
            } else if(pNode->pRight->bf==RightHeavy&&pNode->pRight->pLeft->bf==RightHeavy){
                // 闪电1型
                RotateRight(pNode->pRight);
                RotateLeft(pNode);
                pNode=ppNodePos?*ppNodePos:pRoot;
                pNode->bf=0;
                pNode->pLeft->bf=1;
                pNode->pRight->bf=0;
            }
            else if(pNode->pRight->bf==RightHeavy&&pNode->pRight->pLeft->bf==Balance){
                // 闪电2型
                RotateRight(pNode->pRight);
                RotateLeft(pNode);
                pNode=ppNodePos?*ppNodePos:pRoot;
                pNode->bf=0;
                pNode->pLeft->bf=0;
                pNode->pRight->bf=0;
            }
            else{
                PRINT_MODE(PT_RED,"RightUnBalance maybe some err happened");
            }
            break;
        default:
            PRINT_MODE(PT_RED,"maybe something error happend %d ",pNode->bf);
            return ;
    }
}


inline bool BinarySortTree::ChangeParents(BinaryTreeNode*pNode,BinaryTreeNode*pDst){
    if(!pNode||!pDst){
        return false;
    }
    if(pNode->pParents== nullptr){
        return false;
    }
    if(pNode->pParents->pRight==pNode){
        pNode->pParents->pRight=pDst;
        return true;
    } else if(pNode->pParents->pLeft==pNode){
        pNode->pParents->pLeft=pDst;
        return true;
    } else{
        return false;
    }
}


/*!
 * 改变双亲的平衡因子
 * @param pNode
 * @return
 */
inline bool BinarySortTree::ChangeParentsBf(BinaryTreeNode*pNode){
    if(!pNode){
        return false;
    }
    if(pNode->pParents== nullptr){
        return false;
    }
    if(pNode->pParents->pRight==pNode){
        pNode->pParents->bf--;
        return true;
    } else if(pNode->pParents->pLeft==pNode){
        pNode->pParents->bf++;
        return true;
    } else{
        return false;
    }
}


#if 0
/*!
 * 删除一个节点 通过将节点从网中断开删除节点
 * @param data 节点数据,以找到的第一个为准
 */
void BinarySortTree::DeleteData(int data) {
    BinaryTreeNode*pOri= nullptr;
    BinaryTreeNode*pFree= nullptr;
    if(SearchData(data,&pOri)){
        pFree=pOri;
        // 找到数据
        if(pFree->pRight== nullptr&&pFree->pParents!=nullptr){
            // 1.这个节点没有右子树,
            // 处理删除节点的父和子
            ChangeParents(pFree,pFree->pLeft);
            if(pFree->pLeft){
                pFree->pLeft->pParents=pFree->pParents;
            }
        }else if(pFree->pLeft== nullptr&&pFree->pParents!=nullptr){
            // 2.这个节点没有左子树
            // 处理删除节点的父和子
            ChangeParents(pFree,pFree->pRight);
            if(pFree->pRight){
                pFree->pRight->pParents=pFree->pParents;
            }
        }
        else if(pFree->pParents==nullptr){
            // 删除的是根节点
            // 从左子树找一个最大的移过来
            if(pFree->pLeft== nullptr){
                pRoot=pRoot->pRight;
                if(pRoot){
                    // 避免此时pRoot为空 即已经没有节点了 导致的崩溃
                    pRoot->pParents= nullptr;
                }

            } else{
                //在左子树找一个最大的替换节点,叫做pOri
                pOri=pOri->pLeft;
                while(pOri->pRight!=0){
                    pOri=pOri->pRight;
                }
                // 由于根节点没有父母,因此不需要修改根节点的父母
                //ChangeParents(pFree,pOri);
                // 同时修改替换节点父母的指向
                ChangeParents(pOri,pOri->pLeft);
                if(pOri->pLeft){
                    // 替换节点的孩子节点的父母修改
                    pOri->pLeft->pParents=pOri->pParents;
                }
                pOri->pLeft=pFree->pLeft;
                pOri->pRight=pFree->pRight;
                pOri->pParents=pFree->pParents;
                pRoot=pOri;
                // 删除节点的孩子节点父母修改
                if(pFree->pLeft){
                    pFree->pLeft->pParents=pOri;
                }
                if(pFree->pRight){
                    pFree->pRight->pParents=pOri;
                }
            }

        }else{
            // 在左子树找一个最大的替换节点,叫做pOri
            // 已经处理过没有左右孩子节点的情况
            pOri=pOri->pLeft;
            while(pOri->pRight!=0){
                pOri=pOri->pRight;
            }
            // 将删除节点的父母的孩子指向替换节点
            ChangeParents(pFree,pOri);
            // 同时修改替换节点父母的指向
            ChangeParents(pOri,pOri->pLeft);
            if(pOri->pLeft){
                pOri->pLeft->pParents=pOri->pParents;
            }
            pOri->pLeft=pFree->pLeft;
            pOri->pRight=pFree->pRight;
            pOri->pParents=pFree->pParents;
            // 删除节点的孩子节点父母修改
            if(pFree->pLeft){
                pFree->pLeft->pParents=pOri;
            }
            if(pFree->pRight){
                pFree->pRight->pParents=pOri;
            }
        }
        free(pFree);
        sNodeNum--;
    } else{
        PRINT_MODE(PT_RED,"not find data %d",data);
    }
}
#else

/*!
 * 删除一个节点 通过拷贝数据替换节点,而不是将两个节点从网中断开替换节点
 * @param data 节点数据,以找到的第一个为准
 */
void BinarySortTree::DeleteData(int data) {
    BinaryTreeNode*pOri= nullptr;
    BinaryTreeNode*pFree= nullptr;
    if(SearchData(data,&pOri)){
        pFree=pOri;
        // 找到数据
        if(pFree->pRight== nullptr&&pFree->pParents!=nullptr){
            // 1.这个节点没有右子树,
            // 处理删除节点的父和子
            ChangeParents(pFree,pFree->pLeft);
            if(pFree->pLeft){
                pFree->pLeft->pParents=pFree->pParents;
            }
        }else if(pFree->pLeft== nullptr&&pFree->pParents!=nullptr){
            // 2.这个节点没有左子树
            // 处理删除节点的父和子
            ChangeParents(pFree,pFree->pRight);
            if(pFree->pRight){
                pFree->pRight->pParents=pFree->pParents;
            }
        }
        else if(pFree->pParents==nullptr){
            // 删除的是根节点
            // 从左子树找一个最大的移过来
            if(pFree->pLeft== nullptr){
                pRoot=pRoot->pRight;
                if(pRoot){
                    // 避免此时pRoot为空 即已经没有节点了 导致的崩溃
                    pRoot->pParents= nullptr;
                }

            } else{
                //在左子树找一个最大的替换节点,叫做pFree,释放pFree,保留pOri
                pFree=pFree->pLeft;
                while(pFree->pRight!=0){
                    pFree=pFree->pRight;
                }
                // 同时修改替换节点父母的指向,相当于将替换节点短路
                ChangeParents(pFree,pFree->pLeft);
                if(pFree->pLeft){
                    // 替换节点的孩子节点的父母修改
                    pFree->pLeft->pParents=pFree->pParents;
                }
                // 很关键,将值替换,节点网状结构不断开,因此只需将pFree节点短路即可
                pOri->data=pFree->data;
                pRoot=pOri;

            }

        }else{
            // 在左子树找一个最大的替换节点,叫做pOri
            // 已经处理过没有左右孩子节点的情况
            pFree=pFree->pLeft;
            while(pFree->pRight!=0){
                pFree=pFree->pRight;
            }
            // 同时修改替换节点父母的指向,相当于将替换节点短路
            ChangeParents(pFree,pFree->pLeft);
            if(pFree->pLeft){
                // 替换节点的孩子节点的父母修改
                pFree->pLeft->pParents=pFree->pParents;
            }
            // 很关键,将值替换,节点网状结构不断开,因此只需将pFree节点短路即可
            pOri->data=pFree->data;

        }
        free(pFree);
        sNodeNum--;
    } else{
        PRINT_MODE(PT_RED,"not find data %d",data);
    }
}

#endif

void BinarySortTree::PtNodeData(BinaryTreeNode *pNode) {
    // 中序遍历刚好是按顺序排序
    if(pNode!=nullptr){
        PtNodeData(pNode->pLeft);
        PRINT("access data %d bf %d",pNode->data,pNode->bf);
        PtNodeData(pNode->pRight);
    }
}

void BinarySortTree::PtContent() {
    PRINT_MODE(PT_BLUE,"pt binary tree node data nodenum %d root data %d",sNodeNum,pRoot->data);
    PtNodeData(pRoot);
}

/*!
 * 使用循环方式查找节点
 * @param data
 * @return
 */
bool BinarySortTree::SearchData(int data) {
    BinaryTreeNode*pOri= nullptr;
    pOri=pRoot;
    while (pOri){
        if(data>pOri->data){
            pOri=pOri->pRight;
        } else if(data<pOri->data){
            pOri=pOri->pLeft;
        } else{
            // 找到相等的数据
            PRINT("loop find node data %d",data);
            return true;
        }
    }
    // 因为直到按照规律找到空指针,都没有找到相等数据,因为认为 未找到数据
    PRINT("loop not find data %d",data);
    return false;
}

/*!
 * 循环方式搜索数据,并返回节点地址,拓展使用,感觉返回值写的不合理
 * @param data
 * @param pRet
 * @return true表示找到
 */
bool BinarySortTree::SearchData(int data,BinaryTreeNode**pRet) {
    BinaryTreeNode*pOri= nullptr;
    pOri=pRoot;
    while (pOri){
        if(data>pOri->data){
            pOri=pOri->pRight;
        } else if(data<pOri->data){
            pOri=pOri->pLeft;
        } else{
            *pRet=pOri;
            return true;
        }
    }
    return false;
}

/*!
 * 递归遍历节点是否存在
 * @param data  节点数据
 * @param pNode 从哪个顶点节点开始寻找
 * @param pOut  输出记录退出前最后一个访问节点的指针,及找到的数据指针的双亲节点
 * @return 存在返回true
 */
bool BinarySortTree::SearchDataRecursiveIn(int data, BinaryTreeNode *pNode,BinaryTreeNode**pOut) {
    if(!pNode){
        // 由于二叉排序树寻找方法一定是每步都有正确,找到当前元素一定是固定的路径,不存在试错路径
        // 所以一旦访问到空节点,则认为肯定是没有找到对应元素
        // 遇到不存在的节点才会返回false
        return false;
    }
    if(pNode->data==data){
//        PRINT("recursive find node data %d",data);
        // 遇到相同的节点才会返回true,仅两个返回点
        return true;
    }else if (data>pNode->data){
        // 仅有这两个地方可以记录双亲节点,因为只有这两处会访问子节点
        *pOut=pNode;
        return SearchDataRecursiveIn(data,pNode->pRight,pOut);
    }else if(data<pNode->data) {
        *pOut=pNode;
        return SearchDataRecursiveIn(data,pNode->pLeft,pOut);
    }
    // 不会再这下面返回
    return false;

}

bool BinarySortTree::SearchDataRecursive(int data) {
    BinaryTreeNode*pLast= nullptr;
    bool bOK;
    bOK=SearchDataRecursiveIn(data,pRoot, &pLast);
    PRINT("search data %d bFind %d pLast->data %d",data,bOK,pLast->data);
    return bOK;
}

void TestBinarySortTree(){
    BinarySortTree*pSearch=new BinarySortTree();
    int datalist[10]={62,58,88,47,73,99,35,51,93,37};
    for(int i=0;i<10 ;i++){
        pSearch->InsertData(datalist[i]);
    }
    pSearch->PtContent();
    pSearch->SearchData(51);
    pSearch->SearchData(52);
    pSearch->SearchDataRecursive(51);
    pSearch->SearchDataRecursive(52);
    PRINT("after delete ");
    pSearch->DeleteData(62);
    pSearch->DeleteData(47);
    pSearch->DeleteData(88);
    pSearch->DeleteData(51);
    pSearch->PtContent();

}



void TestAvlTree(){
    BinarySortTree*pSearch=new BinarySortTree();
//    int datalist[10]={62,58,88,47,73,99,35,51,93,37};
    int datalist[10]={3,2,1,4,5,6,7,10,9,8};
    for(int i=0;i<10 ;i++){
        pSearch->AvlInsertData(datalist[i]);
    }
    pSearch->PtContent();


}

