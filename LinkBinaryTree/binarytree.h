//
// Created by cyc20 on 2017/12/20.
//

#ifndef LINKBINARYTREE_BINARYTREE_H
#define LINKBINARYTREE_BINARYTREE_H

#include "stdio.h"
#include "stdlib.h"

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASTABLE -1
#define OVERFLOW -2

typedef char TElemType;
typedef int TNodeKey;
typedef int Status;
typedef struct BiTreeNode {
    TNodeKey key;
    TElemType data;
    BiTreeNode *lchild, *rchild;
} BiTreeNode, *BiTree;

static int autokey = 1;

Status InitBiTree(BiTree &T);

Status DestroyBiTree(BiTree &T);

Status CreateBiTree(BiTree &T, int key);

Status ClearBiTree(BiTree &T);

Status BiTreeEmpty(BiTree T);

int BiTreeDepth(BiTree T);

BiTreeNode Root(BiTree T);

Status Value(BiTree T, int key, TElemType &e);

Status Assign(BiTree &T, TElemType e, TElemType value);

BiTree Parent(BiTree T, TElemType e);

BiTree LeftChild(BiTree T, TElemType e);

BiTree RightChild(BiTree T, TElemType e);

BiTree LeftSibling(BiTree T, TElemType e);

BiTree Rightsibling(BiTree T, TElemType e);

Status InsertChild(BiTree &T, TElemType p, Status LR);

Status DeleteChild(BiTree &T, TElemType p, Status LR);

Status PreOrderTraverse(BiTree T, Status (*visit)(int ,TElemType));

Status InOrderTraverse(BiTree T, Status (*visit)(int ,TElemType));

Status PostOrderTraverse(BiTree T, Status (*visit)(int ,TElemType));

Status LevelOrderTraverse(BiTree T, Status (*visit)(int ,TElemType));

#endif //LINKBINARYTREE_BINARYTREE_H
