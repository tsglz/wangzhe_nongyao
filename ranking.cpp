#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#define MAX_PLAYERS 100

// ��ҽṹ��
typedef struct {
    char name[50];
    int wins;
} Player;

// �ȽϺ�������������
int compare(const void *a, const void *b) {
    Player *playerA = (Player *)a;
    Player *playerB = (Player *)b;
    return playerB->wins - playerA->wins; // ��������
}

// ������Ϸ���
void save_game_result(int win, const char *name) {
    FILE *fp = fopen("ranking.txt", "r+"); // �Զ�дģʽ���ļ�
    if (!fp) {
        // ����ļ������ڣ��������ļ�
        fp = fopen("ranking.txt", "w+");
        if (!fp) {
            printf("�޷������ļ�����д�롣\n");
            return;
        }
    }

    Player players[MAX_PLAYERS];
    int playerCount = 0;
    bool found = false;

    // ��ȡ���������Ϣ
    while (fscanf(fp, "%s %d", players[playerCount].name, &players[playerCount].wins) != EOF) {
        playerCount++;
    }

    // �����Ƿ����и����
    for (int i = 0; i < playerCount; i++) {
        if (strcmp(players[i].name, name) == 0) {
            players[i].wins += win; // ����ʤ������
            found = true;
            break;
        }
    }

    // ���û���ҵ�����ң�����¼�¼
    if (!found && playerCount < MAX_PLAYERS) {
        strncpy(players[playerCount].name, name, sizeof(players[playerCount].name));
        players[playerCount].wins = win;
        playerCount++;
    }

    // ��������б�
    qsort(players, playerCount, sizeof(Player), compare);

    // ��д�ļ�����
    freopen("ranking.txt", "w", fp); // ����ļ�������д��
    for (int i = 0; i < playerCount; i++) {
        fprintf(fp, "%s %d\n", players[i].name, players[i].wins);
    }

    fclose(fp); // �ر��ļ�
}

// ��ʾ���а�
void show_ranking() {
    printf("\n=== ���а� ===\n");
    FILE *fp = fopen("ranking.txt", "r");
    if (!fp) {
        printf("���޼�¼��\n");
        return;
    }

    char player[50];
    int win;
    while (fscanf(fp, "%s %d", player, &win) != EOF) {
        printf("%s: %d ʤ\n", player, win);
    }
    fclose(fp);
}