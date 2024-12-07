﻿#include "routing.h"
#include "Map.h"
Routing::Routing(GameStorage& storage,GameLogic& gameLogic):m_storage(storage),m_gameLogic(gameLogic)
{
}

std::string ConvertCellToString(const CellType& cell) {
    return std::visit([](auto&& arg) -> std::string {
        using T = std::decay_t<decltype(arg)>;
        if constexpr (std::is_same_v<T, std::monostate>) {
            return "0"; // Celul? goal?
        }
        else if constexpr (std::is_same_v<T, Wall>) {
            if (arg.IsDestructible()) {
                if (arg.GetContainedBomb() != nullptr) {
                    return "DB"; // Pereu destructibil cu bomba
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

Routing::Routing(crow::SimpleApp& app, GameStorage& storage, GameLogic& gameLogic):m_app(app), m_storage(storage), m_gameLogic(gameLogic)
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
    GetTheBestPlayersByCrowns();
    GetTheBestPlayersByPoints();
    SetupGameRoute();
    m_app.port(18080).multithreaded().run();
}

void Routing::GetTheBestPlayersByPoints() {
    CROW_ROUTE(m_app, "/leaderboard/points/<int>")
        ([this](int userId) {
        try {
            auto players = m_storage.GetPlayersDAO();

            std::sort(players.begin(), players.end(), [](const PlayerDAO& a, const PlayerDAO& b) {
                return a.GetPoints() > b.GetPoints(); 
                });

            crow::json::wvalue res;
            std::vector<crow::json::wvalue> topPlayers;
            bool isUserInTop10 = false;
            int userRank = -1;

            for (size_t i = 0; i < players.size(); ++i) {
                if (i < 10) {
                    crow::json::wvalue playerJson;
                    playerJson["rank"] = i + 1;
                    playerJson["name"] = players[i].GetName();
                    playerJson["points"] = players[i].GetPoints(); 
                    topPlayers.push_back(std::move(playerJson));
                }
                if (players[i].GetId() == userId) {
                    userRank = i + 1;
                    if (i < 10) {
                        isUserInTop10 = true;
                    }
                }
            }

            if (userRank == -1) {
                return crow::response(404, "User not found");
            }

            res["topPlayers"] = std::move(topPlayers);

            if (!isUserInTop10 && userRank > 0) {
                res["currentUser"]["rank"] = userRank;
                res["currentUser"]["name"] = players[userRank - 1].GetName();
                res["currentUser"]["points"] = players[userRank - 1].GetPoints();
            }

            return crow::response(200, res);
        }
        catch (const std::exception& e) {
            return crow::response(500, std::string("Database error: ") + e.what());
        }
            });
}

PlayerDAO Routing::getPlayerById(int userId)
{
    auto players = m_storage.GetPlayersDAO();
    for (const auto& player : players) {
        if (player.GetId() == userId) {
            return player;
        }
    }
    throw std::runtime_error("Player not found with ID: " + std::to_string(userId));
}


GunDAO Routing::getGunById(int userId)
{
    auto guns = m_storage.GetGunsDAO();
    for (const auto& gun : guns) {
        if (gun.GetId() == userId) {
            return gun;
        }
    }
    throw std::runtime_error("Player not found with ID: " + std::to_string(userId));
}

void Routing::GetTheBestPlayersByCrowns() {
    CROW_ROUTE(m_app, "/leaderboard/<int>")
        ([this](int userId) {
        try {
            auto players = m_storage.GetPlayersDAO();

            std::sort(players.begin(), players.end(), [](const PlayerDAO& a, const PlayerDAO& b) {
                return a.GetScore() > b.GetScore();
                });

            crow::json::wvalue res;
            std::vector<crow::json::wvalue> topPlayers;
            bool isUserInTop10 = false;
            int userRank = -1;

            for (size_t i = 0; i < players.size(); ++i) {
                if (i < 10) {
                    crow::json::wvalue playerJson;
                    playerJson["rank"] = i + 1;
                    playerJson["name"] = players[i].GetName();
                    playerJson["score"] = players[i].GetScore();
                    topPlayers.push_back(std::move(playerJson));
                }
                if (players[i].GetId() == userId) {
                    userRank = i + 1;
                    if (i < 10) {
                        isUserInTop10 = true;
                    }
                }
            }

            if (userRank == -1) {
                return crow::response(404, "User not found");
            }

            res["topPlayers"] = std::move(topPlayers);

            if (!isUserInTop10 && userRank > 0) {
                res["currentUser"]["rank"] = userRank;
                res["currentUser"]["name"] = players[userRank - 1].GetName();
                res["currentUser"]["score"] = players[userRank - 1].GetScore();
            }

            return crow::response(200, res);
        }
        catch (const std::exception& e) {
            return crow::response(500, std::string("Database error: ") + e.what());
        }
            });
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
            res["userId"] = user.GetId(); 
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

        // Verificăm dacă parola îndeplinește criteriile regex
        std::regex passwordRegex("^(?=.*[A-Z])(?=.*[0-9])(?=.*[!@#$%^&*]).{8,}$");
        if (!std::regex_match(password, passwordRegex)) {
            return crow::response(400, "Password does not meet complexity requirements");
        }

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

void Routing::sendMap(crow::response& res) 
{
    std::vector<std::string> map = m_gameLogic.convertMapToString();
    crow::json::wvalue mapJson;

    crow::json::wvalue::list mapArray; 
    for (const auto& line : map) {
        mapArray.push_back(line); 
    }

    mapJson["map"] = std::move(mapArray);

    res.set_header("Content-Type", "application/json");
    res.write(mapJson.dump()); 
}

void Routing::SetupGameRoute() 
{
    CROW_ROUTE(m_app, "/map")
        .methods(crow::HTTPMethod::GET)([this](const crow::request&, crow::response& res) {
        sendMap(res); 
        res.end();
            });
}





void Routing::BuyReloadSpeedUpgrade() {
    CROW_ROUTE(m_app, "/upgrade/reload_speed/<int>")
        ([this](int userId) {
        try {
            // Obține jucătorul din baza de date
            PlayerDAO player = getPlayerById(userId);
            if (player.GetId() == 0) { // Presupunem că un ID 0 semnifică lipsa utilizatorului
                return crow::response(404, "User not found");
            }

            // Obține arma asociată jucătorului
            GunDAO gun = getGunById(player.GetGunId());
            if (gun.GetId() == 0) { // Presupunem că un ID 0 semnifică lipsa armei
                return crow::response(404, "Gun not found for this player");
            }

            const int upgradeCost = 500;     // Costul upgrade-ului
            const double minReloadSpeed = 0.25; // Rata minimă de reîncărcare

            // Verificăm dacă rata de foc este deja la minim
            if (gun.GetFireRate() <= minReloadSpeed) {
                return crow::response(400, "Reload speed is already at minimum value");
            }

            // Verificăm dacă jucătorul are suficiente puncte
            if (player.GetPoints() < upgradeCost) {
                return crow::response(400, "Not enough points to buy upgrade");
            }

            // Actualizăm punctele și rata de foc
            player.SetPoints(player.GetPoints() - upgradeCost);
            gun.SetFireRate(std::max(gun.GetFireRate() / 2.0, minReloadSpeed));

            // Salvează modificările
            m_storage.UpdatePlayerDAO(player);
            m_storage.UpdateGunDAO(gun);

            // Construim răspunsul JSON
            crow::json::wvalue res;
            res["message"] = "Reload speed upgrade purchased successfully!";
            res["remainingPoints"] = player.GetPoints();
            res["newReloadSpeed"] = gun.GetFireRate();

            return crow::response(200, res);
        }
        catch (const std::exception& e) {
            return crow::response(500, std::string("Database error: ") + e.what());
        }
            });
}
