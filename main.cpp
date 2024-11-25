#include <iostream>
#include "user.hpp"
#include "game.hpp"
#include "ranking.hpp"

int main() {
    if (!login()) {
        std::cout << "注册成功，欢迎进入游戏！\n";
    } else {
        std::cout << "登录成功，欢迎回来！\n";
    }

    int choice;
    while (1) {
        std::cout << "\n=== 王者农药 ===\n";
        std::cout << "1. 开始游戏\n";
        std::cout << "2. 查看排行榜\n";
        std::cout << "3. 退出\n";
        std::cout << "请选择: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                start_game();
            break;
            case 2:
                show_ranking();
            break;
            case 3:
                std::cout << "感谢游戏，再见！\n";
            return 0;
            default:
                std::cout << "输入无效，请重新选择。\n";
        }
    }
    return 0;
}
