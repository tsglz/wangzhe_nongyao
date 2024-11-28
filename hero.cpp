#include "hero.hpp" // 引入自定义的头文件，包含Hero结构体的定义

#define HERO_COUNT 15

// 定义一个英雄列表，包含多个英雄的名称及其剪刀、石头、布的数量
Hero hero_list[] = {
    {"赵云", 2, 2, 2}, {"宫本武藏", 4, 1, 1}, {"凯", 2, 3, 1},
    {"白起", 5, 0, 1}, {"韩信", 1, 2, 3},     {"诸葛亮", 2, 1, 3},
    {"刘邦", 2, 0, 4}, {"后羿", 0, 3, 3},     {"王昭君", 1, 1, 4},
    {"妲己", 4, 1, 1}, {"安琪拉", 1, 4, 1},   {"貂蝉", 3, 2, 1},
    {"露娜", 1, 3, 2}, {"不知火舞", 4, 2, 0}, {"蔡文姬", 0, 5, 1}};

// 选择英雄的函数，接收一个英雄队列数组作为参数
void select_heroes(Hero team[3]) {
  int chosen[HERO_COUNT] = {0}; // 用于记录已经选择的英雄编号
  printf("请选择3位英雄（用编号选择）:\n");
  // 输出可选英雄的列表
  for (int i = 0; i < 15; i++) {
    printf("%d. %s (剪刀:%d 石头:%d 布:%d)\n", i + 1, hero_list[i].name,
           hero_list[i].scissors, hero_list[i].rock, hero_list[i].paper);
  }

  // 循环接收用户选择的英雄编号
  for (int i = 0; i < 3; i++) {
    int choice;
    int valid_choice = 0;

    while (!valid_choice) { // 只要输入无效就继续循环
      printf("选择英雄 %d (1-%d): ", i + 1, HERO_COUNT);
      scanf("%d", &choice); // 用户输入选择的编号

      // 检查输入的选择
      if (choice < 1 || choice > HERO_COUNT) {
        printf("无效选择，请重新选择。\n");
      } else if (chosen[choice - 1]) {
        printf("该英雄已被选择，请选择其他英雄。\n");
      } else {
        // 一切有效，更新队伍中的英雄
        team[i] = hero_list[choice - 1]; // 更新队伍中的英雄
        chosen[choice - 1] = 1;          // 标记该英雄为已选择
        valid_choice = 1;                // 标记为有效选择，跳出循环
      }
    }
  }

  // 输出选择的英雄
  printf("你选择的英雄是:");
  for (int i = 0; i < 3; i++) {
    printf("%s ", team[i]);
  }
}

// 随机选择英雄的函数
void random_heroes(Hero team[3]) {
  srand(time(NULL));          // 初始化随机数种子
  int chosen_index[15] = {0}; // 用于记录已经选择的英雄编号
  for (int i = 0; i < 3; i++) {
    int index = rand() % 15;         // 每次从0到14随机取一个英雄
    while (chosen_index[index] == 1) // 如果该英雄已经被选择，则重新随机
    {
      index = rand() % 15;
    }
    team[i] = hero_list[index]; // 更新队伍中的英雄
    chosen_index[index] = 1;    // 标记该英雄为已选择
  }
  // 输出选择的英雄
  printf("对方选择的英雄是:");
  for (int i = 0; i < 3; i++) {
    printf("%s ", team[i]);
  }
}

// 由玩家自己选择怎么移动
int player_move(Hero *hero, Hero *enemy) {
  int move;

  printf("敌方现在的剪刀:%d 石头:%d 布:%d\n", enemy->scissors, enemy->rock,
         enemy->paper);
  printf("你现在的剪刀:%d 石头:%d 布:%d\n", hero->scissors, hero->rock,
         hero->paper);

  std::cout << "请选择你的动作（0=剪刀, 1=石头, 2=布）：" << std::endl;

  std::cin >> move; // 获取玩家输入

  // 校验输入是否有效
  while (move != 0 && move != 1 && move != 2) {
    std::cout << "输入错误，请重新输入（0=剪刀, 1=石头, 2=布）：";
    std::cin >> move; // 获取玩家输入
  }

  while ((move == 0 && hero->scissors == 0) || (move == 1 && hero->rock == 0) ||
         (move == 2 && hero->paper == 0)) {
    printf("你没有%s，请重新选择: ",
           (move == 0 ? "剪刀" : (move == 1 ? "石头" : "布")));
    std::cin >> move; // 获取玩家重新输入
  }

  // 减少相应动作的数量
  if (move == 0) {
    hero->scissors--;
  } else if (move == 1) {
    hero->rock--;
  } else if (move == 2) {
    hero->paper--;
  }

  return move; // 返回所选择的动作
}

// 随机选择移动的函数，返回所选择的移动方式
int random_move(Hero *hero) {
  int move; // 移动方式：0=剪刀, 1=石头, 2=布
  do {
    srand(time(NULL));                           // 初始化随机数种子
    move = rand() % 3;                           // 随机选择一个动作
  } while ((move == 0 && hero->scissors == 0) || // 如果选择剪刀，但没有剪刀可用
           (move == 1 && hero->rock == 0) || // 如果选择石头，但没有石头可用
           (move == 2 && hero->paper == 0)); // 如果选择布，但没有布可用

  // 减少相应动作的数量
  if (move == 0)
    hero->scissors--;
  else if (move == 1)
    hero->rock--;
  else
    hero->paper--;

  return move; // 返回所选择的动作
}