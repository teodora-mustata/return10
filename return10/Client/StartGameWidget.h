//#pragma once
//
//#include <QWidget>
//#include <QLabel>
//#include <QTimer>
//#include <QKeyEvent>
//#include <crow/json.h>
//#include <QPainter>
//#include <map>
//#include <cpr/cpr.h>
//#include <QMessageBox>
//#include <QDebug>
//#include <iostream>
//
//#include "UserSession.h"
//#include "ChooseGameDificulty.h"
//
//// Custom comparator for QPoint to use in std::map
//struct QPointComparator {
//    bool operator()(const QPoint& lhs, const QPoint& rhs) const {
//        return (lhs.x() < rhs.x()) || (lhs.x() == rhs.x() && lhs.y() < rhs.y());
//    }
//};
//
//class StartGameWidget : public QWidget {
//    Q_OBJECT
//
//public:
//    StartGameWidget(QWidget* parent = nullptr, ChooseGameDificulty* chooseGameDificulty = nullptr);
//    ~StartGameWidget();
//
//    void addPlayerToGame(int playerID);
//    void startGame();
//    void handleInput(); // Handles player commands
//    void renderGame(const crow::json::rvalue& gameData, int playerId); // Displays the map
//    void updateMap();
//    bool sendCommandToServer(const std::string& command);
//    void displayStatus();
//    int getActivePlayers();
//    bool checkWinCondition();
//
//protected:
//    void paintEvent(QPaintEvent* event) override; // Override for custom painting
//    void keyPressEvent(QKeyEvent* event) override; // Override for handling keyboard input
//
//private:
//    int playerId;                                    // Player's unique ID
//    QTimer* gameTimer;                               // Timer for game updates
//    ChooseGameDificulty* chooseGameDificultyWidget;
//    int cellSize;
//    std::map<QPoint, char, QPointComparator> mapData;
//    QPoint playerPosition;
//    std::vector<QPoint> enemyPositions;
//
//    void setupUI();
//};
