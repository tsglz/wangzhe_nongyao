#ifndef HERO_H
#define HERO_H

#include <iostream>
#include <memory>
#include <stdio.h>  // 引入标准输入输出库
#include <stdlib.h> // 引入标准库，用于随机数生成
#include <string>
#include <time.h>   // 引入时间库，用于获取当前时间

typedef struct {
    char name[20];
    int scissors;
    int rock;
    int paper;
} Hero;

void select_heroes(Hero team[3]);
void random_heroes(Hero team[3]);
int random_move(Hero *hero);
int player_move(Hero *my_team);

#endif // HERO_H
