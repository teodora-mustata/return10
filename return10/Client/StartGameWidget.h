#pragma once

#include <QMainWindow>
#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include <QStackedWidget>
#include<iostream>
#include <crow/json.h>
#include <cpr/cpr.h>
#include<QMessageBox>
class MainMenuWidget;

class StartGameWidget : public QWidget
{
	Q_OBJECT

public:
	StartGameWidget(QWidget* parent = nullptr, MainMenuWidget* mainMenu = nullptr);
	~StartGameWidget();

private slots:

    void on_easyModeButton_clicked();
    void on_mediumModeButton_clicked();
    void on_hardModeButton_clicked();
    void on_readyToPlayButton_clicked();
    void on_goBackButton_clicked();

private:

    QStackedWidget* stackedWidget; // Widget pentru gestionarea mai multor pagini
    QWidget* chooseGameDificulty; // Pagina cu dificultăți
  

    QPushButton* easyModeButton;
    QPushButton* mediumModeButton;
    QPushButton* hardModeButton;
    QPushButton* goBackButton;
    QPushButton* readyToPlayButton;

    QLabel* titleLabel;
    QVBoxLayout* layout;

    MainMenuWidget* mainMenuWidget; // Pointer to main menu widget

    int selectedDifficulty;
    bool sendDifficultyToServer(int difficulty);
  
    void startServerGame();


    void setupUI();
};
