#include "data.h"
#include "comm.h"

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
    int mid=(left+right)/2;
    int sMinValueIdx=left;
    if(left>=right){
        return ;
    }


    // 三个元素选择其中最中间的一个作为中枢
    if(right-left>=2){
        if(pData[mid]>pData[right]){
            swap(pData[mid],pData[right]);
        }
        if(pData[left]>pData[right]){
            swap(pData[left],pData[right]);
        }
        // 先确定最右边的为最大的数,然后比较左边和中间,把中等的数放在左边
        if(pData[mid]>pData[left]){
            swap(pData[mid],pData[left]);
        }
        PRINT("used %d center",pData[left]);
    }

    while(left<right){
        while(left<right&&pData[right]>=tmp){
            right--;
        }
        // 不采用swap的方式可以减少一次赋值
        // 此时最左端元素相当于空出位置,将合适的元素放置到最左端
        pData[left]=pData[right];
        //pData[left]小于tmp 才会被移动,所以下个while循环肯定成立,不需要手动left++
        while(left<right&&pData[left]<=tmp){
            left++;
        }
        pData[right]=pData[left];
    }
    pData[left]=tmp;
    // 如果是交换swap,则不需要最后pData[left]=tmp赋值,
    // 如果是pData[left]=pData[right]这样的赋值操作,则最后需要pData[left]=tmp赋值,
    QuickSortInterval(pData,sStartIdx,left-1);
    QuickSortInterval(pData,left+1,sEndIdx);

}


void QuickSort(int *pData,int len){
    /*
     * 可以选择当数据间距长度小于7时,采用简单插入排序,此时效率更高
     */

    QuickSortInterval(pData,0,len-1);
}


void TestQuickSort(){
    const int datanum=10;
//    DataElement stData{{5,6,2,3,4,7,8,0,1,9},datanum};
    DataElement stData{{1,0,2,3,4,5,6,7,8,9},datanum};
    QuickSort(stData.data,datanum);
    PtDataContent(&stData);

}

