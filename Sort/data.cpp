/**
 * @File: data
 * @Author: Jialiangjun
 * @Description:
 * @Date: Created on 16:00 2021-10-13.
 * @Modify:
 */
#include <cstdio>
#include "comm.h"
#include "data.h"

void swap(int&a,int &b){
    int c=a;
    a=b;
    b=c;
}


void PtDataContent(DataElement*pEle){
    PRINT("Pt data content");
    for(int i=0;i<pEle->len;i++){
        printf("%d\t",pEle->data[i]);
    }
    printf("\n");

}