//
// Created by cyc20 on 2018/1/3.
//

#ifndef GRAPH_GRAPH_H
#define GRAPH_GRAPH_H

#include "stdio.h"
#include "stdlib.h"

#define MAX_VERTEX_NUM 20
#define TRUE 1
#define FALSE 0
#define ERROR -1
#define OK 1
#define OVERFLOW -2
typedef int Status;

typedef char VertexType;
typedef char InfoType;

typedef enum {unvisited,visited} VisitIf;
typedef struct EBox{
    VisitIf mark;  //访问标记
    int ivex,jvex;  //该边依附的这两个顶点的位置
    EBox *ilink,*jlink;  //分别指向依附这两个顶点的下一条边
    InfoType info;  //该边信息指针
}EBox;

typedef struct VexBox{
    VertexType data;
    EBox *firstedge;  //指向第一条依附该顶点的边
}VexBox;

typedef struct AMLGraph{
    VexBox adjmulist[MAX_VERTEX_NUM];
    int vexnum,edgenum;//无向图定点数和边数
}AMLGraph;
/**
 *
 * @param G
 * @return
 */
Status CreateGraph(AMLGraph &G);
/**
 *
 * @param G
 * @param u
 * @return
 */
int LocateVex(AMLGraph G,VertexType u);

/**
 *
 * @param G
 * @param v
 * @return
 */
VertexType GetVex(AMLGraph G,int v);

/**
 *
 * @param G
 * @param v
 * @param value
 * @return
 */
Status PutVex(AMLGraph &G,VertexType v,VertexType value);
/**
 *
 * @param G
 * @param v
 * @return
 */
int FirstAdjVex(AMLGraph G,VertexType v);
/**
 *
 * @param G
 * @param v
 * @param w
 * @return
 */
int NextAdjVex(AMLGraph G,VertexType v,VertexType w);

/**
 *
 * @param G
 * @param v
 * @return
 */
Status InsertVex(AMLGraph &G,VertexType v);
/**
 *
 * @param G
 * @param v
 * @param w
 * @return
 */
Status DeleteArc(AMLGraph &G,VertexType v,VertexType w);
/**
 *
 * @param G
 * @param v
 * @return
 */
Status DeleteVex(AMLGraph &G,VertexType v);
/**
 *
 * @param G
 */
void DestroyGraph(AMLGraph &G);
Status IsHave(AMLGraph G,VertexType v,VertexType w);
Status InsertArc(AMLGraph &G,VertexType v,VertexType w);
/**
 *
 */

void DFS(AMLGraph G,int v);
void DFSTraverse(AMLGraph G,Status(*vis)(VertexType));
void BFSTraverse(AMLGraph G,Status(*Vis)(VertexType));

#endif //GRAPH_GRAPH_H
