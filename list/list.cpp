#include "list.h"


Status InitList(SqList &l){
	l.elem = (ElemType*)malloc(LIST_INIT_SIZE*sizeof(ElemType));
	if (!l.elem)  exit(OVERFLOW);
	l.length = 0;
	l.listSize = LIST_INIT_SIZE;
	return OK;
}
Status DestroyList(SqList&l){
    free(l.elem);
    l.elem=NULL;
	return OK;
}
Status ClearList(SqList&l){
	l.length = 0;
	return OK;
}
bool ListEmpty(SqList l){
    if(!l.elem) {
            printf("请初始化!");
            return ERROR;
    }
	return l.length;
}
Status GetElem(SqList l, int i, ElemType &e){
    if(!l.elem) {
            printf("请初始化!");
            return ERROR;
    }
	if (i < 1 || i>l.length)return ERROR;
	e = l.elem[i - 1];
	return OK;
}
int LocateElem(SqList l, int e, bool(*equal)(ElemType, ElemType)){
    if(!l.elem) {
            printf("请初始化!");
            return ERROR;
    }
	int i = 1;
	while (i <= l.length&&!(equal(l.elem[i - 1], e)))
	{
		++i;
	}
	if (i <= l.length)return i;
	else return 0;
}
Status PriorElem(SqList l, ElemType cur_e, ElemType&pre_e){
    if(!l.elem) {
            printf("请初始化!");
            return ERROR;
    }
	int i = 1;
	while (i <= l.length&&l.elem[i - 1] != cur_e)
	{
		++i;
	}
	if (i>l.length || i<2)
	{
	    printf("not exist!");
		return ERROR;
	}
	pre_e = l.elem[i - 2];
	return OK;
}
Status NextElem(SqList l, ElemType cur_e, ElemType&next_e){
    if(!l.elem) {
            printf("请初始化!");
            return ERROR;
    }
	int i = 1;
	while (i <= l.length&&l.elem[i - 1] != cur_e){
		++i;
	}
	if (i>l.length - 1)
	{
	    printf("not exist!");
		return ERROR;
	}
	next_e = l.elem[i];
	return OK;
}
Status ListInsert(SqList &l, int i, ElemType e){
    if(!l.elem) {
            printf("请初始化!");
            return ERROR;
    }
	ElemType *p;
	ElemType *q;
	ElemType* newBase;
	if(i>l.length+1||i<1){
            printf("ERROR");
            return ERROR;
	}
	if (l.length >= l.listSize)
	{
		newBase = (ElemType*)realloc(l.elem, (l.listSize + LISTINCREMENT)*sizeof(ElemType));

		if (!newBase)
		{
			printf("内存已满!");
			return OVERFLOW;
		}
		l.elem = newBase;
		l.listSize += LISTINCREMENT;
	}
	q = &(l.elem[i - 1]);
	for (p = &(l.elem[l.length-1]); p >=q; --p)
	{
		*(p + 1) = *p;
	}
	if(l.length==0) *q=e;
	*(p+1) = e;
	++l.length;
	return OK;
}
Status ListDelete(SqList &l, int i, ElemType&e){
    if(!l.elem) {
            printf("请初始化!");
            return ERROR;
    }
	if (i<1 || i>l.length)
	{
	    printf("ERROR!");
		return ERROR;
	}
	ElemType *q, *p;
	q = &l.elem[l.length - 1];
	for (p = &(l.elem[i - 1]), e = *p, ++p; p <= q; p++)
	{
		*(p - 1) = *p;
	}
	--l.length;
	return OK;
}
Status ListTraverse(SqList L, bool(*visit)(ElemType)){
    if(!L.elem) {
            printf("请初始化!");
            return ERROR;
    }
	int i = 1;
	while (i <= L.length && (visit(L.elem[i - 1])))
	{
		++i;
	}
	return OK;
}
int ListLength(SqList L){
    if(!L.elem) {
            printf("请初始化!");
            return ERROR;
    }
	return L.length;
}
Status SaveToFile(SqList L){
    FILE  *fp;
   if ((fp=fopen("test.txt","w+"))==NULL)
	{
	 printf("File open erroe\n ");
	return 1;
	}
   fwrite(L.elem,sizeof(ElemType),L.length,fp);
   fclose(fp);//释放指针，防止内存泄漏
}
Status LoadFromFile(SqList &l){
    FILE  *fp;
    l.length=0;
    if ((fp=fopen("test.txt","r"))==NULL)
	{
	 printf("File open error\n ");
	 return 1;
	}
    while(fread(&(l.elem[l.length]),sizeof(ElemType),1,fp))
    {
        l.length++;
    }
//这里从文件中逐个读取数据元素恢复顺序表，对于不同的物理结构，可通过读//取的数据元素恢复内存中的物理结构。
    fclose(fp);//释放指针，防止内存泄漏

}
