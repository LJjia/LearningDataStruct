/**
 * @Author: Jialiangjun
 * @Description:
 * @Date: Created on 17:00 2021-08-25.
 * @Modify:
 */
#include "MyTree.h"
#include <iostream>
#include <string>
#include <string.h>



MyTree::MyTree() {
    std::cout<<"MyTree init "<<std::endl;
    this->sNodeNum=0;
    // 为初始化时,根节点idx=-1
    this->sRootIdx=-1;
    memset(this->stTreeArray,0, sizeof(stTreeArray));

}

MyTree::~MyTree() {
    std::cout<<"MyTree DeInit"<<std::endl;
    DeleteTreeNodeByIdx(0);
}

/*!
 * 获取节点中实际存在的节点个数
 * @return
 */
int MyTree::GetExistNodeNum(){
    return this->sNodeNum;
}

/*!
 * 通过名字返回节点指针,内部函数,需要遍历子树
 * @param pName
 * @return
 */
int MyTree::FindNodeByName(char *pName){
//    int index=0;
    CHECK_PARAM(!pName, INVALID_IDX);
    // 大规模的的树这种逐个遍历的效率感觉有点低,可能需要增加维护lastidx索引 表示现存的最大值idx
    // 可以选择遍历sNodeNum个行,非bUsed的行跳过,这样可以保证数据都被遍历到
    for (int i = 0; i <MAX_TREE_NODE_NUM ; ++i) {
        if(this->stTreeArray[i].bUsed && strncmp(this->stTreeArray[i].szId,pName,MAX_ID_LEN)==0){
            return i;
        }
    }
    return INVALID_IDX;
}

/*!
 * 发现一个空闲的索引位置,便于填充,找到的第一个idle的值,
 * 内部调用,确保函数不空的时候才可以调用
 * @return 空闲索引idx
 */
int MyTree::FindIdleTreeNode(){
    for (int i = 1; i < MAX_TREE_NODE_NUM; ++i) {
        if(!this->stTreeArray[i].bUsed){
            return i;
        }
    }
    return INVALID_IDX;

}

/*!
 * 通过名字获取节点存储的值
 * @param pName
 * @param pEle
 * @return
 */
int MyTree::GetNodeValueByName(char *pName,ElemType*pEle){
    int idx=0;
    CHECK_PARAM(!pName||!pEle,FAILED);
    idx=this->FindNodeByName(pName);
    CHECK_PARAM(idx==-1,FAILED);
    memcpy(pEle,&stTreeArray[idx].stData, sizeof(ElemType));
    return OK;
}


/*!
 * 将B节点插入到A节点之后,如果插入的是根节点,将pstNodeA置为空,其他情况下A需要是一个实际有效的节点
 * 现在只能做到一个节点一个节点插入,pstNodeB还不可以是一个子树
 * @param pstNodeA  父节点
 * @param pstNodeB  孩子节点
 * @return
 */
int MyTree::InsertTreeNode(char *pParentName,char*pNodeName,ElemType*pEle){
    int sPareIdx=INVALID_IDX;
    int sIdleIdx=INVALID_IDX;
    TreeChildNode* pstChild= nullptr;
    TreeChildNode* pNewNode= nullptr;
    CHECK_PARAM(!pNodeName||!pEle,FAILED);
    if(nullptr==pParentName){
        // insert root node
        // 根节点默认占用索引0,他的parents idx=-1
        if(this->sRootIdx!=-1){
            PRINT("has insert root node repeat");
            return FAILED;
        }
        strncpy(this->stTreeArray[0].szId,pNodeName, MAX_ID_LEN);
        this->stTreeArray[0].bUsed=true;
        this->stTreeArray[0].sParentsIdx=-1;
        this->sRootIdx=0;
        sNodeNum++;
        PRINT("insert root node ok");
        return OK;
    }else{
        sPareIdx=this->FindNodeByName(pParentName);
        CHECK_PARAM(sPareIdx==INVALID_IDX,FAILED);
        sIdleIdx=this->FindIdleTreeNode();
        CHECK_PARAM(sIdleIdx==INVALID_IDX,FAILED);
        pNewNode=(TreeChildNode*)malloc(sizeof(TreeChildNode));
        CHECK_PARAM(!pNewNode,FAILED);
        memset(pNewNode,0,sizeof(TreeChildNode));
        // 链表的pos存放即节点所占的idx 指针存放下一个ChildNode的地址
        // 修改链表
        pNewNode->sPos=sIdleIdx;
        if(0==this->stTreeArray[sPareIdx].pChildList){
            this->stTreeArray[sPareIdx].pChildList=pNewNode;
        }else{
            pstChild=this->stTreeArray[sPareIdx].pChildList;
            while(pstChild->pNext!=0){
                pstChild=pstChild->pNext;
            }
            pstChild->pNext=pNewNode;
        }
        // 修改索引中的值

        //TODO:这样不使用this指针是否可行?
        strncpy(this->stTreeArray[sIdleIdx].szId,pNodeName,MAX_ID_LEN);
        memcpy(&stTreeArray[sIdleIdx].stData,pEle,sizeof(ElemType));
        stTreeArray[sIdleIdx].bUsed=true;
        stTreeArray[sIdleIdx].sParentsIdx=sPareIdx;
        sNodeNum++;

    }
    return OK;
}

