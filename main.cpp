#include <iostream>
#include "user.hpp"
#include "game.hpp"
#include "ranking.hpp"

int main() {
    if (!login()) {
        std::print("ע��ɹ�����ӭ������Ϸ��\n");
    } else {
        std::print("��¼�ɹ�����ӭ������\n");
    }

    int choice;
    while (1) {
        std::print("\n=== ����ũҩ ===\n");
        std::print("1. ��ʼ��Ϸ\n");
        std::print("2. �鿴���а�\n");
        std::print("3. �˳�\n");
        std::print("��ѡ��: ");
        std::cin >> choice;

        switch (choice) {
            case 1:
                start_game();
            break;
            case 2:
                show_ranking();
            break;
            case 3:
                std::print("��л��Ϸ���ټ���\n");
            return 0;
            default:
                std::print("������Ч��������ѡ��\n");
        }
    }
    return 0;
}
