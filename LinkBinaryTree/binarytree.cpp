//
// Created by cyc20 on 2017/12/20.
//
#include "binarytree.h"
#include "Queue.h"
#include "string.h"

/**
 * ��ʼ��������
 * @param T
 * @return
 */


Status InitBiTree(BiTree &T) {
    T = NULL;
    return OK;
}

/**
 * ����һ��������
 * @param T
 * @return
 */
Status DestroyBiTree(BiTree &T) {
    autokey=0;
    if (T) {
        if (T->lchild)
            DestroyBiTree(T->lchild);
        else
            DestroyBiTree(T->rchild);
        free(T);
        T = NULL;
    }
    return OK;
}

/**
 * ����������
 * @param T
 * @return
 */
Status CreateBiTree(BiTree &T, TNodeKey key) {
    TElemType data;
    printf("keyΪ%d :", autokey);
    printf("����value :");
    scanf("%c", &data);
    getchar();
    if (data == '#') {
        T = NULL;
        autokey--;
        return OK;
    } else {
        T = (BiTree) malloc(sizeof(BiTreeNode));
        if (!T)
            return OVERFLOW;
        T->key = key;
        T->data = data;
        CreateBiTree(T->lchild, ++autokey);
        CreateBiTree(T->rchild, ++autokey);
    }
    return OK;
}

/**
 *
 * @param T
 * @return
 */
Status ClearBiTree(BiTree &T) {
    if (T) {
        if (T->lchild)
            ClearBiTree(T->lchild);
        else
            ClearBiTree(T->rchild);
        free(T);
        T = NULL;
    } else {
        printf("������");
        return OK;
    }
    return OK;
}

/**
 * �ж϶������Ƿ�Ϊ��
 * @param T
 * @return
 */

Status BiTreeEmpty(BiTree T) {
    if (T) {
        printf("���ǿն�����");
        return FALSE;
    } else {
        printf("�ǿն�����");
        return TRUE;
    }
}

/**
 * �ݹ��������������
 * @param T
 * @return
 */
int BiTreeDepth(BiTree T) {
    if (T == NULL) {
        return 0;
    }
    int ldepth = BiTreeDepth(T->lchild);
    int rdepth = BiTreeDepth(T->rchild);
    return ldepth > rdepth ? (ldepth + 1) : (rdepth + 1);
}

/**
 * ����ָ����ڵ��ָ��
 * @param T
 * @return ����
 */
BiTreeNode Root(BiTree T) {
    if (!T) {
        printf("T->key:%d", T->key);
        printf("T->value:%c", T->data);
    }
    return *T;
}

/**
 * ��ȡ��Ϊkey��ֵ
 * @param T
 * @param key
 * @return
 */

Status Value(BiTree T, int key, TElemType &e) {
    LinkQueue q;
    QElemType a;
    if (T) {
        InitQueue(q);
        EnQueue(q, T);
        while (!QueueEmpty(q)) {
            DeQueue(q, a);
            if (a->key == key) {
                e = a->data;
                return OK;
            } else {
                if (a->lchild)
                    EnQueue(q, a->lchild);
                if (a->rchild)
                    EnQueue(q, a->rchild);
            }
        }
        DestroyQueue(q);
    }
    return ERROR;
}

/**
 *
 * @param T
 * @param e
 * @param value
 * @return
 */
Status Assign(BiTree &T, TElemType e, TElemType value) {
    if (T) {
        if (T->data == e) {
            T->data = value;
        }
        if (T->lchild != NULL) {
            Assign(T->lchild, e, value);
        }
        if (T->rchild != NULL) {
            Assign(T->rchild, e, value);
        }
    }
    return OK;
}

BiTree Parent(BiTree T, TElemType e) {
    LinkQueue q;
    QElemType a;
    if (T) {
        InitQueue(q);
        EnQueue(q, T);
        while (!QueueEmpty(q)) {
            DeQueue(q, a);
            if ((a->lchild && a->lchild->data == e) || (a->rchild && a->rchild->data == e)) {
                return a;
            } else {
                if (a->lchild)
                    EnQueue(q, a->lchild);
                if (a->rchild)
                    EnQueue(q, a->rchild);
            }
        }
        printf("û���ҵ�");
        DestroyQueue(q);
        return NULL;
    }
    printf("��Ϊ��");
    return NULL;
}

/**
 * �õ�ָ��value�Ľڵ�
 * @param T
 * @param e
 * @return
 */
