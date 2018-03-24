#include<iostream>
#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<string.h>
#include<algorithm>
#include <rpc.h>

int x0 = 80, y0_ = 20;
static int sum_=0;


bool taller, shorter;
using namespace std;
typedef struct {
    char name[30];
    int age;
    int gender;   //0�����У�1����Ů
} info;
typedef struct _BitNode {
    int height;
    info data;
    _BitNode *lson, *rson;
} BitNode, *BitTree;

void InitAVL(BitTree *root);

void DestroyAVL(BitTree *root);

info SearchAVL(BitTree root, char *x);

int InsertAVL(BitTree *root, info x);

int DeleteAVL(BitTree *root, char *x);

void TraverseAVL(BitTree root);

int getHeight(BitTree root);

void DestroyNode(BitTree *root);

int Max(int a, int b);

int namebigger(char *a, char *b);

int namesmaller(char *a, char *b);

void zig(BitTree *x);

void zig(BitTree *x);

void zigzag(BitTree *x);

void zagzig(BitTree *x);

/*�������ܣ��ж��������Ƿ���ͬ
  ���������Ƚϵ�����ֵ
  ����ֵ��0������ͬ��1������ͬ
*/
int IsSamePeople(info a, info b) {
    if (strcmp(a.name, b.name) != 0) return 0;
    if (a.age != b.age) return 0;
    if (a.gender != b.gender) return 0; //���������ݾ���ͬʱ����Ϊ������ͬ
    return 1;
}

/*�������ܣ�����һ����������
  ���������� root
  ����ֵ�����rootΪ�շ���-1��ֻ��һ���ڵ㷵��0������Ϊ�������߶�+1
*/
int getHeight(BitTree root) {
    if (root != NULL) return root->height;
    return -1;
}

/*�������ܣ�����ߵ����ֵ
  ���������Ƚϵ�������
  ����ֵ�������
*/
int Max(int a, int b) {
    if (a > b) return a;
    return b;
}

/*�������ܣ��ж�a����b����
  ������ a,b�ַ���
  ����ֵ��a��b���򷵻�1�����򷵻�0
*/

int namebigger(char *a, char *b) {
    if (strcmp(a, b) > 0) return 1;
    else return 0;
}

/*�������ܣ��ж�a����b��С
  ������ a,b�ַ���
  ����ֵ��a��bС�򷵻�1�����򷵻�0
*/
int namesmaller(char *a, char *b) {
    if (strcmp(a, b) < 0) return 1;
    else return 0;
}

void printNode(info data) {
    if (data.age == -1) {
        printf("�޴��ˣ�����\n");
        return;
    }
    printf("%s ", data.name);
    if (data.gender == 1) printf("woman ");
    else printf("man ");
    printf("age:%d\n", data.age);
}

/*�������ܣ��Ե����ڵ�����
  �������ڵ�
  ����ֵ����
*/
void zig(BitTree *x) {
    BitTree y = (*x)->lson;
    (*x)->lson = y->rson;
    y->rson = (*x);
    (*x)->height = Max(getHeight((*x)->lson), getHeight((*x)->rson)) + 1;
    y->height = Max(getHeight((*x)), getHeight(y->lson)) + 1;
    (*x) = y;
}

/*�������ܣ��Ե����ڵ�����
  �������ڵ�
  ����ֵ����
*/
void zag(BitTree *x) {
    BitTree y = (*x)->rson;
    (*x)->rson = y->lson;
    y->lson = (*x);
    (*x)->height = Max(getHeight((*x)->lson), getHeight((*x)->rson)) + 1;
    y->height = Max(getHeight((*x)), getHeight(y->rson)) + 1;
    (*x) = y;
}

/* �������ܣ��Ե����ڵ��µ������������������
   �������ڵ�
   ����ֵ����
*/
void zigzag(BitTree *x) {
    zig(&((*x)->rson));
    zag(x);
}

/* �������ܣ��Ե����ڵ��µ������������������
   �������ڵ�
   ����ֵ���µĸ��ڵ�
*/
void zagzig(BitTree *x) {
    zag(&((*x)->lson));
    zig(x);
}

/*�������ܣ������в��ҽڵ�x
  ����������root,�ڵ����ƣ�x
  ����ֵ����
  ���Ӷȣ�O(logn)
*/
info SearchAVL(BitTree root, char *x) {
    if (root == NULL) {
        info *temp = (info *) malloc(sizeof(info));
        temp->age = -1;
        return *temp;
    }
    if (namebigger(root->data.name, x)) {
        return SearchAVL(root->lson, x);
    } else if (namesmaller(root->data.name, x)) {
        return SearchAVL(root->rson, x);
    } else return root->data;
}

/*�������ܣ��������һ��Ԫ��
  ������ ������Ԫ��
  ����ֵ�� 1������ӳɹ���0����ʧ�ܣ��Ѵ��ڣ�
  ���Ӷȣ�O(logn)
*/
int InsertAVL(BitTree *root, info x) {
    int temp = 0;
    if ((*root) == NULL) {//����ڵ�Ϊ��,���ڴ˽ڵ㴦����x��Ϣ
        (*root) = (BitTree) malloc(sizeof(BitNode));
        (*root)->data = x;
        (*root)->height = 0;
        (*root)->lson = NULL;
        (*root)->rson = NULL;
        return 1;
    }

    if (namebigger((*root)->data.name, x.name)) {//���xС�ڽڵ��ֵ,�ͼ����ڽڵ���������в���x
        if (InsertAVL(&((*root)->lson), x)) temp = 1;
        if (2 == getHeight((*root)->lson) - getHeight((*root)->rson)) {
            if (namebigger((*root)->lson->data.name, x.name))
                zig(root);
            else
                zagzig(root);
        }
        (*root)->height = Max(getHeight((*root)->lson), getHeight((*root)->rson)) + 1;
        if (temp) return 1;
        else return 0;
    } else if (namesmaller((*root)->data.name, x.name)) {//���x���ڽڵ��ֵ,�ͼ����ڽڵ���������в���x
        if (InsertAVL(&((*root)->rson), x)) temp = 1;
        //����߶�֮��Ϊ2�Ļ���ʧȥ��ƽ��,��Ҫ��ת
        if (2 == getHeight((*root)->rson) - getHeight((*root)->lson)) {
            if (namesmaller((*root)->rson->data.name, x.name))
                zag(root);
            else
                zigzag(root);
        }
        (*root)->height = Max(getHeight((*root)->lson), getHeight((*root)->rson)) + 1;
        if (temp) return 1;
        else return 0;
    } else
        return 0;
}

/*�������ܣ�ǰ�������������
  ����������
  ����ֵ�� ��
  ���Ӷȣ�O(n)
*/
void TraverseAVL(BitTree root) {
    if (root == NULL) return;
    printNode(root->data);//������ڵ�
    TraverseAVL(root->lson); //����������
    TraverseAVL(root->rson);//�ٱ���������
}

/*�������ܣ���ʼ��һ��������
  ������ָ�������������ָ���ַ
  ����ֵ����
*/
void InitAVL(BitTree *root) {
    (*root) = NULL;
    //(*root)->height=-1;
    //(*root)->lson=NULL;(*root)->rson=NULL;
}

