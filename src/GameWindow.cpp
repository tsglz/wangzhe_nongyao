#include "GameWindow.h"
#include "ui_GameWindow.h"
#include "PrepareWindow.h"

GameWindow::GameWindow(const QString &username, QVector<QVector<int> > *oppositeSkillsPtr, QVector<QVector<int> > *selectedSkillsPtr, QWidget *parent)
    : QDialog(parent)
      , ui(new Ui::GameWindow)
      , gameViewModel(new QStandardItemModel)
      , prepareWindow(nullptr)
      , username(username)
      , selectedHeroes(15, 0)
      , oppositeSkills(oppositeSkillsPtr)
      , selectedSkills(selectedSkillsPtr)
      , round(0), win(0), lose(0), draw(0)
      , timer(new QTimer)
{
    ui->setupUi(this);
    ui->gameView->setModel(gameViewModel);

    Hero hero;
    QVector<Hero::Attributes> heroList = hero.showHeroes();

    for (size_t i = 0; i < heroList.size(); ++i) {
        printOnGameView(
            QString::number(i) + ". " + heroList[i].name + " Scissors: " + QString::number(heroList[i].scissors) +
            " Rock::" + QString::number(heroList[i].rock) + " Paper: " + QString::number(heroList[i].paper));
    }
    printOnGameView(""); // Add an empty line

    connect(timer, &QTimer::timeout, this, &GameWindow::onTimeout);
}

GameWindow::~GameWindow() {
    delete ui;
}

void GameWindow::on_comfirm_clicked() // Button to select heroes
{
    if (selectedHeroCount >= 3) {
        printOnGameView("You have already selected three heroes.");
        return;
    }

    QLineEdit *input = ui->input;
    QString inputText = input->text();
    bool ok;
    int heroIndex = inputText.toInt(&ok);

    if (!ok) {
        // TODO
    } else if (inputText.isEmpty()) {
        // TODO
    } else if (heroIndex < 0 || heroIndex > 14) {
        // TODO
    } else if (selectedHeroes[heroIndex] == 1) {
        //TODO
    } else {
        selectedHeroes[heroIndex] = 1; // Mark hero as selected
        selectedHeroCount++;
        qDebug() << "Hero selected: " << heroIndex;
        printOnGameView(QString("Hero %1 selected.").arg(heroIndex));
    }

    if (selectedHeroCount == 3) {
        Hero hero;
        auto heroList = hero.showHeroes();
        printOnGameView("You have selected all three heroes.");
        qDebug() << "selected heroes: " << selectedHeroes;
        qDebug() << "selected heroes: " << oppositeRandomSelectedHeroes;

        for(size_t i = 0; i < selectedHeroes.size(); i++) {
            if (selectedHeroes[i] == 1) {
                selectedSkills->append({heroList[i].scissors, heroList[i].rock, heroList[i].paper});
            }
            if (oppositeRandomSelectedHeroes[i] == 1) {
                oppositeSkills->append({heroList[i].scissors, heroList[i].rock, heroList[i].paper});
            }
        }
        qDebug() << "Selected skills: " << *selectedSkills;
        qDebug() << "Opposite skills: " << *oppositeSkills;

        int index = 0;
        for(size_t i : selectedHeroes) {
            if (i == 1) {
                printOnGameView("You selected hero: " + QString::number(index));
            }
            index++;
        }
        timer->start(5000);
    }

    input->clear();

    for (int i = 0; i < selectedHeroes.size(); i++) {
        if (selectedHeroes[i] == 1) {
            qDebug() << "Selected hero index: " << i;
        }
    }
}


void GameWindow::on_return_2_clicked() {
    prepareWindow = new PrepareWindow(username);
    prepareWindow->show();

    this->hide();
}

void GameWindow::printOnGameView(QString content) {
    auto item = new QStandardItem(content);
    gameViewModel->appendRow(item);
    auto rowCount = gameViewModel->rowCount();
    if (rowCount > 0) {
        QModelIndex lastIndex = gameViewModel->index(rowCount - 1, 0);

        // 确保滚动到最后一行
        ui->gameView->scrollTo(lastIndex, QAbstractItemView::PositionAtBottom);
    }
}

void GameWindow::on_hero_0_clicked() // button 0
{
    playGame({0, getIndexOfHero(selectedHeroes, 0)});
}


void GameWindow::on_hero_1_clicked()
{
    playGame({1, getIndexOfHero(selectedHeroes, 1)});
}

void GameWindow::on_hero_2_clicked()
{
    playGame({2, getIndexOfHero(selectedHeroes, 2)});
}

