#include "GameInterface.h"
#include "Windows.h"
#include <iostream>
#include <chrono>
#include <thread>
#include <conio.h>

#ifdef _WIN32
#include <windows.h>
void enableANSIInWindows() {
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hOut != INVALID_HANDLE_VALUE) {
        DWORD dwMode = 0;
        if (GetConsoleMode(hOut, &dwMode)) {
            dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
            SetConsoleMode(hOut, dwMode);
        }
    }
}
#endif

void GameInterface::handleInput() 
{
    if (_kbhit()) {
        std::cout << "W/A/S/D to move, F to shoot: ";
        char input = _getch();
        input = toupper(input);

        // Traducem input-ul într-o comandă pentru server
        std::string command;
        switch (input) {
        case 'W': command = "MOVE_UP"; break;
        case 'A': command = "MOVE_LEFT"; break;
        case 'S': command = "MOVE_DOWN"; break;
        case 'D': command = "MOVE_RIGHT"; break;
        case 'F': command = "SHOOT"; break;
        default:
            std::cout << "Invalid command!" << std::endl;
            return;
        }
        sendCommandToServer(command);
    }
}

void GameInterface::renderGame(const crow::json::rvalue& gameData, int playerId) {
    const auto& board = gameData["map"];

    for (size_t i = 0; i < board.size(); ++i) {
        const std::string& row = board[i].s();  // Accesăm fiecare șir.

        for (size_t j = 0; j < row.size(); ++j) {
            char cell = row[j]; 

            if (cell == '0') {
                std::cout << "0 ";  // Gol
            }
            else if (cell == 'D') {
                std::cout << "\033[36mD \033[0m";  // Zid destructibil
            }
            else if (cell == 'B') {
                std::cout << "\033[35mB \033[0m";  // Bomba
            }
            else if (cell == 'I') {
                std::cout << "\033[34mI \033[0m";  // Zid indestructibil
            }
            else if (cell == 'P') {
                std::cout << "\033[32mP \033[0m";  // Player-ul curent (verde)
            }
            else if (cell == 'E') {
                std::cout << "\033[31mP \033[0m";  // Inamic (roșu)
            }
            else if (cell == 'T') {
                std::cout << "\033[33mT \033[0m";  // Teleport Trap (galben)
            }
            else if (cell == 'G') {
                std::cout << "\033[33mG \033[0m";  // Gun Disable Trap (galben)
            }
            else if (cell == 'S') {
                std::cout << "\033[33mS \033[0m";  // Stun Trap (galben)
            }
        }
        std::cout << std::endl;
    }
}

bool GameInterface::sendCommandToServer(const std::string& command) {
    try {
        crow::json::wvalue jsonData;
        jsonData["command"] = command;
        jsonData["id"] = UserSession::getInstance().getUserId();

        auto response = cpr::Post(
            cpr::Url{ "http://localhost:18080/command" },
            cpr::Header{ {"Content-Type", "application/json"} },
            cpr::Body{ jsonData.dump() }
        );

        if (response.status_code == 200) {
            auto responseJson = crow::json::load(response.text);

            if (responseJson.has("status") && responseJson["status"].s() == "success") {
                std::cout << "Command executed successfully: " << responseJson["message"].s() << std::endl;
                return true;
            }
            else if (responseJson.has("error")) {
                std::cerr << "Server error: " << responseJson["error"].s() << std::endl;
            }
        }
        else {
            std::cerr << "Failed to execute command. HTTP Status: " << response.status_code << std::endl;
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Exception occurred while sending command: " << e.what() << std::endl;
    }

    return false;
}


void GameInterface::addPlayerToGame(int playerID)
{
    crow::json::wvalue jsonData;
    jsonData["player_id"] = playerID;
    int currentPlayers = -1;
    auto r = cpr::Post(
        cpr::Url{ "http://localhost:18080/add_player" },
        cpr::Header{ {"Content-Type", "application/json"} },
        cpr::Body{ jsonData.dump() }
    );
  
    if (r.status_code == 200) {
        std::cerr << "Player added successfully!\n";
    }
    else {
        std::cerr << "Failed to add player to game. Status code: " << r.status_code << std::endl;
    }
}

void GameInterface::startGame() {

#ifdef _WIN32
    enableANSIInWindows();
#endif

    int playerId = UserSession::getInstance().getUserId();

#ifdef _WIN32
    system("cls");
#else
    std::cout << "\033[2J\033[1;1H";
#endif

    while (true) {
        std::cout << "\033[H";

        cpr::Response r = cpr::Post(cpr::Url{ "http://localhost:18080/map" });

        if (r.status_code == 200) {
            crow::json::rvalue gameData = crow::json::load(r.text);

            if (gameData.has("map") /* && gameData.has("players")*/) {
                renderGame(gameData, playerId); 
                handleInput(); 
                //displayStatus();
            }
            else {
                std::cerr << "Game data is missing necessary fields!" << std::endl;
                break;
            }
        }
        else {
            std::cerr << "Failed to get game state from server. Status code: " << r.status_code << std::endl;
            break;
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(100));

        //std::cout << "\033[2J\033[1;1H"; 
    }
}

int GameInterface::getActivePlayers()
{
    auto response = cpr::Get(cpr::Url{ "http://localhost:18080/get_active_players" });

    if (response.status_code == 200) {
        auto jsonResponse = crow::json::load(response.text);
        if (jsonResponse) {
            return jsonResponse["active_players"].i();
        }
    }
    return -1;
}

//void GameInterface::startGame() {
//#ifdef _WIN32
//    enableANSIInWindows();
//#endif
//
//    int playerId = UserSession::getInstance().getUserId();
//
//    bool isRunning = true;
//    std::thread inputThread([&]() {
//        while (isRunning) {
//            handleInput();
//            std::this_thread::sleep_for(std::chrono::milliseconds(50));
//        }
//        });
//
//
//    while (isRunning) {
//#ifdef _WIN32
//        system("cls");
//#else
//        std::cout << "\033[2J\033[1;1H";
//#endif
//
//        cpr::Response r = cpr::Post(cpr::Url{ "http://localhost:18080/map" });
//
//        if (r.status_code == 200) {
//            crow::json::rvalue gameData = crow::json::load(r.text);
//
//            if (gameData.has("map")) {
//                renderGame(gameData, playerId); 
//            }
//            else {
//                std::cerr << "Game data is missing necessary fields!" << std::endl;
//                isRunning = false;
//            }
//        }
//        else {
//            std::cerr << "Failed to get game state from server. Status code: " << r.status_code << std::endl;
//            isRunning = false;
//        }
//
//        //std::this_thread::sleep_for(std::chrono::milliseconds(50));
//    }
//
//    isRunning = false;
//    inputThread.join();
//}

//void GameInterface::displayStatus() {
//    
//    std::cout << m_user.GetName() << ": Lives=" << m_user.GetLives()
//        << ", Score=" << m_user.GetScore()
//        << ", Position=(" << m_user.GetPosition().i
//        << ", " << m_user.GetPosition().j << ")\n";
//  
//}






