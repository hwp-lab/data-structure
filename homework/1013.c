/*void StrReplace(char *T, char *P, char *S)，将 T 中第一次出现的与 P 相等的子串替换为 S，
串 S 和 P 的长度不一定相等，并分析时间复杂度*/
//写在前面，学了一顿KMP算法来写这个作业，还是喜欢暴力枚举o(╥﹏╥)o

#include<stdio.h>
#include<string.h>
#include<stdlib.h>//malloc,exit

#define Max_Size 200

int next[Max_Size]={0};

//求next[j]
int nextj(char *t,int j){
    if(j<0){//再想想
        printf("Error:j<0\n");
        exit(1);
    }
    if(j==0)
        return -1;

    int k;
    for(k=j-2;k>=0;k--)
        if(t[k]==t[j-1])//先判断两个字符串是否尾部相等吧，要不就没必要继续下去了
            if(strncmp(t,&t[j-k-1],k+1)==0)//若相等返回0，小于返回负数，大于返回正数，依据ASCII码值
                return k+1;
    return 0;
}
//KMP求子串第一次出现位置
int location(char *s,char *t){
    int i=0;//标记s中的位置
    int j=0;//标记t

    int s_len=strlen(s);
    int t_len=strlen(t);

    while(i<s_len&&j<t_len){
        if(next[j]==-1||s[i]==t[j]){
            i++;
            j++;
        }
        else{
            next[j]=nextj(t,j);
            j=next[j];
        }
    }
    if(j>=t_len)
        return i-t_len;
    else
        return -1;
}
//替换子串（T 中第一次出现的与 P 相等的子串替换为 S）
int StrReplace(char *T, char *P, char *S){//改成int类型了，判断一下吧
    int T_len=strlen(T);
    int P_len=strlen(P);
    int S_len=strlen(S);

    int loc=location(T,P);
    int i,j;
    if(loc==-1)
        return 0;

    char *temp;
    temp=(char*)malloc((T_len+S_len+1)*sizeof(char));//增加一个字符，以防万一'\0'
    if (temp == NULL) {
        printf("内存分配失败\n");
        return 0;
    }

    for(i=0;i<loc;i++)
        temp[i]=T[i];
    for(i=loc,j=0;j<S_len;i++,j++)
        temp[i]=S[j];
    for(i=loc+S_len,j=loc+P_len;j<T_len;j++,i++)
        temp[i]=T[j];
    temp[i]='\0';
    
    strcpy(T, temp);
    free(temp);
    return 1;
}
//主函数
int main() {
    // 测试场景1：正常替换（替换串与原串长度相同）
    char T1[Max_Size] = "hello world, world!";
    char P1[] = "world";
    char S1[] = "there";
    printf("测试1：正常替换（长度相同）\n");
    printf("替换前：%s\n", T1);
    int res1 = StrReplace(T1, P1, S1);
    printf("替换后：%s（结果：%s）\n\n", T1, res1 ? "成功" : "未找到");

    // 测试场景2：替换串比原串长
    char T2[Max_Size] = "abc123def";
    char P2[] = "123";
    char S2[] = "xyz789";
    printf("测试2：替换串更长\n");
    printf("替换前：%s\n", T2);
    int res2 = StrReplace(T2, P2, S2);
    printf("替换后：%s（结果：%s）\n\n", T2, res2 ? "成功" : "未找到");

    // 测试场景3：替换串比原串短
    char T3[Max_Size] = "I like programming";
    char P3[] = "programming";
    char S3[] = "code";
    printf("测试3：替换串更短\n");
    printf("替换前：%s\n", T3);
    int res3 = StrReplace(T3, P3, S3);
    printf("替换后：%s（结果：%s）\n\n", T3, res3 ? "成功" : "未找到");

    // 测试场景4：未找到子串
    char T4[Max_Size] = "apple banana cherry";
    char P4[] = "orange";
    char S4[] = "grape";
    printf("测试4：未找到子串\n");
    printf("替换前：%s\n", T4);
    int res4 = StrReplace(T4, P4, S4);
    printf("替换后：%s（结果：%s）\n\n", T4, res4 ? "成功" : "未找到");

    // 测试场景5：子串在开头
    char T5[Max_Size] = "start middle end";
    char P5[] = "start";
    char S5[] = "begin";
    printf("测试5：子串在开头\n");
    printf("替换前：%s\n", T5);
    int res5 = StrReplace(T5, P5, S5);
    printf("替换后：%s（结果：%s）\n\n", T5, res5 ? "成功" : "未找到");

    // 测试场景6：子串在结尾
    char T6[Max_Size] = "first second last";
    char P6[] = "last";
    char S6[] = "final";
    printf("测试6：子串在结尾\n");
    printf("替换前：%s\n", T6);
    int res6 = StrReplace(T6, P6, S6);
    printf("替换后：%s（结果：%s）\n", T6, res6 ? "成功" : "未找到");

    return 0;
}