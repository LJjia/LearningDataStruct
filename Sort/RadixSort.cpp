#include <cstdio>
#include "data.h"
#include "comm.h"

/**
 * @File: RadixSort
 * @Author: Jialiangjun
 * @Description: 基数排序,八大排序算法之一
 * 这个算法实际不经常用,下面仅介绍简单的LSD,地位排序算法
 * @Date: Created on 14:08 2021-10-16.
 * @Modify:
 */



/*!
 *
 * @param pData 源数据
 * @param len   源数据长度
 * @param radix 比较几个十位
 */
void RadixSortLsd(int *pData,int len,int radix){
    // 10位表示0-9 十个数据位,20表示每个数据位相同的元素最多20个;
    // 首列存放这行数据有多少个,不存放实际元素
    int bucket[10][21]{};
    int i=0,j=0;
    int tmp1=1,tmp2=1;
    int idx=0;
    for(i=0;i<radix;i++){
        // 一共排序radix次
        // 输入到二维数组中
        tmp1*=10;
        for(j=0;j<len;j++){
            idx=(pData[j]%tmp1)/tmp2;
            // idx计算后位于0-9
            bucket[idx][bucket[idx][0]+1]=pData[j];
            bucket[idx][0]++;
        }
        tmp2*=10;

        // 从二维数组中还原到pData中
        j=0;
        for(int sReturnedIdx=0;sReturnedIdx<10;sReturnedIdx++){
            for(int sColIdx=0;sColIdx<bucket[sReturnedIdx][0];sColIdx++){
                pData[j++]=bucket[sReturnedIdx][sColIdx+1];
            }
            bucket[sReturnedIdx][0]=0;
        }

        /* 打印每次调用后的结果
        printf("raidx = %d\n",i);
        for(int a=0;a<len;a++){
            printf("%d\t",pData[a]);
        }
        printf("\n");
        */
    }
}

/*!
 * 基数排序至少要关键字有两位数才能显示结果,因此数据内容扩大一点
 */
void  TestRaidxSort(){
    const int datanum=15;
    int radix=2;
    DataElement stData{{10,8,20,34,42,48,58,52,54,59,60,72,88,85,90},datanum};
    RadixSortLsd(stData.data,datanum,radix);
    PtDataContent(&stData);

}
