#include <iostream>
#include <fstream>
#include <string>

int login() {
    std::string username, password, stored_user, stored_pass;

    std::ifstream infile("users.txt");
    if (!infile) {
        std::ofstream outfile("users.txt"); // Create the file if it doesn't exist
        if (!outfile) {
            std::cerr << "无法创建用户文件。\n";
            return -1; // Return an error code
        }
        outfile.close();
    }

    printf("请输入用户名: ");
    std::cin >> username;
    printf("请输入密码: ");
    std::cin >> password;

    bool found = false;
    infile.clear(); // Clear any error flags
    infile.seekg(0, std::ios::beg); // Rewind the file to the beginning

    while (infile >> stored_user >> stored_pass) {
        if (username == stored_user) {
            found = true;
            if (password == stored_pass) {
                printf("登录成功！\n");
                infile.close();
                return 1; // Login successful
            } else {
                printf("密码错误！\n");
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
            printf("注册成功！\n");
        } else {
            std::cerr << "无法打开用户文件进行写入。\n";
            return -1; // Return an error code
        }
        outfile.close();
    }

    return 0;
}
