#include "MainMenuWidget.h"
#include "ShopWidget.h"
#include "LeaderboardWidget.h"
#include "ChooseGameDificulty.h"
#include "StartGameWidget.h"
#include <QApplication>
#include <QMessageBox>

MainMenuWidget::MainMenuWidget(QWidget* parent)
    : QWidget(parent), startGameWidget(nullptr) {
    setupUI();
    this->setWindowTitle("Battle City");
}

MainMenuWidget::~MainMenuWidget() {
    delete startGameWidget;
}

void MainMenuWidget::setupUI() {
    stackedWidget = new QStackedWidget(this);

    // Set up main menu layout
    QWidget* mainMenuWidget = new QWidget(this);
    QVBoxLayout* mainMenuLayout = new QVBoxLayout(mainMenuWidget);

    titleLabel = new QLabel("Battle City", this);
    titleLabel->setAlignment(Qt::AlignCenter);
    mainMenuLayout->addWidget(titleLabel);

    chooseGameDificultyButton = new QPushButton("Start Game", this);
    mainMenuLayout->addWidget(chooseGameDificultyButton);
    connect(chooseGameDificultyButton, &QPushButton::clicked, this, &MainMenuWidget::on_chooseGameDificultyButton_clicked);

    shopButton = new QPushButton("Shop", this);
    mainMenuLayout->addWidget(shopButton);
    connect(shopButton, &QPushButton::clicked, this, &MainMenuWidget::on_shopButton_clicked);

    leaderboardButton = new QPushButton("Leaderboard", this);
    mainMenuLayout->addWidget(leaderboardButton);
    connect(leaderboardButton, &QPushButton::clicked, this, &MainMenuWidget::on_leaderboardButton_clicked);

    exitButton = new QPushButton("Exit", this);
    mainMenuLayout->addWidget(exitButton);
    connect(exitButton, &QPushButton::clicked, this, &MainMenuWidget::on_exitButton_clicked);

    mainMenuWidget->setLayout(mainMenuLayout);
    stackedWidget->addWidget(mainMenuWidget);

    chooseGameDificultyPage = new ChooseGameDificulty(nullptr, this);
    shopPage = new ShopWidget(nullptr, this);
    leaderboardPage = new LeaderboardWidget(nullptr, this);

    stackedWidget->addWidget(chooseGameDificultyPage);
    stackedWidget->addWidget(shopPage);
    stackedWidget->addWidget(leaderboardPage);

    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(stackedWidget);
    setLayout(mainLayout);
}

void MainMenuWidget::on_chooseGameDificultyButton_clicked() {
    if (chooseGameDificultyPage->createGame()) {
        stackedWidget->setCurrentWidget(chooseGameDificultyPage);
        connect(chooseGameDificultyPage, &ChooseGameDificulty::readyToPlay, this, [=]() {
            if (!startGameWidget) {
                startGameWidget = new StartGameWidget(this, chooseGameDificultyPage);
                stackedWidget->addWidget(startGameWidget);
            }
            stackedWidget->setCurrentWidget(startGameWidget);
            startGameWidget->startGame();
            });
    }
    else {
        QMessageBox::critical(this, "Error", "Failed to create the game. Please try again.");
    }
}

void MainMenuWidget::on_shopButton_clicked() {
    stackedWidget->setCurrentWidget(shopPage);
}

void MainMenuWidget::on_leaderboardButton_clicked() {
    stackedWidget->setCurrentWidget(leaderboardPage);
}

void MainMenuWidget::on_exitButton_clicked() {
    QApplication::quit();
}

void MainMenuWidget::showMainMenu() {
    stackedWidget->setCurrentIndex(0);
}
