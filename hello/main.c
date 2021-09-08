//
// Created by LJjia on 2021-08-14.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void ptValue(void *pVoid,int len)
{
    int i=0;
    unsigned char* pChar=NULL;
    pChar=pVoid;
    printf("print mem value\n");
    for(i=0;i<len;i++)
    {
        printf("%u ",pChar[i]);
    }
    printf("\n");
}

int main(int argc,char *argv[])
{

    int a=0;
    void *pVoidOld=NULL;
    void *pVoidNew=NULL;
    pVoidOld=realloc(NULL,5);
    memset(pVoidOld,1, 5);
    printf("first new addr %p \n",pVoidOld);
    ptValue(pVoidOld,5);
    pVoidNew=realloc(pVoidOld,2);
    printf("first new addr %p\n",pVoidNew);
    ptValue(pVoidNew,2);
    ptValue(pVoidNew-5,5);
    free(pVoidNew);
//    unsigned int *pInt=pVoidOld;
//    printf("alloc mem value %u %u\n",pInt[0],pInt[5]);

//    printf("a value %d\n",a);
}