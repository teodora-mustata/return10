//#include "StartGameWidget.h"
//#include "ChooseGameDificulty.h"
//#include "UserSession.h"
//#include <cpr/cpr.h>
//#include <QMessageBox>
//#include <QDebug>
//
//StartGameWidget::StartGameWidget(QWidget* parent, ChooseGameDificulty* chooseGameDificulty)
//    : QWidget(parent), chooseGameDificultyWidget(chooseGameDificulty), playerId(0), gameTimer(nullptr), cellSize(40) {
//    setupUI();
//}
//
//StartGameWidget::~StartGameWidget() {
//    delete gameTimer;
//}
//
//void StartGameWidget::addPlayerToGame(int playerID) {
//    crow::json::wvalue jsonData;
//    jsonData["player_id"] = playerID;
//
//    auto r = cpr::Post(
//        cpr::Url{ "http://localhost:18080/add_player" },
//        cpr::Header{ {"Content-Type", "application/json"} },
//        cpr::Body{ jsonData.dump() }
//    );
//
//    if (r.status_code == 200) {
//        std::cerr << "Player added successfully!\n";
//    }
//    else {
//        std::cerr << "Failed to add player to game. Status code: " << r.status_code << std::endl;
//    }
//}
//
//void StartGameWidget::setupUI() {
//    setFixedSize(800, 600); // Fixed size for the game canvas
//}
//
//void StartGameWidget::startGame() {
//    int playerId = UserSession::getInstance().getUserId();
//
//    bool isGameRunning = true;
//    while (isGameRunning) {
//        crow::json::wvalue jsonData;
//        jsonData["playerId"] = playerId;
//
//        cpr::Response r = cpr::Post(
//            cpr::Url{ "http://localhost:18080/map" },
//            cpr::Header{ { "Content-Type", "application/json" } },
//            cpr::Body{ jsonData.dump() }
//        );
//
//        if (r.status_code == 200) {
//            crow::json::rvalue gameData = crow::json::load(r.text);
//
//            if (gameData.has("map") && gameData["map"].t() == crow::json::type::List) {
//                updateMap();
//                renderGame(gameData, playerId);
//                handleInput();
//                isGameRunning = checkWinCondition();
//            }
//            else {
//                std::cerr << "Game data is missing necessary fields or 'map' is not a list!" << std::endl;
//                break;
//            }
//        }
//        else {
//            std::cerr << "Failed to get game state from server. Status code: " << r.status_code << std::endl;
//            break;
//        }
//
//        std::this_thread::sleep_for(std::chrono::milliseconds(100));
//    }
//}
//
//void StartGameWidget::handleInput() {
//    std::cout << "W/A/S/D to move, F to shoot: ";
//    char input;
//    std::cin >> input;
//    input = toupper(input);
//
//    std::string command;
//    switch (input) {
//    case 'W': command = "MOVE_UP"; break;
//    case 'A': command = "MOVE_LEFT"; break;
//    case 'S': command = "MOVE_DOWN"; break;
//    case 'D': command = "MOVE_RIGHT"; break;
//    case 'F': command = "SHOOT"; break;
//    default:
//        std::cout << "Invalid command!" << std::endl;
//        return;
//    }
//    sendCommandToServer(command);
//}
//
//void StartGameWidget::renderGame(const crow::json::rvalue& gameData, int playerId) {
//    const auto& board = gameData["map"];
//
//    for (size_t i = 0; i < board.size(); ++i) {
//        const std::string& row = board[i].s();
//
//        for (size_t j = 0; j < row.size(); ++j) {
//            char cell = row[j];
//
//            if (cell == '0') {
//                std::cout << "0 ";
//            }
//            else if (cell == 'D') {
//                std::cout << "\033[36mD \033[0m";
//            }
//            else if (cell == 'B') {
//                std::cout << "\033[35mB \033[0m";
//            }
//            else if (cell == 'I') {
//                std::cout << "\033[34mI \033[0m";
//            }
//            else if (cell == 'P') {
//                std::cout << "\033[32mP \033[0m";
//            }
//            else if (cell == 'E') {
//                std::cout << "\033[31mE \033[0m";
//            }
//            else if (cell == 'T') {
//                std::cout << "\033[33mT \033[0m";
//            }
//            else if (cell == 'G') {
//                std::cout << "\033[33mG \033[0m";
//            }
//            else if (cell == 'S') {
//                std::cout << "\033[33mS \033[0m";
//            }
//            else if (cell == '*') {
//                std::cout << "\033[33m* \033[0m";
//            }
//        }
//        std::cout << std::endl;
//    }
//}
//
//void StartGameWidget::updateMap() {
//    crow::json::wvalue jsonData;
//    jsonData["id"] = UserSession::getInstance().getUserId();
//
//    auto response = cpr::Post(
//        cpr::Url{ "http://localhost:18080/update_map" },
//        cpr::Header{ {"Content-Type", "application/json"} },
//        cpr::Body{ jsonData.dump() }
//    );
//
//    if (response.status_code != 200) {
//        std::cerr << "Failed to update map. Status code: " << response.status_code << std::endl;
//    }
//}
//
//bool StartGameWidget::sendCommandToServer(const std::string& command) {
//    try {
//        crow::json::wvalue jsonData;
//        jsonData["command"] = command;
//        jsonData["id"] = UserSession::getInstance().getUserId();
//
//        auto response = cpr::Post(
//            cpr::Url{ "http://localhost:18080/command" },
//            cpr::Header{ {"Content-Type", "application/json"} },
//            cpr::Body{ jsonData.dump() }
//        );
//
//        if (response.status_code == 200) {
//            return true;
//        }
//        else {
//            std::cerr << "Failed to execute command. HTTP Status: " << response.status_code << std::endl;
//        }
//    }
//    catch (const std::exception& e) {
//        std::cerr << "Exception occurred while sending command: " << e.what() << std::endl;
//    }
//
//    return false;
//}
//
//int StartGameWidget::getActivePlayers() {
//    auto response = cpr::Get(cpr::Url{ "http://localhost:18080/get_active_players" });
//
//    if (response.status_code == 200) {
//        auto jsonResponse = crow::json::load(response.text);
//        if (jsonResponse) {
//            return jsonResponse["active_players"].i();
//        }
//    }
//    return -1;
//}
//
//bool StartGameWidget::checkWinCondition() {
//    crow::json::wvalue jsonData;
//    jsonData["id"] = UserSession::getInstance().getUserId();
//
//    auto r = cpr::Get(
//        cpr::Url{ "http://localhost:18080/check_win_condition" },
//        cpr::Header{ {"Content-Type", "application/json"} },
//        cpr::Body{ jsonData.dump() }
//    );
//
//    if (r.status_code == 200) {
//        auto responseJson = crow::json::load(r.text);
//        if (responseJson && responseJson.has("win_condition")) {
//            return responseJson["win_condition"].i() == 1;
//        }
//    }
//    else {
//        std::cerr << "Failed to check win condition. Status code: " << r.status_code << std::endl;
//    }
//    return false;
//}
//
//void StartGameWidget::paintEvent(QPaintEvent* event) {
//    QPainter painter(this);
//
//    for (const auto& [cell, type] : mapData) {
//        QRect cellRect(cell.x() * cellSize, cell.y() * cellSize, cellSize, cellSize);
//
//        switch (type) {
//        case '0': painter.setBrush(Qt::white); break;
//        case 'B': painter.setBrush(Qt::black); break;
//        case 'D': painter.setBrush(Qt::cyan); break;
//        case 'I': painter.setBrush(Qt::blue); break;
//        case 'P': painter.setBrush(Qt::green); break;
//        case 'E': painter.setBrush(Qt::red); break;
//        case 'T': painter.setBrush(Qt::yellow); break;
//        case 'G': painter.setBrush(Qt::magenta); break;
//        case 'S': painter.setBrush(Qt::gray); break;
//        default: painter.setBrush(Qt::darkGray); break;
//        }
//
//        painter.drawRect(cellRect);
//    }
//
//    QRect playerRect(playerPosition.x() * cellSize, playerPosition.y() * cellSize, cellSize, cellSize);
//    painter.setBrush(Qt::green);
//    painter.drawEllipse(playerRect);
//
//    painter.setBrush(Qt::red);
//    for (const auto& enemy : enemyPositions) {
//        QRect enemyRect(enemy.x() * cellSize, enemy.y() * cellSize, cellSize, cellSize);
//        painter.drawEllipse(enemyRect);
//    }
//}
//
//void StartGameWidget::keyPressEvent(QKeyEvent* event) {
//    QString command;
//
//    switch (event->key()) {
//    case Qt::Key_W: command = "MOVE_UP"; break;
//    case Qt::Key_A: command = "MOVE_LEFT"; break;
//    case Qt::Key_S: command = "MOVE_DOWN"; break;
//    case Qt::Key_D: command = "MOVE_RIGHT"; break;
//    case Qt::Key_F: command = "SHOOT"; break;
//    default: return;
//    }
//
//    sendCommandToServer(command.toStdString());
//}
