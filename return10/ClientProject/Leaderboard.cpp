
#include "Leaderboard.h"

void Leaderboard::display() {
    int choice;

    while (true) {
        std::cout << "==== Leaderboard Menu ====\n";
        std::cout << "1. View best players by crown\n";
        std::cout << "2. View best players by points\n";
        std::cout << "3. Exit to Main Menu\n";
        std::cout << "Please select an option: ";
        std::cin >> choice;

        if (choice == 1) {
            std::cout<<"Viewing best players by crowns";
        }
        else if (choice == 2) {
            std::cout << "Viewing best players by points...\n";
        }
        else if (choice == 3) {
            std::cout << "Returning to Main Menu...\n";
            break;
        }
        else {
            std::cout << "Invalid option! Please try again.\n";
        }
    }
}


