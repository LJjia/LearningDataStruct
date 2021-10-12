/**
 * @File: binary_search
 * @Author: Jialiangjun
 * @Description: 二分查找
 * @Date: Created on 10:47 2021-09-28.
 * @Modify:
 */

#include <iostream>
#include <cstdlib>

/*!
 * 二分排序模板
 * @tparam T
 * @param pData
 * @param num 注意num为元素个数,内部是用的是索引idx,对于数组来说,内部需要将其值先-1
 * @param target
 * @return
 */
template <typename T>
int BinarySearch(T*pData,int num,T target){
    int left=0;
    int right=num-1;
    int i=0;
    int sRunTimes=0;
    while(left<=right){
        i=(left+right)/2;
        if(pData[i]==target){
            printf("find idx %d RunTimes %d\n",target,sRunTimes);
            return i;
        } else if(pData[i]>target){
            right=i-1;
        } else{
            left=i+1;
        }
        sRunTimes++;
    }
    printf("not find RunTimes %d\n",sRunTimes);
    return -1;
}

/*!
 * 插值查找
 * @tparam T
 * @param pData
 * @param num
 * @param target
 * @return
 */
template <typename T>
int InterpolationSearch(T*pData,int num,T target){
    int left=0;
    int right=num-1;
    int i=0;
    int sRunTimes=0;
    while(left<=right){
        i=left+(target-pData[left])/(pData[right]-pData[left])*(right-left);

        // 插值查找还要比较一次,防止找不到后 索引发生错乱
        if(target<pData[left]||target>pData[right]){
            break;
        }
        // 或者比较i值是否在left和right之间
        /*if(i<left||i>right){
            break;
        }*/


        if(pData[i]==target){
            printf("find idx %d RunTimes %d\n",target,sRunTimes);
            return i;
        } else if(pData[i]>target){
            right=i-1;
        } else{
            left=i+1;
        }
        sRunTimes++;
    }
    printf("not find RunTimes %d\n",sRunTimes);
    return -1;
}

void TestBinarySearch(){
//    int aData[10] {1,3,5,7,9,11,13,15,17,19};
    int aData[5] {1,3,5,10,11};
//    BinarySearch(aData,10,10);
//    BinarySearch(aData,10,13);
    InterpolationSearch(aData,5,9);
}


/*!
 * 生成fib数组
 * @param pArray
 * @param n
 */
void GenerFibArray(int *pArray,int n){
    int a=0;
    int b=1;
    int tmp=0;
    for(int i=0;i<n;i++){
        pArray[i]=a;
        tmp=a+b;
        a=b;
        b=tmp;
    }
    printf("fib array \n");
    for(int i=0;i<n;i++){
        printf("%4d ",pArray[i]);
    }
    printf("\n");
}

/*!
 * 使用黄金分割比排序
 */
int FibSearch(int*pData,int num,int *pFibArray,int target){
    int left=0;
    int right=num-1;
    int k=0;
    int i=0;
    int mid=0;
    while(right>pFibArray[k]){
        k++;
    }
    // 最后未补齐的地方赋值为最大值
    for(i=right;i<pFibArray[k];i++){
        pData[i]=pData[right];
    }
    while(left<=right){
        // 很多算法这边都会写 mid=left+pFibArray[k-1]-1;
        // 最后的-1不知道为什么,实际没用还会导致算法出问题
        mid=left+pFibArray[k-1];
        if(pData[mid]>target){
            right=mid-1;
            k=k-1;
        } else if(pData[mid]<target){
            left=mid+1;
            k=k-2;
        } else{
            if(mid<=num-1){
                return mid;
            } else{
                return num-1;
            }
        }
    }
    return -1;

}

/*!
 * 测试fib查找
 */
void TestFibSearch(){
    int aFib[10];
    int aData[18]{0,1,16,24,35,47,59,62,73,88,99};
    GenerFibArray(aFib,10);
    int ret=FibSearch(aData,11,aFib,59);
    printf("fib find idx %d",ret);

}


