/**
 * @File: data
 * @Author: Jialiangjun
 * @Description:
 * @Date: Created on 16:00 2021-10-13.
 * @Modify:
 */
#ifndef SORT_DATA_H
#define SORT_DATA_H

#define MAX_DATA_LEN 100

struct DataElement{
    int data[MAX_DATA_LEN];
    int len;
};

void swap(int&a,int &b);
void PtDataContent(DataElement*pEle);

#endif //SORT_DATA_H
