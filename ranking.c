#include <stdio.h>

void save_game_result(int win) {
    FILE *fp = fopen("ranking.txt", "a");
    fprintf(fp, "%s %d\n", "Player", win);
    fclose(fp);
}

void show_ranking() {
    printf("\n=== ÅÅÐÐ°ñ ===\n");
    FILE *fp = fopen("ranking.txt", "r");
    if (!fp) {
        printf("ÔÝÎÞ¼ÇÂ¼¡£\n");
        return;
    }

    char player[50];
    int win;
    while (fscanf(fp, "%s %d", player, &win) != EOF) {
        printf("%s: %d Ê¤\n", player, win);
    }
    fclose(fp);
}
