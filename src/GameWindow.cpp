#include "GameWindow.h"
#include "ui_GameWindow.h"
#include "PrepareWindow.h"

GameWindow::GameWindow(const QString &username, QVector<QVector<int> > *oppositeSkillsPtr, QVector<QVector<int> > *selectedSkillsPtr, QWidget *parent)
    : QDialog(parent)
      , ui(new Ui::GameWindow)
      , gameViewModel(new QStandardItemModel)
      , prepareWindow(nullptr)
      , username(username)
      , hero()
      , selectedHeroes(15, 0)
      , oppositeSkills(oppositeSkillsPtr)
      , selectedSkills(selectedSkillsPtr)
      , round(0), win(0), lose(0), draw(0)
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
        qDebug() << "Selected skills: " << selectedSkills;
        qDebug() << "Opposite skills: " << oppositeSkills;
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
    playGame(0);
}


void GameWindow::on_hero_1_clicked()
{
    playGame(1);
}

void GameWindow::on_hero_2_clicked()
{
    playGame(2);
}

void GameWindow::playGame(int heroSelected) {
    if (selectedHeroCount < 3) {
        printOnGameView("You have not selected three heroes.");
        return;
    }

    qDebug() << "Hero" << heroSelected << "selected";
    Game game;

    if (round < 9) {
        qDebug() << "Selected skills: " << *selectedSkills;
        qDebug() << "Opposite skills: " << *oppositeSkills;

        int result = game.hasGame(username, *oppositeSkills, *selectedSkills, round, heroSelected);

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
            printOnGameView("There is no skills. Please select another hero.");
        }
        qDebug() << "Round: " << round;
        qDebug() << "Selected skills: " << *selectedSkills;
        qDebug() << "Opposite skills: " << *oppositeSkills;
    }
}