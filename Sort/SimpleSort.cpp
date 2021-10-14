/**
 * @File: SimpleSort
 * @Author: Jialiangjun
 * @Description: 简单排序算法 皆是从小到大排序
 * @Date: Created on 16:04 2021-10-13.
 * @Modify:
 */
#include "SimpleSort.h"
#include "data.h"
#include "comm.h"

/*!
 * 冒泡排序有几种思路, 下面这种是遍历整个数组的过程中,发现一个更小的数字,就进行交换,知道遍历完整个数组
 * 和冒泡排序复杂度相似
 * @param pData
 * @param len
 */
void BubbleSort1(int *pData,int len){
    int i,j;
    int sSwapCnt=0;
    int sCmpCnt=0;
    for(i=0;i<len;i++){
        for(j=i+1;j<len;j++){
            if(pData[i]>pData[j]){
                swap(pData[i],pData[j]);
                sSwapCnt++;
            }
            sCmpCnt++;
        }
    }
    PRINT("swap cnt %d cmp %d",sSwapCnt,sCmpCnt);
}

/*!
 * 比较相邻元素的大小,正规冒泡排序
 * @param pData
 * @param len
 */
void BubbleSort2(int *pData,int len){
    int i,j;
    int sSwapCnt=0;
    int sCmpCnt=0;
    for(i=0;i<len;i++){
        for(j=len-2;j>=i;j--){
            if(pData[j]>pData[j+1]){
                swap(pData[j],pData[j+1]);
                sSwapCnt++;
            }
            sCmpCnt++;
        }
    }
    PRINT("swap cnt %d cmp %d",sSwapCnt,sCmpCnt);
}


/*!
 * 比较相邻元素的大小,正规冒泡排序,优化,如果本次没有发生交换,则后面的排序不进行
 * @param pData
 * @param len
 */
void BubbleSort3(int *pData,int len){
    int i,j;
    int sSwapCnt=0;
    int sCmpCnt=0;
    bool bSwap=true;
    for(i=0;i<len;i++){
        if(!bSwap){
            break;
        }
        bSwap=false;
        for(j=len-2;j>=i;j--){
            if(pData[j]>pData[j+1]){
                swap(pData[j],pData[j+1]);
                bSwap=true;
                sSwapCnt++;
            }
            sCmpCnt++;
        }
    }
    PRINT("swap cnt %d cmp %d",sSwapCnt,sCmpCnt);
}


void TestBubble(){
    const int datanum=10;
//    DataElement stData{{5,6,2,3,4,7,8,0,1,9},datanum};
    DataElement stData{{0,2,1,3,4,5,6,7,8,9},datanum};
    BubbleSort2(stData.data,datanum);
    PtDataContent(&stData);

};

/*!
 * 简单选择排序,每次选择数组中最小的作为交换索引
 * @param pData
 * @param len
 */
void SimpleSelect(int *pData,int len){
    int i,j;
    int sMinIdx=0;
    int sSwapCnt=0;
    int sCmpCnt=0;
    for(i=0;i<len;i++){
        sMinIdx=i;
        for(j=i+1;j<len;j++){
            if(pData[j]<pData[sMinIdx]){
                // 用最小值下标表示最小值可以少使用一个变量
                sMinIdx=j;
            }
            sCmpCnt++;
        }
        if(sMinIdx!=i){
            swap(pData[sMinIdx],pData[i]);
            sSwapCnt++;
        }
    }
    PRINT("swap cnt %d cmp %d",sSwapCnt,sCmpCnt);
}

void TestSelect(){
    const int datanum=10;
//    DataElement stData{{5,6,2,3,4,7,8,0,1,9},datanum};
    DataElement stData{{1,0,2,3,4,5,6,7,8,9},datanum};
    SimpleSelect(stData.data,datanum);
    PtDataContent(&stData);

};


void InsertSort(int *pData,int len){
    int i,j;
    int sCurData;

    if(len<2){
        return ;
    }

    // 初始默认第一个元素已经排序好,每次循环新加一个最右侧元素元素,并排序好位置
    for(i=1;i<len;i++){
        if(pData[i]<pData[i-1]){
            // 新来的元素比有序列表中最后一个大,抽出来
            sCurData=pData[i];
            for(j=i-1;j>=0&&pData[j]>sCurData;j--){
                // 相当于比sCurData大的元素都往后移动一位
                pData[j+1]=pData[j];
                // 此时索引为j的元素空出来
            }
            // 注意循环完之后j会-- ,因此此时j+1的位置是空出来的
            // 将元素插入
            pData[j+1]=sCurData;

        }
    }
}

void TestInsertSort(){
    const int datanum=5;
//    DataElement stData{{5,6,2,3,4,7,8,0,1,9},datanum};
    DataElement stData{{5,3,4,6,2},datanum};
    InsertSort(stData.data,datanum);
    PtDataContent(&stData);
}