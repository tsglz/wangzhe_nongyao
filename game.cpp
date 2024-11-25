#include <iostream>
#include <cstdlib>
#include <ctime>
#include "hero.hpp"
#include "ranking.hpp"

#include <format>

void start_game() {
    Hero my_team[3], enemy_team[3];
    select_heroes(my_team);
    random_heroes(enemy_team);

    int my_score = 0, enemy_score = 0;
    for (int round = 0; round < 9; ++round) {
        std::print("\n第 {} 回合:\n", round + 1);
        int my_move = player_move(&my_team[round % 3], &enemy_team[round % 3]);
        int enemy_move = random_move(&enemy_team[round % 3]);

        if (my_move == enemy_move) {
            std::print("平局！\n");
        } else if ((my_move == 0 && enemy_move == 2) ||
                   (my_move == 1 && enemy_move == 0) ||
                   (my_move == 2 && enemy_move == 1)) {
            std::print("我方胜利！\n");
            ++my_score;
                   } else {
                       std::print("敌方胜利！\n");
                       ++enemy_score;
                   }
    }

    std::print("\n游戏结束，我方得分: {}, 敌方得分: {}\n", my_score, enemy_score);
    save_game_result(my_score > enemy_score);
}
