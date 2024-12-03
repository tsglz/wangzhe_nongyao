#include "Game.h"

Game::Game() {
}

/**
 *
 * @param username calculate win rate
 * @param oppositeSkills QList(QList(4, 1, 1), QList(2, 3, 1), QList(5, 0, 1))
 * @param selectedSkills QList(QList(0, 3, 3), QList(4, 1, 1), QList(3, 2, 1))
 * @param round calculate win rate
 * @param heroSelected the first is 0 1 2, which depends on the button clicked. The second is the index of the selected hero, such as 1 9 10
 * @return 0 - draw, 1 - win, -1 - lose, -10 - no skills
 */
int Game::hasGame(QString username, QVector<QVector<int> > &oppositeSkills, QVector<QVector<int> > &selectedSkills,
                  int round, QPair<int, int> heroSelected, QPair<int, int> oppositeHeroSelected) {
    // username 和 round 仅仅用于计算胜率

    Hero hero;
    auto heroList = hero.showHeroes();

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution dis(0, 2);
    // QPair<int, int> oppositeHeroSelected;

    QVector<int> oppositeSkillsSingleList;
    QVector<int> selectedSkillsSingleList = (selectedSkills)[heroSelected.first];

    do {
        oppositeHeroSelected.first = dis(gen);
        oppositeSkillsSingleList = (oppositeSkills)[oppositeHeroSelected.first];
    } while (sum(oppositeSkillsSingleList) == 0);

    if (sum(selectedSkillsSingleList) == 0) {
        return -10; // if selected hero has no skills return -10
    }

    // 0 or 1 or 2
    int oppositeChoice = randomChoose(oppositeSkillsSingleList, oppositeSkills, oppositeHeroSelected); // oppositeHeroSelected 的第二个参数其实为空 具体的处理的部分放在了 randomChoose 函数里面
    int userChoice = randomChoose(selectedSkillsSingleList, selectedSkills, heroSelected);

    qDebug() <<  "oppositeHeroSelected: " << oppositeHeroSelected;
    initDatabase();
    if (userChoice == oppositeChoice) {
        // addDatabase(heroList[oppositeHeroSelected.second].name, QString::number(oppositeChoice), 0);
        addDatabase(heroList[heroSelected.second].name, QString::number(userChoice), 0);
        db.close();
        return 0;
    } else if ((userChoice + 1) % 3 == oppositeChoice) {
        // addDatabase(heroList[oppositeHeroSelected.second].name, QString::number(oppositeChoice), 1);
        addDatabase(heroList[heroSelected.second].name, QString::number(userChoice), -1);
        db.close();
        return -1;
    } else {
        // addDatabase(heroList[oppositeHeroSelected.second].name, QString::number(oppositeChoice), -1);
        addDatabase(heroList[heroSelected.second].name, QString::number(userChoice), 1);
        db.close();
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
 * @brief random and change the list. And append the Hero table.
 * @param list
 * @param skills 
 * @param heroSelected 
 * @return 0 - scissors, 1 - rock, 2 - paper
 */
int Game::randomChoose(QVector<int> list, QVector<QVector<int> > &skills, QPair<int, int> heroSelected) {
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
    QVector<int> &heroSkills = skills[heroSelected.first];
    heroSkills[choice]--;

    // Database part
    // initDatabase();
    // Hero hero;
    // auto heroList = hero.showHeroes();
    // addDatabase(heroList[heroSelected.second].name, QString::number(choice), choice);
    //
    // db.close();
    return choice;
}

void Game::initDatabase() {
    const QString connectionName = "UserConnection";

    // 检查是否已经存在该连接
    if (!QSqlDatabase::contains(connectionName)) {
        QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", connectionName);
        db.setDatabaseName("User");

        if (!db.open()) {
            qDebug() << "Failed to open database.";
            return;
        }
    } else {
        qDebug() << "Reusing existing database connection.";
    }

    // 获取现有连接
    QSqlDatabase db = QSqlDatabase::database(connectionName);

    QSqlQuery query(db);


    QString createTableQuery = R"(
        CREATE TABLE IF NOT EXISTS hero (
        id INTEGER PRIMARY KEY AUTOINCREMENT,
        heroName TEXT NOT NULL,
        skill TEXT NOT NULL,
        result INTEGER
        )
    )"; // Hero table is used to calculate the victory rate

    // 执行创建表的 SQL 语句
    if (!query.exec(createTableQuery)) {
        qDebug() << "Failed to create table.";
    } else {
        qDebug() << "Table 'Game' created successfully.";
    }
}

void Game::addDatabase(QString heroName, QString skill, int result) {
    initDatabase();

    QSqlDatabase db = QSqlDatabase::database();
    if (!db.isOpen()) {
        qDebug() << "Database is not open!";
        return;
    }

    QSqlQuery query(db);
    query.prepare("INSERT INTO Hero (heroName, skill, result) VALUES (:heroName, :skill, :result)");

    query.bindValue(":heroName", heroName);
    query.bindValue(":skill", skill);
    query.bindValue(":result", result);

    if (!query.exec()) {
        qDebug() << "Failed to insert into Hero table.";
    } else {
        qDebug() << "Hero added successfully.";
    }
}

// void Game::appendDatabase(QVector<int> selectedHeroes, int heroSelected) {
//     Hero hero;
//     auto heroList = hero.showHeroes();
//
//     int index = 0;
//     for (size_t i : selectedHeroes) {
//         if (i == 0) {
//             addDatabase(heroList[index].name, QString::number(heroSelected));
//         }
//         index++;
//     }
// }

// void Game::appendDatabase(QPair<int, int> heroSelected, QPair<int, int> oppositeHeroSelected, int result) {
//     Hero hero;
//     auto heroList = hero.showHeroes();
//     addDatabase(heroList[oppositeHeroSelected.second].name, QString::number(oppositeChoice), 0);
// }

