/**
 * @File: EdgeArray
 * @Author: Jialiangjun
 * @Description:边集数组
 * @Date: Created on 09:39 2021-09-15.
 * @Modify:
 */
#ifndef GRAPH_EDGEARRAY_H
#define GRAPH_EDGEARRAY_H

#include "graph_common.h"
#include "comm.h"

namespace EdgeArraySpace {


    struct EdgeDesc {
        int begin;
        int end;
        int weight;
    };
    struct VertexDesc {
        char name[MAX_NAME_LEN];
        int data;
    };

/*!
 * 有向图边集数组结构,无向图类似
 */
    class EdgeArray {
        EdgeArray();

        ~EdgeArray();

        int InsertVertex(const char *pName,int data);

        int InsertEdge(const char *pTailName, const char *pHeadName, int weight=1);

        void PtStruct();

    protected:
        int sVertexNum;
        int sEdgeNum;
        VertexDesc *pVertex;
        EdgeDesc *pEdge;
        int FindVertexByName(const char *pName);

    };

}
#endif //GRAPH_EDGEARRAY_H
