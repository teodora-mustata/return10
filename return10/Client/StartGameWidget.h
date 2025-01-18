#pragma once

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QTimer>
#include <QKeyEvent>
#include <crow/json.h>

class ChooseGameDificulty;

class StartGameWidget : public QWidget {
    Q_OBJECT

public:
    StartGameWidget(QWidget* parent = nullptr, ChooseGameDificulty* chooseGameDificulty = nullptr);
    ~StartGameWidget();
    void startGame();
    void renderGame(const crow::json::rvalue& gameData, int playerId);

protected:
    void keyPressEvent(QKeyEvent* event) override;

private:
    QLabel* imageLabel;
    int playerId;
    QTimer* gameTimer;

    ChooseGameDificulty* chooseGameDificultyWidget;

    void sendCommandToServer(const QString& command);
    void setupUI();
};
