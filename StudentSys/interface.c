#include <stdio.h>
#include "interface.h"

void displayMenu() {
    printf("======= 学生管理系统 =======\n");
    printf("1. 添加学生\n");
    printf("2. 显示所有学生\n");
    printf("3. 搜索学生\n");
    printf("4. 更新学生信息\n");
    printf("5. 删除学生\n");
    printf("0. 退出\n");
    printf("===========================\n");
}

int getUserChoice() {
    int choice;
    printf("请输入选项：");
    scanf("%d", &choice);
    return choice;
}