#include <iostream>
#include "graph.h"
Status equal(VertexType v){
    printf("%c ",v);
    return OK;
}
int main() {
    AMLGraph G;
    int op = 1;
    int locate;

    VertexType v,value;
    while (op) {
        system("cls");
        printf("\n\n");
        printf("       Menu for The graph of the adjacency list \n\n");
        printf("-------------------------------------------------\n");
        printf("    	1. CreateCraph        2. DestroyCraph\n");
        printf("    	3. LocateVex          4. GetVex \n");
        printf("        5. PutVex             6. FirstAdjVex\n");
        printf("        7. NextAdjVex         8. InsertVex\n");
        printf("    	9. DeleteVex          10.InsertArc\n");
        printf("    	11.DeleteArc          12.DFSTraverse \n");
        printf("    	13.BFSTraverse        0. Exit\n");
        printf("-------------------------------------------------\n");
        printf("    ��ѡ����Ĳ���[0~13]:");
        scanf("%d%*c", &op);
        switch (op) {
            case 1:
                CreateGraph(G);
                getchar();
                getchar();
                break;
            case 2:
                DestroyGraph(G);
                printf("���ٳɹ�");
                getchar();
                getchar();
                break;
            case 3:
                printf("��������Ҫ���ҵĽڵ�ֵ(char��)");
                scanf("%c", &v);
                locate = LocateVex(G, v);
                if (locate < 0) {
                    printf("û���ҵ�");
                } else {
                    printf("��Ϊ����ʱ�ĵ�%d��", locate);
                }
                getchar();
                getchar();
                break;
            case 4:
                printf("������v��ֵ��0=<v<%d��:", G.vexnum);
                scanf("%d", &locate);
                v = GetVex(G, locate);
                printf("%c", v);
                getchar();
                getchar();
                break;
            case 5:
                printf("��������Ҫ�޸�ǰ��ֵ��");
                scanf("%c",&v);getchar();
                printf("��������Ҫ�޸ĺ��ֵ��");
                scanf("%c",&value);getchar();
                locate=PutVex(G,v,value);
                if (locate==OK){
                    printf("�޸ĳɹ�");
                }
                getchar();
                getchar();
                break;
            case 6:

                break;
            case 7:
                break;
            case 8:
                break;
            case 9:
                break;
            case 10:
                break;
            case 11:
                break;
            case 12:
                printf("�������Ϊ��");
                DFSTraverse(G,equal);
                getchar();
                getchar();
                break;
            case 13:
                break;
            case 0:
                break;
        }//end of switch
    }//end of while
    printf("    ��ӭ�´���ʹ�ñ�ϵͳ��\n");
    return 0;
}//end of main()

