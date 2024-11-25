#include <iostream>
#include <fstream>
#include <string>

int login() {
    std::string username, password, stored_user, stored_pass;

    std::ifstream infile("users.txt");
    if (!infile) {
        std::ofstream outfile("users.txt"); // 创建文件
        outfile.close();
    }

    std::cout << "请输入用户名: ";
    std::cin >> username;
    std::cout << "请输入密码: ";
    std::cin >> password;

    bool found = false;
    infile.clear(); // 清除状态以重新读取文件
    infile.seekg(0, std::ios::beg); // 回到文件开始

    while (infile >> stored_user >> stored_pass) {
        if (username == stored_user) {
            found = true;
            if (password == stored_pass) {
                std::cout << "登录成功！\n";
                infile.close();
                return 1; // 登录成功
            } else {
                std::cout << "密码错误！\n";
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
        std::cout << "注册成功！\n";
    }

    return 0;
}
