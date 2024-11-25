#include <iostream>
#include "user.hpp"
#include "game.hpp"
#include "ranking.hpp"

int main() {
    if (!login()) {
        std::cout << "ע��ɹ�����ӭ������Ϸ��\n";
    } else {
        std::cout << "��¼�ɹ�����ӭ������\n";
    }

    int choice;
    while (1) {
        std::cout << "\n=== ����ũҩ ===\n";
        std::cout << "1. ��ʼ��Ϸ\n";
        std::cout << "2. �鿴���а�\n";
        std::cout << "3. �˳�\n";
        std::cout << "��ѡ��: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                start_game();
            break;
            case 2:
                show_ranking();
            break;
            case 3:
                std::cout << "��л��Ϸ���ټ���\n";
            return 0;
            default:
                std::cout << "������Ч��������ѡ��\n";
        }
    }
    return 0;
}
