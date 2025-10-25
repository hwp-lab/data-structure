/*已知f为单链表的表头指针，链表中存储的都是整型数据，试写出实现下列运算的递归算法：​​
① 求链表中的最大整数；
② 求链表的结点个数；
③ 求所有整数的平均值。*/
#include<stdio.h>
#include<stdlib.h>
#include <limits.h>

//定义结构体
typedef struct linklist{
    int data;
    struct linklist *next;//不要落下struct！！！
} list;
//初始化链表
list *initial()
{
    list *head;
    head=NULL;
    return head;
}
//头插法插入元素
list *insert(list *head,int e)
{
    list *newnode;
    newnode=(list*)malloc(sizeof(list));
    if(!newnode){
        printf("error\n");
        exit(1);//0表示正常执行，1表示通用错误
    }
    newnode->data=e;
    newnode->next=head;

    head=newnode;

    return head;
}
//求链表中最大整数
int getmax(list *head)
{
    if(head==NULL)
        return INT_MIN;//<limits.h>里面

    int current_value=head->data;
    int rest_max;

    rest_max=getmax(head->next);

    if(current_value>rest_max)
        return current_value;
    else 
        return rest_max;
}
//求链表节点个数
int getlength(list *head)
{
    if(head==NULL)
        return 0;
    return 1+getlength(head->next);
}
//求所有整数平均值
int getsum(list *head)
{
    if(head==NULL)
        return 0;
    return head->data+getsum(head->next);
}
float getaverage(list *head)
{
    return (float)getsum(head)/getlength(head);
}
//清空链表
//清空并销毁链表：释放所有节点并把头指针置为NULL
void destroy(list **head)//如果只用 list* head（一级指针），函数内部修改 head不会影响外部的头指针，可能导致外部仍然持有已释放的内存地址（悬垂指针）。
{
    if(head == NULL || *head == NULL)//head == NULL：检查传入的二级指针是否合法（防止空指针解引用）。*head == NULL：检查链表是否为空（如果链表已经是空的，就不需要释放）
        return;

    list *p = *head;
    list *q;
    while(p != NULL)
    {
        q = p->next;
        free(p);
        p = q;
    }
    *head = NULL;
}

int main()
{
    list *head;
    head=initial();
    // 注意：insert 返回新的头指针，必须接收返回值
    head = insert(head,5);
    head = insert(head,4);
    head = insert(head,10);
    head = insert(head,-2);
    head = insert(head,1);
    head = insert(head,67);
    head = insert(head,-3);
    head = insert(head,55);
    head = insert(head,21);
    head = insert(head,4);

    int len = getlength(head);
    if(len == 0){
        printf("链表为空\n");
    } else {
        printf("链表中最大整数 = %d\n", getmax(head));
        printf("链表节点个数 = %d\n", len);
        printf("所有整数平均值 = %.6f\n", getaverage(head));
    }

    // 销毁并释放所有节点
    destroy(&head);
    return 0;
}



