#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <conio.h> //用于使用getch函数
#include <stdlib.h>
#include <string.h>

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



//定义结构体，保存游戏数据
typedef struct {
    int score;
    int gameProgress; // 游戏进度标记
    int gameOver; // 游戏结束标志
    // 可以添加其他游戏状态数据
} GameSaveData;


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

//————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————
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
