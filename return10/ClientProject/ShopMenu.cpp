#include "ShopMenu.h"

void ShopMenu::display() {
    int choice;

    while (true) {
        std::cout << "==== Shop Menu ====\n";
        std::cout << "1. Buy reload speed upgrade\n";
        std::cout << "2. Buy bullet speed upgrade\n";
        std::cout << "3. Exit to Main Menu\n";
        std::cout << "Please select an option: ";
        std::cin >> choice;

        if (choice == 1) {
            buyReloadSpeedUpgrade();
        }
        else if (choice == 2) {
            buyBulletSpeedUpgrade();
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
void ShopMenu::buyReloadSpeedUpgrade() {
    int userId = UserSession::getInstance().getUserId();

    auto response = cpr::Get(cpr::Url{ "http://localhost:18080/upgrade/reload_speed/" + std::to_string(userId) });

    if (response.status_code == 200) {
        auto responseJson = crow::json::load(response.text);
        std::cout << "==== Upgrade Successful ====\n";
        std::cout << responseJson["message"].s() << "\n";
        std::cout << "Remaining Score: " << responseJson["remainingScore"].i() << "\n";
        std::cout << "New Reload Speed: " << responseJson["newReloadSpeed"].d() << "\n";
    }
    else if (response.status_code == 400) {
        auto responseJson = crow::json::load(response.text);
        if (responseJson.has("error")) {
            std::cout << "Error: " << responseJson["error"].s() << "\n";
        }
        else {
            std::cout << "Error: Something went wrong. Try again.\n";
        }
    }
    else if (response.status_code == 404) {
        std::cout << "Error: User or gun not found. Check your user ID.\n";
    }
    else {
        std::cout << "Error performing upgrade. Please try again later.\n";
        std::cout << "Server responded with status code: " << response.status_code << "\n";
    }
}
void ShopMenu::buyBulletSpeedUpgrade() {
    int userId = UserSession::getInstance().getUserId();

    auto response = cpr::Get(cpr::Url{ "http://localhost:18080/upgrade/bullet_speed/" + std::to_string(userId) });

    if (response.status_code == 200) {
        auto responseJson = crow::json::load(response.text);

        std::cout << "==== Bullet Speed Upgrade Successful ====\n";
        std::cout << responseJson["message"].s() << "\n";
        std::cout << "New Bullet Speed: " << responseJson["newBulletSpeed"].d() << "\n";
        std::cout << "Remaining Crowns: " << responseJson["remainingCrowns"].i() << "\n";
    }
    else if (response.status_code == 400) {
        auto responseJson = crow::json::load(response.text);
        if (responseJson.has("error")) {
            std::cout << "Error: " << responseJson["error"].s() << "\n";
        }
        else {
            std::cout << "Error: Something went wrong. Try again.\n";
        }
    }
    else if (response.status_code == 404) {
        std::cout << "Error: User or gun not found. Check your user ID.\n";
    }
    else {
        std::cout << "Error performing upgrade. Please try again later.\n";
        std::cout << "Server responded with status code: " << response.status_code << "\n";
    }
}
