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
            std::cout << "Starting game...\n";
            GameInterface gameInterface;
            gameInterface.addPlayerToGame(UserSession::getInstance().getUserId());
            while (gameInterface.getPlayersID().size() < 2) //change to 4 later
            {
                std::cout << "Waiting for players";
                std::cout << std::flush;

                for (int i = 0; i < 30; ++i) {  // asteptam 30 de secunde pentru a intra playerii
                    std::cout << "." << std::flush;
                    std::this_thread::sleep_for(std::chrono::seconds(1));
                }
            }
            if (gameInterface.getPlayersID().size() == 2)
            {
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
