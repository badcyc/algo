# define _CRT_SECURE_NO_WARNINGS
#include "linklist.h"

bool visit(ElemType a){
    printf("%d ", a);
    return true;
}
bool compare(ElemType a, ElemType b){
    return a == b;
}
int main(void){
    LinkList L=NULL;  int op = 1;
    ElemType e, cur_e, pri_e, next_e; int n; int i;
    while (op){
        system("cls");	printf("\n\n");
        printf("      Menu for Linear Table On Link Structure \n");
        printf("-------------------------------------------------\n");
        printf("    	  1. InitList        7. LocateElem\n");
        printf("    	  2. DestroyList     8. PriorElem\n");
        printf("    	  3. ClearList       9. NextElem \n");
        printf("    	  4. ListEmpty       10. ListInsert\n");
        printf("    	  5. ListLength      11. ListDelete\n");
        printf("    	  6. GetElem         12. ListTrabverse\n");
        printf("    	  13. SaveToFile  \n");
        printf("    	  0. Exit\n          ");
        printf("-------------------------------------------------\n");
        printf("    请选择你的操作[0~12]:");
        scanf("%d", &op);
        switch (op){
            case 1:
                //printf("\n----IntiaList功能待实现！\n");
                if (InitList(L) == OK) printf("线性表创建成功！\n");
                else printf("线性表创建失败！\n");
                //printf("插入20个随机数");
                //srand(6);
               // for(int i=1;i<20;i++){
                 //   ListInsert(L,1,i);
                //}
                LoadFromFile(L);
                //for (int j = 0; j < 5; j++){
                  //  ListInsert(L, 1, j);
                //}

                getchar(); getchar();
                break;
            case 2:
                DestoryList(L);
                printf("线性表已销毁！");
                getchar(); getchar();
                break;
            case 3:
                if (ClearList(L))
                printf("清空成功");
                getchar(); getchar();
                break;
            case 4:

                ListEmpty(L);
                getchar(); getchar();
                break;
            case 5:

                n = ListLength(L);
                printf("链表长度: %d", n);
                getchar(); getchar();
                break;
            case 6:
                printf("----请输入要查看的元素");
                scanf("%d", &i); getchar();
                while(!GetElem(L, i, e))
                {
                    printf("输入有误!请重新输入！按0退出！\n");
                    scanf("%d", &i); getchar();
                    if (i==0)
                    {
                        goto S;
                        break;

                    }
                }
                printf("该位置的元素是: %d", e);
            S:			getchar(); getchar();
                break;
            case 7:

                printf("请输入要查找的元素:");
                scanf("%d", &e); getchar();
                n = LocateElem(L, e, compare);
                if (n == 0){
                    printf("您查找的元素不存在！\n");
                }
                else printf("您查找的元素是链表的第 %d 个\n", n);
                getchar(); getchar();
                break;
            case 8:

                printf("输入要查找的元素:");
                scanf("%d", &cur_e); getchar();
                if (!PriorElem(L, cur_e, pri_e)){
                    printf("输入的元素不在序列里!\n");
                }
                else printf("此元素之前为: %d ", pri_e);
                getchar(); getchar();
                break;
            case 9:

                printf("输入要查找的元素:");
                scanf("%d", &cur_e); getchar();
                if (!NextElem(L, cur_e, next_e)){
                    printf("输入的元素不在序列里!\n");
                }
                else printf("此元素之后: %d \n", next_e);
                getchar(); getchar();
                break;
            case 10:

                printf("请输入要输入的元素和位置！\n");
                printf("1.请输入要插入的位置（之前）:");
                scanf("%d", &i); getchar();
                printf("2.请输入要插入的元素:");
                scanf("%d", &e); getchar();
                if(ListInsert(L, i, e))printf("插入成功!\n");
                getchar(); getchar();
                break;
            case 11:

                printf("输入要删除的元素的位置\n");
                scanf("%d", &i);
                if (ListDelete(L, i, e)) printf("删除的元素是%d", e);
                getchar(); getchar();
                break;
            case 12:

                if (!ListTraverse(L,visit)) printf("线性表是空表！\n");
                getchar(); getchar();
                break;
            case 13 :
                printf("向文件里写入数据！");
                SaveToFile(L);
                break;
            case 0:
                //ClearList(L);
                DestoryList(L);
                break;
        }//end of switch
    }//end of while
    printf("欢迎下次再使用本系统！\n任意键退出");
    getchar();
    getchar();
}//end of main()
/*--------page 23 on textbook --------------------*/
/*Status IntiaList(SqList & L){
	L.elem = (ElemType *)malloc(LIST_INIT_SIZE * sizeof(ElemType));
	if (!L.elem) exit(OVERFLOW);
	L.length = 0;
	L.listSize = LIST_INIT_SIZE;
	return OK;
}
Status ListTrabverse(SqList L){
	int i;
	printf("\n-----------all elements -----------------------\n");
	for (i = 0; i<L.length; i++) printf("%d ", L.elem[i]);
	printf("\n------------------ end ------------------------\n");
	return L.length;*/
