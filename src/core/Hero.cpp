#include "Hero.h"

Hero::Hero() {
    heroList.append({"赵云", 2, 2, 2});
    heroList.append({"宫本武藏", 4, 1, 1});
    heroList.append({"凯", 2, 3, 1});
    heroList.append({"白起", 5, 0, 1});
    heroList.append({"韩信", 1, 2, 3});
    heroList.append({"诸葛亮", 2, 1, 3});
    heroList.append({"刘邦", 2, 0, 4});
    heroList.append({"后羿", 0, 3, 3});
    heroList.append({"王昭君", 1, 1, 4});
    heroList.append({"妲己", 4, 1, 1});
    heroList.append({"安琪拉", 1, 4, 1});
    heroList.append({"貂蝉", 3, 2, 1});
    heroList.append({"露娜", 1, 3, 2});
    heroList.append({"不知火舞", 4, 2, 0});
    heroList.append({"蔡文姬", 0, 5, 1});
}


/**
 * @brief Reture HeroList to show in the GameView
 * @return
 */
QVector<Hero::Attributes> Hero::showHeroes() {
    return heroList;
}

QVector<int> Hero::oppositeRandomSelectedHeroes() {
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::mt19937 generator(seed);
    std::uniform_int_distribution<int> distribution(0, 14);

    QVector<int> oppositeRandomHeroes(15, 0); // Track chosen heroes

    for (int i = 0; i < 3; i++) {
        int index = distribution(generator); // Randomly select a hero index
        while (oppositeRandomHeroes[index]) { // If already chosen, pick another
            index = distribution(generator);
        }
        oppositeRandomHeroes[index] = 1; // Mark hero as chosen
    }
    return oppositeRandomHeroes;
}

Hero::~Hero() {
}
