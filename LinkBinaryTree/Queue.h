//
// Created by cyc20 on 2017/12/20.
//

#ifndef LINKBINARYTREE_QUEUE_H
#define LINKBINARYTREE_QUEUE_H

#include "binarytree.h"

typedef BiTree QElemType;
typedef struct QNode {
    QElemType data;
    QNode *next;
} *QueuePtr;

struct LinkQueue {
    QueuePtr front, rear; // 队头、队尾指针
};

Status InitQueue(LinkQueue &Q);

Status DestroyQueue(LinkQueue &Q);

Status ClearQueue(LinkQueue &Q);

Status QueueEmpty(LinkQueue Q);

int QueueLength(LinkQueue Q);

Status GetHead(LinkQueue Q, QElemType &e);

Status EnQueue(LinkQueue &Q, QElemType e);

Status DeQueue(LinkQueue &Q, QElemType &e);

Status QueueTraverse(LinkQueue Q, void(*vi)(QElemType));

#endif //LINKBINARYTREE_QUEUE_H
