﻿#pragma once

#include <QMainWindow>
#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include <QStackedWidget>
#include <iostream>
#include <crow/json.h>
#include <cpr/cpr.h>
#include <QMessageBox>

class StartGameWidget;
class MainMenuWidget;

class ChooseGameDificulty : public QWidget
{
    Q_OBJECT

public:
    ChooseGameDificulty(QWidget* parent = nullptr, MainMenuWidget* mainMenu = nullptr);
    ~ChooseGameDificulty();
    QStackedWidget* stackedWidget;


private slots: // Adăugat pentru a marca slot-urile
    void on_easyModeButton_clicked();
    void on_mediumModeButton_clicked();
    void on_hardModeButton_clicked();
    void on_goBackButton_clicked();

private:
   // QStackedWidget* stackedWidget; // Widget pentru gestionarea mai multor pagini
   

    QLabel* titleLabel;
    QVBoxLayout* layout;

    QPushButton* easyModeButton;
    QPushButton* mediumModeButton;
    QPushButton* hardModeButton;
    QPushButton* goBackButton;

    MainMenuWidget* mainMenuWidget; // Pointer to main menu widget
    StartGameWidget* startGameWidgetPage;
    int selectedDifficulty;
    bool sendDifficultyToServer(int difficulty);
    void setupUI();
};