/*�������ܣ�ɾ����������һ���ڵ�
  ����������root���ڵ�x
  ����ֵ�� δ�ҵ�����-1��ɾ���ɹ�����0
  ���Ӷȣ�O(logn)
*/
int DeleteAVL(BitTree *root, char *x) {
    if ((*root) == NULL) return -1;//δ�ҵ��˽ڵ�
    if (namebigger((*root)->data.name, x)) {//����������ɾ���ڵ�x
        DeleteAVL(&((*root)->lson), x);
        if (2 == getHeight((*root)->rson) - getHeight((*root)->lson)) {
            if ((*root)->rson->lson != NULL && getHeight((*root)->rson->lson) > getHeight((*root)->rson->rson))
                zigzag(root);
            else zag(root);
        }
    } else if (namesmaller((*root)->data.name, x)) {//����������ɾ���ڵ�x
        DeleteAVL(&((*root)->rson), x);
        if (2 == getHeight((*root)->lson) - getHeight((*root)->rson)) {
            if ((*root)->lson->rson != NULL && getHeight((*root)->lson->rson) > getHeight((*root)->lson->lson))
                zagzig(root);
            else zig(root);
        }
    } else {//�ҵ��ڵ�x
        if ((*root)->lson != NULL && (*root)->rson != NULL) {
            BitTree temp = (*root)->rson;
            while (temp->lson != NULL) temp = temp->lson;
            (*root)->data = temp->data;

            DeleteAVL(&((*root)->rson), temp->data.name);
            if (2 == getHeight((*root)->lson) - getHeight((*root)->rson)) {
                if ((*root)->lson->rson != NULL && getHeight((*root)->lson->rson) > getHeight((*root)->lson->lson))
                    zagzig(root);
                else
                    zig(root);
            }
        } else {
            BitTree temp = *root;
            if ((*root)->lson == NULL)//���Ҷ��ӻ�û�ж���
                (*root) = (*root)->rson;
            else if ((*root)->rson = NULL)//�������
                (*root) = (*root)->lson;
            free(temp);
        }
    }
    if ((*root) == NULL) return 1;
    (*root)->height = Max(getHeight((*root)->lson), getHeight((*root)->rson)) + 1;
    return 1;
}

/*�������ܣ��Զ������ڵ�ݹ�ɾ��
  ���������ڵ�
  ����ֵ����
*/
void DestroyNode(BitTree *root) {
    if (*root == NULL) return;
    if ((*root)->lson != NULL) DestroyNode(&(*root)->lson);
    if ((*root)->rson != NULL) DestroyNode(&(*root)->rson);
    free(*root);
}

/*�������ܣ����ٶ�����
  ������ָ�������������ָ���ַ
  ����ֵ����
*/
void DestroyAVL(BitTree *root) {
    DestroyNode(root);
    *root = NULL;
}


#define Left 1
#define Centre 0
#define Right -1

typedef struct Information {
    int id;
    char name[10];
    struct BSTNode *friends;
    struct BSTNode *fans;
    struct BSTNode *attention;
    struct BSTNode *hobby;
} Information;
typedef struct BSTNode {
    Information data;
    int b; //balanceƽ������
    int h; //height���
    struct BSTNode *lchild, *rchild;
} BSTNode, *BSTree;


BSTree Ts = NULL;

typedef void(*visit)(BSTree T);   //����һ�ֺ�������
void set_init(BSTree *T);

void set_init(BSTree *T) {
    *T = NULL;
    printf("Successed to init!\n");
}


void set_destory(BSTree *T);

void set_destory(BSTree *T) {
    if ((*T) != NULL) {
        set_destory(&((*T)->lchild));
        set_destory(&((*T)->rchild));
        free(*T);
        T = NULL;
    }
}

void LeftBalance(BSTree *T);

void RightBalance(BSTree *T);

void L_Rotate(BSTree *p);

void R_Rotate(BSTree *p);

bool set_insert(BSTree *T, Information e, bool *taller);

bool set_insert(BSTree *T, Information e, bool *taller) {
    if (!(*T)) {
        (*T) = (BSTree) malloc(sizeof(BSTNode));
        (*T)->data = e;
        (*T)->lchild = (*T)->rchild = NULL;
        (*T)->b = Centre;
        *taller = true;
    } else {
        if (e.id == (*T)->data.id) {
            *taller = false;
            return false;
        }
        if (e.id < (*T)->data.id) {
            if (!set_insert(&((*T)->lchild), e, taller))
                return false;
            if (*taller)
                switch ((*T)->b) {
                    case Left:
                        LeftBalance(T);
                        *taller = false;
                        break;
                    case Centre:
                        (*T)->b = Left;
                        *taller = true;
                        break;
                    case Right:
                        (*T)->b = Centre;
                        *taller = false;
                        break;
                }
        } else {
            if (!set_insert(&((*T)->rchild), e, taller))
                return false;
            if (*taller) {
                switch ((*T)->b) {
                    case Left:
                        (*T)->b = Centre;
                        *taller = false;
                        break;
                    case Centre:
                        (*T)->b = Right;
                        *taller = true;
                        break;
                    case Right:
                        RightBalance(T);
                        *taller = false;
                        break;
                }
            }
        }
    }
    return true;
}


void LeftBalance(BSTree *T) {
    BSTree lc, rd;
    lc = (*T)->lchild;
    switch (lc->b) {
        case Left:
            (*T)->b = lc->b = Centre;
            R_Rotate(T);
            break;
        case Right:
            rd = lc->rchild;
            switch (rd->b) {
                case Left:
                    (*T)->b = Right;
                    lc->b = Centre;
                    break;
                case Centre:
                    (*T)->b = lc->b = Centre;
                    break;
                case Right:
                    (*T)->b = Centre;
                    lc->b = Left;
                    break;
            }
            rd->b = Centre;
            L_Rotate(&((*T)->lchild));
            R_Rotate(T);
    }
}


void RightBalance(BSTree *T) {
    BSTree rc, ld;
    rc = (*T)->rchild;
    switch (rc->b) {
        case Right:
            (*T)->b = rc->b = Centre;
            L_Rotate(T);
            break;
        case Left:
            ld = rc->lchild;
            switch (ld->b) {
                case Left:
                    (*T)->b = Centre;
                    rc->b = Right;
                    break;
                case Centre:
                    (*T)->b = rc->b = Centre;
                    break;
                case Right:
                    (*T)->b = Left;
                    rc->b = Centre;
                    break;
            }
            ld->b = Centre;
            R_Rotate(&((*T)->rchild));
            L_Rotate(T);
    }
}

void L_Rotate(BSTree *p) {
    BSTree rc;
    rc = (*p)->rchild;
    (*p)->rchild = rc->lchild;
    rc->lchild = (*p);
    (*p) = rc;
}


void R_Rotate(BSTree *p) {
    BSTree lc;
    lc = (*p)->lchild;
    (*p)->lchild = lc->rchild;
    lc->rchild = (*p);
    (*p) = lc;
}

bool set_remove(BSTree *T, int key, bool *shorter);

bool set_remove(BSTree *T, int key, bool *shorter) {
    if ((*T) == NULL)
        return false;
    else if (key == (*T)->data.id) {
        BSTree p;
        if ((*T)->lchild == NULL) {
            p = (*T);
            (*T) = (*T)->rchild;
            free(p);
            *shorter = true;
        } else if ((*T)->rchild == NULL) {
            p = (*T);
            (*T) = (*T)->lchild;
            free(p);
            *shorter = true;
        } else {
            p = (*T)->lchild;
            while (p->rchild)
                p = p->rchild;
            (*T)->data = p->data;
            set_remove(&((*T)->lchild), p->data.id, shorter);
        }
    } else if (key < (*T)->data.id) {
        if (!set_remove(&((*T)->lchild), key, shorter))
            return false;
        if (*shorter) {
            switch ((*T)->b) {
                case Left:
                    (*T)->b = Centre;
                    *shorter = true;
                    break;
                case Centre:
                    (*T)->b = Right;
                    *shorter = false;
                    break;
                case Right:
                    if ((*T)->rchild->b == Centre)
                        *shorter = false;
                    else
                        *shorter = true;
                    RightBalance(T);
                    break;
            }
        }
    } else {
        if (!set_remove(&((*T)->rchild), key, shorter))
            return false;
        if (*shorter) {
            switch ((*T)->b) {
                case Left:
                    if ((*T)->lchild->b == Centre)
                        *shorter = false;
                    else
                        *shorter = true;
                    LeftBalance(T);
                    break;
                case Centre:
                    (*T)->b = Left;
                    *shorter = false;
                    break;
                case Right:
                    (*T)->b = Centre;
                    *shorter = true;
                    break;
            }
        }
    }
    return true;
}
bool set_member(BSTree T, int key, BSTree *Ts);//�ж��Ƿ���ڽڵ�

bool set_member(BSTree T, int key, BSTree *Ts)//�ж��Ƿ���ڽڵ�
{
    if (T == NULL)
        return false;
    if (T->data.id == key) {
        *Ts = T;
        return true;
    } else if (key < T->data.id) {
        if (set_member(T->lchild, key, Ts))
            return true;
    } else {
        if (set_member(T->rchild, key, Ts))
            return true;
    }
    return false;
}

