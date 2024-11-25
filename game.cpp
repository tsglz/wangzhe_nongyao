#include <iostream>
#include "hero.hpp"
#include "ranking.hpp"

void start_game() {
    Hero my_team[3], enemy_team[3];
    select_heroes(my_team);
    random_heroes(enemy_team);

    int my_score = 0, enemy_score = 0;
    for (int round = 0; round < 9; round++) {
        std::cout << "\n第 " << round + 1 << " 回合:\n";
        int my_move = player_move(&my_team[round % 3]);
        int enemy_move = random_move(&enemy_team[round % 3]);

        if (my_move == enemy_move) {
            std::cout << "平局！\n";

        } else if ((my_move == 0 && enemy_move == 2) ||
                   (my_move == 1 && enemy_move == 0) ||
                   (my_move == 2 && enemy_move == 1)) {
            std::cout << "我方胜利！\n";
            my_score++;

                   } else {
                       std::cout << "敌方胜利！\n";
                       enemy_score++;
                   }
    }

    std::cout << "\n游戏结束，我方得分: " << my_score << ", 敌方得分: " << enemy_score << "\n";
    save_game_result(my_score > enemy_score);
}
