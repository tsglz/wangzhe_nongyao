#include <iostream>
#include <fstream>
#include <string>
#include <cstring>

// 登录函数，接收用户名指针
int login(char *name)
{
    std::string username, password;       // 用户输入的用户名和密码
    std::string stored_user, stored_pass; // 从文件中读取的用户名和密码

    std::ifstream infile("users.txt"); // 打开用户文件进行读取
    // 检查文件是否存在
    if (!infile)
    {
        // 如果文件不存在，则创建文件
        std::ofstream outfile("users.txt");
        if (!outfile)
        {
            std::cerr << "无法创建用户文件。\n"; // 文件创建失败的提示
            return -1;                           // 返回错误代码
        }
        outfile.close(); // 关闭输出文件
    }

    // 读取用户输入的用户名
    printf("请输入用户名: ");
    std::cin >> username;
    strcpy(name, username.c_str()); // 将输入的用户名复制到传入的 name 指针
    // 读取用户输入的密码
    printf("请输入密码: ");
    std::cin >> password;

    bool found = false;             // 标记是否找到用户名
    infile.clear();                 // 清除任何错误标志
    infile.seekg(0, std::ios::beg); // 将文件指针移回文件开头

    // 从文件中逐行读取用户名和密码
    while (infile >> stored_user >> stored_pass)
    {
        if (username == stored_user)
        {                 // 如果找到匹配的用户名
            found = true; // 将 found 标记为 true
            if (password == stored_pass)
            {                           // 检查密码是否正确
                printf("登录成功！\n"); // 登录成功提示
                infile.close();         // 关闭输入文件
                return 1;               // 返回成功状态
            }
            else
            {
                while (password != stored_pass)
                {
                    printf("密码错误！\n"); // 密码不正确提示
                    // 读取用户输入的密码
                    printf("请重新输入密码: ");
                    std::cin >> password;
                }
                infile.close(); // 关闭输入文件
                return 1;       // 返回密码错误状态
            }
        }
    }
    infile.close(); // 关闭输入文件

    // 如果未找到用户，则进行注册
    if (!found)
    {
        std::ofstream outfile("users.txt", std::ios::app); // 以追加模式打开文件
        if (outfile)
        {
            // 将新注册的用户名和密码写入文件
            outfile << username << ' ' << password << '\n';
            printf("注册成功！\n"); // 注册成功提示
        }
        else
        {
            std::cerr << "无法打开用户文件进行写入。\n"; // 写入文件失败提示
            return -1;                                   // 返回错误代码
        }
        outfile.close(); // 关闭输出文件
    }

    return 0; // 结束函数，返回一般状态
    }
