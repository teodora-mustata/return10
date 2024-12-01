#include "GameInterface.h"
#include "Windows.h"
#include <iostream>
#include <chrono>
#include <thread>

void GameInterface::handleInput() 
{
    char input;
    std::cout << "W/A/S/D to move, F to shoot: ";
    std::cin >> input;

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

    // Trimitem comanda către server
    sendCommandToServer(command);
}

void GameInterface::renderGame(const crow::json::rvalue& gameData, int playerId) {
    const auto& board = gameData["board"];

    for (size_t i = 0; i < board.size(); ++i) {
        for (size_t j = 0; j < board[i].size(); ++j) {
            // Afișează fiecare element pe harta
            char cell = board[i][j].s()[0];

            if (cell == '0') {
                std::cout << "0 ";  // Gol
            }
            else if (cell == 'D') {
                std::cout << "\033[36mD \033[0m";  // Zid destructibil
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
        }
        std::cout << std::endl;
    }
}

bool GameInterface::sendCommandToServer(const std::string& command) {
    try {
        // Creează un obiect JSON pentru a trimite comanda
        crow::json::wvalue jsonData;
        jsonData["command"] = command;

        // Trimite cererea către server
        auto response = cpr::Post(
            cpr::Url{ "http://localhost:18080/command" },
            cpr::Header{ {"Content-Type", "application/json"} },
            cpr::Body{ jsonData.dump() }
        );

        // Verifică răspunsul serverului
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


GameInterface::GameInterface(Player user) : m_user(user)
{}

void GameInterface::startGame() {
    // ID-ul player-ului curent
    int playerId = UserSession::getInstance().getUserId();

    while (true) {
        // Trimite cererea GET pentru a obține starea jocului
        cpr::Response r = cpr::Get(cpr::Url{ "http://localhost:18080/get_game_state" });

        // Verifică dacă cererea a avut succes (status_code 200)
        if (r.status_code == 200) {
            // Parsează răspunsul JSON
            crow::json::rvalue gameData = crow::json::load(r.text);

            // Verifică dacă datele conțin informațiile necesare
            if (gameData.has("board") && gameData.has("players")) {
                // Afișează harta și procesăm inputurile
                renderGame(gameData, playerId);  // Afișează harta curentă
                handleInput();  // Gestionează inputurile utilizatorului
                displayStatus();
            }
            else {
                std::cerr << "Game data is missing necessary fields!" << std::endl;
                break;  // Ieșim din buclă dacă datele sunt incomplete
            }
        }
        else {
            // Dacă cererea nu a avut succes, afișează un mesaj de eroare
            std::cerr << "Failed to get game state from server. Status code: " << r.status_code << std::endl;
            break;
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(100));

        std::cout << "\033[2J\033[1;1H";  // Comandă ANSI pentru curățarea terminalului
    }
}


void GameInterface::displayStatus() {
    
    std::cout << m_user.GetName() << ": Lives=" << m_user.GetLives()
        << ", Score=" << m_user.GetScore()
        << ", Position=(" << m_user.GetPosition().i
        << ", " << m_user.GetPosition().j << ")\n";
  
}






