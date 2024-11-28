#include <iostream>
#include <fstream>
#include <string>
#include <cstring>

// ��¼�����������û���ָ��
int login(char *name)
{
    std::string username, password;       // �û�������û���������
    std::string stored_user, stored_pass; // ���ļ��ж�ȡ���û���������

    std::ifstream infile("users.txt"); // ���û��ļ����ж�ȡ
    // ����ļ��Ƿ����
    if (!infile)
    {
        // ����ļ������ڣ��򴴽��ļ�
        std::ofstream outfile("users.txt");
        if (!outfile)
        {
            std::cerr << "�޷������û��ļ���\n"; // �ļ�����ʧ�ܵ���ʾ
            return -1;                           // ���ش������
        }
        outfile.close(); // �ر�����ļ�
    }

    // ��ȡ�û�������û���
    printf("�������û���: ");
    std::cin >> username;
    strcpy(name, username.c_str()); // ��������û������Ƶ������ name ָ��
    // ��ȡ�û����������
    printf("����������: ");
    std::cin >> password;

    bool found = false;             // ����Ƿ��ҵ��û���
    infile.clear();                 // ����κδ����־
    infile.seekg(0, std::ios::beg); // ���ļ�ָ���ƻ��ļ���ͷ

    // ���ļ������ж�ȡ�û���������
    while (infile >> stored_user >> stored_pass)
    {
        if (username == stored_user)
        {                 // ����ҵ�ƥ����û���
            found = true; // �� found ���Ϊ true
            if (password == stored_pass)
            {                           // ��������Ƿ���ȷ
                printf("��¼�ɹ���\n"); // ��¼�ɹ���ʾ
                infile.close();         // �ر������ļ�
                return 1;               // ���سɹ�״̬
            }
            else
            {
                while (password != stored_pass)
                {
                    printf("�������\n"); // ���벻��ȷ��ʾ
                    // ��ȡ�û����������
                    printf("��������������: ");
                    std::cin >> password;
                }
                infile.close(); // �ر������ļ�
                return 1;       // �����������״̬
            }
        }
    }
    infile.close(); // �ر������ļ�

    // ���δ�ҵ��û��������ע��
    if (!found)
    {
        std::ofstream outfile("users.txt", std::ios::app); // ��׷��ģʽ���ļ�
        if (outfile)
        {
            // ����ע����û���������д���ļ�
            outfile << username << ' ' << password << '\n';
            printf("ע��ɹ���\n"); // ע��ɹ���ʾ
        }
        else
        {
            std::cerr << "�޷����û��ļ�����д�롣\n"; // д���ļ�ʧ����ʾ
            return -1;                                   // ���ش������
        }
        outfile.close(); // �ر�����ļ�
    }

    return 0; // ��������������һ��״̬
    }
