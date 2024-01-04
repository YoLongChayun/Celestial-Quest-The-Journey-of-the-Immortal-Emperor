//存档和加载
#include "game.h"
#include <stdio.h>
#include <stdlib.h>  // 对于 system
#include <string.h>  // 对于 strncmp

// save_game, load_game, delete_save 函数的实现...

//存档系统
//读档
int load_game(GameSaveData* data, const char* filename) {
    FILE* file = fopen(filename, "rb");
    if (file == NULL) {
        printf("存档文件 %s 不存在。\n", filename);
        return 0;
    }
    fread(data, sizeof(GameSaveData), 1, file);
    fclose(file);
    return 1;
}

//存档
void save_game(const GameSaveData* data, const char* filename) {
    FILE* file = fopen(filename, "wb");
    if (file != NULL) {
        fwrite(data, sizeof(GameSaveData), 1, file);
        fclose(file);
    }
    else {
        printf("保存失败。\n");
    }
}

//删档
int delete_save(const char* filename) {
    char confirm[10];
    printf("您确定要删除存档 '%s' 吗？(输入'是'确认): ", filename);
    fgets(confirm, sizeof(confirm), stdin);
    if (strncmp(confirm, "是", 2) == 0) {
        if (remove(filename) == 0) {
            printf("存档 '%s' 已删除。\n", filename);
            return 1;
        }
        else {
            printf("删除存档失败。\n");
        }
    }
    else {
        printf("删除操作已取消。\n");
    }
    return 0;
}
