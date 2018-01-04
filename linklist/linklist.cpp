//
// Created by cyc20 on 2017/11/20.
//

#include "linklist.h"

Status InitList(LinkList&L){// 操作结果：构造一个空的线性表L
    L=(LinkList) malloc(sizeof(LNode));  // 产生头结点,并使L指向此头结点
    if (!L){           //存储分配失败
        printf("分配内存失败");
        return OVERFLOW;
    }
    L->next=NULL;
    return OK;
}
Status DestoryList(LinkList&L){ // 初始条件：线性表L已存在。操作结果：销毁线性表L
    if (!L){
        printf("链表不存在");
        return ERROR;
    }
    LinkList q;
    while(L){
        q=L->next;
        free(L);
        L=q;
    }
    return OK;

}
Status ClearList(LinkList L){ //不改变L
    // 初始条件：线性表L已存在。操作结果：将L重置为空表
    if(!L){
        printf("该表不存在，请重新初始化");
        return ERROR;
    }
    LinkList p,q;
    p=L->next;
    while (p){
        q=p->next;
        free(p);
        p=q;
    }
    L->next=NULL;
    return OK;
}
bool ListEmpty(LinkList L){ // 初始条件：线性表L已存在。操作结果：若L为空表，则返回TRUE，否则返回
    if(!L){
        printf("该表不存在，请重新初始化");
        return ERROR;
    }
    if (L->next){
        printf("该表不是空表");
        return FALSE;
    } else 
{
printf("该表是空表");
return TRUE;
}
}
int ListLength(LinkList L){
    // 初始条件：线性表L已存在。操作结果：返回L中数据元素个数
    if(!L){
        printf("该表不存在，请重新初始化");
        return ERROR;
    }
    LinkList p=L->next;
    int i=0;
    while (p){
        i++;
        p=p->next;
    }
    return i;
}
Status GetElem(LinkList L, int i, ElemType &e)
{  // L为带头结点的单链表的头指针。当第i个元素存在时,其值赋给e并返回OK,否则返回ERROR
    if(!L){
        printf("该表不存在，请重新初始化");
        return ERROR;
    }
    int j=1;  //计数器
    LinkList p=L->next;
    while (p&&j<i){
        p=p->next;
        j++;
    }
    if (!p||j>i)
        return ERROR;
    e=p->data;
    return OK;
}
int LocateElem(LinkList L, int e, bool(*equal)(ElemType, ElemType)){
    // 初始条件: 线性表L已存在,equal是数据元素判定函数(满足为1,否则为0)
    // 操作结果: 返回L中第1个与e满足关系equal()的数据元素的位序。
    //           若这样的数据元素不存在,则返回值为0
    if(!L){
        printf("该表不存在，请重新初始化");
        return ERROR;
    }
    LinkList p=L->next;
    int j=0;
    while (p){
        j++;
        if (equal(p->data,e)){ return j;}
        p=p->next;
    }
    return FALSE;
}
Status PriorElem(LinkList L, ElemType cur_e, ElemType &pre_e){
    // 初始条件: 线性表L已存在
    // 操作结果: 若cur_e是L的数据元素,且不是第一个,则用pre_e返回它的前驱,
    //           返回OK;否则操作失败,pre_e无定义,返回FALSE.

    if(!L){
        printf("该表不存在，请重新初始化");
        return ERROR;
    }
    LinkList q,p=L->next;
    while (p->next){
        q=p->next;
        if (q->data==cur_e){
            pre_e=p->data;
            return OK;
        }
        p=q;
    }
    printf("找不到！");
    return FALSE;
}
Status NextElem(LinkList L, ElemType cur_e, ElemType &next_e){
    // 初始条件：线性表L已存在
    // 操作结果：若cur_e是L的数据元素，且不是最后一个，则用next_e返回它的后继，
    //           返回OK;否则操作失败，next_e无定义，返回INFEASIBLE
    if(!L){
        printf("该表不存在，请重新初始化");
        return ERROR;
    }
    LinkList p=L->next;
    while (p->next){
        if (p->data==cur_e){
            next_e=p->next->data;
            return OK;
        }
        p=p->next;
    }
    printf("找不到!");
    return FALSE;
}
Status ListInsert(LinkList &L, int i, ElemType e){
    if(!L){
        printf("该表不存在，请重新初始化");
        return ERROR;
    }
    LinkList q,p=L;
    if(i==0){
        printf("插入位置有误");
        return ERROR;
    }
    int j=0;
    while (p&&j<i-1){
        j++;
        if (p->next){
            p=p->next;
        } else{
            printf("插入位置有误");
            return ERROR;
        }

    }
    if (!p&&j>i-1){
        printf("插入位置有误");
        return ERROR;
    }
    q=(LinkList)malloc(sizeof(LNode));
    q->data=e;
    q->next=p->next;
    p->next=q;
    return OK;
}
Status ListDelete(LinkList &L, int i, ElemType &e){
    if(!L){
        printf("该表不存在，请重新初始化");
        return ERROR;
    }
    int j=0;
    LinkList p=L,q;
    while(p->next&&j<i-1) // 寻找第i个结点,并令p指向其前趋
    {
        j++;
        if (p->next){
            p=p->next;
        } else{
            printf("删除位置有误");
            return ERROR;
        }

    }
    if(!p->next||j>i-1) // 删除位置不合理
    {
        printf("删除位置有误");
        return ERROR;
    }

    q=p->next; // 删除并释放结点
    p->next=q->next;
    e=q->data;
    free(q);
    return OK;

}
Status ListTraverse(LinkList L, bool(*visit)(ElemType)){
    // 初始条件：线性表L已存在
    // 操作结果:依次对L的每个数据元素调用函数vi()。一旦vi()失败,则操作失败
    if (!L){
        printf("该表不存在，请重新初始化");
        return ERROR;
    }
    LinkList p=L->next;
    while (p&&visit(p->data)){
        p=p->next;
    }
    return OK;

}
Status SaveToFile(LinkList L){
    if (!L){

        return ERROR;
    }
    FILE  *fp;LinkList p=L->next;
    if ((fp=fopen("test.txt","w+"))==NULL)
    {
        printf("File open erroe\n ");
        return 1;
    }
    while (p) {
        ElemType * i=&(p->data);
        fwrite(i,sizeof(ElemType), 1, fp);
        p=p->next;
    }
    fclose(fp);//释放指针，防止内存泄漏
}
Status LoadFromFile(LinkList &L){
    FILE  *fp;
    if ((fp=fopen("test.txt","r"))==NULL)
    {
        printf("File open error\n ");
        return 1;
    }
    ElemType e;
    int length=ListLength(L);
    while(fread(&e,sizeof(ElemType),1,fp))
    {
        ListInsert(L,++length,e);
    }
//这里从文件中逐个读取数据元素恢复顺序表，对于不同的物理结构，可通过读//取的数据元素恢复内存中的物理结构。
    fclose(fp);//释放指针，防止内存泄漏

}