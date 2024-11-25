#include <stdio.h>
#include "user.h"
#include "game.h"
#include "ranking.h"

int main() {
    if (!login()) {
        printf("ע��ɹ�����ӭ������Ϸ��\n");
    } else {
        printf("��¼�ɹ�����ӭ������\n");
    }

    int choice;
    while (1) {
        printf("\n=== ����ũҩ ===\n");
        printf("1. ��ʼ��Ϸ\n");
        printf("2. �鿴���а�\n");
        printf("3. �˳�\n");
        printf("��ѡ��: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                start_game();
                break;
            case 2:
                show_ranking();
                break;
            case 3:
                printf("��л��Ϸ���ټ���\n");
                return 0;
            default:
                printf("������Ч��������ѡ��\n");
        }
    }
    return 0;
}
