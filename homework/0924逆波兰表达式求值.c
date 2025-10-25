/*从键盘上输入一个后缀表达式，试编写算法计算表达式的值。
规定：逆波兰表达式的长度不超过一行，以"$"作为输入结束，
操作数之间用空格分隔，操作符只可能有+、-、*、/四种运算。
例如：23 4 3 4 + 2 * $*/
#include<stdio.h>
#include<stdlib.h>

#define SElemtype char
typedef struct 
{
    SElemtype *base;
    SElemtype *top;
    int stacksize;
}stack;

typedef enum
{
    OK=1,
    ERROR=0,
    OVERFLOW=-1,
}status;
//初始化
status init(stack *s,int m)
{
    s->base=(stack*)malloc(m*sizeof(stack));
    if(!s)
        return ERROR;
    s->top=s->base;
    s->stacksize=m;
    return OK;
}
//入栈
status enter(stack *s,SElemtype e)//初始设置的m即逆波兰表达式长度，一般不会溢出
{
    if(s->top-s->base>=m)
        return OVERFLOW;
    *(s->top)=e;
    s->top++;
    return OK;
}
//出栈
status leave(stack *s,SElemtype *e)
{
    if(s==NULL||e==NULL)
        return ERROR;
    e=*(s->top);
    s->top--;
    return OK;
}
//计算函数
int caculator(SElemtype *c,int m)
{
    stack *s;
    init(s);
    if(!s)
    {
        printf("failed to init stack\n");
        exit (0);
    }
    int i;
}
//主函数