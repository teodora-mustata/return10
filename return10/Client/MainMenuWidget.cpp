#include "MainMenuWidget.h"
#include <QApplication>

MainMenuWidget::MainMenuWidget(QWidget* parent)
    : QWidget(parent) {
    setupUI();
    this->setWindowTitle("Battle City");
}

MainMenuWidget::~MainMenuWidget() {
    // Destructor logic if needed
}

void MainMenuWidget::setupUI() {
    stackedWidget = new QStackedWidget(this);

    // Set up main menu layout
    QWidget* mainMenuWidget = new QWidget(this);
    QVBoxLayout* mainMenuLayout = new QVBoxLayout(mainMenuWidget);

    titleLabel = new QLabel("Battle City", this);
    titleLabel->setAlignment(Qt::AlignCenter);
    mainMenuLayout->addWidget(titleLabel);

    startGameButton = new QPushButton("Start Game", this);
    mainMenuLayout->addWidget(startGameButton);
    connect(startGameButton, &QPushButton::clicked, this, &MainMenuWidget::on_startGameButton_clicked);

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

    // Create instances of ShopWidget and LeaderboardWidget and add them to the stacked widget
    shopPage = new ShopWidget(nullptr, this);
    leaderboardPage = new LeaderboardWidget(nullptr, this);

    stackedWidget->addWidget(shopPage);
    stackedWidget->addWidget(leaderboardPage);

    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(stackedWidget);
    setLayout(mainLayout);
}

