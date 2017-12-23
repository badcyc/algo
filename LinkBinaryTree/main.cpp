#include <iostream>
#include "binarytree.h"

Status visit(TNodeKey key, TElemType data) {
    printf("keyΪ%d ,valueΪ:%c \n", key, data);
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
        printf("    ��ѡ����Ĳ���[0~20]:");
        scanf("%d", &op);
        getchar();
        switch (op) {
            case 1:
                InitBiTree(T);
                printf("��ʼ�����");
                getchar();
                break;
            case 2:
                DestroyBiTree(T);
                printf("���ٳɹ�");
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
                printf("�������Ϊ%d", depth);
                getchar();
                getchar();
                break;
            case 7:
                root = Root(T);
                printf("���root����Ϣ:\n");
                printf("keyֵΪ%d\nvalueΪ%c\n", root.key, root.data);
                getchar();
                getchar();
                break;
            case 8:
                printf("������ҪѰ�ҵ�key\n");
                scanf("%d", &keyForFind);
                getchar();
                Value(T, keyForFind, e);
                printf("keyΪ%d ,valueΪ%c \n", keyForFind, e);
                getchar();
                getchar();
                break;
            case 9:
                printf("��ܰ��ʾ�˷����ı�����ֵ\n");
                printf("������Ҫ�ı�ǰ��ֵ��");
                scanf("%c", &e);getchar();
                printf("������Ҫ�ı���ֵ��");
                scanf("%c", &value);

                Assign(T, e, value);

                printf("�ı�ɹ�");
                getchar();
                getchar();
                break;
            case 10:
                printf("������Ҫ���ҵ�ֵ");
                scanf("%c", &e);
                parent = Parent(T, e);
                if (parent) {
                    printf("���parent����Ϣ:\n");
                    printf("parent��keyΪ��%d\nparent��valueΪ%c\n", parent->key, parent->data);
                }
                getchar();
                getchar();
                break;
            case 11:
                printf("������Ҫ���ҵ�ֵ");
                scanf("%c", &e);
                leftChild = LeftChild(T, e);
                if (leftChild) {
                    printf("���LeftChild����Ϣ:\n");
                    printf("LeftChild��keyΪ��%d\nLeftChild��valueΪ%c\n", leftChild->key, leftChild->data);
                }
                getchar();
                getchar();
                break;
            case 12:
                printf("������Ҫ���ҵ�ֵ");
                scanf("%c", &e);
                rightChild = RightChild(T, e);
                if (rightChild) {
                    printf("���RightChild����Ϣ:\n");
                    printf("RightChild��keyΪ��%d\nRightChild��valueΪ%c\n", rightChild->key, rightChild->data);
                }
                getchar();
                getchar();
                break;
            case 15:
                printf("��Ҫ����ڵ��value��");
                scanf("%c", &e);
                printf("�����������������0��������������1��:");
                scanf("%d", &LR);
                getchar();
                InsertChild(T, e, LR);
                getchar();
                break;
            case 13:
                printf("������Ҫ���ҵ�ֵ");
                scanf("%c", &e);
                leftSibling = LeftSibling(T, e);
                if (leftSibling) {
                    printf("���leftSibling����Ϣ:\n");
                    printf("leftSibling��keyΪ��%d\nleftSibling��valueΪ%c\n", leftSibling->key, leftSibling->data);
                }
                getchar();
                getchar();
                break;
            case 14:
                printf("������Ҫ���ҵ�ֵ");
                scanf("%c", &e);
                rightSibling = Rightsibling(T, e);
                if (rightSibling) {
                    printf("���rightSibling����Ϣ:\n");
                    printf("rightSibling��keyΪ��%d\nrightSibling��valueΪ%c\n", rightSibling->key, rightSibling->data);
                }
                getchar();
                getchar();
                break;
            case 16:
                printf("������Ҫɾ���ڵ��value: ");
                scanf("%c", &e);
                getchar();
                printf("�����������������0��������������1��:");
                scanf("%d",&LR);getchar();
                DeleteChild(T, e, LR);
                printf("ɾ�������ɹ�");
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
    printf("��ӭ�´���ʹ�ñ�ϵͳ��\n");
    return 0;
}//end of main()
