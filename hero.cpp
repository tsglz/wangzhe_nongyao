#include <iostream>
#include <stdio.h>  // �����׼���������
#include <stdlib.h> // �����׼�⣬�������������
#include "hero.hpp" // �����Զ����ͷ�ļ�������Hero�ṹ��Ķ���
#include <string>
#include <memory>
#include "time_check.hpp"

#define HERO_COUNT 15

// ����һ��Ӣ���б��������Ӣ�۵����Ƽ��������ʯͷ����������
Hero hero_list[] = {
    {"����", 2, 2, 2}, {"�������", 4, 1, 1}, {"��", 2, 3, 1}, {"����", 5, 0, 1}, {"����", 1, 2, 3}, {"�����", 2, 1, 3}, {"����", 2, 0, 4}, {"����", 0, 3, 3}, {"���Ѿ�", 1, 1, 4}, {"槼�", 4, 1, 1}, {"������", 1, 4, 1}, {"����", 3, 2, 1}, {"¶��", 1, 3, 2}, {"��֪����", 4, 2, 0}, {"���ļ�", 0, 5, 1}};

// ѡ��Ӣ�۵ĺ���������һ��Ӣ�۶���������Ϊ����
void select_heroes(Hero team[3])
{
    int chosen[HERO_COUNT] = {0}; // ���ڼ�¼�Ѿ�ѡ���Ӣ�۱��
    printf("��ѡ��3λӢ�ۣ��ñ��ѡ��:\n");
    // �����ѡӢ�۵��б�
    for (int i = 0; i < 15; i++)
    {
        printf("%d. %s (����:%d ʯͷ:%d ��:%d)\n", i + 1, hero_list[i].name,
               hero_list[i].scissors, hero_list[i].rock, hero_list[i].paper);
    }

    // ѭ�������û�ѡ���Ӣ�۱��
    for (int i = 0; i < 3; i++)
    {
        int choice;
        int valid_choice = 0;

        while (!valid_choice)
        { // ֻҪ������Ч�ͼ���ѭ��
            printf("ѡ��Ӣ�� %d (1-%d): ", i + 1, HERO_COUNT);
            scanf("%d", &choice); // �û�����ѡ��ı��

            // ��������ѡ��
            if (choice < 1 || choice > HERO_COUNT)
            {
                printf("��Чѡ��������ѡ��\n");
            }
            else if (chosen[choice - 1])
            {
                printf("��Ӣ���ѱ�ѡ����ѡ������Ӣ�ۡ�\n");
            }
            else
            {
                // һ����Ч�����¶����е�Ӣ��
                team[i] = hero_list[choice - 1]; // ���¶����е�Ӣ��
                chosen[choice - 1] = 1;          // ��Ǹ�Ӣ��Ϊ��ѡ��
                valid_choice = 1;                // ���Ϊ��Чѡ������ѭ��
            }
        }
    }

    // ���ѡ���Ӣ��
    printf("��ѡ���Ӣ����:");
    for (int i = 0; i < 3; i++)
    {
        printf("%s ", team[i]);
    }
}

// ���ѡ��Ӣ�۵ĺ���
void random_heroes(Hero team[3])
{
    srand(time(NULL));          // ��ʼ�����������
    int chosen_index[15] = {0}; // ���ڼ�¼�Ѿ�ѡ���Ӣ�۱��
    for (int i = 0; i < 3; i++)
    {
        int index = rand() % 15;         // ÿ�δ�0��14���ȡһ��Ӣ��
        while (chosen_index[index] == 1) // �����Ӣ���Ѿ���ѡ�����������
        {
            index = rand() % 15;
        }
        team[i] = hero_list[index]; // ���¶����е�Ӣ��
        chosen_index[index] = 1;    // ��Ǹ�Ӣ��Ϊ��ѡ��
    }
    // ���ѡ���Ӣ��
    printf("�Է�ѡ���Ӣ����:");
    for (int i = 0; i < 3; i++)
    {
        printf("%s ", team[i]);
    }
}

// ������Լ�ѡ����ô�ƶ�
int player_move(Hero *hero, Hero *enemy)
{
    Timer t;
    int move;

    printf("�з����ڵļ���:%d ʯͷ:%d ��:%d\n", enemy->scissors, enemy->rock, enemy->paper);
    printf("�����ڵļ���:%d ʯͷ:%d ��:%d\n", hero->scissors, hero->rock, hero->paper);

    std::cout << "��ѡ����Ķ�����0=����, 1=ʯͷ, 2=������" << std::endl;
    // �첽�ȴ���10������ EchoFunc
    t.AsyncWait(10000, []() {}); // ������Է�һ������ָ�룬���ڴ���ʱ

    // ʹ�û����������������
    std::mutex input_mutex;

    // ��һ���߳��еȴ��û�����
    std::thread input_thread([&t, &input_mutex, &move]()
                             {
        scanf("%d", &move); // �û�����ѡ��Ķ���
        // ������ɺ�ֹͣ��ʱ��
        std::lock_guard<std::mutex> lock(input_mutex);
        t.Stop(); });

    input_thread.join();

    random_move(hero); // ���ѡ���ƶ�
    return move;       // ������ѡ��Ķ���

    while ((move == 0 && hero->scissors == 0) || // ���ѡ���������û�м�������
           (move == 1 && hero->rock == 0) ||     // ���ѡ��ʯͷ����û��ʯͷ����
           (move == 2 && hero->paper == 0))      // ���ѡ�񲼣���û�в�����
    {
        printf("��û��%s��������ѡ��: ",
               (move == 0 ? "����" : (move == 1 ? "ʯͷ" : "��")));
        std::thread input_thread([&t, &input_mutex, &move]()
                                 {
        scanf("%d", &move); // �û�����ѡ��Ķ���
        // ������ɺ�ֹͣ��ʱ��
        std::lock_guard<std::mutex> lock(input_mutex);
        t.Stop(); });
        random_move(hero); // ���ѡ���ƶ�
        return move;       // ������ѡ��Ķ���
    }

    while (move != 0 && move != 1 && move != 2)
    {
        printf("����������������룡");
        std::thread input_thread([&t, &input_mutex, &move]()
                                 {
        scanf("%d", &move); // �û�����ѡ��Ķ���
        // ������ɺ�ֹͣ��ʱ��
        std::lock_guard<std::mutex> lock(input_mutex);
        t.Stop(); });
        random_move(hero); // ���ѡ���ƶ�
        return move;       // ������ѡ��Ķ���
    }

    // ������Ӧ����������
    if (move == 0)
        hero->scissors--;
    else if (move == 1)
        hero->rock--;
    else if (move == 2)
        hero->paper--;

    return move; // ������ѡ��Ķ���
}

// ���ѡ���ƶ��ĺ�����������ѡ����ƶ���ʽ
int random_move(Hero *hero)
{
    int move; // �ƶ���ʽ��0=����, 1=ʯͷ, 2=��
    do
    {
        move = rand() % 3;                         // ���ѡ��һ������
    } while ((move == 0 && hero->scissors == 0) || // ���ѡ���������û�м�������
             (move == 1 && hero->rock == 0) ||     // ���ѡ��ʯͷ����û��ʯͷ����
             (move == 2 && hero->paper == 0)); // ���ѡ�񲼣���û�в�����

    // ������Ӧ����������
    if (move == 0)
        hero->scissors--;
    else if (move == 1)
        hero->rock--;
    else
        hero->paper--;

    return move; // ������ѡ��Ķ���
}