/*!
 * 依据索引删除idx位置的节点及其子树,用到递归
 * @param sDelIdx
 */
void MyTree::DeleteTreeNodeByIdx(int sDelIdx){
    TreeChildNode *pTreeChildNode= nullptr;
    TreeChildNode **pLastNode= nullptr;
    CHECK_PARAM(sDelIdx < 0||sDelIdx>=MAX_TREE_NODE_NUM,);
//    PRINT("delete idx %d",sDelIdx);
    while (this->stTreeArray[sDelIdx].pChildList){
        pTreeChildNode=this->stTreeArray[sDelIdx].pChildList;
        pLastNode=&this->stTreeArray[sDelIdx].pChildList;
        while(pTreeChildNode->pNext){
                pLastNode=&pTreeChildNode->pNext;
                pTreeChildNode=pTreeChildNode->pNext;
        }
        this->DeleteTreeNodeByIdx(pTreeChildNode->sPos);
        // 调用玩delete 最右侧节点相当于和树脱离,释放当前节点并断开链表
        free(pTreeChildNode);
        *pLastNode= nullptr;
    }
    // 将当前索引中的节点置空,相当于删除
    memset(&this->stTreeArray[sDelIdx],0,sizeof(TreeNode));
}

/*!
 * 删除节点,只能保证能删除叶子节点,子树删除有待试验
 * @param pstNodeA 待删除的节点
 * @return
 */
int MyTree::DeleteTreeNode(char *pName){
    int sDelIdx=INVALID_IDX;
    CHECK_PARAM(!pName,FAILED);
    sDelIdx=FindNodeByName(pName);
    CHECK_PARAM(sDelIdx<0||sDelIdx>20,FAILED);
    this->DeleteTreeNodeByIdx(sDelIdx);
    return OK;
}

void MyTree::PtTreeStruct(){
    int sPtCnt=0;
    TreeChildNode*pChildNode= nullptr;
    std::cout<<"\n";
    PRINT("pt tree struct node num %u",sNodeNum);
    for (int i = 0; i < MAX_TREE_NODE_NUM; ++i) {
        if(sPtCnt>=sNodeNum){
            PRINT("pt tree struct end");
            break;
        }
        std::cout<<"idx "<<i<<" cnt "<<sPtCnt<<"\t";
        std::cout<<"id:"<<stTreeArray[i].szId<<"\tvalue:"<<stTreeArray[i].stData.data<<"\t"
        <<"parents "<<stTreeArray[i].sParentsIdx<<"\t";
        pChildNode=stTreeArray[i].pChildList;
        while(pChildNode!=0){
            std::cout<<" child idx "<<pChildNode->sPos<<" pNext "<<pChildNode->pNext;
            pChildNode=pChildNode->pNext;
        }
        std::cout<<" NULL"<<std::endl;
        sPtCnt++;
    }
}

/*!
 * 传递节点时,外部先给name data,然后这里构造出tree的node,之后再将返回的指针传入
 * @param pstNodeA
 * @param pName
 * @param pEle
 * @return
 */
