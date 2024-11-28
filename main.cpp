#include "game.hpp"
#include "ranking.hpp"
#include "user.hpp"
#include <iostream>

int main() {
  char *name = new char[20];
  if (!login(name)) {
    printf("注册成功，欢迎进入游戏！\n");
  } else {
    printf("登录成功，欢迎回来！\n");
  }

  int choice;
  while (1) {
    printf("\n=== 王者农药 ===\n");
    printf("1. 开始游戏\n");
    printf("2. 查看排行榜\n");
    printf("3. 退出\n");
    printf("请选择: ");
    std::cin >> choice;

    switch (choice) {
    case 1:
      start_game(name);
      break;
    case 2:
      show_ranking();
      break;
    case 3:
      printf("感谢游戏，再见！\n");
      return 0;
    default:
      printf("输入无效，请重新选择。\n");
    }
  }
  return 0;
}