#pragma once

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include <QStackedWidget>

// Forward declarations
class ChooseGameDificulty;
class ShopWidget;
class LeaderboardWidget;
class StartGameWidget;

class MainMenuWidget : public QWidget {
    Q_OBJECT

public:
    explicit MainMenuWidget(QWidget* parent = nullptr);
    ~MainMenuWidget();
    QStackedWidget* stackedWidget;

private slots:
    void on_chooseGameDificultyButton_clicked();
    void on_shopButton_clicked();
    void on_leaderboardButton_clicked();
    void on_exitButton_clicked();
    void showMainMenu();

private:
    QPushButton* chooseGameDificultyButton;
    QPushButton* shopButton;
    QPushButton* leaderboardButton;
    QPushButton* exitButton;
    QLabel* titleLabel;
    QVBoxLayout* layout;

    ChooseGameDificulty* chooseGameDificultyPage;
    ShopWidget* shopPage;
    LeaderboardWidget* leaderboardPage;
    StartGameWidget* startGameWidget;

    void setupUI();
};
