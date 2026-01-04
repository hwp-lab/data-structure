/*试编写算法，对一棵以孩子-兄弟链表表示的树统计叶子的个数
对以孩子-兄弟链表表示的树编写计算树的深度的算法*/
#ifdef c_1105_//宏定义不可以数字开头
#define c_1105_

#include<stdio.h>

typedef char Elemtype;//为数据类型定义别名！！这么定义哎，都忘了,还要加分号

typedef struct node{
    Elemtype data;
    struct node *firstchild,*nextsibling;
}CSnode;

int getleafNum(CSnode *node){
    if(node == NULL)
        return 0;
    if(node->firstchild == NULL)
        return 1 + getleafNum(node->nextsibling);
    else
        return getleafNum(node->firstchild) + getleafNum(node->nextsibling);
}

int getDepth(CSnode *node) {
    if (node == NULL)
        return 0;
    
    int childDepth = getDepth(node->firstchild);  // 孩子子树深度
    int siblingDepth = getDepth(node->nextsibling);  // 兄弟子树深度
    
    if(childDepth + 1 > siblingDepth) 
        return childDepth + 1;
    else 
        return siblingDepth;
}
#endif