
//
// Created by cyc20 on 2018/1/3.
//

#include "graph.h"
#include "Queue.h"

/**
 *采用邻接多重表存储结构，构造无向图
 * @param G
 * @return
 */
bool visit[MAX_VERTEX_NUM]; // 访问标志数组(全局量)
Status (*Func)(VertexType v);

Status CreateGraph(AMLGraph &G) {
    int i, j, IncInfo;
    char s;
    VertexType va, vb;
    EBox *p;
    printf("请输入无向图G的顶点数,边数,边是否含其它信息(是:1，否:0): \n");
    scanf("%d %d %d", &G.vexnum, &G.edgenum, &IncInfo);
    getchar();
    printf("请输入%d个顶点的值(一次1个字符):\n", G.vexnum);
    for (int m = 0; m < G.vexnum; ++m) {
        scanf("%c", &G.adjmulist[m].data);
        getchar();
        G.adjmulist[m].firstedge = NULL;
    }
    printf("请顺序输入每条边的两个端点(以空格作为间隔):\n");
    for (int k = 0; k < G.edgenum; ++k) {
        scanf("%c%c", &va, &vb);
        getchar();
        i = LocateVex(G, va);
        j = LocateVex(G, vb);
        p = (EBox *) malloc(sizeof(EBox));
        p->mark = unvisited;
        p->ivex = i;
        p->jvex = j;
        p->info = ' ';
        p->ilink = G.adjmulist[i].firstedge;
        G.adjmulist[i].firstedge = p;
        p->jlink = G.adjmulist[j].firstedge;
        G.adjmulist[j].firstedge = p;
        if (IncInfo) {
            printf("请输入该弧的相关信息(1个字符)：");
            scanf("%c", &s);
            getchar();
            p->info = s;
        }
    }
    return OK;
}

int LocateVex(AMLGraph G, VertexType u) {
    int j;
    for (j = 0; j < G.vexnum; ++j) {
        if (u == G.adjmulist[j].data) {
            return j;
        }
    }
    return -1;
}

VertexType GetVex(AMLGraph G, int v) {

    if (v >= G.vexnum, v < 0) {
        exit(ERROR);
    }
    return G.adjmulist[v].data;
}

Status PutVex(AMLGraph &G, VertexType v, VertexType value) {
    if (G.vexnum == 0) {
        printf("请先插入顶点");
        return ERROR;
    }
    int i;
    i = LocateVex(G, v);
    if (i < 0) {
        printf("没有找到");
        return ERROR;
    }
    G.adjmulist[i].data = value;
    return OK;
}

int FirstAdjVex(AMLGraph G, VertexType v) {
    int i;
    i = LocateVex(G, v);
    if (i < 0) {
        printf("没有这个顶点");
        return ERROR;
    }
    if (G.adjmulist[i].firstedge) {
        if (G.adjmulist[i].firstedge->ivex == i) {
            return G.adjmulist[i].firstedge->jvex;
        } else return G.adjmulist[i].firstedge->ivex;
    } else {
        // printf("没有邻接顶点");
        return ERROR;
    }
}

int NextAdjVex(AMLGraph G, VertexType v, VertexType w) {
    int i, j;
    EBox *p;
    i = LocateVex(G, v);
    j = LocateVex(G, w);

    if (i < 0 || j < 0) {
        printf("输入的顶点不存在");
        return ERROR;
    }
    p = G.adjmulist[i].firstedge;
    while (p) {
        if (p->ivex == i && p->jvex != j) {
            p = p->ilink;
        } else if (p->jvex == i && p->ivex != j) {
            p = p->jlink;
        } else break;
    }
    if (p && p->ivex == i && p->jvex == j) {
        p = p->ilink;
        if (p && p->ivex == i) {
            return p->jvex;
        } else if (p && p->jvex == i) {
            return p->ivex;
        }
    }
    if (p && p->ivex == j && p->jvex == i) {
        p = p->jlink;
        if (p && p->ivex == i) {
            return p->jvex;
        } else if (p && p->jvex == i) {
            return p->ivex;
        }
    }
    return ERROR;
}

