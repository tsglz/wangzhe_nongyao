#include <iostream>
#include <fstream>
#include <string>

int login() {
    std::string username, password, stored_user, stored_pass;

    std::ifstream infile("users.txt");
    if (!infile) {
        std::ofstream outfile("users.txt"); // �����ļ�
        outfile.close();
    }

    std::cout << "�������û���: ";
    std::cin >> username;
    std::cout << "����������: ";
    std::cin >> password;

    bool found = false;
    infile.clear(); // ���״̬�����¶�ȡ�ļ�
    infile.seekg(0, std::ios::beg); // �ص��ļ���ʼ

    while (infile >> stored_user >> stored_pass) {
        if (username == stored_user) {
            found = true;
            if (password == stored_pass) {
                std::cout << "��¼�ɹ���\n";
                infile.close();
                return 1; // ��¼�ɹ�
            } else {
                std::cout << "�������\n";
                infile.close();
                return 0;
            }
        }
    }
    infile.close();

    if (!found) {
        std::ofstream outfile("users.txt", std::ios::app);
        outfile << username << ' ' << password << '\n';
        outfile.close();
        std::cout << "ע��ɹ���\n";
    }

    return 0;
}
