/*
  编写一个算法，统计输入字符串中 A-Z（26个字母，不区分大小写） 和 0-9（10个数字）
  这些合法字符各自出现的次数（频度），并将统计结果保存到文件中。
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <direct.h> /* _getcwd on Windows */

#define Max_Size 200

/* 0~25 表示字母 A-Z（存储为大写），26~35 表示数字 0-9 */
void statis(const char *str, int *num) {
    int i = 0;
    while (str[i] != '\0' && str[i] != '\n') {
        unsigned char ch = (unsigned char)str[i];
        if (isalpha(ch)) {
            ch = (unsigned char)toupper(ch);
            num[ch - 'A']++;
        } else if (isdigit(ch)) {
            num[26 + (ch - '0')]++;
        }
        i++;
    }
}

/* 将结果写入文件（在当前工作目录下） */
void save_to_file(const int *num, const char *filename) {
    char fullpath[512] = {0};
    if (_getcwd(fullpath, sizeof(fullpath)) == NULL) {
        /* 读取当前目录失败，回退到只用文件名 */
        strncpy(fullpath, filename, sizeof(fullpath) - 1);
    } else {
        strncat(fullpath, "\\", sizeof(fullpath) - strlen(fullpath) - 1);
        strncat(fullpath, filename, sizeof(fullpath) - strlen(fullpath) - 1);
    }
    printf("文件将保存到：%s\n", fullpath);

    FILE *fp = fopen(fullpath, "w");
    if (!fp) {
        printf("Error: failed to open the file %s\n", fullpath);
        exit(1);
    }

    fprintf(fp, "字母统计\n");
    for (int i = 0; i < 26; i++) {
        fprintf(fp, "%c %d\n", 'A' + i, num[i]);
    }

    fprintf(fp, "数字统计\n");
    for (int i = 0; i < 10; i++) {
        fprintf(fp, "%c %d\n", '0' + i, num[26 + i]);
    }

    fclose(fp);
    printf("结果已保存至文件：%s\n", fullpath);
}

int main(void) {
    char str[Max_Size];
    printf("输入一个字符串：");
    if (!fgets(str, Max_Size, stdin)) {
        printf("读取输入失败\n");
        return 1;
    }

    int num[36] = {0};
    statis(str, num);
    save_to_file(num, "result.txt");

    printf("\n统计结果（包含未出现的字符，次数为0）：\n");
    for (int i = 0; i < 26; i++) {
        printf("%c: %d\n", 'A' + i, num[i]);
    }
    for (int i = 0; i < 10; i++) {
        printf("%c: %d\n", '0' + i, num[26 + i]);
    }

    return 0;
}