int GenerOneTreeNode(TreeNode*pstNodeA,char *pName,ElemType*pEle){
    CHECK_PARAM(!pstNodeA||!pName||!pEle,FAILED);
    strncpy(pstNodeA->szId,pName, sizeof(pstNodeA->szId));
    memcpy(&pstNodeA->stData,pEle, sizeof(ElemType));
    return OK;

}


BinaryTreeNode* BinaryTree::PreOrderTraverse(BinaryTreeNode*pNode,char *pName){
    BinaryTreeNode*pRet= nullptr;
    int ret=0;
    if(nullptr==pNode){
        return nullptr;
    }
    // 前续遍历,先判断双亲节点是不是,然后再递归左右节点
    if(!strncmp(pNode->szId,pName,MAX_ID_LEN)){
        return pNode;
    }
    // 此节点不是目标节点,向左子树和右子树寻找
    pRet=PreOrderTraverse(pNode->pLeft,pName);
    if(pRet){
        return pRet;
    }
    pRet=PreOrderTraverse(pNode->pRight,pName);
    if(pRet){
        return pRet;
    }
    // 左子树和右子树都没有,说明没找到,则返回空指针
    return nullptr;

}


BinaryTreeNode* BinaryTree::FindNodeByName(char *pName) {
    BinaryTreeNode* pNode= nullptr;
    pNode=PreOrderTraverse(this->pRoot,pName);
    return pNode?pNode: nullptr;

}

/*!
 * 在名称为pParentName后插入名称为pNodeName的节点,修改修改后应该可以直接插入子树
 * 但是需要外层管理节点了
 * @param pParentName
 * @param pNodeName
 * @param pEle
 * @param direct
 * @return
 */
int BinaryTree::InsertTreeNode(char *pParentName,char*pNodeName,ElemType*pEle,BinaryInsertDir direct){
    BinaryTreeNode*pPareNode= nullptr;
    BinaryTreeNode*pNewNode= nullptr;
    CHECK_PARAM(!pNodeName||!pEle,FAILED);

    if(pParentName== nullptr&&direct==INSERT_ROOT){
        // 插入根节点
        pNewNode=(BinaryTreeNode*)malloc(sizeof(BinaryTreeNode));
        CHECK_PARAM(!pNewNode,FAILED);
        memset(pNewNode,0, sizeof(BinaryTreeNode));
        strncpy(pNewNode->szId,pNodeName,MAX_ID_LEN);
        memcpy(&pNewNode->stData,pEle, sizeof(ElemType));
        pNewNode->pParents= nullptr;
        pRoot=pNewNode;

    }
    else{
        // 插入非根节点
        pPareNode=FindNodeByName(pParentName);
        if(!pPareNode){
            PRINT_MODE(PT_RED,"not find parents node %s",pParentName);
            return FAILED;
        }
        pNewNode=(BinaryTreeNode*)malloc(sizeof(BinaryTreeNode));
        CHECK_PARAM(!pNewNode,FAILED);
        memset(pNewNode,0, sizeof(BinaryTreeNode));
        strncpy(pNewNode->szId,pNodeName,MAX_ID_LEN);
        memcpy(&pNewNode->stData,pEle, sizeof(ElemType));
        pNewNode->pParents=pPareNode;
        if(direct==INSERT_LEFT){
            if(pPareNode->pLeft){
                PRINT_MODE(PT_RED,"%s has left node ,cannot insert ",pPareNode->szId);
                free(pNewNode);
                return FAILED;
            }
            pPareNode->pLeft=pNewNode;
        }
        else if(direct==INSERT_RIGHT){
            if(pPareNode->pRight){
                PRINT_MODE(PT_RED,"%s has right node ,cannot insert ",pPareNode->szId);
                free(pNewNode);
                return FAILED;
            }
            pPareNode->pRight=pNewNode;
        } else{
            PRINT_MODE(PT_RED,"Input insert direct %d error !",direct);
        }
    }
    sNodeCnt++;

    return OK;

}

/*!
 * 递归删除节点
 * @param pNode
 * @return
 */
