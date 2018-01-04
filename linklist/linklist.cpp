//
// Created by cyc20 on 2017/11/20.
//

#include "linklist.h"

Status InitList(LinkList&L){// �������������һ���յ����Ա�L
    L=(LinkList) malloc(sizeof(LNode));  // ����ͷ���,��ʹLָ���ͷ���
    if (!L){           //�洢����ʧ��
        printf("�����ڴ�ʧ��");
        return OVERFLOW;
    }
    L->next=NULL;
    return OK;
}
Status DestoryList(LinkList&L){ // ��ʼ���������Ա�L�Ѵ��ڡ�����������������Ա�L
    if (!L){
        printf("��������");
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
Status ClearList(LinkList L){ //���ı�L
    // ��ʼ���������Ա�L�Ѵ��ڡ������������L����Ϊ�ձ�
    if(!L){
        printf("�ñ����ڣ������³�ʼ��");
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
bool ListEmpty(LinkList L){ // ��ʼ���������Ա�L�Ѵ��ڡ������������LΪ�ձ��򷵻�TRUE�����򷵻�
    if(!L){
        printf("�ñ����ڣ������³�ʼ��");
        return ERROR;
    }
    if (L->next){
        printf("�ñ��ǿձ�");
        return FALSE;
    } else 
{
printf("�ñ��ǿձ�");
return TRUE;
}
}
int ListLength(LinkList L){
    // ��ʼ���������Ա�L�Ѵ��ڡ��������������L������Ԫ�ظ���
    if(!L){
        printf("�ñ����ڣ������³�ʼ��");
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
{  // LΪ��ͷ���ĵ������ͷָ�롣����i��Ԫ�ش���ʱ,��ֵ����e������OK,���򷵻�ERROR
    if(!L){
        printf("�ñ����ڣ������³�ʼ��");
        return ERROR;
    }
    int j=1;  //������
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
    // ��ʼ����: ���Ա�L�Ѵ���,equal������Ԫ���ж�����(����Ϊ1,����Ϊ0)
    // �������: ����L�е�1����e�����ϵequal()������Ԫ�ص�λ��
    //           ������������Ԫ�ز�����,�򷵻�ֵΪ0
    if(!L){
        printf("�ñ����ڣ������³�ʼ��");
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
    // ��ʼ����: ���Ա�L�Ѵ���
    // �������: ��cur_e��L������Ԫ��,�Ҳ��ǵ�һ��,����pre_e��������ǰ��,
    //           ����OK;�������ʧ��,pre_e�޶���,����FALSE.

    if(!L){
        printf("�ñ����ڣ������³�ʼ��");
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
    printf("�Ҳ�����");
    return FALSE;
}
Status NextElem(LinkList L, ElemType cur_e, ElemType &next_e){
    // ��ʼ���������Ա�L�Ѵ���
    // �����������cur_e��L������Ԫ�أ��Ҳ������һ��������next_e�������ĺ�̣�
    //           ����OK;�������ʧ�ܣ�next_e�޶��壬����INFEASIBLE
    if(!L){
        printf("�ñ����ڣ������³�ʼ��");
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
    printf("�Ҳ���!");
    return FALSE;
}
Status ListInsert(LinkList &L, int i, ElemType e){
    if(!L){
        printf("�ñ����ڣ������³�ʼ��");
        return ERROR;
    }
    LinkList q,p=L;
    if(i==0){
        printf("����λ������");
        return ERROR;
    }
    int j=0;
    while (p&&j<i-1){
        j++;
        if (p->next){
            p=p->next;
        } else{
            printf("����λ������");
            return ERROR;
        }

    }
    if (!p&&j>i-1){
        printf("����λ������");
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
        printf("�ñ����ڣ������³�ʼ��");
        return ERROR;
    }
    int j=0;
    LinkList p=L,q;
    while(p->next&&j<i-1) // Ѱ�ҵ�i�����,����pָ����ǰ��
    {
        j++;
        if (p->next){
            p=p->next;
        } else{
            printf("ɾ��λ������");
            return ERROR;
        }

    }
    if(!p->next||j>i-1) // ɾ��λ�ò�����
    {
        printf("ɾ��λ������");
        return ERROR;
    }

    q=p->next; // ɾ�����ͷŽ��
    p->next=q->next;
    e=q->data;
    free(q);
    return OK;

}
Status ListTraverse(LinkList L, bool(*visit)(ElemType)){
    // ��ʼ���������Ա�L�Ѵ���
    // �������:���ζ�L��ÿ������Ԫ�ص��ú���vi()��һ��vi()ʧ��,�����ʧ��
    if (!L){
        printf("�ñ����ڣ������³�ʼ��");
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
    fclose(fp);//�ͷ�ָ�룬��ֹ�ڴ�й©
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
//������ļ��������ȡ����Ԫ�ػָ�˳������ڲ�ͬ������ṹ����ͨ����//ȡ������Ԫ�ػָ��ڴ��е�����ṹ��
    fclose(fp);//�ͷ�ָ�룬��ֹ�ڴ�й©

}