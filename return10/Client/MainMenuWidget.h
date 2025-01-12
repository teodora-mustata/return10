#pragma once

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include <QStackedWidget>

// Forward declarations
class ShopWidget;
class LeaderboardWidget;

class MainMenuWidget : public QWidget {
    Q_OBJECT

public:
    explicit MainMenuWidget(QWidget* parent = nullptr);
    ~MainMenuWidget();
    QStackedWidget* stackedWidget;

private slots:
    void on_startGameButton_clicked();
    void on_shopButton_clicked();
    void on_leaderboardButton_clicked();
    void on_exitButton_clicked();
    void showMainMenu();

private:
    QPushButton* startGameButton;
    QPushButton* shopButton;
    QPushButton* leaderboardButton;
    QPushButton* exitButton;
    QLabel* titleLabel;
    QVBoxLayout* layout;

    ShopWidget* shopPage;
    LeaderboardWidget* leaderboardPage;

    void setupUI();
};

//#pragma once
//
//#include <QWidget>
//#include <QPushButton>
//#include <QVBoxLayout>
//#include <QLabel>
//#include <QStackedWidget>
//#include "ShopWidget.h"
//#include "LeaderboardWidget.h"
//#include "UserSession.h"
//
//class MainMenuWidget : public QWidget {
//    Q_OBJECT
//
//public:
//    explicit MainMenuWidget(QWidget* parent = nullptr);
//    ~MainMenuWidget();
//    QStackedWidget* stackedWidget;
//
//private slots:
//    void on_startGameButton_clicked();
//    void on_shopButton_clicked();
//    void on_leaderboardButton_clicked();
//    void on_exitButton_clicked();
//    void showMainMenu();
//
//private:
//    QPushButton* startGameButton;
//    QPushButton* shopButton;
//    QPushButton* leaderboardButton;
//    QPushButton* exitButton;
//    QLabel* titleLabel;
//    QVBoxLayout* layout;
//
//    ShopWidget* shopPage;
//    LeaderboardWidget* leaderboardPage;
//
//    void setupUI();
//};
//
//#include <QWidget>
////#include "Game.h"
////#include "ShopWidget.h"
//#include "LeaderboardWidget.h"
//#include "LeaderboardWidget.h"
//
//namespace Ui {
//    class MainMenuWidget;
//}
//
//class MainMenuWidget : public QWidget
//{
//    Q_OBJECT
//
//public:
//    explicit MainMenuWidget(QWidget* parent = nullptr);
//    ~MainMenuWidget();
//
//private slots:
//    //void on_startGameButton_clicked();
//    /*void on_shopButton_clicked();
//    void on_leaderboardButton_clicked();*/
//    void on_leaderboardButton_clicked(); 
//    void on_exitButton_clicked();
//
//private:
//    Ui::MainMenuWidget* ui;
//    //Game* gamePage;
//    //ShopWidget* shopPage;
//    LeaderboardWidget* leaderboardPage;
//};
//
//#pragma once
//
//#include <QWidget>
//#include "LeaderboardWidget.h"
//#include "ShopWidget.h"
//
//class MainMenuWidget : public QWidget
//{
//    Q_OBJECT
//
//public:
//    explicit MainMenuWidget(QWidget* parent = nullptr);
//    ~MainMenuWidget();
//
//private slots:
//    void on_startGameButton_clicked();
//    void on_shopButton_clicked();
//    void on_leaderboardButton_clicked();
//    void on_exitButton_clicked();
//
//private:
//    QPushButton* startGameButton;
//    QPushButton* shopButton;
//    QPushButton* leaderboardButton;
//    QPushButton* exitButton;
//    QLabel* titleLabel;
//    QVBoxLayout* layout;
//
//    //Game* gamePage;
//    ShopWidget* shopPage;
//    LeaderboardWidget* leaderboardPage;
//
//    void setupUI();
//};
//
//#pragma once
//
//#include <QWidget>
//#include <QPushButton>
//#include <QVBoxLayout>
//#include <QLabel>
//#include <QStackedWidget>
//#include "ShopWidget.h"
//#include "LeaderboardWidget.h"
//
//class MainMenuWidget : public QWidget {
//    Q_OBJECT
//
//public:
//    explicit MainMenuWidget(QWidget* parent = nullptr);
//    ~MainMenuWidget();
//
//private slots:
//    void on_startGameButton_clicked();
//    void on_shopButton_clicked();
//    void on_leaderboardButton_clicked();
//    void on_exitButton_clicked();
//
//private:
//    QPushButton* startGameButton;
//    QPushButton* shopButton;
//    QPushButton* leaderboardButton;
//    QPushButton* exitButton;
//    QLabel* titleLabel;
//    QVBoxLayout* layout;
//
//    QStackedWidget* stackedWidget;
//    ShopWidget* shopPage;
//    LeaderboardWidget* leaderboardPage;
//
//    void setupUI();
//};
//
//#pragma once
//
//#include <QWidget>
//#include <QPushButton>
//#include <QVBoxLayout>
//#include <QLabel>
//#include <QStackedWidget>
//#include "ShopWidget.h"
//#include "LeaderboardWidget.h"
//#include "UserSession.h"
//
//class MainMenuWidget : public QWidget {
//    Q_OBJECT
//
//public:
//    explicit MainMenuWidget(QWidget* parent = nullptr);
//    ~MainMenuWidget();
//    QStackedWidget* stackedWidget;
//private slots:
//    void on_startGameButton_clicked();
//    void on_shopButton_clicked();
//    void on_leaderboardButton_clicked();
//    void on_exitButton_clicked();
//
//private:
//    QPushButton* startGameButton;
//    QPushButton* shopButton;
//    QPushButton* leaderboardButton;
//    QPushButton* exitButton;
//    QLabel* titleLabel;
//    QVBoxLayout* layout;
//
//    
//    ShopWidget* shopPage;
//    LeaderboardWidget* leaderboardPage;
//
//    void setupUI();
//};


