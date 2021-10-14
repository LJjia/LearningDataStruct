/**
 * @File: ShellSort
 * @Author: Jialiangjun
 * @Description:希尔排序
 * @Date: Created on 11:06 2021-10-14.
 * @Modify:
 */

#include "SimpleSort.h"
#include "data.h"
#include "comm.h"

/*!
 * 希尔排序,实际上是对插入排序的一种优化,increment==1时即为对应的插入排序
 * @param pData
 * @param len
 */
void  ShellSort(int*pData,int len){
    int i,j;
    int increment=len;
    int sCurValue=0;
    while(increment>1){
        increment=increment/3+1;
        // 实际可以除以4 2 等其他的数值,具体看数据情况定多少
        for(i=increment;i<len;i++){
            // 从小到大排序
            // 当increment==1时,最后一遍为插入排序
            if(pData[i]<pData[i-increment]){
                sCurValue=pData[i];
                for(j=i-increment;j>=0&&pData[j]>sCurValue;j-=increment){
                    pData[j+increment]=pData[j];
                }
                pData[j+increment]=sCurValue;
            }
        }

    }
}



void TestShellSort(){
    const int datanum=10;
    DataElement stData{{1,0,2,3,4,5,6,7,8,9},datanum};
    ShellSort(stData.data,datanum);
    PtDataContent(&stData);

}