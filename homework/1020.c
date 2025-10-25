/*设任意n个整数存放于数组A[1..n]中，试编写算法，将所有正数排在所有负数前面*/
#include <stdio.h>
#define n 10
void tranfer(char *A){
    int i=0;
    int j=n-1;

    while(i<j){
        while(A[i]>0)
            i++;
        while(A[j]<0)
            j--;
        if(i<j){
            int t=A[i];
            A[i]=A[j];
            A[j]=t;
        }
    }
}
// 测试主函数
int main() {
    char arr[n] = {3, -2, 1, -5, 4, -1, 7, -8, 9, -3};
    
    printf("原始数组: ");
    for(int i = 0; i < n; i++){
        printf("%d ", arr[i]);
    }
    printf("\n");
    
    tranfer(arr);  // 调用函数进行重排
    
    printf("重排后数组: ");
    for(int i = 0; i < n; i++){
        printf("%d ", arr[i]);
    }
    printf("\n");
    
    return 0;
}