Status InsertVex(AMLGraph &G, VertexType v) {
    if (G.vexnum == MAX_VERTEX_NUM) {
        printf("节点已满，不能插入");
        return ERROR;
    }
    if (LocateVex(G, v) > 0) {
        printf("节点已存在，不能插入");
        return ERROR;
    }
    G.adjmulist[G.vexnum].data = v;
    G.adjmulist[G.vexnum].firstedge = NULL;
    G.vexnum++;
    return OK;
}

Status DeleteVex(AMLGraph &G, VertexType v) {
    int i, j;
    VertexType e;
    EBox *p;
    i = LocateVex(G, v);
    if (i < 0) {
        //printf("没有此节点");
        return ERROR;
    }
    for (j = 0; j < G.vexnum; j++) {
        if (j == i)continue;
        e = GetVex(G, j);
        DeleteArc(G, v, e);
    }
    for (j = i + 1; j < G.vexnum; j++) {
        G.adjmulist[j - 1] = G.adjmulist[j];
    }
    G.vexnum--;
    for (j = i; j < G.vexnum; j++) {
        p = G.adjmulist[j].firstedge;
        if (p) {
            if (p->ivex == j + 1) {
                p->ivex--;
                p = p->ilink;
            } else {
                p->jvex--;
                p = p->jlink;
            }
        }
    }
    return OK;
}

Status DeleteArc(AMLGraph &G, VertexType v, VertexType w) {
    int i, j;
    EBox *p, *q;
    i = LocateVex(G, v);
    j = LocateVex(G, w);
    if (i < 0 || j < 0 || i == j) {
        // printf("顶点不存在");
        return ERROR;
    }
    p = G.adjmulist[i].firstedge;
    if (p && p->jvex == j) {   //第一条即为
        G.adjmulist[i].firstedge = p->ilink;
    } else if (p && p->ivex == j) {      //第一条即为
        G.adjmulist[i].firstedge = p->jlink;
    } else {
        while (p) {
            if (p->ivex == i && p->jvex != j) {
                q = p;
                p = p->ilink;
            } else if (p->jvex == i && p->ivex != j) {
                q = p;
                p = p->jlink;
            } else {
                break;
            }
        }

        if (p == NULL) {
            //  printf("没有找到该弧");
            return ERROR;
        }
        if (p->ivex == i && p->jvex == j) {
            if (q->ivex == i) {
                q->ilink = p->ilink;
            } else {
                q->jlink = p->ilink;
            }
        } else if (p->ivex == j && p->jvex == i) {
            if (q->ivex == i) {
                q->ilink = p->jlink;
            } else {
                q->jlink = p->jlink;
            }
        }
    }
    p = G.adjmulist[j].firstedge;   //lingyige
    if (p->jvex == i) {
        G.adjmulist[j].firstedge = p->ilink;
        free(p);
    } else if (p->ivex == i) {
        G.adjmulist[j].firstedge = p->jlink;
        free(p);
    } else {
        while (p) {// 向后查找弧<v,w>
            if (p->ivex == j && p->jvex != i) // 不是待删除边
            {
                q = p;
                p = p->ilink; // 找下一个邻接顶点
            } else if (p->jvex == j && p->ivex != i) // 不是待删除边
            {
                q = p;
                p = p->jlink; // 找下一个邻接顶点
            } else // 是邻接顶点v
                break;
        }
        if (p->ivex == i && p->jvex == j) // 找到弧<v,w>(情况1)
        {
            if (q->ivex == j)
                q->ilink = p->jlink;
            else
                q->jlink = p->jlink;
            free(p);
        } else if (p->ivex == j && p->jvex == i) // 找到弧<v,w>(情况2)
        {
            if (q->ivex == j)
                q->ilink = p->ilink;
            else
                q->jlink = p->ilink;
            free(p);
        }
    }
    G.edgenum--;
    return OK;
}


