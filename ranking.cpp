#include <iostream>

void save_game_result(int win) {
    FILE *fp = fopen("ranking.txt", "a");
    fprintf(fp, "%s %d\n", "Player", win);
    fclose(fp);
}

void show_ranking() {
    std::print("\n=== ���а� ===\n");
    FILE *fp = fopen("ranking.txt", "r");
    if (!fp) {
        std::print("���޼�¼��\n");
        return;
    }

    char player[50];
    int win;
    while (fscanf(fp, "%s %d", player, &win) != EOF) {
        std::print("{}: {} ʤ\n", player, win);
    }
    fclose(fp);
}