void set_intersection(BSTree T, BSTree T1, BSTree *T0);//�󽻼�
void set_intersection(BSTree T, BSTree T1, BSTree *T0)//�󽻼�
{
    if (T1 == NULL)return;
    if (set_member(T, T1->data.id, &Ts))
        set_insert(T0, T1->data, &taller);
    set_intersection(T, T1->lchild, T0);
    set_intersection(T, T1->rchild, T0);
}

void set_union(BSTree *T, BSTree T1);//�󲢼�
void set_union(BSTree *T, BSTree T1)//�󲢼�
{
    if (T1 == NULL)return;
    set_insert(T, T1->data, &taller);
    set_union(T, T1->lchild);
    set_union(T, T1->rchild);
}

void set_difference(BSTree *T, BSTree T1);//���
void set_difference(BSTree *T, BSTree T1)//���
{
    if (*T == NULL || T1 == NULL)
        return;
    set_remove(T, T1->data.id, &shorter);
    set_difference(T, T1->lchild);
    set_difference(T, T1->rchild);
}


bool set_subset(BSTree TS, BSTree T1);//�ж��Ƿ�Ϊ�Ӽ�
bool set_subset(BSTree T, BSTree T1)//�ж��Ƿ�Ϊ�Ӽ�
{
    if (T1 == NULL)
        return true;
    if (set_member(T, T1->data.id, &Ts))
    {
        if (!set_subset(T, T1->lchild))
            return false;
        if (!set_subset(T, T1->rchild))
            return false;
        return true;
    }
    else
        return false;
}

bool set_equal(BSTree T, BSTree T1);
bool set_equal(BSTree T, BSTree T1)
{
    if (!set_subset(T, T1))
        return false;
    if (!set_subset(T1, T))
        return false;
    return true;
}

bool load_data(BSTree *T, char *filename);

bool save_data(BSTree T, FILE *fp);
bool save_data(BSTree T, FILE *fp)
{
    if (T)
    {
        if (fwrite(T, sizeof(BSTNode), 1, fp) != 1)
        {
            printf("Failed to read_in the data!\n");
            fclose(fp);
            return false;
        }
    }
    else
        return true;
    if (!save_data(T->lchild,fp))
        return false;
    if (!save_data(T->rchild, fp))
        return false;
    return true;
}

void input_data(Information *data);//���뺯��

void input_data(Information *data)//���뺯��
{
    char s[10] = {1, 2, 3};
    printf("Please input id:");
    scanf("%d%*c", &(data->id));
    data->attention = NULL;
    data->fans = NULL;
    data->friends = NULL;
    data->hobby = NULL;
    strcpy(data->name, s);
    printf("\n");
}


void create(BSTree *T);

void height(BSTree T, int i);

void height(BSTree T, int i) {
    if (T)
        T->h = i + 1;
    else
        return;
    height(T->lchild, T->h);
    height(T->rchild, T->h);
}

