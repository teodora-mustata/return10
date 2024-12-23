// MainMenuWidget.cpp
#include "MainMenuWidget.h"
#include "ui_MainMenuWidget.h"
#include <QStackedWidget>
#include <QApplication>

MainMenuWidget::MainMenuWidget(QWidget* parent)
    : QWidget(parent),
    ui(new Ui::MainMenuWidget),
    /*gamePage(new Game()),
    shopPage(new ShopWidget()),
    leaderboardPage(new LeaderboardWidget())*/
    leaderboardPage(new LeaderboardWidget())
{
    ui->setupUi(this);
    this->setWindowTitle("Battle City");
}

MainMenuWidget::~MainMenuWidget()
{
    delete ui;
    /*delete gamePage;
    delete shopPage;
    delete leaderboardPage;*/
    delete leaderboardPage;
}
//
//void MainMenuWidget::on_startGameButton_clicked()
//{
//    gamePage->show();
//    this->close();
//}
//
//void MainMenuWidget::on_shopButton_clicked()
//{
//    shopPage->show();
//    this->close();
//}
//
void MainMenuWidget::on_leaderboardButton_clicked()
{
    leaderboardPage->show();
    this->close();
}

void MainMenuWidget::on_exitButton_clicked()
{
    QApplication::quit();
}
