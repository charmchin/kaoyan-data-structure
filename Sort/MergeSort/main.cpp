#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 7
typedef int ElemType;
typedef struct{
    ElemType *elem;
    int TableLen;
}SSTable;
//生成随机数
void ST_Init(SSTable &ST,int len)//申请空间，并进行随机数生成
{
    ST.TableLen=len;
    ST.elem=(ElemType *)malloc(sizeof(ElemType)*ST.TableLen);
    int i;
    srand(time(NULL));
    for(i=0;i<ST.TableLen;i++)
    {
        ST.elem[i]=rand()%100;
    }
}
//关键代码，合并两个有序数组
void Merge(ElemType A[],int low,int mid,int high)
{
    static ElemType B[N];//加static的目的是无论递归调用多少次，都只有一个B[N]
    int i,j,k;
    for(i=low;i<=high;i++)//把A[i]里的元素都给B[i]
    {
        B[i]=A[i];
    }
    k=low;
    for(i=low,j=mid+1;i<=mid&&j<=high;)//合并两个有序数组
    {
        if(B[i]<B[j])
        {
            A[k]=B[i];
            i++;
            k++;
        }else{
            A[k]=B[j];
            j++;
            k++;
        }
    }
    //把某一个有序数组中剩余的元素放进来
    while(i<=mid)//前一半的有剩余的放入
    {
        A[k]=B[i];
        i++;
        k++;
    }
    while(j<=high)//后一半的有剩余的放入
    {
        A[k]=B[j];
        j++;
        k++;
    }
}
//归并排序不限制是两两归并，还是多个归并，考研都是考两两归并
void MergeSort(ElemType A[],int low,int high)//递归分割
{
    if(low<high)
    {
        int mid=(low+high)/2;
        MergeSort(A,low,mid);//排序好前一半
        MergeSort(A,mid+1,high);//排序好后一半
        Merge(A,low,mid,high);//讲两个排序好的数组合并
    }
}
void print(int* a)
{
    for(int i=0;i<N;i++)
    {
        printf("%3d",a[i]);
    }
    printf("\n");
}
//归并排序
int main() {
    //int A[N]={49,38,65,97,76,13,27};//数组，7个元素
    SSTable A;
    ST_Init(A,7);
    MergeSort(A.elem,0,6);
    print(A.elem);
    return 0;
}