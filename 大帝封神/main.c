//主要游戏逻辑
#include "game.h"
#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>


int main() {
    //登录判断
    FILE* file = fopen(credentialsFile, "r");
    if (file != NULL) {
        fclose(file);
        if (!loginUser()) {
            return 0; // 登录失败或选择重置密码时退出程序
        }
    }
    else {
        registerUser();
    }

    //开始游戏
    GameSaveData gameData = { 0,1,0 };
    char input[100];
    int choice;

    // 起始场景
    printf("欢迎来到《大帝封神》游戏！");
    printf("1. 新游戏 2. 加载存档 3. 删除存档\n请选择操作: ");
    fgets(input, sizeof(input), stdin);
    sscanf_s(input, "%d", &choice);

    if (choice == 1) {
        gameData.score = 0; // 初始化分数
        gameData.gameProgress = 1;
        printf("------游戏初始化-----\n");
        printf("------剧情加载中-----\n");
        printf("------场景搭建中-----\n");
        printf("---第一幕·起始之地---\n");
        printf("----按任意键继续-----\n");
        _getch();  // 等待用户按键
        system("cls");

        printf("你作为仙道世界的凡人，在听说了无始大帝的故事之后，毅然决然的踏上了寻找大帝无始的征程。\n");
        printf("遵循着冥冥中的指引，你来到了一片凄美而神秘的仙凡乡土。\n");
        printf("群山环绕着这片土地，翠绿的竹林在风中轻轻摇曳，白云在天空中缓缓飘动，一缕清风掠过，带来了清新的木香和淡淡的仙气。\n");
        printf("池水清澈透明，远处小巧的古庙在水面上投下了宁静的倒影。\n");
        printf("在这个仙气缭绕的地方，你遇见了一位看似普通的老者。\n");
        printf("他的外貌平平无奇，你从他身上感受不到任何修炼气息，但是你莫名对他感到忌惮。\n");
        printf("老者似乎已经等待你多时，他微微微一笑开口道：“······”\n");
        printf("----按任意键继续-----\n");
        _getch();  // 等待用户按键
        system("cls");
        // 初始化其他游戏状态
    }
    else if (choice == 2) {
        printf("请输入存档文件名: ");
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = 0;
        if (!load_game(&gameData, input)) {
            printf("存档加载失败。开始新游戏。\n");
            gameData.score = 0; // 重新初始化分数
            gameData.gameProgress = 1;
        }
        else {
            printf("存档加载成功。当前分数: %d\n", gameData.score);
            // 根据存档中的游戏进度决定接下来的操作
            switch (gameData.gameProgress) {
            case 1:
                goto continue_from_save_point_1;
            case 2:
                // 从存档点2开始执行游戏逻辑
                goto continue_from_save_point_2;
                // case 3:
                   //  goto continue_from_save_point_3;
                     // 其他存档点
                     // ...
            }
        }
    }
    else if (choice == 3) {
        printf("请输入要删除的存档文件名: ");
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = 0;
        delete_save(input);
    }
    else {
        printf("你做出了错误的选择。\n");
        printf("你死在了危险重重的修炼大道上。\n");
        printf("修炼界危险重重，下次轮回请慎重选择。\n");
        printf("下次再见\n");
        return 0;
    }


    printf("“勇敢的少侠，你愿意接受此次封神之旅吗？\n这是开始你作为凡人踏上追寻无上帝境的起始之地。”\n老者面带微笑看着你请输入你的选择(是/否): ");
    fgets(input, sizeof(input), stdin); // 读取一行输入
    printf("你选择接受，老者微笑着指了一个方向，并递给你一张神秘的地图。\n");
    printf("自此命运的齿轮开始转动\n");
    printf("----按任意键继续-----\n");
    _getch();  // 等待用户按键
    system("cls");

    if (strncmp(input, "是", 2) == 0) {
        printf("你踏上了寻找大帝无始的征程。");
    }
    else {
        printf("你的回答让老者很不满意，他阴冷的说到：“给你机会你不中用啊，老弟”\n");
        printf("你惨死当场。\n");
        return 0; // 游戏结束
    }


    // 存档点（一）
    printf("是否要保存游戏？(是/否): ");
    fgets(input, sizeof(input), stdin);
    if (strncmp(input, "是", 2) == 0) {
        printf("输入存档文件名: ");
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = 0;
        save_game(&gameData, input);
        printf("游戏已保存。\n");
    }
    else {
        printf("你做出了错误的选择。\n");
        printf("你死在了危险重重的修炼大道上。\n");
        printf("修炼界危险重重，下次轮回请慎重选择。\n");
        printf("下次再见\n");
        return 0;
    }
    //————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————
continue_from_save_point_1:

    printf("你仔细观察地图，发现老者指的方向上有四个风水宝地：神源之地、碧海须臾界、古怪极道宝地，以及真仙路口。\n");
    printf("这些地方散发着吸引人的光芒，似乎隐藏着仙道的奥秘和无上的力量。\n");
    printf("然而，地图上还有一个地方，在这四个宝地的相反方向，被浓厚的迷雾所笼罩，显得神秘莫测。\n");
    printf("老者的眼神中闪过一丝警告，似乎暗示不要去那片地方。\n");
    printf("现在，选择权在你手中：\n");
    printf("1.前往神源之地，寻找无始大帝昔日留下的圣品————无始经。\n ");
    printf("2.探索碧海须臾界，沐浴在神秘的仙泉中。 \n");
    printf("3.进入古怪极道宝地，感悟天象之美。 \n");
    printf("4.走向真仙路口，探索未知的神秘力量。 \n");
    printf("5.冒险穿越迷雾之地，探寻那里隐藏的秘密。\n ");
    printf("你深吸一口气，准备做出选择。你知道，这个决定将改变你的命运。\n ");
    printf("请输入你的选择：\n ");
    fgets(input, sizeof(input), stdin);
    system("cls");

    if (strncmp(input, "1", 1) == 0) {
        gameData.score += 30;
        printf("选择了神源之地后，你跟随着地图上的指引，穿过一片密林，来到了一个隐藏在山谷中的神秘地方。\n");
        gosyzd(input, &gameData);
    }
    else if (strncmp(input, "2", 1) == 0) {
        gameData.score += 40;
        printf("决定前往碧海须臾界后，你开始了一段向海的旅程。沿途的风景逐渐变得开阔，海风带着咸湿的气息吹拂在你的脸上。\n");
        gobhxyj(input, &gameData);
    }
    else if (strncmp(input, "3", 1) == 0) {
        gameData.score += 20;
        printf("你选择了古怪极道宝地，这意味着你将进入一个充满未知的世界。你小心翼翼地沿着一条弯曲的小径前行，四周的景象开始变得越来越异乎寻常。\n");
        gojdbd(input, &gameData);
    }
    else if (strncmp(input, "4", 1) == 0) {
        gameData.score += 50;
        printf("在决定前往真仙路口后，你穿越了一条蜿蜒的山路。沿途，风景逐渐变得更加奇异，天空中的云彩呈现出不同寻常的颜色。\n");
        gozxlk(input, &gameData);
    }
    else if (strncmp(input, "5", 1) == 0) {
        gameData.score += 10;
        printf("你选择了冒险的道路——迷雾之地。你小心翼翼地穿越了一片浓厚的迷雾。迷雾中的景象扭曲而神秘，让人感到不安。\n");
        gomwzd(input, &gameData);
    }
    else {
        printf("你做出了错误的选择。\n");
        printf("你死在了危险重重的修炼大道上。\n");
        printf("修炼界危险重重，下次轮回请慎重选择。\n");
        printf("下次再见\n");
        return 0;
    }



    // 存档点 （二）
    printf("是否要保存游戏？(是/否): ");
    fgets(input, sizeof(input), stdin);
    if (strncmp(input, "是", 2) == 0) {
        printf("输入存档文件名: ");
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = 0;
        save_game(&gameData, input);
        printf("游戏已保存。\n");
    }
    else {
        printf("你做出了错误的选择。\n");
        printf("你死在了危险重重的修炼大道上。\n");
        printf("修炼界危险重重，下次轮回请慎重选择。\n");
        printf("下次再见\n");
        return 0;
    }

    //————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

continue_from_save_point_2:


    // 结束场景
    printf("你的冒险旅程到此结束。");
    printf("你的最终得分是: %d", gameData.score);
    return 0;
}