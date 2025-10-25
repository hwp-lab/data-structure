/*编写一个算法，统计输入字符串中 ​​A-Z（26个大写字母）​​ 和 ​​0-9（10个数字）​​ 这些合法字符各自出现的次数（频度），
最后将统计结果保存到文件中。*/

#include<stdio.h>
#include<stdlib.h>

#define Max_Size 200

//计算函数
void statis(char *str,int *num){
    
    int i=0,j=0;
    //0~25表示字母，26~35表示数字
    while(str[i]!='\0'&&str[i]!='\n'){
        char ch=str[i];

        if(ch>='A'&&ch<='Z')   
            num[ch-'A']++;
        
        else if(ch>='0'&&ch<='9')
            num[26+ch-'0']++;

        i++;
    }
}
//写入文件函数
void save_to_file(int *num,const char *filename){//const使文件名不会被修改（只读的感觉）
    
    char fullpath[256];
    // 获取当前工作目录（Windows）学到了，以后应该指定放哪
    _getcwd(fullpath, sizeof(fullpath));
    strcat(fullpath, "\\");
    strcat(fullpath, filename);
    printf("文件将保存到：%s\n", fullpath);  // 打印完整路径

    FILE *fp = fopen(filename, "w");//w表示只写模式，若没有文件，就会新建一个
    if(!fp){
        printf("Error: failed to open the file\n");
        exit(1);
    }

    int i;
    fprintf(fp,"字母统计\n");
    for(i=0;i<26;i++)
        fprintf(fp,"%c %d\n",'A'+i,num[i]);
    
    fprintf(fp, "数字统计\n");
    for(i=0;i<10;i++)
        fprintf(fp,"%c %d\n",'0'+i,num[26+i]);

    fclose(fp);
    printf("结果已保存至文件%s\n",filename);
}
//主函数
int main(){
    char str[Max_Size];
    printf("输入一个字符串：");
    fgets(str,Max_Size,stdin);//保留'\n'

    int num[36]={0};
    statis(str,num);
    save_to_file(num,"result.txt");

    printf("\n统计结果：\n");
    for (int i = 0; i < 26; i++) 
        if (num[i] > 0) 
            printf("%c: %d\n", 'A' + i, num[i]);

    for (int i = 0; i < 10; i++) 
        if (num[26 + i] > 0) 
            printf("%c: %d\n", '0' + i, num[26 + i]);
    return 0;
}