BiTree Point(BiTree T, TElemType e) {
    LinkQueue q;
    QElemType a;
    if (T) {
        InitQueue(q);
        EnQueue(q, T);
        while (!QueueEmpty(q)) {
            DeQueue(q, a);
            if (a->data == e)
                return a;
            if (a->lchild)
                EnQueue(q, a->lchild);
            if (a->rchild)
                EnQueue(q, a->rchild);
        }
        DestroyQueue(q);
    }
    return NULL;
}

/**
 * �õ�ָ���ڵ�����ӽڵ�
 * @param T
 * @param e
 * @return
 */
BiTree LeftChild(BiTree T, TElemType e) {
    BiTree a;
    if (T) {
        a = Point(T, e);
        if (a == NULL) {
            printf("û���ҵ��˽ڵ�");
        }
        if (a->lchild)
            return a->lchild;
        printf("�˽ڵ�û�����ӽڵ�");
        return NULL;
    }
    printf("������δ��ʼ��");
    return NULL;
}

BiTree RightChild(BiTree T, TElemType e) {
    BiTree a;
    if (T) {
        a = Point(T, e);
        if (a == NULL) {
            printf("û���ҵ��˽ڵ�");
        }
        if (a->rchild)
            return a->rchild;
        printf("�˽ڵ�û�����ӽڵ�");
        return NULL;
    }
    printf("������δ��ʼ��");
    return NULL;
}

BiTree LeftSibling(BiTree T, TElemType e) {

    BiTree a;
    if (T) {
        a = Parent(T, e);
        if (a&&a->lchild && a->rchild && a->rchild->data == e) {
            return a->lchild;
        }

    }
    return NULL;
}

BiTree Rightsibling(BiTree T, TElemType e) {
    BiTree a;
    if (T) {
        a = Parent(T, e);
        if (a&&a->rchild && a->lchild && a->lchild->data == e) {
            return a->rchild;
        }

    }
    return NULL;
}

Status InsertChild(BiTree &T, TElemType p, Status LR) {
    BiTree child;
    BiTree q;
    InitBiTree(child);
    CreateBiTree(child, ++autokey);
    q = Point(T, p);
    if (T) {
        if (LR == 0) {
            if (q->lchild) {
                child->rchild = q->lchild;
            }
            q->lchild = child;
        }
        if (LR == 1){
            if (q->rchild){
                child->rchild=q->rchild;
            }
            q->rchild=child;
        }
    }
   // DestroyBiTree(child);
    return OK;
}

Status DeleteChild(BiTree &T, TElemType p, Status LR) {
    BiTree child;BiTree parent;
    child=Point(T,p);
    if (LR==0){
        if (child->lchild){
            child->lchild=NULL;
            //DestroyBiTree(T->lchild);
        }
    }
    if (LR==1){
        if (child->rchild){
            child->rchild=NULL;
        }
    }
 /*   if (parent&&child&&parent->lchild->data==child->data){
        parent->lchild=NULL;
    }
    if (parent&&child&&parent->rchild->data==child->data){
        parent->rchild=NULL;
    }*/
    return OK;

}

Status PreOrderTraverse(BiTree T, Status (*visit)(TNodeKey, TElemType)) {
    if (T) {
        visit(T->key, T->data);
        PreOrderTraverse(T->lchild, visit);
        PreOrderTraverse(T->rchild, visit);
    }
    return OK;
}

Status InOrderTraverse(BiTree T, Status (*visit)(TNodeKey, TElemType)) {
    if (T) {
        InOrderTraverse(T->lchild, visit);
        visit(T->key, T->data);
        InOrderTraverse(T->rchild, visit);
    }
    return OK;
}

Status PostOrderTraverse(BiTree T, Status (*visit)(TNodeKey, TElemType)) {
    if (T) {
        PostOrderTraverse(T->lchild, visit);
        PostOrderTraverse(T->rchild, visit);
        visit(T->key, T->data);
    }
}

Status LevelOrderTraverse(BiTree T, Status (*visit)(TNodeKey, TElemType)) {
    LinkQueue q;
    QElemType a;
    if (T) {
        InitQueue(q);
        EnQueue(q, T);
        while (!QueueEmpty(q)) {
            DeQueue(q, a);
            visit(a->key, a->data);
            if (a->lchild != NULL) {
                EnQueue(q, a->lchild);
            }
            if (a->rchild != NULL) {
                EnQueue(q, a->rchild);
            }
        }
        DestroyQueue(q);
    }
    return OK;
}