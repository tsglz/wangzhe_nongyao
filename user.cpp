#include <iostream>
#include <fstream>
#include <string>

int login() {
    std::string username, password, stored_user, stored_pass;

    std::ifstream infile("users.txt");
    if (!infile) {
        std::ofstream outfile("users.txt"); // Create the file if it doesn't exist
        if (!outfile) {
            std::cerr << "�޷������û��ļ���\n";
            return -1; // Return an error code
        }
        outfile.close();
    }

    printf("�������û���: ");
    std::cin >> username;
    printf("����������: ");
    std::cin >> password;

    bool found = false;
    infile.clear(); // Clear any error flags
    infile.seekg(0, std::ios::beg); // Rewind the file to the beginning

    while (infile >> stored_user >> stored_pass) {
        if (username == stored_user) {
            found = true;
            if (password == stored_pass) {
                printf("��¼�ɹ���\n");
                infile.close();
                return 1; // Login successful
            } else {
                printf("�������\n");
                infile.close();
                return 0; // Incorrect password
            }
        }
    }
    infile.close();

    if (!found) {
        std::ofstream outfile("users.txt", std::ios::app);
        if (outfile) {
            outfile << username << ' ' << password << '\n';
            printf("ע��ɹ���\n");
        } else {
            std::cerr << "�޷����û��ļ�����д�롣\n";
            return -1; // Return an error code
        }
        outfile.close();
    }

    return 0;
}
