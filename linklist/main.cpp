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
        printf("    ��ѡ����Ĳ���[0~12]:");
        scanf("%d", &op);
        switch (op){
            case 1:
                //printf("\n----IntiaList���ܴ�ʵ�֣�\n");
                if (InitList(L) == OK) printf("���Ա����ɹ���\n");
                else printf("���Ա���ʧ�ܣ�\n");
                //printf("����20�������");
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
                printf("���Ա������٣�");
                getchar(); getchar();
                break;
            case 3:
                if (ClearList(L))
                printf("��ճɹ�");
                getchar(); getchar();
                break;
            case 4:

                ListEmpty(L);
                getchar(); getchar();
                break;
            case 5:

                n = ListLength(L);
                printf("������: %d", n);
                getchar(); getchar();
                break;
            case 6:
                printf("----������Ҫ�鿴��Ԫ��");
                scanf("%d", &i); getchar();
                while(!GetElem(L, i, e))
                {
                    printf("��������!���������룡��0�˳���\n");
                    scanf("%d", &i); getchar();
                    if (i==0)
                    {
                        goto S;
                        break;

                    }
                }
                printf("��λ�õ�Ԫ����: %d", e);
            S:			getchar(); getchar();
                break;
            case 7:

                printf("������Ҫ���ҵ�Ԫ��:");
                scanf("%d", &e); getchar();
                n = LocateElem(L, e, compare);
                if (n == 0){
                    printf("�����ҵ�Ԫ�ز����ڣ�\n");
                }
                else printf("�����ҵ�Ԫ��������ĵ� %d ��\n", n);
                getchar(); getchar();
                break;
            case 8:

                printf("����Ҫ���ҵ�Ԫ��:");
                scanf("%d", &cur_e); getchar();
                if (!PriorElem(L, cur_e, pri_e)){
                    printf("�����Ԫ�ز���������!\n");
                }
                else printf("��Ԫ��֮ǰΪ: %d ", pri_e);
                getchar(); getchar();
                break;
            case 9:

                printf("����Ҫ���ҵ�Ԫ��:");
                scanf("%d", &cur_e); getchar();
                if (!NextElem(L, cur_e, next_e)){
                    printf("�����Ԫ�ز���������!\n");
                }
                else printf("��Ԫ��֮��: %d \n", next_e);
                getchar(); getchar();
                break;
            case 10:

                printf("������Ҫ�����Ԫ�غ�λ�ã�\n");
                printf("1.������Ҫ�����λ�ã�֮ǰ��:");
                scanf("%d", &i); getchar();
                printf("2.������Ҫ�����Ԫ��:");
                scanf("%d", &e); getchar();
                if(ListInsert(L, i, e))printf("����ɹ�!\n");
                getchar(); getchar();
                break;
            case 11:

                printf("����Ҫɾ����Ԫ�ص�λ��\n");
                scanf("%d", &i);
                if (ListDelete(L, i, e)) printf("ɾ����Ԫ����%d", e);
                getchar(); getchar();
                break;
            case 12:

                if (!ListTraverse(L,visit)) printf("���Ա��ǿձ�\n");
                getchar(); getchar();
                break;
            case 13 :
                printf("���ļ���д�����ݣ�");
                SaveToFile(L);
                break;
            case 0:
                //ClearList(L);
                DestoryList(L);
                break;
        }//end of switch
    }//end of while
    printf("��ӭ�´���ʹ�ñ�ϵͳ��\n������˳�");
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
