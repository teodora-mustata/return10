#pragma once

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include <QStackedWidget>
#include <crow/json.h>
#include <cpr/cpr.h>
#include <QMessageBox>
#include <QTimer>
#include <thread>
#include <chrono>
#include <iostream>

//class StartGameWidget;
class MainMenuWidget;

class ChooseGameDificulty : public QWidget {
    Q_OBJECT

public:
    explicit ChooseGameDificulty(QWidget* parent = nullptr, MainMenuWidget* mainMenu = nullptr);
    ~ChooseGameDificulty();

    void createGame();
    void checkCurrentDifficulty();
    bool sendDifficultyToServer(int difficulty);

private slots:
    void on_easyModeButton_clicked();
    void on_mediumModeButton_clicked();
    void on_hardModeButton_clicked();
    void on_goBackButton_clicked();
    void on_readyToPlayButton_clicked();

private:
    QLabel* titleLabel;
    QVBoxLayout* layout;
    QPushButton* easyModeButton;
    QPushButton* mediumModeButton;
    QPushButton* hardModeButton;
    QPushButton* goBackButton;
    QPushButton* readyToPlayButton;
    QStackedWidget* stackedWidget;

    MainMenuWidget* mainMenuWidget;
    //StartGameWidget* startGameWidgetPage;
    int selectedDifficulty;

    void setupUI();
};
