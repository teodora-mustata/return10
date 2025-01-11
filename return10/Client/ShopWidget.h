////#pragma once
////
////#include <QWidget>
////#include <QPushButton>
////#include <QVBoxLayout>
////#include <QLabel>
////
////class ShopWidget : public QWidget {
////    Q_OBJECT
////
////public:
////    explicit ShopWidget(QWidget* parent = nullptr);
////    ~ShopWidget();
////
////private slots:
////    void on_buyReloadSpeedButton_clicked();
////    void on_buyBulletSpeedButton_clicked();
////    void on_goBackButton_clicked();
////
////private:
////    QPushButton* buyReloadSpeedButton;
////    QPushButton* buyBulletSpeedButton;
////    QPushButton* goBackButton;
////    QLabel* titleLabel;
////    QVBoxLayout* layout;
////
////    void buyReloadSpeedUpgrade();
////    void buyBulletSpeedUpgrade();
////    void setupUI();
////};
//
////
////#pragma once
////
////#include <QWidget>
////#include <QPushButton>
////#include <QVBoxLayout>
////#include <QLabel>
////#include "MainMenuWidget.h" // Include MainMenuWidget header
////
////class ShopWidget : public QWidget {
////    Q_OBJECT
////
////public:
////    explicit ShopWidget(QWidget* parent = nullptr, MainMenuWidget* mainMenu = nullptr);
////    ~ShopWidget();
////
////private slots:
////    void on_buyReloadSpeedButton_clicked();
////    void on_buyBulletSpeedButton_clicked();
////    void on_goBackButton_clicked();
////
////private:
////    QPushButton* buyReloadSpeedButton;
////    QPushButton* buyBulletSpeedButton;
////    QPushButton* goBackButton;
////    QLabel* titleLabel;
////    QVBoxLayout* layout;
////
////    MainMenuWidget* mainMenuWidget; // Pointer to main menu widget
////
////    void buyReloadSpeedUpgrade();
////    void buyBulletSpeedUpgrade();
////    void setupUI();
////};
//
//#pragma once
//
//#include <QWidget>
//#include <QPushButton>
//#include <QVBoxLayout>
//#include <QLabel>
//#include "MainMenuWidget.h" // Include MainMenuWidget header
//
//class ShopWidget : public QWidget {
//    Q_OBJECT
//
//public:
//    explicit ShopWidget(QWidget* parent = nullptr, MainMenuWidget* mainMenu = nullptr);
//    ~ShopWidget();
//
//private slots:
//    void on_buyReloadSpeedButton_clicked();
//    void on_buyBulletSpeedButton_clicked();
//    void on_goBackButton_clicked();
//
//private:
//    QPushButton* buyReloadSpeedButton;
//    QPushButton* buyBulletSpeedButton;
//    QPushButton* goBackButton;
//    QLabel* titleLabel;
//    QVBoxLayout* layout;
//
//    MainMenuWidget* mainMenuWidget; // Pointer to main menu widget
//
//    void buyReloadSpeedUpgrade();
//    void buyBulletSpeedUpgrade();
//    void setupUI();
//};

//#pragma once
//
//#include <QWidget>
//#include <QPushButton>
//#include <QVBoxLayout>
//#include <QLabel>
//#include "MainMenuWidget.h" // Include MainMenuWidget header
//#include "UserSession.h"
//class ShopWidget : public QWidget {
//    Q_OBJECT
//
//public:
//    explicit ShopWidget(QWidget* parent = nullptr, MainMenuWidget* mainMenu = nullptr);
//    ~ShopWidget();
//
//private slots:
//    void on_buyReloadSpeedButton_clicked();
//    void on_buyBulletSpeedButton_clicked();
//    void on_goBackButton_clicked();
//
//private:
//    QPushButton* buyReloadSpeedButton;
//    QPushButton* buyBulletSpeedButton;
//    QPushButton* goBackButton;
//    QLabel* titleLabel;
//    QVBoxLayout* layout;
//
//    MainMenuWidget* mainMenuWidget; // Pointer to main menu widget
//
//    void buyReloadSpeedUpgrade();
//    void buyBulletSpeedUpgrade();
//    void setupUI();
//};

#pragma once

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include "MainMenuWidget.h" // Include MainMenuWidget header
#include "UserSession.h"

class ShopWidget : public QWidget {
    Q_OBJECT

public:
    explicit ShopWidget(QWidget* parent = nullptr, MainMenuWidget* mainMenu = nullptr);
    ~ShopWidget();

private slots:
    void on_buyReloadSpeedButton_clicked();
    void on_buyBulletSpeedButton_clicked();
    void on_goBackButton_clicked();

private:
    QPushButton* buyReloadSpeedButton;
    QPushButton* buyBulletSpeedButton;
    QPushButton* goBackButton;
    QLabel* titleLabel;
    QVBoxLayout* layout;

    MainMenuWidget* mainMenuWidget; // Pointer to main menu widget

    void buyReloadSpeedUpgrade();
    void buyBulletSpeedUpgrade();
    void setupUI();
};