#include <iostream>
#include "binarytree.h"

Status visit(TNodeKey key, TElemType data) {
    printf("key为%d ,value为:%c \n", key, data);
    return OK;
}

int main() {

    int keyForFind;
    TElemType e;
    TElemType value;
    BiTreeNode root;
    BiTree parent;
    BiTree leftChild;
    BiTree rightChild;
    BiTree leftSibling;
    BiTree rightSibling;
    BiTree p;
    Status LR;
    BiTree c;
    int op = 1;
    BiTree T=NULL;


    int depth;
    while (op) {
        system("cls");
        printf("\n\n");
        printf("                  Menu for Binary Tree \n");
        printf("-------------------------------------------------\n");
        printf("    	  1.InitBiTree          2.DestroyBiTree\n");
        printf("    	  3.CreateBiTree        4.ClearBiTree\n");
        printf("    	  5.BiTreeEmpty         6.BiTreeDepth\n");
        printf("    	  7.Root                8.Value\n");
        printf("    	  9.Assign              10.Parent\n");
        printf("    	  11.LeftChild          12.RightChild\n");
        printf("          13.LeftSibling        14.RightSibling\n");
        printf("          15.InsertChild        16.DeleteChild\n");
        printf("          17.PreOrderTraverse   18.InorderTraverse\n");
        printf("          19.PostOrderTraverse  20.LevelOrderTraverse\n");
        printf("    	  0. Exit\n");
        printf("-------------------------------------------------\n");
        printf("    请选择你的操作[0~20]:");
        scanf("%d", &op);
        getchar();
        switch (op) {
            case 1:
                InitBiTree(T);
                printf("初始化完毕");
                getchar();
                break;
            case 2:
                DestroyBiTree(T);
                printf("销毁成功");
                getchar();
                getchar();
                break;
            case 3:
                CreateBiTree(T, autokey);
                getchar();
                getchar();
                break;
            case 4:
                ClearBiTree(T);
                getchar();
                getchar();
                break;
            case 5:
                BiTreeEmpty(T);
                getchar();
                getchar();

                break;
            case 6:
                depth = BiTreeDepth(T);
                printf("树的深度为%d", depth);
                getchar();
                getchar();
                break;
            case 7:
                root = Root(T);
                printf("输出root的信息:\n");
                printf("key值为%d\nvalue为%c\n", root.key, root.data);
                getchar();
                getchar();
                break;
            case 8:
                printf("请输入要寻找的key\n");
                scanf("%d", &keyForFind);
                getchar();
                Value(T, keyForFind, e);
                printf("key为%d ,value为%c \n", keyForFind, e);
                getchar();
                getchar();
                break;
            case 9:
                printf("温馨提示此方法改变所有值\n");
                printf("输入你要改变前的值：");
                scanf("%c", &e);getchar();
                printf("输入你要改变后的值：");
                scanf("%c", &value);

                Assign(T, e, value);

                printf("改变成功");
                getchar();
                getchar();
                break;
            case 10:
                printf("输入你要查找的值");
                scanf("%c", &e);
                parent = Parent(T, e);
                if (parent) {
                    printf("输出parent的信息:\n");
                    printf("parent的key为：%d\nparent的value为%c\n", parent->key, parent->data);
                }
                getchar();
                getchar();
                break;
            case 11:
                printf("输入你要查找的值");
                scanf("%c", &e);
                leftChild = LeftChild(T, e);
                if (leftChild) {
                    printf("输出LeftChild的信息:\n");
                    printf("LeftChild的key为：%d\nLeftChild的value为%c\n", leftChild->key, leftChild->data);
                }
                getchar();
                getchar();
                break;
            case 12:
                printf("输入你要查找的值");
                scanf("%c", &e);
                rightChild = RightChild(T, e);
                if (rightChild) {
                    printf("输出RightChild的信息:\n");
                    printf("RightChild的key为：%d\nRightChild的value为%c\n", rightChild->key, rightChild->data);
                }
                getchar();
                getchar();
                break;
            case 15:
                printf("你要插入节点的value：");
                scanf("%c", &e);
                printf("请输入插入左子树（0）还是右子树（1）:");
                scanf("%d", &LR);
                getchar();
                InsertChild(T, e, LR);
                getchar();
                break;
            case 13:
                printf("输入你要查找的值");
                scanf("%c", &e);
                leftSibling = LeftSibling(T, e);
                if (leftSibling) {
                    printf("输出leftSibling的信息:\n");
                    printf("leftSibling的key为：%d\nleftSibling的value为%c\n", leftSibling->key, leftSibling->data);
                }
                getchar();
                getchar();
                break;
            case 14:
                printf("输入你要查找的值");
                scanf("%c", &e);
                rightSibling = Rightsibling(T, e);
                if (rightSibling) {
                    printf("输出rightSibling的信息:\n");
                    printf("rightSibling的key为：%d\nrightSibling的value为%c\n", rightSibling->key, rightSibling->data);
                }
                getchar();
                getchar();
                break;
            case 16:
                printf("输入你要删除节点的value: ");
                scanf("%c", &e);
                getchar();
                printf("请输入插入左子树（0）还是右子树（1）:");
                scanf("%d",&LR);getchar();
                DeleteChild(T, e, LR);
                printf("删除子树成功");
                getchar();
                break;
            case 17:
                PreOrderTraverse(T, visit);
                getchar();
                getchar();
                break;
            case 18:
                InOrderTraverse(T, visit);
                getchar();
                getchar();
                break;
            case 19:
                PostOrderTraverse(T, visit);
                getchar();
                getchar();
                break;
            case 20:
                LevelOrderTraverse(T, visit);
                getchar();
                getchar();
                break;
            case 0:
                break;
        }//end of switch
    }//end of while
    printf("欢迎下次再使用本系统！\n");
    return 0;
}//end of main()
