/**
 * @File: HeapSort
 * @Author: Jialiangjun
 * @Description: 堆排序
 * @Date: Created on 18:17 2021-10-14.
 * @Modify:
 */



#include "data.h"
#include "comm.h"
#include <cstdio>

/*!
 * 大顶堆调节函数,调节会将根索引移动到孩子节点中合适的位置,而其中若有某些孩子节点的子树存在大小问题,不会调节
 * 因此上层调用是从末尾的中间节点开始调用
 * @param pData 所有数据开头指针
 * @param len 数据总长
 * @param sRootIdx 出问题的根索引,注意是索引
 */
void HeapAdjust(int *pData,int len,int sRootIdx){
    int tmp=0;
    int i,j=0;
    int sBiggerIdx=0;
    if(sRootIdx>len-1){
        // 异常
        return ;
    }
    tmp=pData[sRootIdx];
    // sRootIdx为索引 实际孩子节点公式从1开始,需要处理
    // 以下循环需要注意,i是第几个从1开始,sBiggerIdx是索引,从0开始,注意之间的转换
    for(i=(sRootIdx+1)*2;i<=len;i*=2) {
        sBiggerIdx = i - 1;
        if (i < len && pData[i - 1] < pData[i]) {
            sBiggerIdx = i;
        }
        if (tmp >= pData[sBiggerIdx]) {
            // 注意这里的判断条件是tmp的值是否大于孩子节点的值
            // 这样就可以省去循环最后,将tmp值赋给孩子节点,待到循环跳出时,再对对应的根节点或者孩子节点赋值
            break;
        }

        //此时的sRootIdx相当于空位,把孩子节点的值放置到sRootIdx中
        pData[sRootIdx] = pData[sBiggerIdx];
        sRootIdx = sBiggerIdx;
        i = sBiggerIdx + 1;
    }
    pData[sRootIdx]=tmp;

}

void HeapSort(int *pData,int len){
    int i;
    for(i=len/2-1;i>=0;i--){
        HeapAdjust(pData,len,i);


    }

    for(i=len-1;i>0;i--){
        swap(pData[0],pData[i]);
        HeapAdjust(pData,i,0);
    }
}



void TestHeapSort(){
    const int datanum=10;
//    DataElement stData{{5,6,2,3,4,7,8,0,1,9},datanum};
    DataElement stData{{1,0,2,3,4,5,6,7,8,9},datanum};
    HeapSort(stData.data,datanum);
    PtDataContent(&stData);

}

