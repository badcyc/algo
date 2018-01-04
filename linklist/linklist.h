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
//�������������һ���յ����Ա�L��


Status ClearList(LinkList L);
//��ʼ���������Ա�L�Ѵ��ڡ�
//�����������L����Ϊ�ձ�

bool ListEmpty(LinkList L);
//��ʼ���������Ա�L�Ѵ��ڡ�
//�����������LΪ�ձ��򷵻�TRUE�����򷵻�FALSE��

int ListLength(LinkList L);
//��ʼ���������Ա�L�Ѵ��ڡ�
//�������������L������Ԫ�صĸ�����

Status GetElem(LinkList L, int i, ElemType &e);
//��ʼ���������Ա�L�Ѵ��ڣ�1<=i<=ListLength(L)��
//�����������e����L�е�i������Ԫ�ص�ֵ��

int LocateElem(LinkList L, int e, bool(*equal)(ElemType, ElemType));
//��ʼ���������Ա�L�Ѵ��ڣ�compare()������Ԫ���ж�������
//����L�е�һ����e�����ϵcompare()������Ԫ�ص�λ��������������Ԫ�ز����ڣ��򷵻�ֵΪ0.

Status PriorElem(LinkList L, ElemType cur_e, ElemType &pre_e);
//��ʼ���������Ա�L�Ѵ��ڡ�
//�����������cur_e��L�е�����Ԫ�أ��Ҳ��ǵ�һ��������pre_e��������ǰ�����������ʧ�ܣ�pre_e�޶��塣

Status NextElem(LinkList L, ElemType cur_e, ElemType &next_e);
//��ʼ���������Ա�L�Ѵ��ڡ�
//�����������cur_e��L�е�����Ԫ�أ��Ҳ������һ��������next_e�������ĺ�̣��������ʧ�ܣ�next_e�޶��塣

Status ListInsert(LinkList &L, int i, ElemType e);
//��ʼ���������Ա�L�Ѵ��ڣ�1<=i<=ListLength(L)+1.
//�����������L�е�i��λ��֮ǰ�����µ�����Ԫ��e��L�ĳ��ȼ�1.

Status ListDelete(LinkList &L, int i, ElemType &e);
//��ʼ���������Ա�L�Ѵ����ҷǿգ�1<=i<=ListLength(L).
//���������ɾ��L�ĵ�i������Ԫ�أ�����e������ֵ��L�ĳ��ȼ�1.

Status ListTraverse(LinkList L, bool(*visit)(ElemType));
//��ʼ���������Ա�L�Ѵ���
//������������ζ�L��ÿ��Ԫ�ص��ú���visit().һ��visit()ʧ��,�����ʧ�ܡ�
Status SaveToFile(LinkList L);
Status LoadFromFile(LinkList &L);

#endif //LINKLIST_LINKLIST_H
