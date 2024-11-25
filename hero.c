#include <stdio.h>
#include <stdlib.h>
#include "hero.h"

Hero hero_list[] = {
    {"����", 2, 2, 2}, {"�������", 4, 1, 1}, {"��", 2, 3, 1}, 
    {"����", 5, 0, 1}, {"����", 1, 2, 3}, {"�����", 2, 1, 3}
    // �ɼ�������Ӣ���б�
};

void select_heroes(Hero team[3]) {
    printf("��ѡ��3λӢ�ۣ��ñ��ѡ��:\n");
    for (int i = 0; i < 6; i++) {
        printf("%d. %s (����:%d ʯͷ:%d ��:%d)\n", i + 1, hero_list[i].name,
               hero_list[i].scissors, hero_list[i].rock, hero_list[i].paper);
    }

    for (int i = 0; i < 3; i++) {
        int choice;
        printf("ѡ��Ӣ�� %d: ", i + 1);
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
