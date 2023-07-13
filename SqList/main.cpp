#include <stdio.h>
/**
 * 实现顺序表的增、删、改、查完整可运行代码
 */
#define MaxSize 50
typedef int ElemType;//为快速实现代码修改
typedef struct {
    ElemType data[MaxSize];
    int length;//顺序表长度
}SqList;
//顺序表的插入，因为L会改变，故用引用
bool ListInsert(SqList &L,int i,ElemType e){
    if(i<1||i>L.length+1){
        return false;
    }
    if(L.length>MaxSize){
        return false;
    }
    for (int j = L.length; j >=i ; j--) {
        L.data[j]=L.data[j-1];//将要插入位置的后面的元素一次后移
    }
    L.data[i-1]=e;//因数组下表从零开始
    L.length+=1;
    return true;
}

//打印顺序表元素
void PrintList(SqList L){
    for (int i = 0; i < L.length; i++) {
        printf("%4d",L.data[i]);
    }
    printf("\n");
}

//删除顺序表中的元素
bool ListDelete(SqList &L,int i,ElemType &del){
    if(i<1||i>L.length){//判断位置是否合法
        return false;
    }
    if(L.length==0){//顺序表无元素，无需删除
        return false;
    }
    del=L.data[i-1];//获取顺序表中对应的元素，赋值给del
    for (int j = i; j<L.length ; j++) {
        L.data[j-1]=L.data[j];
    }
    L.length--;
    return true;
}

//查找顺序表中元素e的位置，成功返回所在位序，失败返回0
int LocateElem(SqList L,ElemType e){
    for (int i = 0; i < L.length; ++i) {
        if(L.data[i]==e)
            return i+1;//加1就是元素在顺序表中的位置
    }
    return 0;
}

int main() {
    SqList L;//定义一个顺序表，变量L
    bool ret;
    L.data[0]=1;
    L.data[1]=2;
    L.data[2]=3;
    L.length=3;//设置长度
    ret = ListInsert(L,4,60);
    if(ret){
        printf("insert success!\n");
        PrintList(L);
    } else{
        printf("insert failed!\n");
    }
    printf("*********************\n");
    ElemType del;
    ret= ListDelete(L,3,del);
    if(ret){
        printf("delete success!\n");
        printf("delete elem=%d\n",del);//输出删除元素
        PrintList(L);
    } else{
        printf("delete failed!\n");
    }
    int elem_pos;//顺序表中元素位置
    elem_pos=LocateElem(L,60);
    if(elem_pos){
        printf("find it!\n");
        printf("elem location:%d\n",elem_pos);
        PrintList(L);
    } else{
        printf("not find!\n");
    }
    return 0;
}
