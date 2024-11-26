#include <iostream>
#include <format>  // Include this for std::print in C++23
#include <cstdlib>
#include <ctime>
#include "hero.hpp"

// Define the list of heroes
Hero hero_list[] = {
    {"赵云", 2, 2, 2}, {"宫本武藏", 4, 1, 1}, {"凯", 2, 3, 1}, {"白起", 5, 0, 1}, {"韩信", 1, 2, 3},
    {"诸葛亮", 2, 1, 3}, {"刘邦", 2, 0, 4}, {"后羿", 0, 3, 3}, {"王昭君", 1, 1, 4}, {"妲己", 4, 1, 1},
    {"安琪拉", 1, 4, 1}, {"貂蝉", 3, 2, 1}, {"露娜", 1, 3, 2}, {"不知火舞", 4, 2, 0}, {"蔡文姬", 0, 5, 1}
};

void select_heroes(Hero team[3]) {
    std::print("请选择3位英雄（用编号选择）:\n");
    for (int i = 0; i < 15; ++i) {
        std::print("{}. {} (剪刀:{} 石头:{} 布:{})\n", i + 1, hero_list[i].name, hero_list[i].scissors, hero_list[i].rock, hero_list[i].paper);
    }

    for (int i = 0; i < 3; ++i) {
        int choice;
        std::print("选择英雄 {}: ", i + 1);
        std::cin >> choice;
        if (choice < 1 || choice > 15) {
            std::print("无效选择，请输入1到15之间的编号。\n");
            --i;  // Decrement to re-choose
        } else {
            team[i] = hero_list[choice - 1];
        }
    }
}

void random_heroes(Hero team[3]) {
    for (int i = 0; i < 3; ++i) {
        team[i] = hero_list[std::rand() % 15];  // Correct the range to match the number of heroes
    }
}

// Function to randomly select a move for a given hero
int random_move(Hero* hero) {
    int move;
    do {
        move = std::rand() % 3;
    } while ((move == 0 && hero->scissors == 0) ||
             (move == 1 && hero->rock == 0) ||
             (move == 2 && hero->paper == 0));

    if (move == 0) hero->scissors--;
    else if (move == 1) hero->rock--;
    else hero->paper--;

    return move;
}

// Function for the player to choose a move
int player_move(Hero* hero, Hero* enemy) {
    std::print("敌方现在的剪刀:{} 石头:{} 布:{}\n", enemy->scissors, enemy->rock, enemy->paper);
    std::print("你现在的剪刀:{} 石头:{} 布:{}\n", hero->scissors, hero->rock, hero->paper);
    std::print("请选择你的动作（0=剪刀, 1=石头, 2=布）：");
    int move;
    std::cin >> move;

    while ((move == 0 && hero->scissors == 0) ||
           (move == 1 && hero->rock == 0) ||
           (move == 2 && hero->paper == 0) ||
           (move != 0 && move != 1 && move != 2)) {
        if (move != 0 && move != 1 && move != 2) {
            std::print("输入错误，请重新输入！\n");
        } else {
            std::print("你没有{}，请重新选择: ", (move == 0 ? "剪刀" : (move == 1 ? "石头" : "布")));
        }
        std::cin >> move;
    }

    if (move == 0) hero->scissors--;
    else if (move == 1) hero->rock--;
    else hero->paper--;

    return move;
}
