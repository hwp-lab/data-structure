/*void StrReplace(char *T, char *P, char *S)，将 T 中第一次出现的与 P 相等的子串替换为 S，
串 S 和 P 的长度不一定相等，并分析时间复杂度*/
// 写在前面，学了一顿KMP算法来写这个作业，还是喜欢暴力枚举o(╥﹏╥)o

#include <stdio.h>
#include <string.h>
#include <stdlib.h> // malloc, exit

#define Max_Size 200

int next[Max_Size] = {0};

// 计算模式串 t 的 next 数组（经典 KMP 的 next，next[0] = -1）
void computeNext(const char *t, int next[]) {//递推哎，本来不想学，被动学了
    int t_len = strlen(t);
    int j = 0, k = -1;
    if (t_len == 0) return;
    next[0] = -1;
    while (j < t_len - 1) {
        if (k == -1 || t[j] == t[k]) {
            j++; k++;
            next[j] = k;
        } else {
            k = next[k];
        }
    }
}

// KMP 求子串第一次出现位置（若未找到返回 -1）
int location(const char *s, const char *t) {
    int i = 0; // s index
    int j = 0; // t index

    int s_len = strlen(s);
    int t_len = strlen(t);

    if (t_len == 0) return 0; // 空模式视为匹配在位置 0

    computeNext(t, next);

    while (i < s_len && j < t_len) {
        if (j == -1 || s[i] == t[j]) {
            i++; j++;
        } else {
            j = next[j];
        }
    }
    if (j >= t_len)
        return i - t_len;
    else
        return -1;
}

// 替换子串（T 中第一次出现的与 P 相等的子串替换为 S）
int StrReplace(char *T, const char *P, const char *S) {
    int T_len = strlen(T);
    int P_len = strlen(P);
    int S_len = strlen(S);

    if (P_len == 0) return 0; // 不处理空模式

    int loc = location(T, P);
    if (loc == -1)
        return 0;

    int new_len = T_len - P_len + S_len;
    if (new_len >= Max_Size) {
        printf("替换后长度超出缓冲区 Max_Size=%d，操作取消\n", Max_Size);
        return 0;
    }

    char *temp = (char *)malloc((new_len + 1) * sizeof(char));
    if (temp == NULL) {
        printf("内存分配失败\n");
        return 0;
    }

    int i, j;
    for (i = 0; i < loc; i++)
        temp[i] = T[i];
    for (i = loc, j = 0; j < S_len; i++, j++)
        temp[i] = S[j];
    for (j = loc + P_len; j < T_len; j++, i++)
        temp[i] = T[j];
    temp[i] = '\0';

    strcpy(T, temp);
    free(temp);
    return 1;
}

// 主函数：包含若干测试用例
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
