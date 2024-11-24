#include "routing.h"
#include "Map.h"


std::string ConvertCellToString(const CellType& cell) {
    return std::visit([](auto&& arg) -> std::string {
        using T = std::decay_t<decltype(arg)>;
        if constexpr (std::is_same_v<T, std::monostate>) {
            return "0"; // Celul? goal?
        }
        else if constexpr (std::is_same_v<T, Wall>) {
            if (arg.IsDestructible()) {
                if (arg.GetContainedBomb() != nullptr) {
                    return "DB"; // Pereu destructibil cu bomb?
                }
                else {
                    return "D"; // Pereu destructibil
                }
            }
            else {
                return "I"; // Pereu indestructibil
            }
        }
        return "?"; // Dac? tipul nu este recunoscut
        }, cell);
}


void Routing::Run() {
    Map game_map;
    CROW_ROUTE(m_app, "/map")([&game_map]() {
        crow::json::wvalue map_json;

        // Dimensiunile hartii
        map_json["dimensions"] = crow::json::wvalue{
            {"height", game_map.GetDimensions().first},
            {"width", game_map.GetDimensions().second}
        };

        // Matricea completa a hartii
        std::vector<crow::json::wvalue> map_matrix;
        for (const auto& row : game_map.GetBoard()) {
            std::vector<crow::json::wvalue> json_row;
            for (const auto& cell : row) {
                json_row.push_back(crow::json::wvalue(ConvertCellToString(cell))); // Creaza un nou obiect `wvalue` din string
            }
            map_matrix.push_back(std::move(json_row)); // Folosim `std::move` pentru a muta `json_row`
        }

        map_json["board"] = std::move(map_matrix); // Mutam `map_matrix` în `map_json` pentru a evita copierea

        return map_json; // Returnam obiectul JSON
        });



    m_app.port(18080).multithreaded().run();
}

