#include "function.h"
/**
 * 二叉树层次建树实战，因暂不涉及遍历输出，故需通过打断点调试查看建树情况
 * @return
 */
int main() {
    BiTree pnew;//用来指向新申请的树结点
    BiTree tree=NULL;//tree是指向树根的，代表树
    char c;
    //phead、ptail风别指向队头和队尾，listpnew指向新生成的链表结点
    //pcur指向当前入队元素的父节点元素
    ptag_t phead=NULL,ptail=NULL,list_pnew=NULL,pcur;
    //abcdefghij
    while(scanf("%c",&c))
    {
        if(c=='\n')
        {
            break;//读取到换行就结束
        }
        //calloc申请的空间大小是两个参数直接相乘，并对空间进行初始化，赋值为0
        pnew= (BiTree)calloc(1,sizeof(BiTNode));
        pnew->c=c;
        list_pnew= (ptag_t)calloc(1,sizeof(tag_t));//给队列结点申请空间
        list_pnew->p=pnew;
        //如果是树的第一个结点
        if(NULL==tree)
        {
            tree=pnew;//tree指向树的根结点
            phead=list_pnew;//第一个结点即是队列头，也是队列尾
            ptail=list_pnew;
            pcur=list_pnew;//pcur要指向要进入树的父亲元素
        }else{
            //让元素先入队列
            ptail->pnext=list_pnew;
            ptail=list_pnew;
            //接下来把结点放入树中
            if(NULL==pcur->p->lchild)
            {
                pcur->p->lchild=pnew;//pcur->p左孩子为空，就放入左孩子
            }else if(NULL==pcur->p->rchild)
            {
                pcur->p->rchild=pnew;//pcur->p右孩子为空，就放入右孩子
                pcur=pcur->pnext;//当前结点左右孩子都有了，pcur就指向下一个
            }
        }
    }
    return 0;
}
