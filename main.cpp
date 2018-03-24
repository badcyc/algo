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
    int gender;   //0代表男，1代表女
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

/*函数功能：判断两个人是否相同
  参数：待比较的两个值
  返回值：0代表不相同，1代表相同
*/
int IsSamePeople(info a, info b) {
    if (strcmp(a.name, b.name) != 0) return 0;
    if (a.age != b.age) return 0;
    if (a.gender != b.gender) return 0; //当三个数据均相同时才认为两人相同
    return 1;
}

/*函数功能：返回一棵树的树高
  参数：树根 root
  返回值：如果root为空返回-1，只有一个节点返回0，否则为其子树高度+1
*/
int getHeight(BitTree root) {
    if (root != NULL) return root->height;
    return -1;
}

/*函数功能：求二者的最大值
  参数：待比较的两个数
  返回值：大的数
*/
int Max(int a, int b) {
    if (a > b) return a;
    return b;
}

/*函数功能：判定a串比b串大
  参数： a,b字符串
  返回值：a比b大则返回1，否则返回0
*/

int namebigger(char *a, char *b) {
    if (strcmp(a, b) > 0) return 1;
    else return 0;
}

/*函数功能：判定a串比b串小
  参数： a,b字符串
  返回值：a比b小则返回1，否则返回0
*/
int namesmaller(char *a, char *b) {
    if (strcmp(a, b) < 0) return 1;
    else return 0;
}

void printNode(info data) {
    if (data.age == -1) {
        printf("无此人！！！\n");
        return;
    }
    printf("%s ", data.name);
    if (data.gender == 1) printf("woman ");
    else printf("man ");
    printf("age:%d\n", data.age);
}

/*函数功能：对单个节点右旋
  参数：节点
  返回值：空
*/
void zig(BitTree *x) {
    BitTree y = (*x)->lson;
    (*x)->lson = y->rson;
    y->rson = (*x);
    (*x)->height = Max(getHeight((*x)->lson), getHeight((*x)->rson)) + 1;
    y->height = Max(getHeight((*x)), getHeight(y->lson)) + 1;
    (*x) = y;
}

/*函数功能：对单个节点左旋
  参数：节点
  返回值：空
*/
void zag(BitTree *x) {
    BitTree y = (*x)->rson;
    (*x)->rson = y->lson;
    y->lson = (*x);
    (*x)->height = Max(getHeight((*x)->lson), getHeight((*x)->rson)) + 1;
    y->height = Max(getHeight((*x)), getHeight(y->rson)) + 1;
    (*x) = y;
}

/* 函数功能：对单个节点下的子树完成右旋再左旋
   参数：节点
   返回值：空
*/
void zigzag(BitTree *x) {
    zig(&((*x)->rson));
    zag(x);
}

/* 函数功能：对单个节点下的子树完成左旋再右旋
   参数：节点
   返回值：新的根节点
*/
void zagzig(BitTree *x) {
    zag(&((*x)->lson));
    zig(x);
}

