#include <iostream>
#include <cstdlib> // For rand()
#include "hero.hpp"

Hero hero_list[] = {
    {"赵云", 2, 2, 2}, {"宫本武藏", 4, 1, 1}, {"凯", 2, 3, 1},
    {"白起", 5, 0, 1}, {"韩信", 1, 2, 3}, {"诸葛亮", 2, 1, 3}
    // 可继续补充英雄列表
};

void select_heroes(Hero team[3]) {
    std::cout << "请选择3位英雄（用编号选择）:\n";
    for (int i = 0; i < 6; i++) {
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
