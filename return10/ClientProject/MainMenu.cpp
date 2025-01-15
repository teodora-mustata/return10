#include "MainMenu.h"
//
//void MainMenu::display() {
//    bool exitProgram = false;
//    int choice;
//
//    while (!exitProgram) {
//        std::cout << "==== Main Menu ====\n";
//        std::cout << "1. Start Game\n";
//        std::cout << "2. Shop\n";
//        std::cout << "3. Leaderboard\n";
//        std::cout << "4. Exit\n";
//        std::cout << "Please select an option: ";
//        std::cin >> choice;
//
//        if (choice == 1) {
//            int difficulty;
//            bool validDifficulty = false;
//            std::cout << "====Choose Difficulty====\n";
//            std::cout << "1.Easy\n";
//            std::cout << "2.Medium\n";
//            std::cout << "3.Hard\n";
//            std::cout << "Please select difficulty: ";
//            std::cin >> difficulty;
//            if (difficulty >= 1 && difficulty <= 3)
//            {
//                if (sendDifficultyToServer(difficulty)) {
//                }
//                else {
//                    std::cout << "Difficulty could not be set. Another client may have already set it.\n";
//                }
//                validDifficulty = true;
//            }
//            else std::cout << "Invalid choice! Please select 1, 2, or 3.\n";
//            if (validDifficulty)
//            {
//                std::cout << "Starting game...\n";
//                GameInterface gameInterface;
//                int currentId = UserSession::getInstance().getUserId();
//
//                gameInterface.addPlayerToGame(currentId);
//                int currentPlayers = gameInterface.getActivePlayers();
//                std::cout << "There are currently " << currentPlayers << "/4 players in the game!\n";
//                while (currentPlayers < 2) // change to 4 later
//                {
//                    std::cout << "Waiting for players";
//                    std::cout << std::flush;
//
//                    for (int i = 0; i < 60; ++i) 
//                    {
//                        currentPlayers = gameInterface.getActivePlayers();
//                        std::cout << "." << std::flush;
//                        std::this_thread::sleep_for(std::chrono::seconds(1));
//                        if (currentPlayers >= 2) {
//                            std::cout << "\nPlayer joined! Currently " << currentPlayers << "/4 players in the game.\n";
//                            break;
//                        }
//                    }
//                    if (currentPlayers < 2) {
//                        std::cout << "\nNo one joined. Exiting...\n";
//                        break;
//                    }
//                }
//                if (currentPlayers == 2)
//                {
//                    std::cout << "Game starting now!" << std::endl;
//
//                    for (int i = 3; i > 0; --i)
//                    {
//                        std::cout << i << "..." << std::endl;
//                        std::this_thread::sleep_for(std::chrono::seconds(1)); // Așteaptă 1 secundă
//                    }
//                    startServerGame();
//                    bool gameRunning = true;
//                    while (gameRunning)
//                    {
//                        gameInterface.startGame();
//                    }
//                }
//            }
//        }   
//        else if (choice == 2) {
//            ShopMenu shopMenu;
//            shopMenu.display();  
//        }
//        else if (choice == 3) {
//            Leaderboard leaderboardMenu;
//            leaderboardMenu.display();
//        }
//        else if (choice == 4) {
//            std::cout << "Exiting the game. Goodbye!\n";
//            exitProgram = true;  
//        }
//        else {
//            std::cout << "Invalid option! Please try again.\n";
//        }
//    }
//}


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
                validDifficulty = true;
            }
            else {
                std::cout << "Invalid choice! Please select 1, 2, or 3.\n";
            }

            if (validDifficulty)
            {
                std::cout << "Starting game...\n";
                GameInterface gameInterface;
                int currentId = UserSession::getInstance().getUserId();

                gameInterface.addPlayerToGame(currentId);
                int currentPlayers = gameInterface.getActivePlayers();
                std::cout << "There are currently " << currentPlayers << "/4 players in the game!\n";
                while (currentPlayers < 2) // change to 4 later
                {
                    std::cout << "Waiting for players";
                    std::cout << std::flush;

                    for (int i = 0; i < 60; ++i)
                    {
                        currentPlayers = gameInterface.getActivePlayers();
                        std::cout << "." << std::flush;
                        std::this_thread::sleep_for(std::chrono::seconds(1));
                        if (currentPlayers >= 2) {
                            std::cout << "\nPlayer joined! Currently " << currentPlayers << "/4 players in the game.\n";
                            break;
                        }
                    }
                    if (currentPlayers < 2) {
                        std::cout << "\nNo one joined. Exiting...\n";
                        break;
                    }
                }
                if (currentPlayers >= 2)
                {
                    std::cout << "Game starting now!" << std::endl;

                    for (int i = 3; i > 0; --i)
                    {
                        std::cout << i << "..." << std::endl;
                        std::this_thread::sleep_for(std::chrono::seconds(1)); // Așteaptă 1 secundă
                    }

                    createGame();

                    // Set the difficulty after the game has started
                    if (sendDifficultyToServer(difficulty)) {
                        std::cout << "Difficulty set successfully!\n";
                    }
                    else {
                        std::cout << "Difficulty could not be set. Another client may have already set it.\n";
                    }

                    createGame();
                    bool gameRunning = true;
                    while (gameRunning)
                    {
                        gameInterface.startGame();
                    }
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

//bool MainMenu::sendDifficultyToServer(int difficulty)
//{
//    crow::json::wvalue jsonData;
//    jsonData["difficulty"] = difficulty;
//
//    auto response = cpr::Post(
//        cpr::Url{ "http://localhost:18080/send_difficulty" },
//        cpr::Header{ { "Content-Type", "application/json" } },
//        cpr::Body{ jsonData.dump() }
//    );
//
//    if (response.status_code == 200) {
//        std::cout << "Difficulty set successfully!\n";
//        return true;
//    }
//    else if (response.status_code == 403) {
//        std::cout << "Difficulty already set by another client.\n";
//    }
//    else {
//        std::cout << "Couldn't send difficulty to server. Try again.\n";
//    }
//    return false;
//}

//bool MainMenu::sendDifficultyToServer(int difficulty)
//{
//    crow::json::wvalue jsonData;
//    jsonData["difficulty"] = difficulty;
//    jsonData["playerId"] = UserSession::getInstance().getUserId();
//
//    auto response = cpr::Post(
//        cpr::Url{ "http://localhost:18080/send_difficulty" },
//        cpr::Header{ { "Content-Type", "application/json" } },
//        cpr::Body{ jsonData.dump() }
//    );
//
//    if (response.status_code == 200) {
//        std::cout << "Difficulty set successfully!\n";
//        return true;
//    }
//    else if (response.status_code == 403) {
//        std::cout << "Difficulty already set by another client.\n";
//    }
//    else {
//        std::cout << "Couldn't send difficulty to server. Try again.\n";
//    }
//    return false;
//}


bool MainMenu::sendDifficultyToServer(int difficulty)
{
    crow::json::wvalue jsonData;
    jsonData["difficulty"] = difficulty;
    jsonData["playerId"] = UserSession::getInstance().getUserId();

    auto response = cpr::Post(
        cpr::Url{ "http://localhost:18080/send_difficulty" },
        cpr::Header{ { "Content-Type", "application/json" } },
        cpr::Body{ jsonData.dump() }
    );

    if (response.status_code == 200) {
        std::cout << "Difficulty set successfully!\n";
        return true;
    }
    else if (response.status_code == 403) {
        std::cout << "Difficulty already set by another client.\n";
    }
    else {
        std::cout << "Couldn't send difficulty to server. Try again.\n";
    }
    return false;
}


void MainMenu::checkCurrentDifficulty()
{
    auto response = cpr::Get(
        cpr::Url{ "http://localhost:18080/get_difficulty" }
    );

    if (response.status_code == 200) {
        auto responseJson = crow::json::load(response.text);
        int currentDifficulty = responseJson["difficulty"].i();
        std::cout << "Current difficulty: " << currentDifficulty << "\n";

        if (currentDifficulty == 0) {
            std::cout << "You can set the difficulty.\n";
        }
        else {
            std::cout << "Difficulty already set to: " << currentDifficulty << ".\n";
        }
    }
    else {
        std::cout << "Couldn't retrieve current difficulty.\n";
    }
}

void MainMenu::createGame()
{
    try {
        auto response = cpr::Post(
            cpr::Url{ "http://localhost:18080/start_game" }
        );

        if (response.status_code == 200) {
            std::cout << "Game started!\n";
        }
        else {
            std::cout << "Failed to contact server. Status code: " << response.status_code << std::endl;
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}