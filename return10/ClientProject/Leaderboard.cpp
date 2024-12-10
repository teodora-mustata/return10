
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
            displayPlayersByCrowns();
        }
        else if (choice == 2) {
            displayPlayersByPoints();
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

void Leaderboard::displayPlayersByPoints() {
    int userId = UserSession::getInstance().getUserId();

    auto response = cpr::Get(cpr::Url{ "http://localhost:18080/leaderboard/points/" + std::to_string(userId) });

    if (response.status_code == 200) {

        auto responseJson = crow::json::load(response.text);

        std::cout << "==== Leaderboard ====\n";
        for (const auto& player : responseJson["topPlayers"]) {
            std::cout << player["rank"].i() << ". " << player["name"].s() << " - " << player["points"].i() << " points\n";
        }

        if (responseJson.has("currentUser")) {
            auto currentUser = responseJson["currentUser"];
            std::cout << "-----------------------\n";
            std::cout << currentUser["rank"].i() << ". " << currentUser["name"].s() << " - " << currentUser["points"].i() << " points (You)\n";
        }
    }
    else {
        std::cout << "Error fetching leaderboard. Please try again.\n";
        std::cout << userId;
    }
}


void Leaderboard::displayPlayersByCrowns() {
    int userId = UserSession::getInstance().getUserId();

    auto response = cpr::Get(cpr::Url{ "http://localhost:18080/leaderboard/" + std::to_string(userId) });
    if (response.status_code == 200) {
        
        auto responseJson = crow::json::load(response.text);

        std::cout << "==== Leaderboard ====\n";
        for (const auto& player : responseJson["topPlayers"]) {
            std::cout << player["rank"].i() << ". " << player["name"].s() << " - " << player["score"].i() << " crowns\n";
        }

        if (responseJson.has("currentUser")) {
            auto currentUser = responseJson["currentUser"];
            std::cout << "-----------------------\n";
            std::cout << currentUser["rank"].i() << ". " << currentUser["name"].s() << " - " << currentUser["score"].i() << " crowns (You)\n";
        }
    }
    else {
        std::cout << "Error fetching leaderboard. Please try again.\n";
        std::cout << userId;
    }
}
