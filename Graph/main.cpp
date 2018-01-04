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
        printf("    请选择你的操作[0~13]:");
        scanf("%d%*c", &op);
        switch (op) {
            case 1:
                CreateGraph(G);
                getchar();
                getchar();
                break;
            case 2:
                DestroyGraph(G);
                printf("销毁成功");
                getchar();
                getchar();
                break;
            case 3:
                printf("请输入你要查找的节点值(char型)");
                scanf("%c", &v);
                locate = LocateVex(G, v);
                if (locate < 0) {
                    printf("没有找到");
                } else {
                    printf("此为创建时的第%d个", locate);
                }
                getchar();
                getchar();
                break;
            case 4:
                printf("请输入v的值（0=<v<%d）:", G.vexnum);
                scanf("%d", &locate);
                v = GetVex(G, locate);
                printf("%c", v);
                getchar();
                getchar();
                break;
            case 5:
                printf("请输入你要修改前的值：");
                scanf("%c",&v);getchar();
                printf("请输入你要修改后的值：");
                scanf("%c",&value);getchar();
                locate=PutVex(G,v,value);
                if (locate==OK){
                    printf("修改成功");
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
                printf("遍历结果为：");
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
    printf("    欢迎下次再使用本系统！\n");
    return 0;
}//end of main()

