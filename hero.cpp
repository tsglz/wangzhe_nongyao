#include <iostream>
#include <cstdlib>
#include <ctime>
#include "hero.hpp"

Hero hero_list[] = {
    {"����", 2, 2, 2}, {"�������", 4, 1, 1}, {"��", 2, 3, 1},
    {"����", 5, 0, 1}, {"����", 1, 2, 3}, {"�����", 2, 1, 3},
    {"����", 2, 0, 4}, {"����", 0, 3, 3}, {"���Ѿ�", 1, 1, 4},
    {"槼�", 4, 1, 1}, {"������", 1, 4, 1}, {"����", 3, 2, 1},
    {"¶��", 1, 3, 2}, {"��֪����", 4, 2, 0}, {"���ļ�", 0, 5, 1}
};

void select_heroes(Hero team[3]) {
    std::cout << "��ѡ��3λӢ�ۣ��ñ��ѡ��:\n";
    for (int i = 0; i < 15; i++) {
        std::cout << i + 1 << ". " << hero_list[i].name
                  << " (����:" << hero_list[i].scissors
                  << " ʯͷ:" << hero_list[i].rock
                  << " ��:" << hero_list[i].paper << ")\n";
    }

    for (int i = 0; i < 3; i++) {
        int choice;
        std::cout << "ѡ��Ӣ�� " << i + 1 << ": ";
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
    std::cout << "�����ڵļ���:" << hero->scissors
              << " ʯͷ:" << hero->rock
              << " ��:" << hero->paper << std::endl;
    std::cout << "��ѡ����Ķ�����0=����, 1=ʯͷ, 2=��: ";
    std::cin >> move;
    while ((move == 0 && hero->scissors == 0) ||
           (move == 1 && hero->rock == 0) ||
           (move == 2 && hero->paper == 0)) {
        std::cout << "��û��" << (move == 0 ? "����" : (move == 1 ? "ʯͷ" : "��")) << "��������ѡ��: ";
        std::cin >> move;
    }

    if (move == 0) hero->scissors--;
    else if (move == 1) hero->rock--;
    else hero->paper--;

    return move;
}