#include <iostream>
#include <cstdlib>
#include <ctime>
#include "hero.hpp"

Hero hero_list[] = {
    {"赵云", 2, 2, 2}, {"宫本武藏", 4, 1, 1}, {"凯", 2, 3, 1},
    {"白起", 5, 0, 1}, {"韩信", 1, 2, 3}, {"诸葛亮", 2, 1, 3},
    {"刘邦", 2, 0, 4}, {"后羿", 0, 3, 3}, {"王昭君", 1, 1, 4},
    {"妲己", 4, 1, 1}, {"安琪拉", 1, 4, 1}, {"貂蝉", 3, 2, 1},
    {"露娜", 1, 3, 2}, {"不知火舞", 4, 2, 0}, {"蔡文姬", 0, 5, 1}
};

void select_heroes(Hero team[3]) {
    std::cout << "请选择3位英雄（用编号选择）:\n";
    for (int i = 0; i < 15; i++) {
        std::cout << i + 1 << ". " << hero_list[i].name
                  << " (剪刀:" << hero_list[i].scissors
                  << " 石头:" << hero_list[i].rock
                  << " 布:" << hero_list[i].paper << ")\n";
    }

    for (int i = 0; i < 3; i++) {
        int choice;
        std::cout << "选择英雄 " << i + 1 << ": ";
        std::cin >> choice;
        team[i] = hero_list[choice - 1];
    }
}

void random_heroes(Hero team[3]) {
    for (int i = 0; i < 3; i++) {
        team[i] = hero_list[rand() % 6];
    }
}

int random_move(Hero* hero) {
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

int player_move(Hero* hero) {
    int move;
    std::cout << "你现在的剪刀:" << hero->scissors
              << " 石头:" << hero->rock
              << " 布:" << hero->paper << std::endl;
    std::cout << "请选择你的动作：0=剪刀, 1=石头, 2=布: ";
    std::cin >> move;
    while ((move == 0 && hero->scissors == 0) ||
           (move == 1 && hero->rock == 0) ||
           (move == 2 && hero->paper == 0)) {
        std::cout << "你没有" << (move == 0 ? "剪刀" : (move == 1 ? "石头" : "布")) << "，请重新选择: ";
        std::cin >> move;
    }

    if (move == 0) hero->scissors--;
    else if (move == 1) hero->rock--;
    else hero->paper--;

    return move;
}