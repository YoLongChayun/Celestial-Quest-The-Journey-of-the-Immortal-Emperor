#ifndef GAME_H
#define GAME_H

// 游戏数据结构体定义
typedef struct {
    int score;
    int gameProgress;
    int gameOver;
} GameSaveData;

extern const char* credentialsFile;


// 函数声明
void gosyzd(char* input, GameSaveData* gameData);
void gobhxyj(char* input, GameSaveData* gameData);
void gojdbd(char* input, GameSaveData* gameData);
void gozxlk(char* input, GameSaveData* gameData);
void gomwzd(char* input, GameSaveData* gameData);
void save_game(const GameSaveData* data, const char* filename);
int load_game(GameSaveData* data, const char* filename);
int delete_save(const char* filename);
void saveCredentials(const char* username, const char* password);
int checkCredentials(const char* username, const char* password);
void registerUser();
int loginUser();

#endif