void MainMenuWidget::on_startGameButton_clicked() {
    // Start game logic here
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

////// MainMenuWidget.cpp
////#include "MainMenuWidget.h"
//////#include "ui_MainMenuWidget.h
////#include <QStackedWidget>
////#include <QApplication>
////
////MainMenuWidget::MainMenuWidget(QWidget* parent)
////    : QWidget(parent),
////    ui(new Ui::MainMenuWidget),
////    //gamePage(new Game()),
////    /*shopPage(new ShopWidget()),
////    leaderboardPage(new LeaderboardWidget())*/
////    leaderboardPage(new LeaderboardWidget())
////{
////    ui->setupUi(this);
////    this->setWindowTitle("Battle City");
////}
////
////MainMenuWidget::~MainMenuWidget()
////{
////    delete ui;
////    //delete gamePage;
////    /*delete shopPage;
////    delete leaderboardPage;*/
////    delete leaderboardPage;
////}
//////
//////void MainMenuWidget::on_startGameButton_clicked()
//////{
//////    gamePage->show();
//////    this->close();
//////}
//////
//////void MainMenuWidget::on_shopButton_clicked()
//////{
//////    shopPage->show();
//////    this->close();
//////}
//////
////void MainMenuWidget::on_leaderboardButton_clicked()
////{
////    leaderboardPage->show();
////    this->close();
////}
////
////void MainMenuWidget::on_exitButton_clicked()
////{
////    QApplication::quit();
////}
//
//#include "MainMenuWidget.h"
//#include <QApplication>
//#include <QVBoxLayout>
//#include <QLabel>
//#include <QPushButton>
//
//MainMenuWidget::MainMenuWidget(QWidget* parent)
//    : QWidget(parent),
//    //gamePage(new Game()),
//    shopPage(new ShopWidget()),
//    leaderboardPage(new LeaderboardWidget())
//{
//    setupUI();
//    this->setWindowTitle("Battle City");
//}
//
//MainMenuWidget::~MainMenuWidget()
//{
//    //delete gamePage;
//    delete shopPage;
//    delete leaderboardPage;
//}
//
//void MainMenuWidget::setupUI()
//{
//    layout = new QVBoxLayout(this);
//
//    titleLabel = new QLabel("Battle City", this);
//    titleLabel->setAlignment(Qt::AlignCenter);
//    layout->addWidget(titleLabel);
//
//    startGameButton = new QPushButton("Start Game", this);
//    layout->addWidget(startGameButton);
//    connect(startGameButton, &QPushButton::clicked, this, &MainMenuWidget::on_startGameButton_clicked);
//
//    shopButton = new QPushButton("Shop", this);
//    layout->addWidget(shopButton);
//    connect(shopButton, &QPushButton::clicked, this, &MainMenuWidget::on_shopButton_clicked);
//
//    leaderboardButton = new QPushButton("Leaderboard", this);
//    layout->addWidget(leaderboardButton);
//    connect(leaderboardButton, &QPushButton::clicked, this, &MainMenuWidget::on_leaderboardButton_clicked);
//
//    exitButton = new QPushButton("Exit", this);
//    layout->addWidget(exitButton);
//    connect(exitButton, &QPushButton::clicked, this, &MainMenuWidget::on_exitButton_clicked);
//}
//
//void MainMenuWidget::on_startGameButton_clicked()
//{
//    //gamePage->show();
//    this->close();
//}
//
//void MainMenuWidget::on_shopButton_clicked()
//{
//    shopPage->show();
//    this->close();
//}
//
//void MainMenuWidget::on_leaderboardButton_clicked()
//{
//    leaderboardPage->show();
//    this->close();
//}
//
//void MainMenuWidget::on_exitButton_clicked()
//{
//    QApplication::quit();
//}


//#include "MainMenuWidget.h"
//#include <QApplication>
//
//MainMenuWidget::MainMenuWidget(QWidget* parent)
//    : QWidget(parent),
//    shopPage(new ShopWidget(nullptr, this)),
//    leaderboardPage(new LeaderboardWidget(nullptr, this)) {
//    setupUI();
//    this->setWindowTitle("Battle City");
//}
//
//MainMenuWidget::~MainMenuWidget() {
//    delete shopPage;
//    delete leaderboardPage;
//}
//
//void MainMenuWidget::setupUI() {
//    layout = new QVBoxLayout(this);
//
//    titleLabel = new QLabel("Battle City", this);
//    titleLabel->setAlignment(Qt::AlignCenter);
//    layout->addWidget(titleLabel);
//
//    startGameButton = new QPushButton("Start Game", this);
//    layout->addWidget(startGameButton);
//    connect(startGameButton, &QPushButton::clicked, this, &MainMenuWidget::on_startGameButton_clicked);
//
//    shopButton = new QPushButton("Shop", this);
//    layout->addWidget(shopButton);
//    connect(shopButton, &QPushButton::clicked, this, &MainMenuWidget::on_shopButton_clicked);
//
//    leaderboardButton = new QPushButton("Leaderboard", this);
//    layout->addWidget(leaderboardButton);
//    connect(leaderboardButton, &QPushButton::clicked, this, &MainMenuWidget::on_leaderboardButton_clicked);
//
//    exitButton = new QPushButton("Exit", this);
//    layout->addWidget(exitButton);
//    connect(exitButton, &QPushButton::clicked, this, &MainMenuWidget::on_exitButton_clicked);
//
//    stackedWidget = new QStackedWidget(this);
//    stackedWidget->addWidget(this);
//    stackedWidget->addWidget(shopPage);
//    stackedWidget->addWidget(leaderboardPage);
//
//    layout->addWidget(stackedWidget);
//}
//
//void MainMenuWidget::on_startGameButton_clicked() {
//    // Start game logic here
//}
//
//void MainMenuWidget::on_shopButton_clicked() {
//    stackedWidget->setCurrentWidget(shopPage);
//}
//
//void MainMenuWidget::on_leaderboardButton_clicked() {
//    stackedWidget->setCurrentWidget(leaderboardPage);
//}
//
//void MainMenuWidget::on_exitButton_clicked() {
//    QApplication::quit();
//}


//#include "MainMenuWidget.h"
//#include <QApplication>
//
//MainMenuWidget::MainMenuWidget(QWidget* parent)
//    : QWidget(parent) {
//    setupUI();
//    this->setWindowTitle("Battle City");
//}
//
//MainMenuWidget::~MainMenuWidget() {
//    // Destructor logic if needed
//}
//
//void MainMenuWidget::setupUI() {
//    stackedWidget = new QStackedWidget(this);
//
//    // Set up main menu layout
//    QWidget* mainMenuWidget = new QWidget(this);
//    QVBoxLayout* mainMenuLayout = new QVBoxLayout(mainMenuWidget);
//
//    titleLabel = new QLabel("Battle City", this);
//    titleLabel->setAlignment(Qt::AlignCenter);
//    mainMenuLayout->addWidget(titleLabel);
//
//    startGameButton = new QPushButton("Start Game", this);
//    mainMenuLayout->addWidget(startGameButton);
//    connect(startGameButton, &QPushButton::clicked, this, &MainMenuWidget::on_startGameButton_clicked);
//
//    shopButton = new QPushButton("Shop", this);
//    mainMenuLayout->addWidget(shopButton);
//    connect(shopButton, &QPushButton::clicked, this, &MainMenuWidget::on_shopButton_clicked);
//
//    leaderboardButton = new QPushButton("Leaderboard", this);
//    mainMenuLayout->addWidget(leaderboardButton);
//    connect(leaderboardButton, &QPushButton::clicked, this, &MainMenuWidget::on_leaderboardButton_clicked);
//
//    exitButton = new QPushButton("Exit", this);
//    mainMenuLayout->addWidget(exitButton);
//    connect(exitButton, &QPushButton::clicked, this, &MainMenuWidget::on_exitButton_clicked);
//
//    mainMenuWidget->setLayout(mainMenuLayout);
//    stackedWidget->addWidget(mainMenuWidget);
//
//    // Create instances of ShopWidget and LeaderboardWidget and add them to the stacked widget
//    shopPage = new ShopWidget(nullptr, this);
//    leaderboardPage = new LeaderboardWidget(nullptr, this);
//
//    stackedWidget->addWidget(shopPage);
//    stackedWidget->addWidget(leaderboardPage);
//
//    QVBoxLayout* mainLayout = new QVBoxLayout(this);
//    mainLayout->addWidget(stackedWidget);
//    setLayout(mainLayout);
//}
//
//void MainMenuWidget::on_startGameButton_clicked() {
//    // Start game logic here
//}
//
//void MainMenuWidget::on_shopButton_clicked() {
//    stackedWidget->setCurrentWidget(shopPage);
//}
//
//void MainMenuWidget::on_leaderboardButton_clicked() {
//    stackedWidget->setCurrentWidget(leaderboardPage);
//}
//
//void MainMenuWidget::on_exitButton_clicked() {
//    QApplication::quit();
//}

