#include <iostream>
#include <format>  // Include this for std::print in C++23
#include <cstdlib>
#include <ctime>
#include "hero.hpp"

// Define the list of heroes
Hero hero_list[] = {
    {"����", 2, 2, 2}, {"�������", 4, 1, 1}, {"��", 2, 3, 1}, {"����", 5, 0, 1}, {"����", 1, 2, 3},
    {"�����", 2, 1, 3}, {"����", 2, 0, 4}, {"����", 0, 3, 3}, {"���Ѿ�", 1, 1, 4}, {"槼�", 4, 1, 1},
    {"������", 1, 4, 1}, {"����", 3, 2, 1}, {"¶��", 1, 3, 2}, {"��֪����", 4, 2, 0}, {"���ļ�", 0, 5, 1}
};

void select_heroes(Hero team[3]) {
    std::print("��ѡ��3λӢ�ۣ��ñ��ѡ��:\n");
    for (int i = 0; i < 15; ++i) {
        std::print("{}. {} (����:{} ʯͷ:{} ��:{})\n", i + 1, hero_list[i].name, hero_list[i].scissors, hero_list[i].rock, hero_list[i].paper);
    }

    for (int i = 0; i < 3; ++i) {
        int choice;
        std::print("ѡ��Ӣ�� {}: ", i + 1);
        std::cin >> choice;
        if (choice < 1 || choice > 15) {
            std::print("��Чѡ��������1��15֮��ı�š�\n");
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
    std::print("�з����ڵļ���:{} ʯͷ:{} ��:{}\n", enemy->scissors, enemy->rock, enemy->paper);
    std::print("�����ڵļ���:{} ʯͷ:{} ��:{}\n", hero->scissors, hero->rock, hero->paper);
    std::print("��ѡ����Ķ�����0=����, 1=ʯͷ, 2=������");
    int move;
    std::cin >> move;

    while ((move == 0 && hero->scissors == 0) ||
           (move == 1 && hero->rock == 0) ||
           (move == 2 && hero->paper == 0) ||
           (move != 0 && move != 1 && move != 2)) {
        if (move != 0 && move != 1 && move != 2) {
            std::print("����������������룡\n");
        } else {
            std::print("��û��{}��������ѡ��: ", (move == 0 ? "����" : (move == 1 ? "ʯͷ" : "��")));
        }
        std::cin >> move;
    }

    if (move == 0) hero->scissors--;
    else if (move == 1) hero->rock--;
    else hero->paper--;

    return move;
}
