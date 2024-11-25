#include <stdio.h>  // �����׼���������
#include <stdlib.h> // �����׼�⣬�������������
#include "hero.hpp" // �����Զ����ͷ�ļ�������Hero�ṹ��Ķ���

// ����һ��Ӣ���б����������Ӣ�۵����Ƽ��������ʯͷ����������
Hero hero_list[] = {
    {"����", 2, 2, 2}, {"�������", 4, 1, 1}, {"��", 2, 3, 1}, {"����", 5, 0, 1}, {"����", 1, 2, 3}, {"�����", 2, 1, 3}, {"����", 2, 0, 4}, {"����", 0, 3, 3}, {"���Ѿ�", 1, 1, 4}, {"槼�", 4, 1, 1}, {"������", 1, 4, 1}, {"����", 3, 2, 1}, {"¶��", 1, 3, 2}, {"��֪����", 4, 2, 0}, {"���ļ�", 0, 5, 1}};

// ѡ��Ӣ�۵ĺ���������һ��Ӣ�۶���������Ϊ����
void select_heroes(Hero team[3])
{
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
        printf("ѡ��Ӣ�� %d: ", i + 1);
        scanf("%d", &choice);            // �û�����ѡ��ı��
        team[i] = hero_list[choice - 1]; // ���¶����е�Ӣ��
    }
}

// ���ѡ��Ӣ�۵ĺ���
void random_heroes(Hero team[3])
{
    // �����ǰ6��Ӣ����ѡ��3λӢ��
    for (int i = 0; i < 3; i++)
    {
        team[i] = hero_list[rand() % 6]; // ÿ�δ�0��5���ȡһ��Ӣ��
    }
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

// ������Լ�ѡ����ô�ƶ�
int player_move(Hero *hero, Hero *enemy)
{
    int move;
    printf("�з����ڵļ���:%d ʯͷ:%d ��:%d\n", hero->scissors, hero->rock, hero->paper);
    printf("�����ڵļ���:%d ʯͷ:%d ��:%d\n", enemy->scissors, enemy->rock, enemy->paper);
    printf("��ѡ����Ķ�����0=����, 1=ʯͷ, 2=������");
    scanf("%d", &move);                          // �û�����ѡ��Ķ���
    while ((move == 0 && hero->scissors == 0) || // ���ѡ���������û�м�������
           (move == 1 && hero->rock == 0) ||     // ���ѡ��ʯͷ����û��ʯͷ����
           (move == 2 && hero->paper == 0))      // ���ѡ�񲼣���û�в�����
    {
        printf("��û��%s��������ѡ��: ",
               (move == 0 ? "����" : (move == 1 ? "ʯͷ" : "��")));
        scanf("%d", &move);
    }

    while (move != 0 && move != 1 && move != 2)
    {
        printf("����������������룡");
        scanf("%d", &move);
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