void BinaryTree::RecurFreeNode(BinaryTreeNode*pNode){
    if(!pNode){
        return ;
    }

    if(pNode->enLeft==TREE_POINT_NODE){
        RecurFreeNode(pNode->pLeft);
    }
    if(pNode->enRight==TREE_POINT_NODE){
        RecurFreeNode(pNode->pRight);
    }

//    PRINT("free node name %s",pNode->szId);
    free(pNode);
}

/*!
 * 删除一个节点,及其子树
 * @param pName
 * @return
 */
void BinaryTree::DeleteTreeNode(char *pName) {
    BinaryTreeNode*pNode= nullptr;
    BinaryTreeNode*pPareNode= nullptr;
    pNode=FindNodeByName(pName);
    pPareNode=pNode->pParents;
    CHECK_PARAM(!pNode,);

    // 删除时,先将树真个剥离,然后再把树由顶向下释放
    if(pPareNode){
        if(pPareNode->pLeft==pNode){
            pPareNode->pLeft= nullptr;
        } else if(pPareNode->pRight==pNode){
            pPareNode->pRight= nullptr;
        }
    } else{
        PRINT("maybe delete root node name %s",pNode->szId);
        pRoot= nullptr;
    }
    RecurFreeNode(pNode);
    return ;
}

/*!
 * 打印节点值,声明成成员变量函数似乎会因为this指针出现问题,原因具体看不懂,大概是两个三个参数的问题
 * 修改方法
 * 1.改成全局函数,
 * 2.改成static成员函数
 * @param pNode
 */
void PtNodeValue(BinaryTreeNode*pNode){
    CHECK_PARAM(!pNode,);
    PRINT("access node name %s value %lld enLeft %d pLeft %p enRight %d pRight %p ",
            pNode->szId,pNode->stData.data,pNode->enLeft,pNode->pLeft,pNode->enRight,pNode->pRight);
}

void BinaryTree::PreOrderPtTree(BinaryTreeNode*pNode,ProcNodeFunc pFunc){
    if(!pNode){
        return ;
    }
    pFunc(pNode);
//    PRINT("access node name %s",pNode->szId);
    if(pNode->enLeft==TREE_POINT_NODE){
        PreOrderPtTree(pNode->pLeft,pFunc);
    }
    if(pNode->enRight==TREE_POINT_NODE){
        PreOrderPtTree(pNode->pRight,pFunc);
    }
}

void BinaryTree::PostOrderPtTree(BinaryTreeNode*pNode,ProcNodeFunc pFunc){
    if(!pNode){
        return ;
    }
    if(pNode->enLeft==TREE_POINT_NODE) {
        PostOrderPtTree(pNode->pLeft, pFunc);
    }
    if(pNode->enRight==TREE_POINT_NODE){
        PostOrderPtTree(pNode->pRight,pFunc);
    }
    pFunc(pNode);
//    PRINT("access Node name %s",pNode->szId);
}

void BinaryTree::MiddleOrderPtTree(BinaryTreeNode*pNode,ProcNodeFunc pFunc){
    if (!pNode){
        return ;
    }
    if(pNode->enLeft==TREE_POINT_NODE) {
        MiddleOrderPtTree(pNode->pLeft, pFunc);
    }
    pFunc(pNode);
//    PRINT("access Node name %s",pNode->szId);
    if(pNode->enRight==TREE_POINT_NODE) {
        MiddleOrderPtTree(pNode->pRight, pFunc);
    }
}



void BinaryTree::TraverseTree(TraverseTreeOrder order){
    switch (order){
        case PREORDER_TRAVERSE:
            PRINT_MODE(PT_BLUE,"PREORDER_TRAVERSE");
            PreOrderPtTree(pRoot,PtNodeValue);
            break;
        case POSTORDER_TRAVERSE:
            PRINT_MODE(PT_BLUE,"POSTORDER_TRAVERSE");
            PostOrderPtTree(pRoot,PtNodeValue);
            break;
        case MIDDLEORDER_TRAVERSE:
            PRINT_MODE(PT_BLUE,"MIDDLEORDER_TRAVERSE");
            MiddleOrderPtTree(pRoot,PtNodeValue);
            break;
        case LAYERORDER_TRAVERSE:
            break;
    }
}