/*函数功能：在树中查找节点x
  参数：树根root,节点名称：x
  返回值：空
  复杂度：O(logn)
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

/*函数功能：给树添加一个元素
  参数： 树根，元素
  返回值： 1代表添加成功，0代表失败（已存在）
  复杂度：O(logn)
*/
int InsertAVL(BitTree *root, info x) {
    int temp = 0;
    if ((*root) == NULL) {//如果节点为空,就在此节点处加入x信息
        (*root) = (BitTree) malloc(sizeof(BitNode));
        (*root)->data = x;
        (*root)->height = 0;
        (*root)->lson = NULL;
        (*root)->rson = NULL;
        return 1;
    }

    if (namebigger((*root)->data.name, x.name)) {//如果x小于节点的值,就继续在节点的左子树中插入x
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
    } else if (namesmaller((*root)->data.name, x.name)) {//如果x大于节点的值,就继续在节点的右子树中插入x
        if (InsertAVL(&((*root)->rson), x)) temp = 1;
        //如果高度之差为2的话就失去了平衡,需要旋转
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

/*函数功能：前序序遍历二叉树
  参数：树根
  返回值： 无
  复杂度：O(n)
*/
void TraverseAVL(BitTree root) {
    if (root == NULL) return;
    printNode(root->data);//输出根节点
    TraverseAVL(root->lson); //遍历左子树
    TraverseAVL(root->rson);//再遍历右子树
}

/*函数功能：初始化一个二叉树
  参数：指向二叉树树根的指针地址
  返回值：无
*/
void InitAVL(BitTree *root) {
    (*root) = NULL;
    //(*root)->height=-1;
    //(*root)->lson=NULL;(*root)->rson=NULL;
}

/*函数功能：删除二叉树的一个节点
  参数：树根root，节点x
  返回值： 未找到返回-1，删除成功返回0
  复杂度：O(logn)
*/
int DeleteAVL(BitTree *root, char *x) {
    if ((*root) == NULL) return -1;//未找到此节点
    if (namebigger((*root)->data.name, x)) {//在左子树内删除节点x
        DeleteAVL(&((*root)->lson), x);
        if (2 == getHeight((*root)->rson) - getHeight((*root)->lson)) {
            if ((*root)->rson->lson != NULL && getHeight((*root)->rson->lson) > getHeight((*root)->rson->rson))
                zigzag(root);
            else zag(root);
        }
    } else if (namesmaller((*root)->data.name, x)) {//在右子树内删除节点x
        DeleteAVL(&((*root)->rson), x);
        if (2 == getHeight((*root)->lson) - getHeight((*root)->rson)) {
            if ((*root)->lson->rson != NULL && getHeight((*root)->lson->rson) > getHeight((*root)->lson->lson))
                zagzig(root);
            else zig(root);
        }
    } else {//找到节点x
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
            if ((*root)->lson == NULL)//有右儿子或没有儿子
                (*root) = (*root)->rson;
            else if ((*root)->rson = NULL)//有左儿子
                (*root) = (*root)->lson;
            free(temp);
        }
    }
    if ((*root) == NULL) return 1;
    (*root)->height = Max(getHeight((*root)->lson), getHeight((*root)->rson)) + 1;
    return 1;
}

/*函数功能：对二叉树节点递归删除
  参数：根节点
  返回值：空
*/
void DestroyNode(BitTree *root) {
    if (*root == NULL) return;
    if ((*root)->lson != NULL) DestroyNode(&(*root)->lson);
    if ((*root)->rson != NULL) DestroyNode(&(*root)->rson);
    free(*root);
}

/*函数功能：销毁二叉树
  参数：指向二叉树树根的指针地址
  返回值：空
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
    int b; //balance平衡因数
    int h; //height深度
    struct BSTNode *lchild, *rchild;
} BSTNode, *BSTree;


BSTree Ts = NULL;

typedef void(*visit)(BSTree T);   //声明一种函数类型
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
bool set_member(BSTree T, int key, BSTree *Ts);//判断是否存在节点

bool set_member(BSTree T, int key, BSTree *Ts)//判断是否存在节点
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

void set_intersection(BSTree T, BSTree T1, BSTree *T0);//求交集
void set_intersection(BSTree T, BSTree T1, BSTree *T0)//求交集
{
    if (T1 == NULL)return;
    if (set_member(T, T1->data.id, &Ts))
        set_insert(T0, T1->data, &taller);
    set_intersection(T, T1->lchild, T0);
    set_intersection(T, T1->rchild, T0);
}

void set_union(BSTree *T, BSTree T1);//求并集
void set_union(BSTree *T, BSTree T1)//求并集
{
    if (T1 == NULL)return;
    set_insert(T, T1->data, &taller);
    set_union(T, T1->lchild);
    set_union(T, T1->rchild);
}

void set_difference(BSTree *T, BSTree T1);//求差
void set_difference(BSTree *T, BSTree T1)//求差
{
    if (*T == NULL || T1 == NULL)
        return;
    set_remove(T, T1->data.id, &shorter);
    set_difference(T, T1->lchild);
    set_difference(T, T1->rchild);
}


bool set_subset(BSTree TS, BSTree T1);//判断是否为子集
bool set_subset(BSTree T, BSTree T1)//判断是否为子集
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

void input_data(Information *data);//输入函数

void input_data(Information *data)//输入函数
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

void graph(BSTree T, int x, int y, visit fp);//将二叉树图形列表
void gotoxy(int x, int y)//移动光标
{
    COORD coord = {(SHORT) x, (SHORT) y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void graph(BSTree T, int x, int y, visit fp)//将二叉树图形列表
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

void operate_id(BSTree T);//输出所有成员id
void operate_relation(BSTree T1, BSTree T);

void operate_hobby(BSTree T1, BSTree H);

void gotoxy(int x, int y);//移动光标
void menu();

bool person_input(BSTree *T, int p_gross);//生成二叉树
bool hobby_set_input(BSTree *H, int *h_gross);//生成二叉树
void relation_input(BSTree *T, int p_gross, int h_gross);//二叉树的每个节点随机生成人际关系和兴趣爱好
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

void input_data(Information *data);//输入函数
void input_data_person(Information *data);

void PreOrderTraverse(BSTree T);//遍历每个节点
void indirect_friends_traverse(BSTree T, BSTree Tf, BSTree *T0);//遍历二度好友
void indirect_friends_insert(BSTree T, BSTree *T0);//将二度好友赋给T0
void adjust_traverse(BSTree T);

void complete_traverse(BSTree T, BSTree T0);             //完善函数
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

void set_init(set *group);// 初始化集合
void set_destroy(set *group); //销毁集合
int set_insert(set *group, info data); //插入元素
int set_remove(set *group, info data); //删除元素
set set_intersection(set groupA, set groupB); //集合的交
set set_union(set groupA, set groupB); //集合的并
set set_diffrence(set groupA, set groupB); //集合的差
int set_size(set group); //集合大小
int set_member(set group, info data); //判断一个元素是否为集合成员
int set_subset(set groupA, set groupB); //判断一个集合是否为另一个集合的子集
int set_equal(set groupA, set groupB); //判断两个集合是否相等
void treemerge(BitTree a, BitTree b, set *p);//求两棵树的交并插入新的集合中
void treeadd(BitTree a, set *p);//将一棵树插入新的集合中
void set_minus(set groupA, set groupB, set *p);//在A中除去B中的元素 并放到p中
int tree_subset(BitTree A, set p);//判断树A中元素是否都在p中
void set_Traverse(set group);//遍历输出集合
/*函数功能： 初始化集合
  参数： 集合指针
  返回值：空
*/
void set_init(set *group) {
    (*group) = (set) malloc(sizeof(Set));
    (*group)->avlTree = NULL;

    InitAVL(&((*group)->avlTree));
    (*group)->number = 0;
}

/*函数功能： 销毁集合
  参数： 集合指针
  返回值： 空
*/
void set_destroy(set *group) {
    DestroyAVL(&((*group)->avlTree));
    free(*group);
    *group = NULL;
}

/*函数功能： 插入元素
  参数： 集合指针 ，元素数据
  返回值：-1代表已经存在，1代表插入成功 0代表非法操作
  复杂度：O(logn)
*/
int set_insert(set *group, info data) {
    if ((*group) == NULL) return 0;
    if (InsertAVL(&((*group)->avlTree), data) == 1) {
        (*group)->number++;
        return 1;
    } else
        return -1;
}

/*函数功能： 删除元素
  参数： 集合指针 数据元素
  返回值：-1代表元素不存在，1代表删除成功 0代表非法操作
*/
int set_remove(set *group, info data) {
    if ((*group) == NULL) return 0;
    if (DeleteAVL(&((*group)->avlTree), data.name)) {
        (*group)->number--;
        return 1;
    } else return -1;

}

/*函数功能：求两棵树的交集
  参数： 树a，b 集合p
  返回值：空
*/
void treemerge(BitTree a, BitTree b, set *p) {
    if (a == NULL) return;
    info temp;
    temp = SearchAVL(b, a->data.name);
    if ((temp.age != -1)) set_insert(p, temp);
    treemerge(a->lson, b, p);
    treemerge(a->rson, b, p);
}

/*函数功能： 将一棵树中元素加入到集合中
  参数： 树a，集合p
  返回值：空
*/
void treeadd(BitTree a, set *p) {
    if (a == NULL) return;
    set_insert(p, a->data);
    treeadd(a->lson, p);
    treeadd(a->rson, p);
}

/*函数功能： 求两个集合的交集
  参数： 集合A，B
  返回值：交集 非法操作返回空
  复杂度：O(n)
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

/*函数功能： 求两集合的并
  参数： 集合A，B
  返回值：并集 非法操作返回空
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

/*函数功能： 将两棵树中不一样的元素放到新集合中
  参数： 树A,B 集合P
  返回值：空
*/
void set_minus(BitTree A, BitTree B, set *p) {
    if (A == NULL) return;
    info temp;
    temp = SearchAVL(B, A->data.name);
    if (temp.age == -1) set_insert(p, A->data);
    set_minus(A->lson, B, p);
    set_minus(A->rson, B, p);
}

/*函数功能： 求两集合的差
  参数： 集合A,B
  返回值：差集 非法操作返回空
  复杂度：O(n)
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

/*函数功能： 返回集合的大小
  参数： 集合
  返回值：集合大小 ,非法操作为-1;
*/
int set_size(set group) {
    if (group == NULL) return -1;
    return group->number;
}

/*函数功能： 判断元素是否为集合成员
  参数： 集合group 元素data
  返回值：是为1，否为0，非法操作为-1
*/
int set_member(set group, info data) {
    if (group == NULL) return -1;
    if (SearchAVL(group->avlTree, data.name).age != -1) return 1;
    else return 0;
}

/*函数功能： 判断集合A是否是B的子集
  参数： 集合A,集合B
  返回值：是则为1，不是为0;
*/
int tree_subset(BitTree A, set p) {
    if (A == NULL) return 1;
    if (SearchAVL(p->avlTree, A->data.name).age == -1) return 0;
    else {
        return tree_subset(A->lson, p) & tree_subset(A->rson, p);
    }
}

/*函数功能： 判断集合A是否是B的子集
  参数： 集合A,集合B
  返回值：是则为1，不是为0，非法操作为-1;
  复杂度：O(n)
*/
int set_subset(set groupA, set groupB) {
    if (groupA == NULL || groupB == NULL) return -1;
    if (tree_subset(groupA->avlTree, groupB)) return 1;
    else return 0;
}

/*函数功能： 判断两个集合是否相等
  参数： 集合A，B
  返回值：相等为1，否则为0，非法操作为-1
*/
int set_equal(set groupA, set groupB) {
    if (groupA == NULL || groupB == NULL) return -1;
    if (set_subset(groupA, groupB) == 1 && groupA->number == groupB->number) return 1;
    else return 0;
}

/*函数功能： 遍历输出一个集合
  参数： 集合group
  返回值：空
*/
void set_Traverse(set group) {
    printf("共：%d人\n", group->number);
    TraverseAVL(group->avlTree);
    //printf("******完毕*******\n");
}

typedef struct {   //定义应用层结构：人
    info Myinfo;
    set Myfriends;
    set Myfans;
    set Myidols;
} Person, *person;

void init_person(person *ren);//初始化一个人
void destroy_person(person *ren);//删除一个人
int add_friends(person *a, person *b);//a,b互相添加为好友
int remove_friends(person *a, person *b);//a,b互相解除好友
int search_friends(person *a, person *b);//查询a，b是否是好友
int add_fans(person *a, person *b);//a成为b的粉丝
int remove_fans(person *a, person *b);//a解除b的粉丝
int search_fans(person *a, person *b);//查询a是不是b的粉丝
int add_idols(person *a, person *b);//a成为b的关注
int remove_idols(person *a, person *b);//a解除是b的关注
int search_idols(person *a, person *b);//查询a是不是b的关注
set common_idols(person *a, person *b);//求a和b的共同关注
set common_fans(person *a, person *b);//求a和b的共同粉丝
set two_degree_friends(person *a);//求a的二度好友
void printPerson(person a);//打印输出一个人的信息
/*函数功能：  初始化一个人
  参数：  结构指针 a
  返回值： 空
*/
void init_person(person *a) {
    if ((*a) != NULL) destroy_person(a);
    (*a) = (person) malloc(sizeof(Person));
    set_init(&((*a)->Myfriends));
    set_init(&((*a)->Myfans));
    set_init(&((*a)->Myidols));
}

/*函数功能：  销毁一个人
  参数：  结构指针 a
  返回值： 空
*/
void destroy_person(person *ren) {
    if ((*ren) == NULL) return;
    set_destroy(&((*ren)->Myfriends));
    set_destroy(&((*ren)->Myfans));
    set_destroy(&((*ren)->Myidols));
    free(*ren);
}

/*函数功能：  添加两人互为朋友关系
  参数：  两个人a，b
  返回值： 添加成功为1，非法为-1
*/
int add_friends(person *a, person *b) {
    if ((*a) == NULL || (*b) == NULL) return -1;
    if (set_insert(&((*a)->Myfriends), (*b)->Myinfo) == 1 && set_insert(&((*b)->Myfriends), (*a)->Myinfo) == 1)
        return 1;
    else return 0;
}

/*函数功能：  解除两人的好友关系
  参数：  两个人a,b
  返回值： 解除成功为1，解除失败为0，非法操作为-1
*/
int remove_friends(person *a, person *b) {
    if ((*a) == NULL || (*b) == NULL) return -1;
    if (search_friends(a, b) != 1) return 0;
    if (set_remove(&((*a)->Myfriends), (*b)->Myinfo) == 1 && set_remove(&((*b)->Myfriends), (*a)->Myinfo) == 1)
        return 1;
    else return 0;
}

/*函数功能： 查找两人是否为好友关系
  参数：  两个人a,b
  返回值： 是则为1，否为0，非法为-1
*/
int search_friends(person *a, person *b) {
    if ((*a) == NULL || (*b) == NULL) return -1;
    if (set_member((*a)->Myfriends, (*b)->Myinfo) == 1) return 1;
    else return 0;
}

/*函数功能：  添加a为b的粉丝
  参数：  两个人a,b
  返回值： 添加成功为1，失败为0，非法为-1
*/
int add_fans(person *a, person *b) {
    if ((*a) == NULL || (*b) == NULL) return -1;
    if (set_insert(&((*b)->Myfans), (*a)->Myinfo) == 1 && set_insert(&((*a)->Myidols), (*b)->Myinfo) == 1) return 1;
    else return 0;
}

/*函数功能：  解除a是b的粉丝
  参数：  两个人a,b
  返回值： 解除成功为1，失败为0，非法为-1
*/
int remove_fans(person *a, person *b) {
    if ((*a) == NULL || (*b) == NULL) return -1;
    if (search_fans(a, b) != 1) return 0;
    if (set_remove(&((*b)->Myfans), (*a)->Myinfo) == 1 && set_remove(&((*a)->Myidols), (*b)->Myinfo) == 1) return 1;
    else return 0;
}

/*函数功能： 查询a是不是b的粉丝
  参数：  两个人a,b
  返回值： 是则返回，否则返回0，非法为-1
*/
int search_fans(person *a, person *b) {
    if ((*a) == NULL || (*b) == NULL) return -1;
    if (set_member((*b)->Myfans, (*a)->Myinfo) == 1) return 1;
    else return 0;
}

/*函数功能：  添加a为b的关注
  参数：  两个人a,b
  返回值： 添加成功为1，失败为0，非法为-1
*/
int add_idols(person *a, person *b) {
    if ((*a) == NULL || (*b) == NULL) return -1;
    if (set_insert(&((*b)->Myidols), (*a)->Myinfo) == 1 && set_insert(&((*a)->Myfans), (*b)->Myinfo) == 1) return 1;
    else return 0;
}

/*函数功能：  解除a是b的关注
  参数：  两个人a,b
  返回值： 解除成功为1，失败为0，非法为-1
  */
int remove_idols(person *a, person *b) {
    if ((*a) == NULL || (*b) == NULL) return -1;
    if (search_idols(a, b) != 1) return 0;
    if (set_remove(&((*b)->Myidols), (*a)->Myinfo) == 1 && set_remove(&((*a)->Myfans), (*b)->Myinfo) == 1) return 1;
    else return 0;
}

/*函数功能： 查询a是不是b的关注
  参数：  两个人a,b
  返回值： 是则返回，否则返回0，非法为-1
*/

int search_idols(person *a, person *b) {
    if ((*a) == NULL || (*b) == NULL) return -1;
    if (set_member((*b)->Myidols, (*a)->Myinfo) == 1) return 1;
    else return 0;
}

/*函数功能：  求两个人的共同关注
  参数：  两个人a,b
  返回值： 共同关注的集合
*/
set common_idols(person *a, person *b) {
    return set_intersection((*a)->Myidols, (*b)->Myidols);
}

/*函数功能：  求两个人的共同粉丝
  参数：  两个人a,b
  返回值： 共同粉丝的集合
*/
set common_fans(person *a, person *b) {
    return set_intersection((*a)->Myfans, (*b)->Myfans);
}


person personList[20];

/*函数功能：  求一个人的二度好友
  参数：  一个人a
  返回值： a的所有二度好友构成的集合
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

/*函数功能：  输出一个人
  参数：  一个人a
  返回值： void
*/
void printPerson(person a) {
    if (a == NULL) return;
    printf("名字是：%s 性别是：", a->Myinfo.name);
    if (a->Myinfo.gender == 0) printf("男 ");
    else printf("女 ");
    printf("年龄是：%d\n", a->Myinfo.age);
    if (a->Myfriends->number > 0) {
        printf("Ta的好友包括：\n");
        set_Traverse(a->Myfriends);
    } else printf("Ta没有好友\n");
    if (a->Myfans->number > 0) {
        printf("Ta的粉丝包括：\n");
        set_Traverse(a->Myfans);
    } else printf("Ta没有粉丝\n");
    if (a->Myidols->number > 0) {
        printf("Ta的关注包括：\n");
        set_Traverse(a->Myidols);
    } else printf("Ta没有关注\n");
    printf("******完毕*******\n");
}

int op = 1;

/*函数功能：  打印现有成员信息
  参数：  void
  返回值： 现有成员个数
*/
int print_now_person() {
    int ans = 0;
    for (int i = 0; i < 20; i++) {
        if (personList[i] == NULL) continue;
        ans = i + 1;
       // printf("第%d位用户为 : %s\n", ans, personList[i]->Myinfo.name);
    }
    if (ans == 0) {
        printf("当前还无用户！！\n");
    }
    return ans;
}

void print_now_person2(){
    int ans = 0;
    for (int i = 0; i < 20; i++) {
        if (personList[i] == NULL) continue;
        ans = i + 1;
        printf("第%d位用户为 : %s\n", ans, personList[i]->Myinfo.name);
    }
    if (ans == 0) {
        printf("当前还无用户！！\n");
    }
}

/*函数功能：  添加一位用户
  参数：  void
  返回值： void
*/
void Insert_A_Person() {
   // printf("现有用户数据如下：\n");
    int now = print_now_person();
    printf("--------------------------------\n");
    info temp;
    printf("请输入用户姓名，注意不要与存在用户姓名重复：\n");
    scanf("%s", temp.name);
    printf("请输入用户性别，0代表男，1代表女：\n");
    scanf("%d", &temp.gender);
    printf("请输入用户年龄，0~99之间：\n");
    scanf("%d", &temp.age);
    for (int i = 0; i < 20; i++) {
        if (personList[i] == NULL) continue;
        if (strcmp(personList[i]->Myinfo.name, temp.name) == 0) {
            printf("输入已存在，请重新操作\n");
            return;
        }
    }
    if (temp.gender != 0 && temp.gender != 1) {
        printf("性别输入错误，请重新操作\n");
        return;
    }
    if (temp.age < 0 || temp.age > 99) {
        printf("年龄输入错误，请重新操作\n");
        return;
    }
    init_person(&personList[now]);
    personList[now]->Myinfo = temp;
    printf("添加成功!\n");
}

/*函数功能：  删除一位用户
  参数：  void
  返回值： void
*/
void Delete_A_Person() {
  //  printf("现有用户数据如下：\n");
    int now = print_now_person();
    printf("--------------------------------\n");
    int del;
    printf("请输入要删除的用户编号：（在1--%d之间）\n", now);
    scanf("%d", &del);
    if (del < 1 || del > now) {
        printf("编号输入有误，请重新操作\n");
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
    printf("删除成功！\n");
}

/*函数功能：  增添两个人的好友关系
  参数：  void
  返回值： void
*/
void Make_Friends() {
  //  printf("现有用户数据如下：\n");
    int now = print_now_person();
    printf("--------------------------------\n");
    int per1, per2;
    printf("请输入两位用户的编号：\n用户1：\n");
    scanf("%d", &per1);
    printf("用户2：\n");
    scanf("%d", &per2);
    if (per1 < 1 || per1 > now || per2 < 1 || per2 > now) {
        printf("编号输入有误，请重新操作\n");
        return;
    }
    if (search_friends(&personList[per1 - 1], &personList[per2 - 1]) == 1) {
        printf("这两位已经是好友了！！\n");
        return;
    } else {
        if (add_friends(&personList[per1 - 1], &personList[per2 - 1]) == 1) printf("操作成功！！\n");
        else printf("操作失败！！\n");
        return;
    }
}

/*函数功能：  删除两个人的好友关系
  参数：  void
  返回值： void
*/
void Remove_Friends() {
    //printf("现有用户数据如下：\n");
    int now = print_now_person();
    printf("--------------------------------\n");
    int per1, per2;
    printf("请输入两位用户的编号：\n用户1：\n");
    scanf("%d", &per1);
    printf("用户2：\n");
    scanf("%d", &per2);
    if (per1 < 1 || per1 > now || per2 < 1 || per2 > now) {
        printf("编号输入有误，请重新操作\n");
        return;
    }
    if (search_friends(&personList[per1 - 1], &personList[per2 - 1]) != 1) {
        printf("这两位还不是好友！！\n");
        return;
    } else {
        if (remove_friends(&personList[per1 - 1], &personList[per2 - 1]) == 1) printf("操作成功！！\n");
        else printf("操作失败！！\n");
        return;
    }
}

/*函数功能：  查询两个人是不是好友
  参数：  void
  返回值： void
*/
void Search_Friends() {
   // printf("现有用户数据如下：\n");
    int now = print_now_person();
    printf("--------------------------------\n");
    int per1, per2;
    printf("请输入两位用户的编号：\n用户1：\n");
    scanf("%d", &per1);
    printf("用户2：\n");
    scanf("%d", &per2);
    if (per1 < 1 || per1 > now || per2 < 1 || per2 > now) {
        printf("编号输入有误，请重新操作\n");
        return;
    }
    if (search_friends(&personList[per1 - 1], &personList[per2 - 1]) != 1) {
        printf("这两位还不是好友！！\n");
        return;
    } else {
        printf("这两位确实是好友！！\n");
        return;
    }
}

/*函数功能：  添加一个人为另一个的粉丝
  参数：  void
  返回值： void
*/
void Add_A_Fans() {
  //  printf("现有用户数据如下：\n");
    int now = print_now_person();
    printf("--------------------------------\n");
    int per1, per2;
    printf("请输入两位用户的编号：\n用户1：（粉丝）\n");
    scanf("%d", &per1);
    printf("用户2：（偶像）\n");
    scanf("%d", &per2);
    if (per1 < 1 || per1 > now || per2 < 1 || per2 > now) {
        printf("编号输入有误，请重新操作\n");
        return;
    }
    if (search_fans(&personList[per1 - 1], &personList[per2 - 1]) == 1) {
        printf("Ta已经是Ta的粉丝了！！\n");
        return;
    } else {
        if (add_fans(&personList[per1 - 1], &personList[per2 - 1]) == 1) printf("操作成功！！\n");
        else printf("操作失败！！\n");
        return;
    }
}

/*函数功能：  解除一个人为另一个的粉丝
  参数：  void
  返回值： void
*/
void Remove_Fans() {
  //  printf("现有用户数据如下：\n");
    int now = print_now_person();
    printf("--------------------------------\n");
    int per1, per2;
    printf("请输入两位用户的编号：\n用户1：（粉丝）\n");
    scanf("%d", &per1);
    printf("用户2：（偶像）\n");
    scanf("%d", &per2);
    if (per1 < 1 || per1 > now || per2 < 1 || per2 > now) {
        printf("编号输入有误，请重新操作\n");
        return;
    }
    if (search_fans(&personList[per1 - 1], &personList[per2 - 1]) != 1) {
        printf("Ta还不是Ta的粉丝！！\n");
        return;
    } else {
        if (remove_fans(&personList[per1 - 1], &personList[per2 - 1]) == 1) printf("操作成功！！\n");
        else printf("操作失败！！\n");
        return;
    }
}

/*函数功能：  查询一个人是不是另一个的粉丝
  参数：  void
  返回值： void
*/
void Search_Fans() {
   // printf("现有用户数据如下：\n");
    int now = print_now_person();
    printf("--------------------------------\n");
    int per1, per2;
    printf("请输入两位用户的编号：\n用户1：（粉丝）\n");
    scanf("%d", &per1);
    printf("用户2：（偶像）\n");
    scanf("%d", &per2);
    if (per1 < 1 || per1 > now || per2 < 1 || per2 > now) {
        printf("编号输入有误，请重新操作\n");
        return;
    }
    if (search_fans(&personList[per1 - 1], &personList[per2 - 1]) != 1) {
        printf("Ta还不是Ta的粉丝！！\n");
        return;
    } else {
        printf("Ta确实是Ta的粉丝！！\n");
        return;
    }
}

/*函数功能：  查询两个人的共同粉丝
  参数：  void
  返回值： void
*/
void Commom_Fans() {
    //printf("现有用户数据如下：\n");
    int now = print_now_person();
    printf("--------------------------------\n");
    int per1, per2;
    printf("请输入两位用户的编号：\n用户1：\n");
    scanf("%d", &per1);
    printf("用户2：\n");
    scanf("%d", &per2);
    if (per1 < 1 || per1 > now || per2 < 1 || per2 > now) {
        printf("编号输入有误，请重新操作\n");
        return;
    }
    printf("他们的共同粉丝包括如下：\n");
    set_Traverse(common_fans(&personList[per1 - 1], &personList[per2 - 1]));
    return;
}

/*函数功能：  查询两个人的共同关注
  参数：  void
  返回值： void
*/
void Commom_Idols() {
   // printf("现有用户数据如下：\n");
    int now = print_now_person();
    printf("--------------------------------\n");
    int per1, per2;
    printf("请输入两位用户的编号：\n用户1：\n");
    scanf("%d", &per1);
    printf("用户2：\n");
    scanf("%d", &per2);
    if (per1 < 1 || per1 > now || per2 < 1 || per2 > now) {
        printf("编号输入有误，请重新操作\n");
        return;
    }
    printf("他们的共同关注包括如下：\n");
    set_Traverse(common_idols(&personList[per1 - 1], &personList[per2 - 1]));
    return;
}

/*函数功能：  查询两一个人的二度好友
  参数：  void
  返回值： void
*/
void TwoDFriends() {
   // printf("现有用户数据如下：\n");
    int now = print_now_person();
    printf("--------------------------------\n");
    int per1;
    printf("请输入要查询的用户的编号：\n");
    scanf("%d", &per1);
    if (per1 < 1 || per1 > now) {
        printf("编号输入有误，请重新操作\n");
        return;
    }
    printf("他Ta的二度好友包括如下：\n");
    set_Traverse(two_degree_friends(&personList[per1 - 1]));
    return;
}

/*函数功能：  将数据写入到文件中
  参数：  void
  返回值： void
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
    printf("已成功保存！！！\n");
}

/*函数功能：  从文件中读取数据
  参数：  void
  返回值： void
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
    printf("读取成功！！！\n");
}

void Traverse(BSTree T)//遍历每个节点
{
    if (T == NULL)return;
    printf("%3d  ", T->data.id);
    Traverse(T->lchild);
    Traverse(T->rchild);
    return;
}

void operate_id(BSTree T)//输出所有成员id
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
        printf("                                    主界面\n");
        printf("                 ----------------------------------------------------\n");
        printf("                 |                   1. AVL层                        |\n");
        printf("                 |                   2. set层                        |\n");
        printf("                 |                   3. 应用层                       |\n");
        printf("                 |                   0. 退出程序                     |\n");
        printf("                 -----------------------------------------------------\n");
        printf("                                   请输入你的选择:");
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
                    printf("                |                           0. 返回主界面                     |\n");
                    printf("-----------------------------------------------------------------------------------\n");
                    printf("                  请选择你的操作[0~6]: ");
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
                    printf("                |                        0. 返回主界面                        |\n");
                    printf("                  请选择你的操作[0~14]:\n");
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
                                printf("%d是该集合的元素!\n",key);
                            else
                                printf("%d不是该集合的元素!\n",key);
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
                                    printf("是当前集合的子集!\n");
                                else
                                    printf("不是当前集合的子集!\n");
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
                                    printf("两个集合相同!\n");
                                else
                                    printf("两个集合不同!\n");
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
                            printf("返回主界面\n");
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
                    printf("                                   应用层  \n");
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
                    printf("                  请选择你的操作[0~13]:");
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
                            printf("返回主界面\n");
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
           printf("请选择你的操作[0~35]:");

       }*/
    return 0;
}