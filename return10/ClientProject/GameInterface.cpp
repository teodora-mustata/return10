#include "GameInterface.h"
#include "Windows.h"
#include <iostream>
#include <chrono>
#include <thread>
#include <conio.h>
import validation;
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
        if (Validator::ValidateUserInput(std::string_view(&input, 1))) {
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
        else {
            return;
        }
    }
}

void GameInterface::renderGame(const crow::json::rvalue& gameData, int playerId) {
    const auto& board = gameData["map"];

    for (size_t i = 0; i < board.size(); ++i) {
        const std::string& row = board[i].s();

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
            else if (cell == '*') {
                std::cout << "\033[33m* \033[0m";  // Bullet (galben)
            }
        }
        std::cout << std::endl;
    }
}

void GameInterface::updateMap() {
    crow::json::wvalue jsonData;
    jsonData["id"] = UserSession::getInstance().getUserId();

    auto response = cpr::Post(
        cpr::Url{ "http://localhost:18080/update_map" },
        cpr::Header{ {"Content-Type", "application/json"} },
        cpr::Body{ jsonData.dump() }
    );

    if (response.status_code == 200) {
    }
    else {
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
            return true;
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
    bool isGameRunning = true;
    while (isGameRunning) {
        std::cout << "\033[H";

        
        crow::json::wvalue jsonData;
        jsonData["playerId"] = playerId;

   
        cpr::Response r = cpr::Post(
            cpr::Url{ "http://localhost:18080/map" },
            cpr::Header{ { "Content-Type", "application/json" } },
            cpr::Body{ jsonData.dump() }
        );



        if (r.status_code == 200) {
            crow::json::rvalue gameData = crow::json::load(r.text);
            if (gameData.has("map") && gameData["map"].t() == crow::json::type::List) {
                updateMap();
                renderGame(gameData, playerId);
                handleInput();
                //updateMap();
                isGameRunning = checkWinCondition();
            }
            else {
                std::cerr << "Game data is missing necessary fields or 'map' is not a list!" << std::endl;
                break;
            }
        }
        else {
            std::cerr << "Failed to get game state from server. Status code: " << r.status_code << std::endl;
            break;
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    if (isGameRunning == false)
    {
#ifdef _WIN32
        enableANSIInWindows();
#endif

#ifdef _WIN32
        system("cls");
#else
        std::cout << "\033[2J\033[1;1H";
#endif
        std::cout << "Game is over! \n";
        std::cout << "Exiting";
        for (int i = 0; i < 3; i++)
        {
            std::cout << "." << std::flush;
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
        exit(0);
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

bool GameInterface::checkWinCondition()
{
    crow::json::wvalue jsonData;
    jsonData["id"] = UserSession::getInstance().getUserId();
    auto r = cpr::Get(
        cpr::Url{ "http://localhost:18080/check_win_condition" },
        cpr::Header{ {"Content-Type", "application/json"} },
        cpr::Body{ jsonData.dump() }
    );
    if (r.status_code == 200) {
        auto responseJson = crow::json::load(r.text);
        if (responseJson && responseJson.has("win_condition")) {
            int winCondition = responseJson["win_condition"].i();
            if (winCondition == 1) return true;
            else return false;
        }
    }
    else {
        std::cerr << "Eroare: Raspunsul nu contine cheia 'win_condition'." << std::endl;
        return false;
    }
    return false;
}






