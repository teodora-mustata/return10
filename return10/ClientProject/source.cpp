#include <iostream>
#include <cpr/cpr.h>
#include <crow.h>
#include "LoginMenu.h"
#include "MainMenu.h"

int main() {
    //// 1. Obtin harta de la server
    //auto response = cpr::Get(cpr::Url{ "http://localhost:18080/map" });
    //if (response.status_code != 200)
    //{
    //    std::cout << "eroare";
    //}
    //if (response.status_code == 200) {
    //    auto map_data = crow::json::load(response.text);


    //    // 2. Afisez dimensiunile hartii
    //    std::cout << "Map dimensions:\n";
    //    std::cout << "Height: " << map_data["dimensions"]["height"] << "\n";
    //    std::cout << "Width: " << map_data["dimensions"]["width"] << "\n";

    //    // 3. Afisam punctele de spawn
    //    std::cout << "Spawn points:\n";
    //    for (const auto& sp : map_data["spawn_points"]) {
    //        std::cout << "Spawn point: (" << sp["x"].i() << ", " << sp["y"].i() << ")\n";
    //    }
    //    // 4. Afisam matricea hartii
    //    std::cout << "Map board:\n";
    //    for (const auto& row : map_data["board"]) {
    //        for (const auto& cell : row) {
    //            std::cout << cell.s() << " "; // presupunem ca fiecare celula este un string
    //        }
    //        std::cout << "\n"; // La sfarsitul fiecarui rand, trecem la linia urmatoare
    //    }
    //}
    //else {
    //    std::cerr << "Failed to fetch map information. Status code: " << response.status_code << "\n";
    //    return 1;
    //}
    std::cout << "Client" << std::endl;
    try {
        std::cout << "Welcome to Battle City!\n";

        LoginMenu loginMenu;
        loginMenu.display();
        MainMenu mainMenu;
        mainMenu.display();  


    }
    catch (const std::exception& e) {
        std::cerr << "An unexpected error occurred: " << e.what() << '\n';
    }
    catch (...) {
        std::cerr << "An unknown error occurred." << '\n';
    }

    return 0;

}


//vizualizare a jocului
//preia input de user si trimite la server

//in server avem toata logica jocului