/**
 * @File: EdgeArray
 * @Author: Jialiangjun
 * @Description:
 * @Date: Created on 09:39 2021-09-15.
 * @Modify:
 */
#include <cstdlib>
#include <iostream>
#include "EdgeArray.h"

namespace EdgeArraySpace{
    using std::cout;
    using std::cin;
    using std::endl;

    EdgeArray::EdgeArray(){
        sVertexNum=0;
        pVertex= nullptr;
        pEdge= nullptr;
    }
    EdgeArray::~EdgeArray() {
        free(pVertex);
        free(pEdge);
    }

    int EdgeArray::InsertVertex(const char *pName,int data){
        VertexDesc*pTmp=nullptr;
        CHECK_PARAM(!pName,FAILED);
        pTmp=(VertexDesc*)realloc(pVertex,sizeof(VertexDesc)*(sVertexNum+1));
        if(pTmp){
            pVertex=pTmp;
        } else{
            PRINT_ERR("malloc mem err vertex num %d",sVertexNum);
            return FAILED;
        }
        pVertex[sVertexNum].data=data;
        strncpy(pVertex[sVertexNum].name,pName,MAX_NAME_LEN);

        sVertexNum++;

    }

    int EdgeArray::InsertEdge(const char *pTailName, const char *pHeadName, int weight){
        VertexDesc*pTmp=nullptr;
        CHECK_PARAM(!pTailName||!pHeadName,FAILED);
        pTmp=(VertexDesc*)realloc(pVertex,sizeof(EdgeDesc)*(sEdgeNum+1));
        if(pTmp){
            pVertex=pTmp;
        } else{
            PRINT_ERR("malloc mem err vertex num %d",sEdgeNum);
            return FAILED;
        }




        sEdgeNum++;
    }

    void EdgeArray::PtStruct(){

    }

    int EdgeArray::FindVertexByName(const char *pName){
        CHECK_PARAM(!pName,FAILED);
        for(int i=0;i<sVertexNum;i++)
        {}
    }
}


