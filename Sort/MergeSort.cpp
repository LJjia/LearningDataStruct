/**
 * @File: MergeSort
 * @Author: Jialiangjun
 * @Description: 归并排序
 * @Date: Created on 11:28 2021-10-15.
 * @Modify:
 */


#include "comm.h"
#include "data.h"




/*!
 * 合并pData中两个有序数列的数据到pOut中,输出在pOut中的位置和pData中相同
 * 二分归并使得这里的索引可以是start mid 和 end三个值,切分为start-mid 和mid-end两段
 * @param pData
 * @param pOut
 * @param start 第一个有序序列开始索引
 * @param mid 中间索引,这个索引属于第一个有序序列
 * @param end 第二个有序数列结束索引
 */
void MergeData(int *pData,int *pOut,int start,int mid,int end){
    PRINT("part1 %d-%d part2 %d-%d",start,mid,mid+1,end);
    int sOutIdx=0;
    int i=start,j=mid+1;
    for(sOutIdx=start;i<=mid&&j<=end;){
        if(pData[i]<=pData[j]){
            pOut[sOutIdx++]=pData[i++];
        }else{
            pOut[sOutIdx++]=pData[j++];
        }
    }

    for(;i<=mid;){
        pOut[sOutIdx++]=pData[i++];
    }
    for(;j<=end;){
        pOut[sOutIdx++]=pData[j++];
    }

}

/*!
 * 对数组从start开始到end的元素进行归并排序,从pData中取元素,输出到pOut中
 * @param pData 源数据地址
 * @param pOut 输出地址
 * @param start 开始idx
 * @param end   结束idx
 */
void MergeSort(int *pData,int *pOut,int start ,int end){
    int mid=0;
    if(start>end){
        return ;
    }
    if(start==end){
//        pOut[start]=pData[start];
        return ;
    }else{
        mid=(start+end)/2;

        MergeSort(pData,pOut,start,mid);
        MergeSort(pData,pOut,mid+1,end);
        MergeData(pData,pOut,start,mid,end);
        memcpy(&pData[start],&pOut[start], sizeof(int)*(end-start+1));
        // 先拷贝到一个临时的内存中,然后这个临时的值再拷贝到原先内存中
    }
}


/*!
 * 递归实现
 * @return
 */
void MergeSortRecursive(int *pData,int len){
    int buff[MAX_DATA_LEN]{};
    MergeSort(pData,buff,0,len-1);

}



/*!
 * 合并特定长度的片段
 * @param pData
 * @param slice
 * @param sTotalLen
 */
void MergeLenSlice(int *pData,int *pOut,int slice,int sTotalLen){

    int group=0;
    // [start end) 左闭右开
    int start=0;
    if(slice==1){
        for(int j=0;j<sTotalLen;j++){
            pOut[j]=pData[j];
        }
    }

    group=slice;
    for(start=0;start+group*2<=sTotalLen;start+=slice*2){
        MergeData(pData,pOut,start,start+group-1,start+group*2-1);
    }
    if(start+group<sTotalLen){
        // 剩下一个半子序列,这这时修改结尾长度,将这完整的一个和多余的半个合并
        MergeData(pData,pOut,start,start+group-1,sTotalLen-1);
    }else{
        //start + group >= sTotalLen
        // 剩下单个子序列需要拷贝走
        for(int i=start;i<sTotalLen;i++){
            pOut[i]=pData[i];
        }

    }



}

/*!
 * 循环实现归并排序
 * @param pData
 * @param len
 */
void MergeSortLoop(int *pData,int len){
    // 归并排序的缺陷就是需要新申请和排序数据同样大小的空间
    int buff[MAX_DATA_LEN]{};
    int slice=1;
    while(slice<len){
        MergeLenSlice(pData,buff,slice,len);
        slice*=2;
        MergeLenSlice(buff,pData,slice,len);
        slice*=2;
        // slice 表示已经排序好的元素片段大小
    }

}

void TestMergeSort(){
    const int datanum=10;
    int buff[MAX_DATA_LEN]{};
    DataElement stData{{1,0,2,3,4,5,6,7,8,9},datanum};
//    MergeSortRecursive(stData.data,datanum);
    MergeSortLoop(stData.data,datanum);
    PtDataContent(&stData);
//    MergeData(stData.data,buff,0,1,2,3);
//    for(int i=0;i<4;i++){
//        printf("%d\t",buff[i]);
//    }
//    printf("\n");

}