void graph(BSTree T, int x, int y, visit fp);//��������ͼ���б�
void gotoxy(int x, int y)//�ƶ����
{
    COORD coord = {(SHORT) x, (SHORT) y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void graph(BSTree T, int x, int y, visit fp)//��������ͼ���б�
{
    if (T) {
        gotoxy(x + x0, y + y0_ + 1);
        fp(T);
    } else
        return;
    if (T->lchild || T->rchild) {
        gotoxy(x + x0 - 1, y + y0_ + 1);
        printf("|");
        if (T->lchild) {
            int i = 80 / ((int) pow(2, T->h) + 1);
            int j = i;
            gotoxy(x + x0 - j, y + y0_ + 3);
            printf("|");
            gotoxy(x + x0 - i + 1, y + y0_ + 2);
            while (i) {
                printf("_");
                i--;
            }
            graph(T->lchild, x - j, y + 4, fp);
        }
        if (T->rchild) {
            int i = 80 / ((int) pow(2, T->h) + 1);
            int j = i;
            gotoxy(x + x0 + 1, y + y0_ + 2);
            while (i) {
                printf("_");
                i--;
            }
            gotoxy(x + x0 + j, y + y0_ + 3);
            printf("|");
            graph(T->rchild, x + j, y + 4, fp);
        }
    }
}

void operate_id(BSTree T);//������г�Աid
void operate_relation(BSTree T1, BSTree T);

void operate_hobby(BSTree T1, BSTree H);

void gotoxy(int x, int y);//�ƶ����
void menu();

bool person_input(BSTree *T, int p_gross);//���ɶ�����
bool hobby_set_input(BSTree *H, int *h_gross);//���ɶ�����
void relation_input(BSTree *T, int p_gross, int h_gross);//��������ÿ���ڵ���������˼ʹ�ϵ����Ȥ����
void id_input(BSTree *T, int gross, int max, int min);

bool load_data(BSTree *T, char *filename);
bool load_data(BSTree *T, char *filename)
{
    BSTree p;
    FILE *fp;
    if ((fp = fopen(filename, "rb")) == NULL)
    {
        printf("Failed to open the file!\n");
        fclose(fp);
        return false;
    }
    while (!feof(fp))
    {
        if ((p = (BSTree)malloc(sizeof(BSTNode))) == NULL)
        {
            printf("Failed to apply memory!\n");
            fclose(fp);
            return false;
        }
        if (fread(p, sizeof(BSTNode), 1, fp) != 1)
        {
            free(p);
            break;
        }
        set_insert(T, p->data, &taller);
    }
    fclose(fp);
    height(*T, 0);
    return true;
}

bool save_data(BSTree T, FILE *fp);

void input_data(Information *data);//���뺯��
void input_data_person(Information *data);

void PreOrderTraverse(BSTree T);//����ÿ���ڵ�
void indirect_friends_traverse(BSTree T, BSTree Tf, BSTree *T0);//�������Ⱥ���
void indirect_friends_insert(BSTree T, BSTree *T0);//�����Ⱥ��Ѹ���T0
void adjust_traverse(BSTree T);

void complete_traverse(BSTree T, BSTree T0);             //���ƺ���
void complete_friends(BSTree T, BSTree T1, BSTree Tf);   //...
void complete_fans(BSTree T, BSTree T1, BSTree Tf);      //...
void complete_attention(BSTree T, BSTree T1, BSTree Tf); //...
void complete_hobby(BSTree T, BSTree T1, BSTree Tf);

void change(BSTree Ts);

void delete_(BSTree T);

void insert_information(BSTree *Ts);



typedef struct {
    BitTree avlTree;
    int number;
} Set, *set;
set setList[10];

void set_init(set *group);// ��ʼ������
void set_destroy(set *group); //���ټ���
int set_insert(set *group, info data); //����Ԫ��
int set_remove(set *group, info data); //ɾ��Ԫ��
set set_intersection(set groupA, set groupB); //���ϵĽ�
set set_union(set groupA, set groupB); //���ϵĲ�
set set_diffrence(set groupA, set groupB); //���ϵĲ�
int set_size(set group); //���ϴ�С
int set_member(set group, info data); //�ж�һ��Ԫ���Ƿ�Ϊ���ϳ�Ա
int set_subset(set groupA, set groupB); //�ж�һ�������Ƿ�Ϊ��һ�����ϵ��Ӽ�
int set_equal(set groupA, set groupB); //�ж����������Ƿ����
void treemerge(BitTree a, BitTree b, set *p);//���������Ľ��������µļ�����
void treeadd(BitTree a, set *p);//��һ���������µļ�����
void set_minus(set groupA, set groupB, set *p);//��A�г�ȥB�е�Ԫ�� ���ŵ�p��
int tree_subset(BitTree A, set p);//�ж���A��Ԫ���Ƿ���p��
void set_Traverse(set group);//�����������
/*�������ܣ� ��ʼ������
  ������ ����ָ��
  ����ֵ����
*/
void set_init(set *group) {
    (*group) = (set) malloc(sizeof(Set));
    (*group)->avlTree = NULL;

    InitAVL(&((*group)->avlTree));
    (*group)->number = 0;
}

/*�������ܣ� ���ټ���
  ������ ����ָ��
  ����ֵ�� ��
*/
void set_destroy(set *group) {
    DestroyAVL(&((*group)->avlTree));
    free(*group);
    *group = NULL;
}

/*�������ܣ� ����Ԫ��
  ������ ����ָ�� ��Ԫ������
  ����ֵ��-1�����Ѿ����ڣ�1�������ɹ� 0����Ƿ�����
  ���Ӷȣ�O(logn)
*/
int set_insert(set *group, info data) {
    if ((*group) == NULL) return 0;
    if (InsertAVL(&((*group)->avlTree), data) == 1) {
        (*group)->number++;
        return 1;
    } else
        return -1;
}

/*�������ܣ� ɾ��Ԫ��
  ������ ����ָ�� ����Ԫ��
  ����ֵ��-1����Ԫ�ز����ڣ�1����ɾ���ɹ� 0����Ƿ�����
*/
int set_remove(set *group, info data) {
    if ((*group) == NULL) return 0;
    if (DeleteAVL(&((*group)->avlTree), data.name)) {
        (*group)->number--;
        return 1;
    } else return -1;

}

/*�������ܣ����������Ľ���
  ������ ��a��b ����p
  ����ֵ����
*/
void treemerge(BitTree a, BitTree b, set *p) {
    if (a == NULL) return;
    info temp;
    temp = SearchAVL(b, a->data.name);
    if ((temp.age != -1)) set_insert(p, temp);
    treemerge(a->lson, b, p);
    treemerge(a->rson, b, p);
}

/*�������ܣ� ��һ������Ԫ�ؼ��뵽������
  ������ ��a������p
  ����ֵ����
*/
void treeadd(BitTree a, set *p) {
    if (a == NULL) return;
    set_insert(p, a->data);
    treeadd(a->lson, p);
    treeadd(a->rson, p);
}

/*�������ܣ� ���������ϵĽ���
  ������ ����A��B
  ����ֵ������ �Ƿ��������ؿ�
  ���Ӷȣ�O(n)
*/
set set_intersection(set groupA, set groupB) {
    set temp;
    set_init(&temp);
    if (groupA == NULL || groupB == NULL) {
        set_destroy(&temp);
        return temp;
    }
    BitTree treeA = groupA->avlTree;
    BitTree treeB = groupB->avlTree;
    treemerge(treeA, treeB, &temp);
    return temp;
}

/*�������ܣ� �������ϵĲ�
  ������ ����A��B
  ����ֵ������ �Ƿ��������ؿ�
*/
set set_union(set groupA, set groupB) {
    set temp;
    set_init(&temp);
    if (groupA == NULL || groupB == NULL) {
        set_destroy(&temp);
        return temp;
    }
    BitTree treeA = groupA->avlTree;
    BitTree treeB = groupB->avlTree;
    treeadd(treeA, &temp);
    treeadd(treeB, &temp);
    return temp;
}

/*�������ܣ� ���������в�һ����Ԫ�طŵ��¼�����
  ������ ��A,B ����P
  ����ֵ����
*/
void set_minus(BitTree A, BitTree B, set *p) {
    if (A == NULL) return;
    info temp;
    temp = SearchAVL(B, A->data.name);
    if (temp.age == -1) set_insert(p, A->data);
    set_minus(A->lson, B, p);
    set_minus(A->rson, B, p);
}

/*�������ܣ� �������ϵĲ�
  ������ ����A,B
  ����ֵ��� �Ƿ��������ؿ�
  ���Ӷȣ�O(n)
*/
set set_diffrence(set groupA, set groupB) {

    set crossgroup = set_intersection(groupA, groupB);
    set temp;
    set_init(&temp);
    if (groupA == NULL || crossgroup == NULL) {
        set_destroy(&temp);
        return temp;
    }
    BitTree treeA = groupA->avlTree;
    BitTree treeB = crossgroup->avlTree;
    set_minus(treeA, treeB, &temp);
    return temp;
}

/*�������ܣ� ���ؼ��ϵĴ�С
  ������ ����
  ����ֵ�����ϴ�С ,�Ƿ�����Ϊ-1;
*/
int set_size(set group) {
    if (group == NULL) return -1;
    return group->number;
}

/*�������ܣ� �ж�Ԫ���Ƿ�Ϊ���ϳ�Ա
  ������ ����group Ԫ��data
  ����ֵ����Ϊ1����Ϊ0���Ƿ�����Ϊ-1
*/
int set_member(set group, info data) {
    if (group == NULL) return -1;
    if (SearchAVL(group->avlTree, data.name).age != -1) return 1;
    else return 0;
}

/*�������ܣ� �жϼ���A�Ƿ���B���Ӽ�
  ������ ����A,����B
  ����ֵ������Ϊ1������Ϊ0;
*/
int tree_subset(BitTree A, set p) {
    if (A == NULL) return 1;
    if (SearchAVL(p->avlTree, A->data.name).age == -1) return 0;
    else {
        return tree_subset(A->lson, p) & tree_subset(A->rson, p);
    }
}

/*�������ܣ� �жϼ���A�Ƿ���B���Ӽ�
  ������ ����A,����B
  ����ֵ������Ϊ1������Ϊ0���Ƿ�����Ϊ-1;
  ���Ӷȣ�O(n)
*/
int set_subset(set groupA, set groupB) {
    if (groupA == NULL || groupB == NULL) return -1;
    if (tree_subset(groupA->avlTree, groupB)) return 1;
    else return 0;
}

/*�������ܣ� �ж����������Ƿ����
  ������ ����A��B
  ����ֵ�����Ϊ1������Ϊ0���Ƿ�����Ϊ-1
*/
int set_equal(set groupA, set groupB) {
    if (groupA == NULL || groupB == NULL) return -1;
    if (set_subset(groupA, groupB) == 1 && groupA->number == groupB->number) return 1;
    else return 0;
}

/*�������ܣ� �������һ������
  ������ ����group
  ����ֵ����
*/
void set_Traverse(set group) {
    printf("����%d��\n", group->number);
    TraverseAVL(group->avlTree);
    //printf("******���*******\n");
}

typedef struct {   //����Ӧ�ò�ṹ����
    info Myinfo;
    set Myfriends;
    set Myfans;
    set Myidols;
} Person, *person;

void init_person(person *ren);//��ʼ��һ����
void destroy_person(person *ren);//ɾ��һ����
int add_friends(person *a, person *b);//a,b�������Ϊ����
int remove_friends(person *a, person *b);//a,b����������
int search_friends(person *a, person *b);//��ѯa��b�Ƿ��Ǻ���
int add_fans(person *a, person *b);//a��Ϊb�ķ�˿
int remove_fans(person *a, person *b);//a���b�ķ�˿
int search_fans(person *a, person *b);//��ѯa�ǲ���b�ķ�˿
int add_idols(person *a, person *b);//a��Ϊb�Ĺ�ע
int remove_idols(person *a, person *b);//a�����b�Ĺ�ע
int search_idols(person *a, person *b);//��ѯa�ǲ���b�Ĺ�ע
set common_idols(person *a, person *b);//��a��b�Ĺ�ͬ��ע
set common_fans(person *a, person *b);//��a��b�Ĺ�ͬ��˿
set two_degree_friends(person *a);//��a�Ķ��Ⱥ���
void printPerson(person a);//��ӡ���һ���˵���Ϣ
/*�������ܣ�  ��ʼ��һ����
  ������  �ṹָ�� a
  ����ֵ�� ��
*/
void init_person(person *a) {
    if ((*a) != NULL) destroy_person(a);
    (*a) = (person) malloc(sizeof(Person));
    set_init(&((*a)->Myfriends));
    set_init(&((*a)->Myfans));
    set_init(&((*a)->Myidols));
}

/*�������ܣ�  ����һ����
  ������  �ṹָ�� a
  ����ֵ�� ��
*/
void destroy_person(person *ren) {
    if ((*ren) == NULL) return;
    set_destroy(&((*ren)->Myfriends));
    set_destroy(&((*ren)->Myfans));
    set_destroy(&((*ren)->Myidols));
    free(*ren);
}

/*�������ܣ�  ������˻�Ϊ���ѹ�ϵ
  ������  ������a��b
  ����ֵ�� ��ӳɹ�Ϊ1���Ƿ�Ϊ-1
*/
int add_friends(person *a, person *b) {
    if ((*a) == NULL || (*b) == NULL) return -1;
    if (set_insert(&((*a)->Myfriends), (*b)->Myinfo) == 1 && set_insert(&((*b)->Myfriends), (*a)->Myinfo) == 1)
        return 1;
    else return 0;
}

/*�������ܣ�  ������˵ĺ��ѹ�ϵ
  ������  ������a,b
  ����ֵ�� ����ɹ�Ϊ1�����ʧ��Ϊ0���Ƿ�����Ϊ-1
*/
int remove_friends(person *a, person *b) {
    if ((*a) == NULL || (*b) == NULL) return -1;
    if (search_friends(a, b) != 1) return 0;
    if (set_remove(&((*a)->Myfriends), (*b)->Myinfo) == 1 && set_remove(&((*b)->Myfriends), (*a)->Myinfo) == 1)
        return 1;
    else return 0;
}

/*�������ܣ� ���������Ƿ�Ϊ���ѹ�ϵ
  ������  ������a,b
  ����ֵ�� ����Ϊ1����Ϊ0���Ƿ�Ϊ-1
*/
int search_friends(person *a, person *b) {
    if ((*a) == NULL || (*b) == NULL) return -1;
    if (set_member((*a)->Myfriends, (*b)->Myinfo) == 1) return 1;
    else return 0;
}

/*�������ܣ�  ���aΪb�ķ�˿
  ������  ������a,b
  ����ֵ�� ��ӳɹ�Ϊ1��ʧ��Ϊ0���Ƿ�Ϊ-1
*/
int add_fans(person *a, person *b) {
    if ((*a) == NULL || (*b) == NULL) return -1;
    if (set_insert(&((*b)->Myfans), (*a)->Myinfo) == 1 && set_insert(&((*a)->Myidols), (*b)->Myinfo) == 1) return 1;
    else return 0;
}

/*�������ܣ�  ���a��b�ķ�˿
  ������  ������a,b
  ����ֵ�� ����ɹ�Ϊ1��ʧ��Ϊ0���Ƿ�Ϊ-1
*/
int remove_fans(person *a, person *b) {
    if ((*a) == NULL || (*b) == NULL) return -1;
    if (search_fans(a, b) != 1) return 0;
    if (set_remove(&((*b)->Myfans), (*a)->Myinfo) == 1 && set_remove(&((*a)->Myidols), (*b)->Myinfo) == 1) return 1;
    else return 0;
}

/*�������ܣ� ��ѯa�ǲ���b�ķ�˿
  ������  ������a,b
  ����ֵ�� ���򷵻أ����򷵻�0���Ƿ�Ϊ-1
*/
int search_fans(person *a, person *b) {
    if ((*a) == NULL || (*b) == NULL) return -1;
    if (set_member((*b)->Myfans, (*a)->Myinfo) == 1) return 1;
    else return 0;
}

/*�������ܣ�  ���aΪb�Ĺ�ע
  ������  ������a,b
  ����ֵ�� ��ӳɹ�Ϊ1��ʧ��Ϊ0���Ƿ�Ϊ-1
*/
int add_idols(person *a, person *b) {
    if ((*a) == NULL || (*b) == NULL) return -1;
    if (set_insert(&((*b)->Myidols), (*a)->Myinfo) == 1 && set_insert(&((*a)->Myfans), (*b)->Myinfo) == 1) return 1;
    else return 0;
}

/*�������ܣ�  ���a��b�Ĺ�ע
  ������  ������a,b
  ����ֵ�� ����ɹ�Ϊ1��ʧ��Ϊ0���Ƿ�Ϊ-1
  */
int remove_idols(person *a, person *b) {
    if ((*a) == NULL || (*b) == NULL) return -1;
    if (search_idols(a, b) != 1) return 0;
    if (set_remove(&((*b)->Myidols), (*a)->Myinfo) == 1 && set_remove(&((*a)->Myfans), (*b)->Myinfo) == 1) return 1;
    else return 0;
}

/*�������ܣ� ��ѯa�ǲ���b�Ĺ�ע
  ������  ������a,b
  ����ֵ�� ���򷵻أ����򷵻�0���Ƿ�Ϊ-1
*/

int search_idols(person *a, person *b) {
    if ((*a) == NULL || (*b) == NULL) return -1;
    if (set_member((*b)->Myidols, (*a)->Myinfo) == 1) return 1;
    else return 0;
}

/*�������ܣ�  �������˵Ĺ�ͬ��ע
  ������  ������a,b
  ����ֵ�� ��ͬ��ע�ļ���
*/
set common_idols(person *a, person *b) {
    return set_intersection((*a)->Myidols, (*b)->Myidols);
}

/*�������ܣ�  �������˵Ĺ�ͬ��˿
  ������  ������a,b
  ����ֵ�� ��ͬ��˿�ļ���
*/
set common_fans(person *a, person *b) {
    return set_intersection((*a)->Myfans, (*b)->Myfans);
}


person personList[20];

/*�������ܣ�  ��һ���˵Ķ��Ⱥ���
  ������  һ����a
  ����ֵ�� a�����ж��Ⱥ��ѹ��ɵļ���
*/
set two_degree_friends(person *a) {
    set temp;
    set_init(&temp);
    set one_degree_friendss = (*a)->Myfriends;
    for (int i = 0; i < 20; i++) {
        if (personList[i] == NULL)
            continue;
        if (search_friends(&personList[i], a) == 1) {
            temp = set_union(temp, personList[i]->Myfriends);
        }
    }
    set_remove(&temp, (*a)->Myinfo);
    return temp;
}

/*�������ܣ�  ���һ����
  ������  һ����a
  ����ֵ�� void
*/
void printPerson(person a) {
    if (a == NULL) return;
    printf("�����ǣ�%s �Ա��ǣ�", a->Myinfo.name);
    if (a->Myinfo.gender == 0) printf("�� ");
    else printf("Ů ");
    printf("�����ǣ�%d\n", a->Myinfo.age);
    if (a->Myfriends->number > 0) {
        printf("Ta�ĺ��Ѱ�����\n");
        set_Traverse(a->Myfriends);
    } else printf("Taû�к���\n");
    if (a->Myfans->number > 0) {
        printf("Ta�ķ�˿������\n");
        set_Traverse(a->Myfans);
    } else printf("Taû�з�˿\n");
    if (a->Myidols->number > 0) {
        printf("Ta�Ĺ�ע������\n");
        set_Traverse(a->Myidols);
    } else printf("Taû�й�ע\n");
    printf("******���*******\n");
}

int op = 1;

/*�������ܣ�  ��ӡ���г�Ա��Ϣ
  ������  void
  ����ֵ�� ���г�Ա����
*/
int print_now_person() {
    int ans = 0;
    for (int i = 0; i < 20; i++) {
        if (personList[i] == NULL) continue;
        ans = i + 1;
       // printf("��%dλ�û�Ϊ : %s\n", ans, personList[i]->Myinfo.name);
    }
    if (ans == 0) {
        printf("��ǰ�����û�����\n");
    }
    return ans;
}

void print_now_person2(){
    int ans = 0;
    for (int i = 0; i < 20; i++) {
        if (personList[i] == NULL) continue;
        ans = i + 1;
        printf("��%dλ�û�Ϊ : %s\n", ans, personList[i]->Myinfo.name);
    }
    if (ans == 0) {
        printf("��ǰ�����û�����\n");
    }
}

/*�������ܣ�  ���һλ�û�
  ������  void
  ����ֵ�� void
*/
void Insert_A_Person() {
   // printf("�����û��������£�\n");
    int now = print_now_person();
    printf("--------------------------------\n");
    info temp;
    printf("�������û�������ע�ⲻҪ������û������ظ���\n");
    scanf("%s", temp.name);
    printf("�������û��Ա�0�����У�1����Ů��\n");
    scanf("%d", &temp.gender);
    printf("�������û����䣬0~99֮�䣺\n");
    scanf("%d", &temp.age);
    for (int i = 0; i < 20; i++) {
        if (personList[i] == NULL) continue;
        if (strcmp(personList[i]->Myinfo.name, temp.name) == 0) {
            printf("�����Ѵ��ڣ������²���\n");
            return;
        }
    }
    if (temp.gender != 0 && temp.gender != 1) {
        printf("�Ա�������������²���\n");
        return;
    }
    if (temp.age < 0 || temp.age > 99) {
        printf("����������������²���\n");
        return;
    }
    init_person(&personList[now]);
    personList[now]->Myinfo = temp;
    printf("��ӳɹ�!\n");
}

/*�������ܣ�  ɾ��һλ�û�
  ������  void
  ����ֵ�� void
*/
void Delete_A_Person() {
  //  printf("�����û��������£�\n");
    int now = print_now_person();
    printf("--------------------------------\n");
    int del;
    printf("������Ҫɾ�����û���ţ�����1--%d֮�䣩\n", now);
    scanf("%d", &del);
    if (del < 1 || del > now) {
        printf("����������������²���\n");
        return;
    }
    for (int i = 0; i < now; i++) {
        if (i + 1 == del) continue;
        if (search_fans(&personList[del - 1], &personList[i]) == 1) remove_fans(&personList[del - 1], &personList[i]);
        if (search_friends(&personList[del - 1], &personList[i]) == 1)
            remove_friends(&personList[del - 1], &personList[i]);
        if (search_idols(&personList[del - 1], &personList[i]) == 1) remove_idols(&personList[del - 1], &personList[i]);
    }
    printf("******\n");
    destroy_person(&personList[del - 1]);
    for (int i = del; i < now; i++)
        personList[i - 1] = personList[i];
    personList[now - 1] = NULL;
    printf("ɾ���ɹ���\n");
}

/*�������ܣ�  ���������˵ĺ��ѹ�ϵ
  ������  void
  ����ֵ�� void
*/
void Make_Friends() {
  //  printf("�����û��������£�\n");
    int now = print_now_person();
    printf("--------------------------------\n");
    int per1, per2;
    printf("��������λ�û��ı�ţ�\n�û�1��\n");
    scanf("%d", &per1);
    printf("�û�2��\n");
    scanf("%d", &per2);
    if (per1 < 1 || per1 > now || per2 < 1 || per2 > now) {
        printf("����������������²���\n");
        return;
    }
    if (search_friends(&personList[per1 - 1], &personList[per2 - 1]) == 1) {
        printf("����λ�Ѿ��Ǻ����ˣ���\n");
        return;
    } else {
        if (add_friends(&personList[per1 - 1], &personList[per2 - 1]) == 1) printf("�����ɹ�����\n");
        else printf("����ʧ�ܣ���\n");
        return;
    }
}

/*�������ܣ�  ɾ�������˵ĺ��ѹ�ϵ
  ������  void
  ����ֵ�� void
*/
void Remove_Friends() {
    //printf("�����û��������£�\n");
    int now = print_now_person();
    printf("--------------------------------\n");
    int per1, per2;
    printf("��������λ�û��ı�ţ�\n�û�1��\n");
    scanf("%d", &per1);
    printf("�û�2��\n");
    scanf("%d", &per2);
    if (per1 < 1 || per1 > now || per2 < 1 || per2 > now) {
        printf("����������������²���\n");
        return;
    }
    if (search_friends(&personList[per1 - 1], &personList[per2 - 1]) != 1) {
        printf("����λ�����Ǻ��ѣ���\n");
        return;
    } else {
        if (remove_friends(&personList[per1 - 1], &personList[per2 - 1]) == 1) printf("�����ɹ�����\n");
        else printf("����ʧ�ܣ���\n");
        return;
    }
}

/*�������ܣ�  ��ѯ�������ǲ��Ǻ���
  ������  void
  ����ֵ�� void
*/
void Search_Friends() {
   // printf("�����û��������£�\n");
    int now = print_now_person();
    printf("--------------------------------\n");
    int per1, per2;
    printf("��������λ�û��ı�ţ�\n�û�1��\n");
    scanf("%d", &per1);
    printf("�û�2��\n");
    scanf("%d", &per2);
    if (per1 < 1 || per1 > now || per2 < 1 || per2 > now) {
        printf("����������������²���\n");
        return;
    }
    if (search_friends(&personList[per1 - 1], &personList[per2 - 1]) != 1) {
        printf("����λ�����Ǻ��ѣ���\n");
        return;
    } else {
        printf("����λȷʵ�Ǻ��ѣ���\n");
        return;
    }
}

/*�������ܣ�  ���һ����Ϊ��һ���ķ�˿
  ������  void
  ����ֵ�� void
*/
void Add_A_Fans() {
  //  printf("�����û��������£�\n");
    int now = print_now_person();
    printf("--------------------------------\n");
    int per1, per2;
    printf("��������λ�û��ı�ţ�\n�û�1������˿��\n");
    scanf("%d", &per1);
    printf("�û�2����ż��\n");
    scanf("%d", &per2);
    if (per1 < 1 || per1 > now || per2 < 1 || per2 > now) {
        printf("����������������²���\n");
        return;
    }
    if (search_fans(&personList[per1 - 1], &personList[per2 - 1]) == 1) {
        printf("Ta�Ѿ���Ta�ķ�˿�ˣ���\n");
        return;
    } else {
        if (add_fans(&personList[per1 - 1], &personList[per2 - 1]) == 1) printf("�����ɹ�����\n");
        else printf("����ʧ�ܣ���\n");
        return;
    }
}

/*�������ܣ�  ���һ����Ϊ��һ���ķ�˿
  ������  void
  ����ֵ�� void
*/
void Remove_Fans() {
  //  printf("�����û��������£�\n");
    int now = print_now_person();
    printf("--------------------------------\n");
    int per1, per2;
    printf("��������λ�û��ı�ţ�\n�û�1������˿��\n");
    scanf("%d", &per1);
    printf("�û�2����ż��\n");
    scanf("%d", &per2);
    if (per1 < 1 || per1 > now || per2 < 1 || per2 > now) {
        printf("����������������²���\n");
        return;
    }
    if (search_fans(&personList[per1 - 1], &personList[per2 - 1]) != 1) {
        printf("Ta������Ta�ķ�˿����\n");
        return;
    } else {
        if (remove_fans(&personList[per1 - 1], &personList[per2 - 1]) == 1) printf("�����ɹ�����\n");
        else printf("����ʧ�ܣ���\n");
        return;
    }
}

/*�������ܣ�  ��ѯһ�����ǲ�����һ���ķ�˿
  ������  void
  ����ֵ�� void
*/
void Search_Fans() {
   // printf("�����û��������£�\n");
    int now = print_now_person();
    printf("--------------------------------\n");
    int per1, per2;
    printf("��������λ�û��ı�ţ�\n�û�1������˿��\n");
    scanf("%d", &per1);
    printf("�û�2����ż��\n");
    scanf("%d", &per2);
    if (per1 < 1 || per1 > now || per2 < 1 || per2 > now) {
        printf("����������������²���\n");
        return;
    }
    if (search_fans(&personList[per1 - 1], &personList[per2 - 1]) != 1) {
        printf("Ta������Ta�ķ�˿����\n");
        return;
    } else {
        printf("Taȷʵ��Ta�ķ�˿����\n");
        return;
    }
}

/*�������ܣ�  ��ѯ�����˵Ĺ�ͬ��˿
  ������  void
  ����ֵ�� void
*/
void Commom_Fans() {
    //printf("�����û��������£�\n");
    int now = print_now_person();
    printf("--------------------------------\n");
    int per1, per2;
    printf("��������λ�û��ı�ţ�\n�û�1��\n");
    scanf("%d", &per1);
    printf("�û�2��\n");
    scanf("%d", &per2);
    if (per1 < 1 || per1 > now || per2 < 1 || per2 > now) {
        printf("����������������²���\n");
        return;
    }
    printf("���ǵĹ�ͬ��˿�������£�\n");
    set_Traverse(common_fans(&personList[per1 - 1], &personList[per2 - 1]));
    return;
}

/*�������ܣ�  ��ѯ�����˵Ĺ�ͬ��ע
  ������  void
  ����ֵ�� void
*/
void Commom_Idols() {
   // printf("�����û��������£�\n");
    int now = print_now_person();
    printf("--------------------------------\n");
    int per1, per2;
    printf("��������λ�û��ı�ţ�\n�û�1��\n");
    scanf("%d", &per1);
    printf("�û�2��\n");
    scanf("%d", &per2);
    if (per1 < 1 || per1 > now || per2 < 1 || per2 > now) {
        printf("����������������²���\n");
        return;
    }
    printf("���ǵĹ�ͬ��ע�������£�\n");
    set_Traverse(common_idols(&personList[per1 - 1], &personList[per2 - 1]));
    return;
}

/*�������ܣ�  ��ѯ��һ���˵Ķ��Ⱥ���
  ������  void
  ����ֵ�� void
*/
void TwoDFriends() {
   // printf("�����û��������£�\n");
    int now = print_now_person();
    printf("--------------------------------\n");
    int per1;
    printf("������Ҫ��ѯ���û��ı�ţ�\n");
    scanf("%d", &per1);
    if (per1 < 1 || per1 > now) {
        printf("����������������²���\n");
        return;
    }
    printf("��Ta�Ķ��Ⱥ��Ѱ������£�\n");
    set_Traverse(two_degree_friends(&personList[per1 - 1]));
    return;
}

/*�������ܣ�  ������д�뵽�ļ���
  ������  void
  ����ֵ�� void
*/
void SaveToFile() {
    FILE *fp;
    info temp;
    temp.age = -1;
    if ((fp = fopen("data.txt", "w")) == NULL) {
        printf("File open error\n ");
        return;
    }
    int ans = 0;
    for (int i = 0; i < 20; i++) {
        if (personList[i] == NULL) continue;
        ans = i + 1;
        fwrite(&(personList[i]->Myinfo), sizeof(info), 1, fp);
    }
    int zero = 0;
    fwrite((&temp), sizeof(info), 1, fp);
    for (int i = 1; i <= ans; i++)
        for (int j = 1; j <= ans; j++) {
            if (search_friends(&personList[i - 1], &personList[j - 1]) == 1) {
                fwrite(&i, sizeof(int), 1, fp);
                fwrite(&j, sizeof(int), 1, fp);
            }
        }
    fwrite(&zero, sizeof(int), 1, fp);
    for (int i = 1; i <= ans; i++)
        for (int j = 1; j <= ans; j++) {
            if (search_fans(&personList[i - 1], &personList[j - 1]) == 1) {
                fwrite(&i, sizeof(int), 1, fp);
                fwrite(&j, sizeof(int), 1, fp);
            }
        }
    fwrite(&zero, sizeof(int), 1, fp);
    fclose(fp);
    printf("�ѳɹ����棡����\n");
}

/*�������ܣ�  ���ļ��ж�ȡ����
  ������  void
  ����ֵ�� void
*/
void LoadFromFile() {
    FILE *fp;
    if ((fp = fopen("data.txt", "r")) == NULL) {
        printf("File open error\n ");
        return;
    }
    int ans = 0;
    init_person(&personList[ans]);
    while (fread(&(personList[ans]->Myinfo), sizeof(info), 1, fp)) {
        if (personList[ans]->Myinfo.age == -1) {
            destroy_person(&personList[ans]);
            personList[ans] = NULL;
            break;
        }
        ans++;
        init_person(&personList[ans]);
    }
    int a, b;
    while (fread(&a, sizeof(int), 1, fp)) {
        if (a == 0) break;
        fread(&b, sizeof(int), 1, fp);
        add_friends(&personList[a - 1], &personList[b - 1]);
    }
    while (fread(&a, sizeof(int), 1, fp)) {
        if (a == 0) break;
        fread(&b, sizeof(int), 1, fp);
        add_fans(&personList[a - 1], &personList[b - 1]);
    }
    fclose(fp);
    printf("��ȡ�ɹ�������\n");
}

void Traverse(BSTree T)//����ÿ���ڵ�
{
    if (T == NULL)return;
    printf("%3d  ", T->data.id);
    Traverse(T->lchild);
    Traverse(T->rchild);
    return;
}

void operate_id(BSTree T)//������г�Աid
{
    printf("%d", T->data.id);
}
int size(BSTree t)
{
    if(t)
    {
        sum_++;
        size(t->lchild);
        size(t->rchild);
    }
    return sum_;
}

int main() {
    int op = 1, t;
    int op1 = 1, op2 = 1, op3 = 1;
    BSTree T = NULL;
    BSTree H = NULL;
    visit fp = &operate_id;
    while (op) {
        system("cls");
        printf("\n\n\n\n\n");
        printf("                                    ������\n");
        printf("                 ----------------------------------------------------\n");
        printf("                 |                   1. AVL��                        |\n");
        printf("                 |                   2. set��                        |\n");
        printf("                 |                   3. Ӧ�ò�                       |\n");
        printf("                 |                   0. �˳�����                     |\n");
        printf("                 -----------------------------------------------------\n");
        printf("                                   ���������ѡ��:");
        scanf("%d", &op);
        switch (op) {
            case 1:

                op1 = 1;
                while (op1) {
                    system("cls");
                    system("mode con:cols=150 lines=160");
                    printf("\n\n");

                    printf("                                         AVL                                 \n");
                    printf("----------------------------------------------------------------------------------\n");
                    printf("                |                                                            |\n");
                    printf("                |     1.InitAVL                      2.DestroyAVL            |\n");
                    printf("                |     3.SearchAVL                    4.InsertAVL             |\n");
                    printf("                |     5.DelectAVL                    6.TraverseAVL           |\n");
                    printf("                |                           0. ����������                     |\n");
                    printf("-----------------------------------------------------------------------------------\n");
                    printf("                  ��ѡ����Ĳ���[0~6]: ");
                    scanf("%d", &op1);
                    switch (op1) {

                        case 1: {
                            set_init(&T);
                            getchar();
                            break;
                        }
                        case 2: {
                            set_destory(&T);
                            T = NULL;
                            printf("Successed to destory!\n");
                            getchar();
                            getchar();
                            break;
                        }
                        case 3: {
                            int key;
                            printf("Please input id:");
                            scanf("%d%*c", &key);
                            printf("\n");
                            if (set_member(T, key, &Ts))
                                printf("Yes!\n");
                            else
                                printf("No!\n");

                            getchar();
                            getchar();
                            break;
                        }
                        case 4: {
                            Information datas;
                            input_data(&datas);
                            if (set_insert(&T, datas, &taller)) {
                                printf("Successed to insert!\n");
                                height(T, 0);
                            } else
                                printf("Failed to insert!\n");

                            getchar();
                            getchar();
                            break;
                        }
                        case 5: {
                            int key;
                            printf("Please input id:");
                            scanf("%d%*c", &key);
                            if (set_remove(&T, key, &shorter)) {
                                printf("Successed to remove!\n");
                                height(T, 0);
                            } else
                                printf("Failed to remove!\n");
                            getchar();
                            getchar();
                            break;
                        }
                        case 6:
                            Traverse(T);


                            graph(T, 0, 0, fp);

                            getchar();
                            getchar();
                            break;
                        case 0:
                            printf("");
                            break;
                    }
                }
                break;
            case 2:
                op2 = 1;
                while (op2) {
                    system("cls");
                    printf("\n\n");
                    printf("                                             set                     \n");
                    printf("------------------------------------------------------------------------------------\n");
                    printf("                |     1.set init                     2.set destroy           |\n");
                    printf("                |     3.set insert                   4.set remove            |\n");
                    printf("                |     5.set intersection            6.set union              |\n");
                    printf("                |     7.set difference              8.set size               |\n");
                    printf("                |     9.set member                  10.set subset            |\n");
                    printf("                |     11.set equal                  12. graph               |\n");
                    printf("                |     13.load data                  14. save data            |\n");
                    printf("                |                        0. ����������                        |\n");
                    printf("                  ��ѡ����Ĳ���[0~14]:\n");
                    printf("------------------------------------------------------------------------------------\n");
                    scanf("%d", &op2);
                    switch (op2) {
                        case 1:
                            set_init(&T);
                            break;
                        case 2: {
                            set_destory(&T);
                            T = NULL;
                            printf("Successed to destory!\n");
                            break;
                        }
                        case 3: {
                            Information datas;
                            input_data(&datas);
                            if (set_insert(&T, datas, &taller)) {
                                printf("Successed to insert!\n");
                                height(T, 0);
                            } else
                                printf("Failed to insert!\n");
                            break;
                        }
                        case 4: {
                            int key;
                            printf("Please input id:");
                            scanf("%d%*c", &key);
                            if (set_remove(&T, key, &shorter)) {
                                printf("Successed to remove!\n");
                                height(T, 0);
                            } else
                                printf("Failed to remove!\n");
                            break;
                        }
                        case 5: {
                            char filename[20];
                            BSTree T1 = NULL;
                            BSTree T0 = NULL;
                            printf("Please input filename:");
                            scanf("%s", filename);
                            getchar();
                            printf("\n");
                            if (load_data(&T1, filename)) {
                                printf("Successed to load!\n");
                                set_intersection(T, T1, &T0);
                                set_init(&T);
                                T = T0;
                                height(T, 0);
                                printf("Successed to take the intersection!\n");
                            } else
                                printf("Failed to load!\n");
                            break;
                        }
                        case 6: {
                            char filename[20];
                            BSTree T1 = NULL;
                            printf("Please input filename:");
                            scanf("%s", filename);
                            getchar();
                            printf("\n");
                            if (load_data(&T1, filename)) {
                                printf("Successed to load!\n");
                                set_union(&T, T1);
                                height(T, 0);
                                printf("Successed to union!\n");
                            } else
                                printf("Failed to load!\n");
                            break;
                        }
                        case 7: {
                            char filename[20];
                            BSTree T1 = NULL;
                            printf("Please input filename:");
                            scanf("%s", filename);
                            getchar();
                            printf("\n");
                            if (load_data(&T1, filename)) {
                                printf("Successed to load!\n");
                                set_difference(&T, T1);
                                height(T, 0);
                                printf("Successed to different!\n");
                            } else
                                printf("Failed to load!\n");
                            break;
                        }
                        case 8: {
                            int i = 0;
                            sum_ = 0;
                            i = size(T);
                            printf("size = %d", i);
                            break;
                        }
                        case 9: {
                            int key;
                            printf("Please input id:");
                            scanf("%d%*c", &key);
                            printf("\n");
                            if (set_member(T, key, &Ts))
                                printf("%d�Ǹü��ϵ�Ԫ��!\n",key);
                            else
                                printf("%d���Ǹü��ϵ�Ԫ��!\n",key);
                            break;
                        }

                        case 10:
                        {
                            char filename[20];
                            BSTree T1 = NULL;
                            printf("Please input filename:");
                            scanf("%s", filename);
                            getchar();
                            printf("\n");
                            if (load_data(&T1, filename))
                            {
                                if (set_subset(T, T1))
                                    printf("�ǵ�ǰ���ϵ��Ӽ�!\n");
                                else
                                    printf("���ǵ�ǰ���ϵ��Ӽ�!\n");
                            }
                            else
                                printf("Failed to load!\n");
                            break;
                        }
                        case 11:
                        {
                            char filename[20];
                            BSTree T1 = NULL;
                            printf("Please input filename:");
                            scanf("%s", filename);
                            getchar();
                            printf("\n");
                            if (load_data(&T1, filename))
                            {
                                if (set_equal(T, T1))
                                    printf("����������ͬ!\n");
                                else
                                    printf("�������ϲ�ͬ!\n");
                            }
                            else
                                printf("Failed to load!\n");
                            break;
                        }
                        case 12:

                            graph(T, 0, 0, fp);
                            break;
                        case 13:
                        {
                            char filename[20];
                            printf("Please input filename:");
                            scanf("%s", filename);
                            getchar();
                            printf("\n");
                            if (load_data(&T, filename))
                                printf("Successed to load!\n");
                            else
                                printf("Failed to load!\n");
                            break;
                        }
                        case 14:
                        {
                            FILE * fp;
                            char filename[20];
                            printf("Please input filename:");
                            scanf("%s", filename);
                            getchar();
                            printf("\n");
                            if ((fp = fopen(filename, "wb")) == NULL)
                            {
                                printf("Failed to open file!\n");
                                break;
                            }
                            if (save_data(T, fp))
                                printf("Successed to save!\n");
                            else
                                printf("Failed to save!\n");
                            fclose(fp);
                            break;
                        }

                        case 0:
                            printf("����������\n");
                            break;
                    }
                    getchar();
                    getchar();
                }
                break;
            case 3:
                op3 = 1;
                while (op3) {
                    system("cls");
                    printf("\n\n");
                    printf("                                   Ӧ�ò�  \n");
                    printf("---------------------------------------------------------------------------------\n");
                    printf("|    	           1. InsertPerson       2. DeletePerson                        |\n");
                    printf("|   	           3. MakeFriend         4. ReliveFriend                        |\n");
                    printf("|   	           5. SearchFriend       6. Add_A_Fans                          |\n");
                    printf("|   	           7. Relive_AFans       8. SearchFans                          |\n");
                    printf("|   	           9. Common_Fans        10. Commom_idols                       |\n");
                    printf("|   	           11. Friend's_Friends  12.Save                                |\n");
                    printf("|   	           13.Load               14. print_all_person                   |\n");
                    printf("|                  0. Exit\n");
                    printf("---------------------------------------------------------------------------------\n");
                    printf("                  ��ѡ����Ĳ���[0~13]:");
                    scanf("%d", &op3);
                    switch (op3) {
                        case 1:
                            Insert_A_Person();
                            getchar();
                            getchar();
                            break;
                        case 2:
                            Delete_A_Person();
                            getchar();
                            getchar();
                            break;
                        case 3:
                            Make_Friends();
                            getchar();
                            getchar();
                            break;
                        case 4:
                            Remove_Friends();
                            getchar();
                            getchar();
                            break;
                        case 5:
                            Search_Friends();
                            getchar();
                            getchar();
                            break;
                        case 6:
                            Add_A_Fans();
                            getchar();
                            getchar();
                            break;
                        case 7:
                            Remove_Fans();
                            getchar();
                            getchar();
                            break;
                        case 8:
                            Search_Fans();
                            getchar();
                            getchar();
                            break;
                        case 9:
                            Commom_Fans();
                            getchar();
                            getchar();
                            break;
                        case 10:
                            Commom_Idols();
                            getchar();
                            getchar();
                            break;
                        case 11:
                            TwoDFriends();
                            getchar();
                            getchar();
                            break;
                        case 12:
                            SaveToFile();
                            getchar();
                            getchar();
                            break;
                        case 13:

                            LoadFromFile();
                            getchar();
                            getchar();
                            break;
                        case 14:
                            print_now_person2();

                            getchar();
                            getchar();
                        case 0:
                            printf("����������\n");
                            break;

                    }
                }
                break;
            case 0:
                break;
        }
    }

    /*   while (op) {
           system("cls");
           system("mode con:cols=140 lines=180");
           printf("\n\n");
           printf("\t\tMenu for BinaryTree \n");
           printf("------------------------------------------------------\n");
           printf("1.InitAVL                          2.DestoryAVL\n");
           printf("3.SearchAVL                        4.InsertAVL\n");
           printf("5.DeleteAVL                        6.TraverseAVL\n");
           printf("7.graph                            8.randomAVL\n");
           printf("9.SaveAVL                          10.LoadAVL\n");
           printf("------------------------------------------------------\n");
           printf("11.create new data                 12.set init\n");
           printf("13.set destroy                     14.set insert\n");
           printf("15.set remove                      16.set intersection\n");
           printf("17.set union                       18.set difference\n");
           printf("19.set is member                   20.set is subset\n");
           printf("21.set is equal                    22.set size\n");
           printf("23.look through                    24.save data\n");
           printf("25.load\n");
           printf("------------------------------------------------------\n");
           printf("26.create                          27.traverse\n");
           printf("28.serch personal information      29.attention for both\n");
           printf("30.hobby for both                  31.indirect friends\n");
           printf("32.insert information              33.delete infomation\n");
           printf("34.motify information              35.find common hoobby friends\n");
           printf("0. Exit\n");
           printf("------------------------------------------------------\n");
           printf("��ѡ����Ĳ���[0~35]:");

       }*/
    return 0;
}