void GameWindow::playGame(QPair<int, int> heroSelected) {
    timer->start(5000);
    if (selectedHeroCount < 3) {
        printOnGameView("You have not selected three heroes.");
        return;
    }

    qDebug() << "Hero" << heroSelected.first << "selected";
    Game game;

    if (round < 9) {
        auto userPrev = *selectedSkills;
        auto oppositePrev = *oppositeSkills;

        qDebug() << "Selected skills: " << *selectedSkills;
        qDebug() << "Opposite skills: " << *oppositeSkills;

        int result = game.hasGame(username, *oppositeSkills, *selectedSkills, round, heroSelected, {0, 0});

        auto userAfter = *selectedSkills;
        auto oppositeAfter = *oppositeSkills;

        showResult(userPrev, oppositePrev, userAfter, oppositeAfter, result);

        qDebug() << "Round: " << round;
        qDebug() << "Selected skills: " << *selectedSkills;
        qDebug() << "Opposite skills: " << *oppositeSkills;

    } else {
        printOnGameView("");
        printOnGameView("Game over!");
        printOnGameView("You win: " + QString::number(win));
        printOnGameView("You draw: " + QString::number(draw));
        printOnGameView("You lose: " + QString::number(lose));
        timer->stop();
    }
}

/**
 *
 * @param selectedHeroes
 * @param heroSelectedIndex 0 1 2
 * @return
 */
int GameWindow::getIndexOfHero(QVector<int> selectedHeroes, int heroSelectedIndex) {
    int index = 0, acount = 0;
    for (size_t i : selectedHeroes) {
        if (i == 1) {
            if(heroSelectedIndex == acount) {
                return index;
            }
            acount++;
        }
        index++;
    }
}

void GameWindow::onTimeout() {
    timer->start(5000);

    std::random_device rd;
    std::mt19937 eng(rd());
    std::uniform_int_distribution distr(0, 2);

    int randomIndex = distr(eng);

    switch (randomIndex) {
        case 0:
            on_hero_0_clicked();
        break;
        case 1:
            on_hero_1_clicked();
        break;
        case 2:
            on_hero_2_clicked();
        break;
    }
}


void GameWindow::showResult(QVector<QVector<int> > userPrev, QVector<QVector<int> > oppositePrev, QVector<QVector<int> > userAfter, QVector<QVector<int> > oppositeAfter, int result) {
    QPair<int, int> userDiffer = differ(userPrev, userAfter);
    QPair<int, int> oppositeDiffer = differ(oppositePrev, oppositeAfter);

    QVector<QString> skills = {"Scissors", "Rock", "Paper"};

    printOnGameView("Round: " + QString::number(round));

    printOnGameView("You selected: " + QString::number(userDiffer.first) + ". And used : " + skills[userDiffer.second]);
    printOnGameView("Computer selected: " + QString::number(oppositeDiffer.first) + ". And used : " + skills[oppositeDiffer.second]);

    qDebug() << "SelectedSkill: " << selectedSkills[0][0][1];

    printOnGameView("You first hero has: " + QString::number(selectedSkills[0][0][0]) + skills[0] + QString::number(selectedSkills[0][0][1]) + skills[1] + QString::number(selectedSkills[0][0][2]) + skills[2]);
    printOnGameView("You second hero has: " + QString::number(selectedSkills[0][1][0]) + skills[0] + QString::number(selectedSkills[0][1][2]) + skills[1] + QString::number(selectedSkills[0][1][2]) + skills[2]);
    printOnGameView("You third hero has: " + QString::number(selectedSkills[0][2][0]) + skills[0] + QString::number(selectedSkills[0][2][1]) + skills[1] + QString::number(selectedSkills[0][2][2]) + skills[2]);

    if (result == 1) {
        printOnGameView("You win!");
        round++; win++;
    } else if (result == 0) {
        printOnGameView("Draw!");
        round++; draw++;
    } else if (result == -1) {
        printOnGameView("You lose!");
        round++; lose++;
    } else if (result == -10) {
        printOnGameView("You have no skills left.");
    }
    printOnGameView("");
}

QPair<int, int> GameWindow::differ(QVector<QVector<int> > prev, QVector<QVector<int> > after) {
    if (prev.size() != after.size()) {
        return QPair<int, int>(-1, -1);
    }

    for (int i = 0; i < prev.size(); ++i) {
        const QVector<int>& prevVec = prev[i];
        const QVector<int>& afterVec = after[i];

        // Check if inner QVector sizes are equal
        if (prevVec.size() != afterVec.size()) {
            return QPair<int, int>(-1, -1); // Return invalid pair if sizes differ
        }

        // Compare elements in the inner QVectors
        for (int j = 0; j < prevVec.size(); ++j) {
            if (prevVec[j] != afterVec[j]) {
                return QPair<int, int>(i, j); // Return the indices of the first difference found
            }
        }
    }
}