void DestroyGraph(AMLGraph &G) {
    int i;
    for (i = G.vexnum - 1; i >= 0; i--) {
        DeleteVex(G, G.adjmulist[i].data);
    }
}

Status InsertArc(AMLGraph &G, VertexType v, VertexType w) {
    int i, j;
    EBox *p;
    int IncInfo;
    i = LocateVex(G, v);
    j = LocateVex(G, w);
    // if (IsHave(G, v, w) == OK) {
    //   printf("已存在");
    //  return ERROR;
    // }
    if (i < 0 || j < 0) {
        printf("没有找到");
        return ERROR;
    }
    p = (EBox *) malloc(sizeof(EBox));
    p->mark = unvisited;
    p->ivex = i;
    p->jvex = j;
    p->info = ' ';
    p->ilink = G.adjmulist[i].firstedge;
    G.adjmulist[i].firstedge = p;
    p->jlink = G.adjmulist[j].firstedge;
    G.adjmulist[j].firstedge = p;
    printf("该边是否有相关信息(1.有 0.无)");
    scanf("%d", &IncInfo);
    getchar();
    if (IncInfo) {
        printf("请输入该边的相关信息(1个字符)：");
        scanf("%c", &p->info);
    }
    G.edgenum++;
    return OK;
}

Status IsHave(AMLGraph G, VertexType v, VertexType w) {
    int i, j;
    int flag = 0;
    i = LocateVex(G, v);
    j = LocateVex(G, w);
    EBox *p;
    for (int k = 0; i < G.vexnum; ++k) {
        p = G.adjmulist[k].firstedge;
        while (p) {
            if (p->ivex == i && p->jvex == j) {
                flag = 1;
                break;
            }
            if (p->jvex == i && p->ivex == j) {
                flag = 1;
                break;
            }
        }
        if (flag == 1) {
            break;
        }
    }
    if (flag == 1) {
        return OK;
    }
    return ERROR;
}

void DFS(AMLGraph G, int v) {
    int j;
    EBox *p;
    Func(G.adjmulist[v].data);
    visit[v] = true;
    p = G.adjmulist[v].firstedge;
    while (p) {
        j = p->ivex == v ? p->jvex : p->ivex;
        if (!visit[j]) {
            DFS(G, j);
        }
        p = p->ivex == v ? p->ilink : p->jlink;
    }
}

void DFSTraverse(AMLGraph G, Status(*vis)(VertexType)) {
    int v;
    Func = vis;
    for (v = 0; v < G.vexnum; v++) {
        visit[v] = FALSE;
    }
    for (v = 0; v < G.vexnum; v++) {
        if (!visit[v]) {
            DFS(G, v);
        }
    }
    printf("\n");
}

void BFSTraverse(AMLGraph G, Status(*Vi)(VertexType)) {
    int v, u, w;
    VertexType u1;
    LinkQueue Q;
    for (int i = 0; i < G.vexnum; i++) {
        visit[i] = FALSE;
    }
    InitQueue(Q);
    for (v = 0; v < G.vexnum; v++)
        if (!visit[v]) // v尚未访问
        {
            visit[v] = TRUE; // 设置访问标志为TRUE(已访问)
            Vi(G.adjmulist[v].data);
            EnQueue(Q, v); // v入队列
            while (!QueueEmpty(Q)) // 队列不空
            {
                DeQueue(Q, u); // 队头元素出队并置为u
                u1 = GetVex(G, u);
                for (w = FirstAdjVex(G, u1); w >= 0; w = NextAdjVex(G, u1, GetVex(G, w)))
                    if (!visit[w]) // w为u的尚未访问的邻接顶点的序号
                    {
                        visit[w] = TRUE;
                        Vi(G.adjmulist[w].data);
                        EnQueue(Q, w);
                    }
            }
        }
    printf("\n");
}


