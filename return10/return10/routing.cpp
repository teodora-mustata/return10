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

Routing::Routing(crow::SimpleApp& app, GameStorage& storage):m_app(app), m_storage(storage)
{
}

void Routing::Run() {

    //Map game_map;
    //CROW_ROUTE(m_app, "/map")([&game_map]() {
    //    crow::json::wvalue map_json;

    //    // Dimensiunile hartii
    //    map_json["dimensions"] = crow::json::wvalue{
    //        {"height", game_map.GetDimensions().first},
    //        {"width", game_map.GetDimensions().second}
    //    };

    //    // Matricea completa a hartii
    //    std::vector<crow::json::wvalue> map_matrix;
    //    for (const auto& row : game_map.GetBoard()) {
    //        std::vector<crow::json::wvalue> json_row;
    //        for (const auto& cell : row) {
    //            json_row.push_back(crow::json::wvalue(ConvertCellToString(cell))); // Creaza un nou obiect `wvalue` din string
    //        }
    //        map_matrix.push_back(std::move(json_row)); // Folosim `std::move` pentru a muta `json_row`
    //    }

    //    map_json["board"] = std::move(map_matrix); // Mutam `map_matrix` în `map_json` pentru a evita copierea

    //    return map_json; // Returnam obiectul JSON
    //    });

    SetupLoginRoutes(m_app);

    m_app.port(18080).multithreaded().run();
}

void Routing::SetupLoginRoutes(crow::SimpleApp& app)
{
    // Route pentru login
    CROW_ROUTE(app, "/login").methods("POST"_method)([this](const crow::request& req) {
        auto body = crow::json::load(req.body);
        if (!body) {
            return crow::response(400, "Invalid JSON format");
        }

        std::string username = body["username"].s();
        std::string password = body["password"].s();

        try {
            auto players = m_storage.GetPlayersDAO();

            // Caută utilizatorul în lista de jucători
            auto it = std::find_if(players.begin(), players.end(), [&](const PlayerDAO& player) {
                return player.GetName() == username && player.GetPassword() == password;
                });

            if (it == players.end()) {
                // Utilizatorul nu a fost găsit
                return crow::response(401, "Invalid username or password!");
            }

            const auto& user = *it;

            crow::json::wvalue gunDetails;
            if (user.GetGunId() != -1) {
                // Obține arma utilizatorului din baza de date
                auto gun = m_storage.GetGunById(user.GetGunId());
                gunDetails["fireRate"] = gun.GetFireRate();
                gunDetails["bulletSpeed"] = gun.GetBulletSpeed();
            }
            else {
                gunDetails = crow::json::wvalue(); // obiect gol
            }

            // Construiește răspunsul JSON
            crow::json::wvalue res;
            res["message"] = "Welcome " + user.GetName() + "!";
            res["points"] = user.GetPoints();
            res["score"] = user.GetScore();
            res["gunDetails"] = std::move(gunDetails);
            //CROW_LOG_INFO << "Response JSON: " << res.dump();
            return crow::response(200, res);
        }
        catch (const std::exception& e) {
            return crow::response(500, std::string("Database error: ") + e.what());
        }
        });

    // Route pentru signup
    CROW_ROUTE(app, "/signup").methods("POST"_method)([this](const crow::request& req) {
        auto body = crow::json::load(req.body);

        if (!body) {
            return crow::response(400, "Invalid JSON format");
        }

        // Obține numele utilizatorului și parola
        std::string username = body["username"].s();
        std::string password = body["password"].s();

        // Verificăm dacă utilizatorul există deja în baza de date
        auto players = m_storage.GetPlayersDAO();
        for (const auto& player : players) {
            if (player.GetName() == username) {
                return crow::response(409, "Username already exists");
            }
        }
        // Creăm un obiect GunDAO pentru a adăuga o armă asociată player-ului
        GunDAO newGun;
        newGun.SetFireRate(4);  // fire rate implicit
        newGun.SetBulletSpeed(0.25);  // bullet speed implicit

        // Inserăm arma în baza de date și obținem gunId
        int gunId = m_storage.AddGunDAO(newGun);

        // Creăm un obiect PlayerDAO
        PlayerDAO newPlayer;
        newPlayer.SetName(username);
        newPlayer.SetPassword(password);
        newPlayer.SetScore(0);  // Scor implicit: 0
        newPlayer.SetPoints(0); // Puncte implicite: 0
        newPlayer.SetGunId(gunId);  // Asociere implicită cu un GunId, poți schimba această logică

        // Adăugăm player-ul în baza de date
        m_storage.AddPlayerDAO(newPlayer);

        return crow::response(201, "Account created successfully!");
        });
}
