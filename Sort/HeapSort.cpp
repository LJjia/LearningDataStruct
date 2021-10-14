/**
 * @File: HeapSort
 * @Author: Jialiangjun
 * @Description: 堆排序
 * @Date: Created on 18:17 2021-10-14.
 * @Modify:
 */



#include "data.h"
#include <cstdio>

/*!
 * 大顶堆调节函数,调节会将根索引移动到孩子节点中合适的位置
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
    sBiggerIdx=sRootIdx;
    // sRootIdx为索引 实际孩子节点公式从1开始,需要处理
    // 以下循环需要注意,i是第几个从1开始,sBiggerIdx是索引,从0开始,注意之间的转换
    for(i=sRootIdx+1;i*2<len;i=i*2){
        sBiggerIdx=i-1;
        if(pData[i-1]<pData[i*2-1]){
            sBiggerIdx=i*2-1;
            // 找孩子节点最大的值
            // 首先判断是不是存在右孩子节点,然后判断左右孩子节点哪个大
            if((i*2+1)<len&&pData[i*2-1]<pData[i*2]){
                sBiggerIdx=i*2;
            }
        }else{
            // 证明root已经比孩子节点大,结束
            break;
        }
        pData[i-1]=pData[sBiggerIdx];
        i=sBiggerIdx+1;
    }
    pData[sBiggerIdx]=tmp;

}

void HeapSort(int *pData,int len){
    int i;
    for(i=len/2-1;i>=0;i--){
        HeapAdjust(pData,len,i);

        for(int i=0;i<len;i++){
            printf("%d\t",pData[i]);
        }
        printf("\n");
    }



    for(i=len-1;i>0;i--){
        swap(pData[0],pData[i]);
        HeapAdjust(pData,len,0);
    }
}



void TestHeapSort(){
    const int datanum=10;
//    DataElement stData{{5,6,2,3,4,7,8,0,1,9},datanum};
    DataElement stData{{1,0,2,3,4,5,6,7,8,9},datanum};
    HeapSort(stData.data,datanum);
    PtDataContent(&stData);

}

