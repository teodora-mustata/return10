#pragma once

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include <QStackedWidget>
#include <crow/json.h>
#include <cpr/cpr.h>
#include <QMessageBox>

class StartGameWidget;
class MainMenuWidget;

class ChooseGameDificulty : public QWidget {
    Q_OBJECT

public:
    explicit ChooseGameDificulty(QWidget* parent = nullptr, MainMenuWidget* mainMenu = nullptr);
    ~ChooseGameDificulty();
    QStackedWidget* stackedWidget;
    bool createGame();

signals:
    void readyToPlay(); // Signal to notify when ready to play

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

    MainMenuWidget* mainMenuWidget;
    StartGameWidget* startGameWidgetPage;
    int selectedDifficulty;

    bool sendDifficultyToServer(int difficulty);
    void setupUI();
};
