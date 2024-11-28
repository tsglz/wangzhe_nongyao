#include "ranking.hpp"

#define MAX_PLAYERS 100

// 玩家结构体
typedef struct {
  char name[50];
  int wins;
} Player;

// 比较函数，用于排序
int compare(const void *a, const void *b) {
  Player *playerA = (Player *)a;
  Player *playerB = (Player *)b;
  return playerB->wins - playerA->wins; // 降序排序
}

// 保存游戏结果
void save_game_result(int win, const char *name) {
  FILE *fp = fopen("ranking.txt", "r+"); // 以读写模式打开文件
  if (!fp) {
    // 如果文件不存在，创建新文件
    fp = fopen("ranking.txt", "w+");
    if (!fp) {
      printf("无法创建文件进行写入。\n");
      return;
    }
  }

  Player players[MAX_PLAYERS];
  int playerCount = 0;
  bool found = false;

  // 读取现有玩家信息
  while (fscanf(fp, "%s %d", players[playerCount].name,
                &players[playerCount].wins) != EOF) {
    playerCount++;
  }

  // 查找是否已有该玩家
  for (int i = 0; i < playerCount; i++) {
    if (strcmp(players[i].name, name) == 0) {
      players[i].wins += win; // 更新胜利次数
      found = true;
      break;
    }
  }

  // 如果没有找到该玩家，添加新记录
  if (!found && playerCount < MAX_PLAYERS) {
    strncpy(players[playerCount].name, name, sizeof(players[playerCount].name));
    players[playerCount].wins = win;
    playerCount++;
  }

  // 排序玩家列表
  qsort(players, playerCount, sizeof(Player), compare);

  // 重写文件内容
  freopen("ranking.txt", "w", fp); // 清空文件并重新写入
  for (int i = 0; i < playerCount; i++) {
    fprintf(fp, "%s %d\n", players[i].name, players[i].wins);
  }

  fclose(fp); // 关闭文件
}

// 显示排行榜
void show_ranking() {
  printf("\n=== 排行榜 ===\n");
  FILE *fp = fopen("ranking.txt", "r");
  if (!fp) {
    printf("暂无记录。\n");
    return;
  }

  char player[50];
  int win;
  while (fscanf(fp, "%s %d", player, &win) != EOF) {
    printf("%s: %d 胜\n", player, win);
  }
  fclose(fp);
}