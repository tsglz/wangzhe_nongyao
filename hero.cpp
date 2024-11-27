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
    int move;
    bool input_valid = false;

    printf("�з����ڵļ���:%d ʯͷ:%d ��:%d\n", enemy->scissors, enemy->rock, enemy->paper);
    printf("�����ڵļ���:%d ʯͷ:%d ��:%d\n", hero->scissors, hero->rock, hero->paper);

    std::cout << "��ѡ����Ķ�����0=����, 1=ʯͷ, 2=������" << std::endl;

    std::mutex input_mutex;
    std::condition_variable cv;
    Timer t([hero, &move, &input_valid, &cv]()
            {
                std::cout << "��ʱ���Զ�ִ������ƶ���" << std::endl;
                move = random_move(hero);
                input_valid = true;
                cv.notify_all(); // ֪ͨ�����̳߳�ʱ�ѷ���
            });

    t.AsyncWait(10000); // ������Է�һ������ָ�룬���ڴ���ʱ

    while (!input_valid)
    {
        std::thread input_thread([&t, &input_mutex, &cv, &move, &input_valid]()
                                 {
            std::lock_guard<std::mutex> lock(input_mutex);
            if (!t.IsTimeoutTriggered()) { // ��ʱδ����ʱ�Ž�������
                scanf("%d", &move); // �û�����

                // У�������Ƿ���Ч
                if (move == 0 || move == 1 || move == 2) {
                    input_valid = true; // ������Ч
                    t.Stop();           // ֹͣ��ʱ��
                    cv.notify_all();    // ֪ͨ�����߳�������Ч
                } else {
                    std::cout << "����������������루0=����, 1=ʯͷ, 2=����: ";
                }
            } else {
                input_valid = true; // ��ʱ�������˳�ѭ��
                cv.notify_all();    // ֪ͨ�����̳߳�ʱ
            } });

        input_thread.detach(); // ���������̵߳����ȴ�

        // �ȴ�������ɻ�ʱ
        std::unique_lock<std::mutex> lock(input_mutex);
        cv.wait(lock, [&input_valid]()
                { return input_valid; }); // �ȴ�������Ч��ʱ
    }

    // �������Ƿ����㹻����Ʒ���иö���
    if (t.IsTimeoutTriggered())
    {
        return move; // ��ʱ�������ѡ��Ķ���
    }

    while ((move == 0 && hero->scissors == 0) ||
           (move == 1 && hero->rock == 0) ||
           (move == 2 && hero->paper == 0))
    {
        printf("��û��%s��������ѡ��: ",
               (move == 0 ? "����" : (move == 1 ? "ʯͷ" : "��")));

        std::thread input_thread([&t, &input_mutex, &cv, &move]()
                                 {
                                     std::lock_guard<std::mutex> lock(input_mutex);
                                     scanf("%d", &move); // ��������ѡ��Ķ���
                                     t.Stop();           // ������ɺ�ֹͣ��ʱ��
                                     cv.notify_all();    // ֪ͨ�����߳������Ѹ���
                                 });

        input_thread.detach(); // ���������̵߳����ȴ�

        // �ȴ�������ɻ�ʱ
        std::unique_lock<std::mutex> lock(input_mutex);
        cv.wait(lock, [&input_valid]()
                { return input_valid; }); // �����ȴ�
    }

    // ������Ӧ����������
    if (move == 0)
    {
        hero->scissors--;
    }
    else if (move == 1)
    {
        hero->rock--;
    }
    else if (move == 2)
    {
        hero->paper--;
    }

    return move; // ������ѡ��Ķ���
}

// ���ѡ���ƶ��ĺ�����������ѡ����ƶ���ʽ
int random_move(Hero *hero)
{
    int move; // �ƶ���ʽ��0=����, 1=ʯͷ, 2=��
    do
    {
        srand(time(NULL)); // ��ʼ�����������
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
