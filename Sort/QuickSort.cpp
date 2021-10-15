#include "data.h"

/**
 * @File: QuickSort
 * @Author: Jialiangjun
 * @Description:
 * @Date: Created on 19:04 2021-10-15.
 * @Modify:
 */


/*!
 * 对某个区间进行快排start end表示idx 都是闭区间
 * @param pData
 * @param start
 * @param end
 */
void QuickSortInterval(int *pData,int sStartIdx,int sEndIdx){
    int tmp=pData[sStartIdx];
    int left=sStartIdx;
    int right=sEndIdx;
    if(left>=right){
        return ;
    }
    while(left<right){
        while(left<right&&pData[right]>=tmp){
            right--;
        }
        swap(pData[left],pData[right]);
        left++;
        while(left<right&&pData[left]<=tmp){
            left++;
        }
        swap(pData[left],pData[right]);
        right--;
    }
    // 如果是交换swap,则不需要最后pData[left]=tmp赋值,
    // 如果是pData[left]=pData[right]这样的赋值操作,则最后需要pData[left]=tmp赋值,
    QuickSortInterval(pData,sStartIdx,left-1);
    QuickSortInterval(pData,left+1,sEndIdx);

}


void QuickSort(int *pData,int len){
    QuickSortInterval(pData,0,len-1);
}


void TestQuickSort(){
    const int datanum=10;
//    DataElement stData{{5,6,2,3,4,7,8,0,1,9},datanum};
    DataElement stData{{1,0,2,3,4,5,6,7,8,9},datanum};
    QuickSort(stData.data,datanum);
    PtDataContent(&stData);

}

