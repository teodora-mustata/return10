#include "MainMenu.h"

void MainMenu::display() {
    bool exitProgram = false;
    int choice;

    while (!exitProgram) {
        std::cout << "==== Main Menu ====\n";
        std::cout << "1. Start Game\n";
        std::cout << "2. Shop\n";
        std::cout << "3. Leaderboard\n";
        std::cout << "4. Exit\n";
        std::cout << "Please select an option: ";
        std::cin >> choice;

        if (choice == 1) {
            int difficulty;
            bool validDifficulty = false;
            std::cout << "====Choose Difficulty====\n";
            std::cout << "1.Easy\n";
            std::cout << "2.Medium\n";
            std::cout << "3.Hard\n";
            std::cout << "Please select difficulty: ";
            std::cin >> difficulty;
            if (difficulty >= 1 && difficulty <= 3)
            {
                sendDifficultyToServer(difficulty);
                validDifficulty = true;
            }
            else std::cout << "Invalid choice! Please select 1, 2, or 3.\n";
            if (validDifficulty);

            std::cout << "Starting game...\n";
            GameInterface gameInterface;
            int currentId = UserSession::getInstance().getUserId();

            int currentPlayers = gameInterface.addPlayerToGame(currentId);

            while (currentPlayers < 1) //change to 4 later
            {
                std::cout << "Waiting for players";
                std::cout << std::flush;

                for (int i = 0; i < 60; ++i) {  // asteptam 60 de secunde pentru a intra playerii
                    std::cout << "." << std::flush;
                    std::this_thread::sleep_for(std::chrono::seconds(1));
                }
                std::cout << "No one joined. Exiting...\n";
                break;
            }
            if (currentPlayers == 1)
            {
                std::cout << "Game starting now!" << std::endl;

                for (int i = 3; i > 0; --i)
                {
                    std::cout << i << "..." << std::endl;
                    std::this_thread::sleep_for(std::chrono::seconds(1)); // A?teaptã 1 secundã
                }

                bool gameRunning = true;
                while (gameRunning)
                {
                    gameInterface.startGame();
                }
            }
        }
        else if (choice == 2) {
            ShopMenu shopMenu;
            shopMenu.display();
        }
        else if (choice == 3) {
            Leaderboard leaderboardMenu;
            leaderboardMenu.display();
        }
        else if (choice == 4) {
            std::cout << "Exiting the game. Goodbye!\n";
            exitProgram = true;
        }
        else {
            std::cout << "Invalid option! Please try again.\n";
        }
    }
}

void MainMenu::sendDifficultyToServer(int difficulty)
{
    crow::json::wvalue jsonData;
    jsonData["difficulty"] = difficulty;

    auto response = cpr::Post(
        cpr::Url{ "http://localhost:18080/send_difficulty" },
        cpr::Header{ {"Content-Type", "application/json"} },
        cpr::Body{ jsonData.dump() }
    );

    if (response.status_code == 200) {
        auto responseJson = crow::json::load(response.text);
        std::cout << "Difficulty sent successfully!\n";
    }
    else std::cout << "Couldn't send difficulty to server. Try again.\n";
}
