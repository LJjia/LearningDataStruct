/**
 * @Author: Jialiangjun
 * @Description:
 * @Date: Created on 18:23 2021-08-21.
 * @Modify:
 */
#include "str_match.h"
#include <string>
#include <iostream>
#include "comm.h"

using namespace std;

/*!
 * 返回字串在主字符串中的索引,找到的第一个字串,朴素算法
 * @param maj
 * @param sub
 * @return
 */
int classic_match(string & maj,string & sub){
    int i=0,j=0;
    PRINT("input strings size %d %d",maj.size(),sub.size());
    for(i=0;i<maj.size();i++){
        for(j=0;j<sub.size();j++){
            if(maj[i+j]!=sub[j]){
                break;
            }
        }
        if(j==sub.size()){
            PRINT("find match strings index in maj %d",i);
            return i;
        }
    }
    return -1;
}

/*!
 * 计算pNext字串
 * @param sub
 * @param pRetArray
 * @return
 */
int get_next_array(string &sub,int *pRetArray){
    int sub_str_len=0;
    int i=0,j=-1;
    int k=0;
    sub_str_len=sub.size();
    pRetArray[0]=-1;
    if(sub_str_len<1)return OK;
//    pRetArray[1]=0;
    // 注意循环跳出的条件是将pRetArray[i]设置完,如果有5个字符,则pRetArray[4]设置完后就应该退出,此时sub_str_len长度为5
    while(i<sub_str_len-1){
        // 首次比较时,就比较第二个字符和第一个是否相等,一个字符直接退出
        //sub[j] 表示前缀,sub[i]表示后缀
        if(j==-1||sub[j]==sub[i]){
            // 这里设置j==-1的含义在于j==-1时,则是首字母和最后一个字符都不相等,这种情况下不需要移位
            // 直接主串向右移动,字串pRetArray[i]=j j=-1经过++后j=0;
            i++;
            j++;
            pRetArray[i]=j;
        } else{
            // 因为这里j会变成0值,-1值,所以表示前缀,最前面的几个字符
            j=pRetArray[j];
        }
    }
    cout<<"stand kmp get pNext "<<endl;
    for(int index=0;index<sub_str_len;index++){
        cout<<pRetArray[index]<<" ";
    }
    cout<<endl;
    return OK;
}

/*!
 * 计算pNext子串 优化版本 可以避免多次递归,计算的时候辅助计算最后一个字符
 * @param sub
 * @param pRetArray
 * @return
 */
int get_next_array_modify(string &sub,int *pRetArray){
    int sub_str_len=0;
    int i=0,j=-1;
    int k=0;
    sub_str_len=sub.size();
    pRetArray[0]=-1;
    if(sub_str_len<1)return OK;
//    pRetArray[1]=0;
    // 注意循环跳出的条件是将pRetArray[i]设置完,如果有5个字符,则pRetArray[4]设置完后就应该退出,此时sub_str_len长度为5
    while(i<sub_str_len-1){
        // 首次比较时,就比较第二个字符和第一个是否相等,一个字符直接退出
        //sub[j] 表示前缀,sub[i]表示后缀
        if(j==-1||sub[j]==sub[i]){
            // 这里设置j==-1的含义在于j==-1时,则是首字母和最后一个字符都不相等,这种情况下不需要移位
            // 直接主串向右移动,字串pRetArray[i]=j j=-1经过++后j=0;
            i++;
            j++;
            if(sub[i]==sub[j]){
                // 比对前缀后缀的比较位是否相等
                // 如果相等,则说明主串接下来第一次求的pNext求着没有用处,因为肯定不会一样(最后比较位不同)
                // 计算的时候预先帮着先递归一层
                // 计算求解的时候,是123456反向的,但使用的时候是从654321递归的,所以最后得出的
                // 就是最终的递归结果,而不是一次递归的临时值
                pRetArray[i]=pRetArray[j];
            }else{
                // 不相等则无能为力,按正常的来
                pRetArray[i]=j;
            }
        } else{
            // 因为这里j会变成0值,-1值,所以表示前缀,最前面的几个字符
            j=pRetArray[j];
        }
    }
    cout<<"modify optimize kmp get pNext "<<endl;
    for(int index=0;index<sub_str_len;index++){
        cout<<pRetArray[index]<<" ";
    }
    cout<<endl;
    return OK;
}

/*!
 * kmp匹配算法,似乎和计算字串十分相似
 * @param maj
 * @param sub
 * @return
 */
int kmp_alg(string & maj,string & sub){
    int analy_sub[20]={0};
    int sub_idx=0;
    int maj_idx=0;
    get_next_array(sub,analy_sub);
    get_next_array_modify(sub,analy_sub);
    while(sub_idx<sub.size() && maj_idx<maj.size()){
        if(sub_idx==-1||sub[sub_idx]==maj[maj_idx]){
            sub_idx++;
            maj_idx++;
        }else{
            sub_idx=analy_sub[sub_idx];
        }
    }
    if(sub_idx==sub.size()){
        PRINT("find same maj %u sub %u",maj_idx,sub_idx);
        // 返回的是从第几位开始相等,比如主9个字符,子6个字符,和最后6个匹配,则返回3
        return maj_idx-sub_idx;
    } else{
        return -1;
    }
}

int analysis_sub_str(string &sub,int* pRetArray){
    int sub_str_size=sub.size();
    int i=0,j=0;
    int offset=0;
    // !! memset为逐字节操作,因此如果置位为1,int类型将都不到正确的1,而是一个非常大的数字
    memset(pRetArray,0,sizeof(int)*sub_str_size);
    if(sub_str_size==1){
        pRetArray[0]=0;
        return OK;
    }
    for(i=1;i<sub_str_size;i++){
        for(offset=pRetArray[i-1];offset>=0;offset--){
            for(j=0;j<offset+1;j++){
//            for(j=i-offset-1;j<i;j++){
                if(sub[i+j-offset]!=sub[j]){
                    break;
                }
            }
            if(j==offset+1){
                pRetArray[i]=offset+1;
                break;
            } else{
                pRetArray[i]=0;
            }
        }
    }

    cout<<"pt sub str index"<<endl;
    for(int index=0;index<sub_str_size;index++){
        cout<<pRetArray[index]<<" ";
    }
    cout<<endl;
    return OK;

}
/*!
 * kmp 匹配算法,先用自己写的来试试
 * @param maj
 * @param sub
 * @return
 */
int kmp_match(string & maj,string & sub){
    int analy_sub[20]={0};
    int offset=0;
    analysis_sub_str(sub,analy_sub);
    int i=0,j=0;
//    while(i<=maj.size()&&j<=sub.size()){}


    for(i=0;i<maj.size();i++){
        for(j=0;j<sub.size();j++){
            if(maj[i+j]!=sub[j]){
                if(j!=0){
                    offset=analy_sub[j-1];
                    if(offset>0){
                        PRINT("happend ")
                        j=offset;

                    }
                }

                break;
            }
        }
        if(j==sub.size()){
            PRINT("find match strings index in maj %d",i);
            return i;
        }

    }
    return -1;
}


void TestStrMatch(){
    string major="abcabcabx";
    string sub="abcabx";
    major.size();
    int index=0;
    index=classic_match(major,sub);

    PRINT("classic get index %u",index);
    index=kmp_match(major,sub);
    PRINT("self designer  get index %u",index);

    index=kmp_alg(major,sub);
    PRINT("classic designer  get index %u",index);
}
