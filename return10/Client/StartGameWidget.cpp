#include "StartGameWidget.h"
#include "ChooseGameDificulty.h"
#include "UserSession.h"
#include <cpr/cpr.h>
#include <QMessageBox>

StartGameWidget::StartGameWidget(QWidget* parent, ChooseGameDificulty* chooseGameDificulty)
    : QWidget(parent), chooseGameDificultyWidget(chooseGameDificulty), playerId(0), gameTimer(nullptr) {
    setupUI();
}

StartGameWidget::~StartGameWidget() {
    delete gameTimer;
}

void StartGameWidget::setupUI() {
    QVBoxLayout* layout = new QVBoxLayout(this);
    imageLabel = new QLabel(this);
    layout->addWidget(imageLabel);
    setLayout(layout);
}

void StartGameWidget::startGame() {
    playerId = UserSession::getInstance().getUserId();
    gameTimer = new QTimer(this);
    connect(gameTimer, &QTimer::timeout, [=]() {
        crow::json::wvalue jsonData;
        jsonData["playerId"] = playerId;

        auto response = cpr::Post(
            cpr::Url{ "http://localhost:18080/map" },
            cpr::Header{ {"Content-Type", "application/json"} },
            cpr::Body{ jsonData.dump() }
        );

        if (response.status_code == 200) {
            auto gameData = crow::json::load(response.text);
            renderGame(gameData, playerId);
        }
        });
    gameTimer->start(1000);
}

void StartGameWidget::renderGame(const crow::json::rvalue& gameData, int playerId) {
    // Implement rendering logic here
}

void StartGameWidget::keyPressEvent(QKeyEvent* event) {
    QString command;
    switch (event->key()) {
    case Qt::Key_W: command = "MOVE_UP"; break;
    case Qt::Key_A: command = "MOVE_LEFT"; break;
    case Qt::Key_S: command = "MOVE_DOWN"; break;
    case Qt::Key_D: command = "MOVE_RIGHT"; break;
    case Qt::Key_F: command = "SHOOT"; break;
    default: return;
    }
    sendCommandToServer(command);
}

void StartGameWidget::sendCommandToServer(const QString& command) {
    crow::json::wvalue jsonData;
    jsonData["command"] = command.toStdString();
    jsonData["id"] = playerId;

    cpr::Post(
        cpr::Url{ "http://localhost:18080/command" },
        cpr::Header{ {"Content-Type", "application/json"} },
        cpr::Body{ jsonData.dump() }
    );
}
