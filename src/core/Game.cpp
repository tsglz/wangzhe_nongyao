#include "Game.h"

Game::Game() {
}

/**
 *
 * @param username caculate win rate
 * @param oppositeSkills QList(QList(4, 1, 1), QList(2, 3, 1), QList(5, 0, 1))
 * @param selectedSkills QList(QList(0, 3, 3), QList(4, 1, 1), QList(3, 2, 1))
 * @param round caculate win rate
 * @param heroSelected 0 1 2 depands on the button clicked
 * @return
 */
int Game::hasGame(QString username, QVector<QVector<int> > &oppositeSkills, QVector<QVector<int> > &selectedSkills,
                  int round, int heroSelected) {
    // username 和 round 仅仅用于计算胜率

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution dis(0, 2);
    int oppositeHeroSelected;

    QVector<int> oppositeSkillsSingleList;
    QVector<int> selectedSkillsSingleList = (selectedSkills)[heroSelected];

    do {
        oppositeHeroSelected = dis(gen);
        oppositeSkillsSingleList = (oppositeSkills)[oppositeHeroSelected];
    } while (sum(oppositeSkillsSingleList) == 0);

    if (sum(selectedSkillsSingleList) == 0) {
        return -10; // if selected hero has no skills return -10
    }

    int oppositeChoice = randomChoose(oppositeSkillsSingleList, oppositeSkills, oppositeHeroSelected);
    int userChoice = randomChoose(selectedSkillsSingleList, selectedSkills, heroSelected);

    if (userChoice == oppositeChoice) {
        return 0;
    } else if ((userChoice + 1) % 3 == oppositeChoice) {
        return -1;
    } else {
        return 1;
    }
}

Game::~Game() {
}

void Game::appendDatabase() {
    // TODO
}

int Game::sum(QVector<int> list) {
    int sum = 0;
    for (int value: list) {
        sum += value;
    }
    return sum;
}

/**
 * @brief random and change the list
 * @param list
 * @param skills 
 * @param heroSelected 
 * @return 0 - scissors, 1 - rock, 2 - paper
 */
int Game::randomChoose(QVector<int> list, QVector<QVector<int> > &skills, int heroSelected) {
    // 创建随机数生成器
    std::random_device rd;
    std::mt19937 gen(rd());

    // 收集可用选择的索引
    QVector<int> availableChoices;
    for (int i = 0; i < list.size(); ++i) {
        if (list[i] > 0) {
            availableChoices.append(i);
        }
    }

    // 随机选择一个可用的物品
    std::uniform_int_distribution<> dis(0, availableChoices.size() - 1);
    int randomIndex = dis(gen);
    int choice = availableChoices[randomIndex];

    // 更新技能列表
    QVector<int> &heroSkills = skills[heroSelected];
    heroSkills[choice]--;

    return choice;
}