/*!
 * 递归调用,建立二进制树的线索
 * 建立完成后,仅存在两个空指针,按顺序首个叶子节点的left指针,但这不是前续遍历的第一个节点
 * 和最后一个叶子节点的right指针是前续遍历的最后一个节点
 * @param pNode
 */
void ThreadPreEstabBinTree(BinaryTreeNode* pNode){
    static BinaryTreeNode* pLatsNode= nullptr;
//    BinaryTreeNode*pNode= nullptr;
    if(nullptr==pNode){
        return ;
    }

    // 没有左右节点指针的一定是叶子节点
    if(!pNode->pLeft&&pNode->enLeft==TREE_POINT_NODE){
        pNode->pLeft=pLatsNode;
        pNode->enLeft=TREE_POINT_THREAD;
    }
    if (pLatsNode&&!pLatsNode->pRight&&pNode->enRight==TREE_POINT_NODE){
        pLatsNode->pRight=pNode;
        pLatsNode->enRight=TREE_POINT_THREAD;
    }
    pLatsNode=pNode;

    // 防止前续遍历因为之前已经修改node节点left指针而发生的无限递归
    if(pNode->enLeft==TREE_POINT_NODE){
        ThreadPreEstabBinTree(pNode->pLeft);
    }
    if(pNode->enRight==TREE_POINT_NODE){
        ThreadPreEstabBinTree(pNode->pRight);
    }

}

/*!
 * 中序遍历 是先访问左树,再访问中间节点,后访问右树
 * @param pNode
 */
void ThreadMiddleEstabBinTree(BinaryTreeNode* pNode){
    static BinaryTreeNode* pLatsNode= nullptr;
    CHECK_PARAM(!pNode,)
    ThreadMiddleEstabBinTree(pNode->pLeft);
    // 应对线索指针的 node节点的头尾两个节点,所以需要加上枚举判断
    if(pLatsNode&&pLatsNode->enRight==TREE_POINT_NODE&&pLatsNode->pRight== nullptr){
        pLatsNode->enRight=TREE_POINT_THREAD;
        pLatsNode->pRight=pNode;
    }
    if(pNode->enLeft==TREE_POINT_NODE&&pNode->pLeft== nullptr){
        pNode->enLeft=TREE_POINT_THREAD;
        pNode->pLeft=pLatsNode;
    }
    //真实访问到节点后,将访问过的节点pNode赋值给pLastNode
    pLatsNode=pNode;
    ThreadMiddleEstabBinTree(pNode->pRight);
}

/*!
 * 在原先二叉树已经建立基础上初始化线索二叉树,使用前序遍历初始化
 * 尝试点不一样的
 * 相对于中序遍历,因为中序遍历第一个节点就是left节点为空,最后一个节点right也为空,使用循环链表应该更加合适
 * 但是前序遍历第一个访问到的叶子节点(顺序排在中间)left节点才为空,最后一个节点rigth也为空,相对来说不太合适
 * @return
 */
int BinaryTree::InitThread(TraverseTreeOrder order){
    BinaryTreeNode*pNode= nullptr;
    if(order==PREORDER_TRAVERSE){
        ThreadPreEstabBinTree(pRoot);
    }else if(order==MIDDLEORDER_TRAVERSE){
        ThreadMiddleEstabBinTree(pRoot);
    }

    return OK;

}

/*!
 * 通过前序建立的线索
 * 遍历二叉树,遍历不使用递归了,而是循环
 */
void BinaryTree::ThreadPreTraverseTree(){
    BinaryTreeNode*pNode= pRoot;
    while(pNode){

        PtNodeValue(pNode);

        while(pNode->enLeft==TREE_POINT_NODE&&pNode->pLeft!= nullptr){
            pNode=pNode->pLeft;
            PtNodeValue(pNode);
        }
        // 访问到叶子节点了

        while(pNode->enRight==TREE_POINT_THREAD&&pNode->pRight!= nullptr){
            pNode=pNode->pRight;
            PtNodeValue(pNode);
        }

        // 处理非叶子节点,前续遍历可能遇到有或者没有左右子树的非叶子节点,优先判断有没有左子树
        // 而中序遍历经过跳转之后,一定访问到parent节点 ,下一个 则一定是访问右子树,右子树不存在,则遍历结束
        if(pNode->enLeft==TREE_POINT_NODE){
            pNode=pNode->pLeft;
        } else if(pNode->enRight==TREE_POINT_NODE){
            pNode=pNode->pRight;
        } else if(pNode->enRight==TREE_POINT_THREAD&&pNode->pRight== nullptr){
            PRINT("assess last node break");
            break;
        }
    }
//    PtNodeValue(pNode);
}

