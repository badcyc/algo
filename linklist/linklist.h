//
// Created by cyc20 on 2017/11/20.
//

#ifndef LINKLIST_LINKLIST_H
#define LINKLIST_LINKLIST_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define ERROR 0
#define OK 1
#define OVERFLOW -2
typedef int Status;
typedef int ElemType;

typedef struct Node{
    ElemType data;
    struct Node *next;
}LNode;
typedef struct Node* LinkList;

Status InitList(LinkList&L);

Status DestoryList(LinkList&L);
//操作结果：构造一个空的线性表L。


Status ClearList(LinkList L);
//初始条件：线性表L已存在。
//操作结果：将L重置为空表。

bool ListEmpty(LinkList L);
//初始条件：线性表L已存在。
//操作结果：若L为空表，则返回TRUE，否则返回FALSE。

int ListLength(LinkList L);
//初始条件：线性表L已存在。
//操作结果：返回L中数据元素的个数。

Status GetElem(LinkList L, int i, ElemType &e);
//初始条件：线性表L已存在，1<=i<=ListLength(L)。
//操作结果：用e返回L中第i个数据元素的值。

int LocateElem(LinkList L, int e, bool(*equal)(ElemType, ElemType));
//初始条件：线性表L已存在，compare()是数据元素判定函数。
//返回L中第一个与e满足关系compare()的数据元素的位序。若这样的数据元素不存在，则返回值为0.

Status PriorElem(LinkList L, ElemType cur_e, ElemType &pre_e);
//初始条件：线性表L已存在。
//操作结果：若cur_e是L中的数据元素，且不是第一个，则用pre_e返回它的前驱，否则操作失败，pre_e无定义。

Status NextElem(LinkList L, ElemType cur_e, ElemType &next_e);
//初始条件：线性表L已存在。
//操作结果：若cur_e是L中的数据元素，且不是最后一个，则用next_e返回它的后继，否则操作失败，next_e无定义。

Status ListInsert(LinkList &L, int i, ElemType e);
//初始条件：线性表L已存在，1<=i<=ListLength(L)+1.
//操作结果：在L中第i个位置之前插入新的数据元素e，L的长度加1.

Status ListDelete(LinkList &L, int i, ElemType &e);
//初始条件：线性表L已存在且非空，1<=i<=ListLength(L).
//操作结果：删除L的第i个数据元素，并用e返回其值，L的长度减1.

Status ListTraverse(LinkList L, bool(*visit)(ElemType));
//初始条件：线性表L已存在
//操作结果：依次对L的每个元素调用函数visit().一旦visit()失败,则操作失败。
Status SaveToFile(LinkList L);
Status LoadFromFile(LinkList &L);

#endif //LINKLIST_LINKLIST_H
