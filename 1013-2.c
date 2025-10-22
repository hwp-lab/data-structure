/*给定字符串“abaababc”，求 next[] 值。​​
​​答案为：{-1, 0, 0, 1, 1, 1, 2, 3, 2}​​
​​利用定义直接看出来，利用三个算法手工执行出来，熟悉和掌握算法*/
#include<stdio.h>
#include<string.h>

int getnext1(char *s,int j){
    if(j==0)
        return -1;
    // 按定义直接计算：对于位置 j（表示子串 s[0..j-1]），寻找最大的 m (1..j-1)
    // 使得 s[0..m-1] == s[j-m..j-1]，若不存在则返回 0；j==0 返回 -1
    for (int m = j - 1; m >= 1; m--) {
        // 比较前缀 s[0..m-1] 与后缀 s[j-m..j-1]
        if (strncmp(s, s + j - m, m) == 0)
            return m;
    }
    return 0;
}
int getnext2(char *s,int j){
    if(j<0){
        printf("Error:j<0\n");
        exit(1);
    }
    if(j==0)
        return -1;

    int k;
    for(k=j-2;k>=0;k--)
        if(s[k]==s[j-1])//先判断两个字符串是否尾部相等吧，要不就没必要继续下去了
            if(strncmp(s,&s[j-k-1],k+1)==0)//若相等返回0，小于返回负数，大于返回正数，依据ASCII码值
                return k+1;
    return 0;
}
void getnext3(char *s,int *next){
    int j = 2, k = 2;
    next[0]=-1;
    next[1]=0;

    int len=strlen(s);
    while(j<len){
        k=next[j-1];//
        while(k>0&&s[k]!=s[j-1])//
            k=next[k];
        if(k<=0)//
            if(s[0]==s[j-1])
                next[j]=1;
            else
                next[j]=0;
        else
            next[j]=k+1;
        j++;
    }
}
int main(){
    char s[]="abaaababc";

    int next[9];

    getnext3(s,next);

    for(int i=0;i<9;i++)
        printf("%d ",getnext1(s,i));
    printf("\n");

    for(int i=0;i<9;i++)
        printf("%d ",getnext2(s,i));
    printf("\n");

    for(int i=0;i<9;i++)
        printf("%d ",next[i]);
    printf("\n");

    return 0;
}