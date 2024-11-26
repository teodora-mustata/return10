#include "ShopMenu.h"

void ShopMenu::display() {
    int choice;

    while (true) {
        std::cout << "==== Shop Menu ====\n";
        std::cout << "1. Buy reload speed upgrade\n";
        std::cout << "2. Sell bullet speed upgrade\n";
        std::cout << "3. Exit to Main Menu\n";
        std::cout << "Please select an option: ";
        std::cin >> choice;

        if (choice == 1) {
            std::cout << "Buying reload speed upgrade...\n";
        }
        else if (choice == 2) {
            std::cout << "Buying bullet speed upgrade...\n";
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
