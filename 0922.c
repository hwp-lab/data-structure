/*(1)将编号为0和1的两个栈存放于一个数组空间V[m]中,栈底分别处于数组的两端。
当第 0号栈的栈顶指针top[0]等于-1时该栈为空;当第1号栈的栈顶指针top[1]等于m时,该栈为空。
 两个栈均从两端向中间增长
 试编写双栈初始化,判断栈空、栈满、进栈和出栈等算。 法的函数。双栈数据结构的定义如下:
typedef struct
int top[2], bot [2]; //栈顶和栈底指针
 SElemType *V; //栈数组 
 int m; //栈最大可容纳元素个数!
  )Dblstack;*/
#include<stdio.h>
#include<stdlib.h>

#define SElemType int 

//定义双栈数据结构体
typedef struct 
{
    int top[2], bot [2]; //栈顶和栈底指针,整型哎，表示在数组中的位置！
    SElemType *V; //栈数组 
    int m; //栈最大可容纳元素个数!
}Dblstack;

//定义status
typedef enum//枚举 定义一组相关常量
{
    OK=1,
    ERROR=0,
    OVERFLOW=-1,//枚举类型用逗号
}status;

//双栈初始化
status init(Dblstack *stack, int maxsize)
{
    if(stack==NULL||maxsize<=0)
        return ERROR;
    stack->V=(SElemType*)malloc(maxsize*sizeof(SElemType));
    if(!stack->V)
        return OVERFLOW;

    stack->top[0]=-1;
    stack->bot[0]=0;

    stack->top[1]=maxsize;
    stack->bot[1]=maxsize-1;

    stack->m=maxsize;

    return OK;
}
//栈空
int ifempty(Dblstack *stack)
{
    if(stack->top[0]==-1&&stack->top[1]==stack->m)
        return 1;
    else 
        return 0;
}
//栈满
int iffull(Dblstack *stack)
{
    if(stack==NULL)
        return -1;
    if(stack->top[0]+1==stack->top[1])//top是顶指针！
        return 1;
    return 0;
}
//进栈
int enter(Dblstack *stack,int i,SElemType e)
{
    if(iffull(stack))
    {
        printf("the stack is full\n");
        return OVERFLOW;
    }
    if(i!=0&&i!=1)
        return ERROR;
    
    if(i==0)
    {
        stack->top[0]++;
        stack->V[stack->top[0]]=e;
    }
    else
    {
        stack->top[1]--;
        stack->V[stack->top[1]]=e;
    }

    return 0;
}
//出栈
int leave(Dblstack *stack,int i,SElemType *e)
{
    if(ifempty(stack)||e==NULL)
    {
        printf("the stack is empty\n");
        return ERROR;
    }

    if(i!=0&&i!=1)
        return ERROR;
    
    if(i==0)
    {
        if(stack->top[0] == -1)
         {  // 左栈空
            printf("左栈为空，无法出栈\n");
            return ERROR;
         }
        *e=stack->V[stack->top[0]];
        stack->top[0]--;
        printf("从左栈弹出元素: %d\n", *e);
    }
    if(i==1)
    {
        if(stack->top[1] == stack->m) 
        {  // 右栈空
            printf("右栈为空，无法出栈\n");
            return ERROR;
        }
        *e=stack->V[stack->top[1]];
        stack->top[1]++;
        printf("从右栈弹出元素: %d\n", *e);
    }

    return OK;
}
// 释放栈内存
void destroy(Dblstack *stack)
{
    if(stack != NULL && stack->V != NULL)
    {
        free(stack->V);
        stack->V = NULL;//指针置空(否则变成指向的内存已经被释放，但指针本身仍然保存着原内存地址​​的悬垂指针)
    }
}
//主函数 腾讯元宝给的测试主函数，学一学
int main()
{
    Dblstack stack;
    SElemType value;
    int i;
    
    printf("=== 双栈测试开始 ===\n");
    
    // 1. 测试初始化
    printf("\n1. 初始化双栈（容量10）...\n");
    if(init(&stack, 10) == OK) {//整个代码都用status哎
        printf("初始化成功！\n");
    } else {
        printf("初始化失败！\n");
        return -1;
    }
    
    // 2. 测试栈空判断
    printf("\n2. 测试栈空判断...\n");
    if(ifempty(&stack)) {
        printf("双栈均为空（正确）\n");
    } else {
        printf("栈非空（异常）\n");
    }
    
    // 3. 测试向左栈压入数据
    printf("\n3. 向左栈压入数据：1, 2, 3, 4, 5\n");
    for(i = 1; i <= 5; i++) {
        enter(&stack, 0, i);
    }
    
    // 4. 测试向右栈压入数据
    printf("\n4. 向右栈压入数据：10, 20, 30, 40\n");
    for(i = 1; i <= 4; i++) {
        enter(&stack, 1, i * 10);
    }
    
    // 5. 测试栈满判断
    printf("\n5. 测试栈满判断...\n");
    if(iffull(&stack)) {
        printf("栈已满（当前使用情况）\n");
    } else {
        printf("栈未满，剩余空间: %d\n", stack.top[1] - stack.top[0] - 1);
    }
    
    // 6. 测试从左栈弹出数据
    printf("\n6. 从左栈弹出2个元素：\n");
    leave(&stack, 0, &value);
    leave(&stack, 0, &value);
    
    // 7. 测试从右栈弹出数据
    printf("\n7. 从右栈弹出2个元素：\n");
    leave(&stack, 1, &value);
    leave(&stack, 1, &value);
    
    // 8. 测试栈空再次判断
    printf("\n8. 再次测试栈空判断...\n");
    if(ifempty(&stack)) {
        printf("双栈均为空\n");
    } else {
        printf("栈非空（正确）\n");
    }
    
    // 9. 测试边界情况
    printf("\n9. 测试边界情况：\n");
    
    // 尝试从空左栈弹出
    printf("尝试从空左栈弹出：");
    if(leave(&stack, 0, &value) == ERROR) {
        printf("左栈为空（预期结果）\n");
    }
    
    // 尝试从空右栈弹出
    printf("尝试从空右栈弹出：");
    if(leave(&stack, 1, &value) == ERROR) {
        printf("右栈为空（预期结果）\n");
    }
    
    // 10. 测试栈满情况
    printf("\n10. 测试栈满情况：\n");
    printf("向左栈压入数据直到栈满...\n");
    for(i = 6; i <= 15; i++) {
        if(enter(&stack, 0, i) == OVERFLOW) {
            printf("栈已满，无法继续压入 %d\n", i);
            break;
        }
    }
    
    // 11. 打印最终栈状态
    printf("\n11. 最终栈状态：\n");
    printf("左栈顶位置: %d, 右栈顶位置: %d\n", stack.top[0], stack.top[1]);
    printf("剩余空间: %d\n", stack.top[1] - stack.top[0] - 1);
    
    // 12. 释放内存
    printf("\n12. 释放栈内存...\n");
    destroy(&stack);
    printf("内存释放完成！\n");
    
    printf("\n=== 双栈测试结束 ===\n");
    
    return 0;
}