void BinaryTree::ThreadMiddleTraverseTree(){

    BinaryTreeNode*pNode= pRoot;

    // 第一个判断条件使得第一次根节点如果为空,可以跳出,或者遇到最后一个节点,pNode=pNode->pRight pRight节点为空
    // 第二个判断条件是循环真正退出条件
    while(pNode){
        while(pNode->enLeft==TREE_POINT_NODE){
            pNode=pNode->pLeft;
        }
        // 遍历到第一个,或者线索链表之后的第一个节点
        PtNodeValue(pNode);
        while(pNode->enRight==TREE_POINT_THREAD&&pNode->pRight!=0){
            // 下一个节点必然是中间节点
            pNode=pNode->pRight;
            PtNodeValue(pNode);
        }
        // 线索寻找结束,证明当前节点为中间节点,之前的左子树和中间节点已经遍历完成,
        // 下面通过正常树子节点关系访问右子树的根节点(非线索链表)
        // 这也是中序遍历特点
        // 或者是循环退出情况pNode->enRight==TREE_POINT_THREAD&&pNode->pRight==0
        // 右边无树,并且pRigth=0
        pNode=pNode->pRight;
    }
    // 因为之前树经过处理,仅存在两个空,一个是pNode->enRight==TREE_POINT_THREAD的pRight的尾,
    // 另一个是pNode->enLeft==TREE_POINT_THREAD的pLeft的头,
    //遇到空节点,证明是

}

/*!
 *递归利用外部传入的字符串,构造树结构,使用前续遍历
 * @param ppChar 这个值一定要是二级指针,因为相当于递归的过程中,需要一个静态变量,
 * 使用二级指针可以修改一级指针的值,从而使得外部变量看起来像实现静态变量的功能
 * @param ppNode 为pLeft和pRigth指针,时候用在本函数内申请节点地址,使用二级指针,
 * 方便在本函数内修改pLeft和pRigth地址
 */
void BinaryTree::InitTreeByStruct(char **ppChar,BinaryTreeNode**ppNode){
    BinaryTreeNode* pNewNode= nullptr;
    CHECK_PARAM(!ppChar||!ppNode,);
    if(**ppChar=='\0'){
        return ;
    }
    if(**ppChar=='#'){
        *ppNode= nullptr;
        *ppChar=*ppChar+1;
    } else{
        pNewNode=(BinaryTreeNode*)malloc(sizeof(BinaryTreeNode));
        CHECK_PARAM(!pNewNode,);
        memset(pNewNode,0,sizeof(BinaryTreeNode));
        PRINT("Init node name %c",**ppChar);
        pNewNode->stData.data=(unsigned long long)this->sGenerNodeCnt++;
        sNodeCnt++;
        pNewNode->szId[0]=**ppChar;
        *ppChar=*ppChar+1;
        *ppNode=pNewNode;
        InitTreeByStruct(ppChar,&pNewNode->pLeft);
        InitTreeByStruct(ppChar,&pNewNode->pRight);
    }
    return ;
}

/*!
 * 使用字符串初始化函数,默认使用前序遍历
 * @param pStru
 */
BinaryTree::BinaryTree(char *pStru){
    pRoot=0;
    sNodeCnt=0;
    sGenerNodeCnt=0;
    char **ppChar=0;
    char *pVoid= nullptr;
    pVoid=(char*)malloc(strlen(pStru)+1);
    memcpy(pVoid,pStru,strlen(pStru)+1);
    ppChar=&pVoid;


//    pChar=pStru;
    InitTreeByStruct(ppChar,&pRoot);

}

BinaryTree::BinaryTree(){
    pRoot=0;
    sNodeCnt=0;
}


BinaryTree::~BinaryTree(){
    RecurFreeNode(pRoot);
}

