//登录系统
#include "game.h"
#include <stdio.h>
#include <string.h>
#define _countof(array) (sizeof(array) / sizeof((array)[0]))

// saveCredentials, checkCredentials, registerUser, loginUser 函数的实现...
//登录系统

const char* credentialsFile = "credentials.txt";

void saveCredentials(const char* username, const char* password) {
    FILE* file = fopen(credentialsFile, "w");
    if (file != NULL) {
        fprintf_s(file, "%s\n%s", username, password);
        fclose(file);
    }
    else {
        printf("无法保存凭证。\n");
    }
}

int checkCredentials(const char* username, const char* password) {
    char storedUser[100], storedPass[100];
    FILE* file = fopen(credentialsFile, "r");
    if (file != NULL) {
        // 注意：在 %s 后面加上缓冲区大小
        fscanf_s(file, "%99s", storedUser, (unsigned)_countof(storedUser));
        fscanf_s(file, "%99s", storedPass, (unsigned)_countof(storedPass));
        fclose(file);
        return strcmp(username, storedUser) == 0 && strcmp(password, storedPass) == 0;
    }
    return 0; // 文件不存在，视为凭证不匹配
}

void registerUser() {
    char username[100], password[100];
    printf("注册新用户\n请输入用户名: ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = 0; // 移除换行符

    printf("请输入密码: ");
    fgets(password, sizeof(password), stdin);
    password[strcspn(password, "\n")] = 0; // 移除换行符

    saveCredentials(username, password);
    printf("注册成功。\n");
}


int loginUser() {
    char username[100], password[100];
    for (int attempts = 0; attempts < 3; ++attempts) {
        printf("请输入用户名: ");
        fgets(username, sizeof(username), stdin);
        username[strcspn(username, "\n")] = 0; // 移除换行符

        printf("请输入密码: ");
        fgets(password, sizeof(password), stdin);
        password[strcspn(password, "\n")] = 0; // 移除换行符

        if (checkCredentials(username, password)) {
            printf("登录成功。\n");
            return 1;
        }
        else {
            printf("用户名或密码错误。\n");
            if (attempts < 2) {
                printf("1. 重试登录\n2. 忘记密码\n请选择操作: ");
                int choice;
                scanf_s("%d", &choice); // 这里保留了 scanf，因为它用于读取一个整数
                while (getchar() != '\n'); // 清除输入缓冲区
                if (choice == 2) {
                    remove(credentialsFile);
                    printf("凭证已重置，请重新启动程序进行注册。\n");
                    return 0;
                }
            }
        }
    }
    printf("多次登录失败，程序将退出。\n");
    return 0;
}
