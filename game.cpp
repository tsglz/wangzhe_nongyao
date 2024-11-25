#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "hero.hpp"
#include "ranking.hpp"

void start_game()
{
    Hero my_team[3], enemy_team[3];
    select_heroes(my_team);
    random_heroes(enemy_team);

    int my_score = 0, enemy_score = 0;
    for (int round = 0; round < 9; round++)
    {
        printf("\n�� %d �غ�:\n", round + 1);
        int my_move = player_move(&my_team[round % 3], &enemy_team[round % 3]);
        int enemy_move = random_move(&enemy_team[round % 3]);

        if (my_move == enemy_move)
        {
            printf("ƽ�֣�\n");
        }
        else if ((my_move == 0 && enemy_move == 2) ||
                 (my_move == 1 && enemy_move == 0) ||
                 (my_move == 2 && enemy_move == 1))
        {
            printf("�ҷ�ʤ����\n");
            my_score++;
        }
        else
        {
            printf("�з�ʤ����\n");
            enemy_score++;
        }
    }

    printf("\n��Ϸ�������ҷ��÷�: %d, �з��÷�: %d\n", my_score, enemy_score);
    save_game_result(my_score > enemy_score);
}
