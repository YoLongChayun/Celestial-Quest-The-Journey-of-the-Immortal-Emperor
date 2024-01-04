//游戏级别和逻辑
#include "game.h"
#include <stdio.h>
#include <stdlib.h>  // 对于 system
#include <string.h>  // 对于 strncmp

// gosyzd, gobhxyj, gojdbd, gozxlk, gomwzd 函数的实现...

// 神源之地的函数
void gosyzd(char* input, GameSaveData* gameData) {
    printf("选择了神源之地后，你跟随着地图上的指引，穿过一片密林，来到了一个隐藏在山谷中的神秘地方。\n");
    printf("阳光透过树梢，照在地上形成斑驳的光影。神源之地是一片充满神秘力量的圣地，这里环绕着蔚蓝色的光环，中央有一个散发着璀璨光芒的仙泉。\n");
    printf("泉水清澈见底，泉边生长着奇花异草，散发着迷人的香气。仙泉旁边放置着一本古老的书籍——无始经，令人敬畏的气息弥漫在空气中。\n");
    printf("请选择你的行动：\n");
    printf("1. 捡起无始经\n2. 观赏仙泉\n3. 禅语悟道\n");

    fgets(input, 100, stdin); // 假设 input 是大小为 100 的字符数组
    system("cls");

    if (strncmp(input, "1", 1) == 0) {
        gameData->score += 50;
        printf("你走近一本放在石台上的古老经书，轻轻翻开。书页上的文字仿佛蕴含着宇宙的智慧，你的心灵感受到前所未有的震撼。\n");
    }
    else if (strncmp(input, "2", 1) == 0) {
        gameData->score += 20;
        printf("你靠近仙泉，泉水的波纹似乎在讲述着古老的故事。你的心随着泉水的流动而平静，感受到内心的宁静和力量。\n");
    }
    else if (strncmp(input, "3", 1) == 0) {
        gameData->score += 30;
        printf("在仙泉旁的石凳上，你闭上眼睛，沉浸在环绕的仙气中。在这个宁静的环境下，你领悟到了深奥的道理。\n");
    }
    else {
        printf("你做出了错误的选择。\n");
        printf("你在神源之地迷失了方向，未能发现仙道的真谛。\n");
        gameData->gameOver = 1;
    }
}



// 碧海须臾界的函数
void gobhxyj(char* input, GameSaveData* gameData) {
    printf("决定前往碧海须臾界后，你开始了一段向海的旅程。\n");
    printf("最终，你到达了一片广阔的海域，海面上漂浮着几块仙岛。\n");
    printf("请选择你的行动：\n");
    printf("1. 观赏仙泉\n2. 捡起无始之心\n3. 探寻禁地\n");

    fgets(input, 100, stdin);
    system("cls");

    if (strncmp(input, "1", 1) == 0) {
        gameData->score += 30;
        printf("你来到仙泉边，感受到心灵的平和。\n");
    }
    else if (strncmp(input, "2", 1) == 0) {
        gameData->score += 120;
        printf("你发现了散发着温暖光芒的无始之心，并感受到了强大的力量。\n");
    }
    else if (strncmp(input, "3", 1) == 0) {
        gameData->score += 80;
        printf("你探寻了一个隐藏的神秘洞穴，发现了无始大帝留下的真传。\n");
    }
    else {
        printf("你在碧海须臾界迷失了方向。\n");
        gameData->gameOver = 1;
    }
}



// 极道宝地的函数
void gojdbd(char* input, GameSaveData* gameData) {
    printf("选择古怪极道宝地意味着你将进入一个充满未知的世界。\n");
    printf("你来到了一个光怪陆离的地方，星辰闪烁着不同的光芒。\n");
    printf("请选择你的行动：\n");
    printf("1. 观赏天象\n2. 捡起无始钟\n3. 探寻禁地\n");

    fgets(input, 100, stdin);
    system("cls");

    if (strncmp(input, "1", 1) == 0) {
        gameData->score += 20;
        printf("你仰望星空，感受到了宇宙深邃的秘密。\n");
    }
    else if (strncmp(input, "2", 1) == 0) {
        gameData->score += 90;
        printf("你拾起了一处被光环环绕的神秘钟形物体，感受到了穿越时空的力量。\n");
    }
    else if (strncmp(input, "3", 1) == 0) {
        gameData->score += 60;
        printf("你探寻了一条隐藏的小径，发现了古老的智慧。\n");
    }
    else {
        printf("你在古怪极道宝地迷失了方向。\n");
        gameData->gameOver = 1;
    }
}



// 真仙路口的函数
void gozxlk(char* input, GameSaveData* gameData) {
    printf("在决定前往真仙路口后，你穿越了一条蜿蜒的山路。\n");
    printf("当你到达真仙路口时，眼前展现的是一片被古老神木环绕的神圣之地。\n");
    printf("请选择你的行动：\n");
    printf("1. 捡起无始剑\n2. 观赏神木\n3. 尝试仙道\n");

    fgets(input, 100, stdin);
    system("cls");

    if (strncmp(input, "1", 1) == 0) {
        gameData->score += 70;
        printf("你发现了一把散发着强大力量的古剑，并与之产生了共鸣。\n");
    }
    else if (strncmp(input, "2", 1) == 0) {
        gameData->score += 20;
        printf("你走近一棵巨大的神木，感受到了仙道的奥义。\n");
    }
    else if (strncmp(input, "3", 1) == 0) {
        gameData->score += 40;
        printf("你在神木下打坐，体会到了这片土地的仙气。\n");
    }
    else {
        printf("你做出了错误的选择，在真仙路口迷失了方向。\n");
        gameData->gameOver = 1;
    }
}



// 迷雾之地的函数
void gomwzd(char* input, GameSaveData* gameData) {
    printf("你勇敢地选择了冒险的道路——迷雾之地。\n");
    printf("在这片古老的遗迹中，十个神秘的符号出现在你面前。\n");
    printf("请选择你的行动：\n");
    printf("1. 选择金色的符号，代表着财富和权力。\n");
    printf("2. 选择蓝色的符号，象征着智慧和真知。\n");
    printf("3. 选择红色的符号，象征着勇气和战斗。\n");
    printf("4. 选择绿色的符号，代表着生命和自然。\n");
    printf("5. 选择黑色的符号，代表着神秘和未知。\n");
    printf("6. 选择白色的符号，代表着纯洁和光明。\n");
    printf("7. 选择紫色的符号，象征着魔法和超自然力量。\n");
    printf("8. 选择橙色的符号，代表着活力和热情。\n");
    printf("9. 选择灰色的符号，象征着平衡和中立。\n");
    printf("10. 选择透明的符号，它几乎与空气融为一体，难以察觉。\n");

    fgets(input, 100, stdin);
    system("cls");

    // 假设透明的符号是唯一正确的选择
    if (strncmp(input, "10", 2) == 0) {
        gameData->score += 1000; // 假设这是一个巨大的分数增加
        printf("你选择了透明的符号，经历了真正的凤凰涅槃，重生为更强大的存在。\n");
    }
    else {
        printf("你的选择导致了灵魂的迷失。\n");
        gameData->gameOver = 1;
    }
}
