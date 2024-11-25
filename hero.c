#include <stdio.h>
#include <stdlib.h>
#include "hero.h"

Hero hero_list[] = {
    {"赵云", 2, 2, 2}, {"宫本武藏", 4, 1, 1}, {"凯", 2, 3, 1}, 
    {"白起", 5, 0, 1}, {"韩信", 1, 2, 3}, {"诸葛亮", 2, 1, 3}
    // 可继续补充英雄列表
};

void select_heroes(Hero team[3]) {
    printf("请选择3位英雄（用编号选择）:\n");
    for (int i = 0; i < 6; i++) {
        printf("%d. %s (剪刀:%d 石头:%d 布:%d)\n", i + 1, hero_list[i].name,
               hero_list[i].scissors, hero_list[i].rock, hero_list[i].paper);
    }

    for (int i = 0; i < 3; i++) {
        int choice;
        printf("选择英雄 %d: ", i + 1);
        scanf("%d", &choice);
        team[i] = hero_list[choice - 1];
    }
}

void random_heroes(Hero team[3]) {
    for (int i = 0; i < 3; i++) {
        team[i] = hero_list[rand() % 6];
    }
}

int random_move(Hero *hero) {
    int move;
    do {
        move = rand() % 3;
    } while ((move == 0 && hero->scissors == 0) ||
             (move == 1 && hero->rock == 0) ||
             (move == 2 && hero->paper == 0));

    if (move == 0) hero->scissors--;
    else if (move == 1) hero->rock--;
    else hero->paper--;

    return move;
}
