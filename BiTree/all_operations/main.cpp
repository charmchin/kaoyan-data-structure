#include <stdio.h>
#include <stdlib.h>
/**
 * �漰�����������л���������ʵ��
 */

typedef char BiElemType;
typedef struct BiTNode{
    BiElemType c;
    struct BiTNode *lchild;
    struct BiTNode *rchild;
}BiTNode, *BiTree;

//tag�ṹ���Ǹ�������ʹ�õ�
typedef struct tag{
    BiTree p;//����ĳһ�����ĵ�ֵַ
    struct tag *pnext;
}tag_t, *ptag_t;

//ջ��������ݽṹ
#define MaxSize 50
typedef BiTree ElemType;
typedef struct{
    ElemType data[MaxSize];
    int top;
}SqStack;

//�Ժ������������ⲽ���������Լ��ع�ѧϰ
void InitStack(SqStack &S);
bool StackEmpty(SqStack &S);
bool Push(SqStack &S, ElemType x);
bool Pop(SqStack &S, ElemType &x);
bool GetTop(SqStack &S, ElemType &x);

//���е�������ݽṹ
typedef struct LinkNode{
    ElemType data;
    struct LinkNode *next;
}LinkNode;
typedef struct{
    LinkNode *front, *rear;
}LinkQueue;
void InitQueue(LinkQueue &Q);
bool IsEmpty(LinkQueue Q);
void EnQueue(LinkQueue &Q, ElemType x);
bool DeQueue(LinkQueue &Q, ElemType &x);

//queue���
//��ͷ���Ķ���
void InitQueue(LinkQueue &Q)
{
    Q.front = Q.rear = (LinkNode*)malloc(sizeof(LinkNode));
    Q.front->next = NULL;
}

bool IsEmpty(LinkQueue Q)
{
    if (Q.front == Q.rear)
        return true;
    else
        return false;
}

void EnQueue(LinkQueue &Q, ElemType x)
{
    LinkNode *s = (LinkNode *)malloc(sizeof(LinkNode));
    s->data = x; s->next = NULL;
    Q.rear->next = s;
    Q.rear = s;
}

bool DeQueue(LinkQueue &Q, ElemType &x)
{
    if (Q.front == Q.rear) return false;
    LinkNode *p = Q.front->next;//ͷ���ʲô��û�棬����ͷ������һ���ڵ��������
    x = p->data;
    Q.front->next = p->next;
    if (Q.rear == p)
        Q.rear = Q.front;
    free(p);
    return true;
}

//stack���
void InitStack(SqStack &S)
{
    S.top = -1;
}

bool StackEmpty(SqStack &S)
{
    if (S.top == -1)
        return true;
    else
        return false;
}
//��ջ
bool Push(SqStack &S, ElemType x)
{
    if (S.top == MaxSize - 1)
    {
        return false;
    }
    S.data[++S.top] = x;
    return true;
}
//��ջ
bool Pop(SqStack &S, ElemType &x)
{
    if (-1 == S.top)
        return false;
    x = S.data[S.top--];
    return true;
}
//��ȡջ��Ԫ��
bool GetTop(SqStack &S, ElemType &x)
{
    if (-1 == S.top)
        return false;
    x = S.data[S.top];
    return true;
}

//main���
//�ݹ�ʵ��
//abdhiejcfg  ǰ�������ǰ���������������ȱ���
void preOrder(BiTree p)
{
    if (p != NULL)
    {
        putchar(p->c);//�ȼ���visit����
        preOrder(p->lchild);
        preOrder(p->rchild);
    }
}
//�������  hdibjeafcg
void InOrder(BiTree p)
{
    if (p != NULL)
    {
        InOrder(p->lchild);
        putchar(p->c);
        InOrder(p->rchild);
    }
}
//hidjebfgca  �������
void PostOrder(BiTree p)
{
    if (p != NULL)
    {
        PostOrder(p->lchild);
        PostOrder(p->rchild);
        putchar(p->c);
    }
}
//��������ǵݹ飬�ǵݹ�ִ��Ч�ʸ��ߣ����ĸ��ʺܵ�
void InOrder2(BiTree T)
{
    SqStack S;
    InitStack(S);
    BiTree p = T;
    while (p || !StackEmpty(S))//�߼���||
    {
        if (p)
        {//��һ����㲻Ϊ�գ�ѹջ����ȡ����
            Push(S, p);
            p = p->lchild;
        }
        else{//����ջ��Ԫ�ز���ӡ����ȡ��ӡԪ�ص��ҽ��
            Pop(S, p);
            putchar(p->c);
            p = p->rchild;
        }
    }
}
//��α���,���������������ȱ���
void LevelOrder(BiTree T)
{
    LinkQueue Q;//��������
    InitQueue(Q);//��ʼ������
    BiTree p;
    EnQueue(Q, T);//�������
    while (!IsEmpty(Q))
    {
        DeQueue(Q, p);//���ӵ�ǰ��㲢��ӡ
        putchar(p->c);
        if (p->lchild != NULL) //�������
            EnQueue(Q, p->lchild);
        if (p->rchild != NULL)  //����Һ���
            EnQueue(Q, p->rchild);
    }
}

//�������Ľ�������ν�������ǰ�����򡢺������������ǵݹ��������α���
int main()
{
    BiTree pnew;
    int i, j, pos;
    char c;
    BiTree tree = NULL;//����
    ptag_t phead = NULL, ptail = NULL, listpnew = NULL, pcur = NULL;//phead���Ƕ���ͷ��ptail���Ƕ���β
    //abcdefghij
    while (scanf("%c", &c) != EOF)
    {
        if (c == '\n')
        {
            break;
        }
        pnew = (BiTree)calloc(1, sizeof(BiTNode));//calloc����ռ䲢�Կռ���г�ʼ������ֵΪ0
        pnew->c = c;//���ݷŽ�ȥ
        listpnew = (ptag_t)calloc(1, sizeof(tag_t));//�����н������ռ�
        listpnew->p = pnew;
        if (NULL == tree)//����д��ţ
        {
            tree = pnew;//���ĸ�
            phead = listpnew;//����ͷ
            ptail = listpnew;//����β
            pcur = listpnew;
            continue;
        }
        else{
            ptail->pnext = listpnew;//�½���������ͨ��β�巨
            ptail = listpnew;//ptailָ�����β��
        }//pcurʼ��ָ��Ҫ����Ľ���λ��
        if (NULL == pcur->p->lchild)//��ΰ��½�������
        {
            pcur->p->lchild = pnew;//���½��ŵ�Ҫ����������
        }
        else if (NULL == pcur->p->rchild)
        {
            pcur->p->rchild = pnew;//���½��ŵ�Ҫ��������ұ�
            pcur = pcur->pnext;//���Ҷ����˽���pcurָ����е���һ��
        }
    }
    printf("--------ǰ�����----------\n");//Ҳ������������ȴ�ӡ��ǰ��㣬��ӡ���ӣ���ӡ�Һ���
    preOrder(tree);
    printf("\n--------�������------------\n");//�ȴ�ӡ���ӣ���ӡ���ף���ӡ�Һ���
    InOrder(tree);
    printf("\n--------�������------------\n");//�ȴ�ӡ���ӣ���ӡ�Һ��ӣ�����ӡ����
    PostOrder(tree);
    printf("\n--------��������ǵݹ�------\n");//��Ҫ�Ե�
    InOrder2(tree);
    printf("\n--------��α���-----------\n");
    LevelOrder(tree);
    printf("\n");
}