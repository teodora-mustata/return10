#include "routing.h"
#include "Map.h"



//Routing::Routing(GameStorage& storage, GameLogic& gameLogic) :m_storage(storage), m_gameLogic(gameLogic)
//{
//}

std::string ConvertCellToString(const CellType& cell) {
    return std::visit([](auto&& arg) -> std::string {
        using T = std::decay_t<decltype(arg)>;
        if constexpr (std::is_same_v<T, std::monostate>) {
            return "0";
        }
        else if constexpr (std::is_same_v<T, Wall>) {
            if (arg.isDestructible()) {
                if (arg.getContainedBomb() != nullptr) {
                    return "DB";
                }
                else {
                    return "D";
                }
            }
            else {
                return "I";
            }
        }
        return "?";
        }, cell);
}

//Routing::Routing(crow::SimpleApp& app, GameStorage& storage, GameLogic& gameLogic) :m_app(app), m_storage(storage), m_gameLogic(gameLogic)
//{
//}

Routing::Routing(GameStorage& storage, GameManager& gameLogic):m_storage(storage),m_games(gameLogic)
{
}

void Routing::Run() {

    SetupLoginRoutes();
    GetTheBestPlayersByCrowns();
    GetTheBestPlayersByScore();
    BuyReloadSpeedUpgrade();
    BuyBulletSpeedUpgrade();
    SetupGameRoute();
    getActivePlayers();
    SetDifficulty();
    //AddPlayerToGame();
    AddPlayerToLobby();
    CreateGame();
    HandlePlayerCommand();
    updateMap();
    m_app.port(18080).multithreaded().run();
}

void Routing::GetTheBestPlayersByScore() {
    CROW_ROUTE(m_app, "/leaderboard/score/<int>")
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


GunDAO Routing::getGunById(int gunId)
{
    auto guns = m_storage.GetGunsDAO();
    for (const auto& gun : guns) {
        if (gun.GetId() == gunId) {
            return gun;
        }
    }
    throw std::runtime_error("Gun not found with ID: " + std::to_string(gunId));
}

void Routing::GetTheBestPlayersByCrowns() {
    CROW_ROUTE(m_app, "/leaderboard/<int>")
        ([this](int userId) {
        try {
            auto players = m_storage.GetPlayersDAO();

            std::sort(players.begin(), players.end(), [](const PlayerDAO& a, const PlayerDAO& b) {
                return a.GetCrowns() > b.GetCrowns();
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
                    playerJson["crowns"] = players[i].GetCrowns();
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
                res["currentUser"]["crowns"] = players[userRank - 1].GetCrowns();
            }

            return crow::response(200, res);
        }
        catch (const std::exception& e) {
            return crow::response(500, std::string("Database error: ") + e.what());
        }
            });
}

void Routing::SetupLoginRoutes()
{
    // Route pentru login
    CROW_ROUTE(m_app, "/login").methods("POST"_method)([this](const crow::request& req) {
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
            res["score"] = user.GetScore();
            res["crowns"] = user.GetCrowns();
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

    CROW_ROUTE(m_app, "/signup").methods("POST"_method)([this](const crow::request& req) {
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
        newPlayer.SetCrowns(0);  // Scor implicit: 0
        newPlayer.SetScore(0); // Puncte implicite: 0
        newPlayer.SetGunId(gunId);  // Asociere implicită cu un GunId, poți schimba această logică

        // Adăugăm player-ul în baza de date
        m_storage.AddPlayerDAO(newPlayer);

        return crow::response(201, "Account created successfully!");
        });
}

//void Routing::sendMap(crow::response& res)
//{
//    std::vector<std::string> map = m_gameLogic.convertMapToString();
//
//    //std::vector<std::tuple<int, int, int>> playerPositions; // id+position
//    //for (auto player : m_gameLogic.GetPlayers())
//    //{
//
//    //    int i = player.GetPosition().i;
//    //    int j = player.GetPosition().j;
//    //    playerPositions.emplace_back(i, j);
//    //}
//
//    crow::json::wvalue mapJson;
//
//    crow::json::wvalue::list mapArray;
//    for (const auto& line : map) {
//        mapArray.push_back(line);
//    }
//    mapJson["map"] = std::move(mapArray);
//    res.set_header("Content-Type", "application/json");
//    res.write(mapJson.dump());
//}

void Routing::sendMap(crow::response& res, int playerId)
{
    auto game = m_games.getGameByPlayerId(playerId);
    CROW_LOG_INFO << "Game found: " << game.get();
    if (!game.get()) {
        res.code = 404; // Not Found
        res.write("Game not found for the player.");
        res.end();
        return;
    }

    std::vector<std::string> map = game->convertMapToString();

    crow::json::wvalue mapJson;
    crow::json::wvalue::list mapArray;
    for (const auto& line : map) {
        mapArray.push_back(line);
    }
    mapJson["map"] = std::move(mapArray);
    //CROW_LOG_INFO << "Sending map data: " << mapJson.dump();
    res.set_header("Content-Type", "application/json");
    res.write(mapJson.dump());
    res.end();
}

void Routing::SetupGameRoute()
{
    // Rută pentru a trimite harta
    CROW_ROUTE(m_app, "/map")
        .methods(crow::HTTPMethod::POST)([this](const crow::request& req, crow::response& res) {
        auto jsonData = crow::json::load(req.body);
        if (!jsonData) {
            res.code = 400;
            res.write("Invalid JSON data.");
            res.end();
            return;
        }
        int playerId = jsonData["playerId"].i();
        sendMap(res,playerId);
        res.end();
            });

}


void Routing::BuyReloadSpeedUpgrade() {

    CROW_ROUTE(m_app, "/upgrade/reload_speed/<int>")
        ([this](int userId) {
        try {
            //PlayerDAO player = getPlayerById(userId);
            PlayerDAO player = m_storage.GetPlayerByID(userId);

            if (player.GetId() == 0) {
                crow::json::wvalue res;
                res["error"] = "User not found";
                return crow::response(404, res);
            }

            //GunDAO gun = getGunById(player.GetGunId());
            GunDAO gun = m_storage.GetGunById(player.GetGunId());
            if (gun.GetId() == 0) {
                crow::json::wvalue res;
                res["error"] = "Gun not found for this player";
                return crow::response(404, res);
            }



            const int upgradeCost = 500;
            const double minReloadSpeed = 0.25;

            //if (gun.GetFireRate() <= minReloadSpeed) {
            //    return crow::response(400, "Reload speed is already at minimum value");
            //}

            if (gun.GetFireRate() <= minReloadSpeed) {
                crow::json::wvalue res;
                res["error"] = "Reload speed is already at minimum value";
                return crow::response(400, res);
            }


            if (player.GetScore() < upgradeCost) {
                crow::json::wvalue res;
                res["error"] = "Not enough score to buy upgrade";
                return crow::response(400, res);
            }

            player.SetScore(player.GetScore() - upgradeCost);
            gun.SetFireRate(std::max(gun.GetFireRate() / 2.0, minReloadSpeed));

            m_storage.UpdatePlayerDAO(player);
            m_storage.UpdateGunDAO(gun);

            crow::json::wvalue res;
            res["message"] = "Reload speed upgrade purchased successfully!";
            res["remainingScore"] = player.GetScore();
            res["newReloadSpeed"] = gun.GetFireRate();

            return crow::response(200, res);
        }
        catch (const std::exception& e) {
            crow::json::wvalue res;
            res["error"] = std::string("Database error: ") + e.what();
            return crow::response(500, res);
        }
            });
}

void Routing::BuyBulletSpeedUpgrade() {
    CROW_ROUTE(m_app, "/upgrade/bullet_speed/<int>")
        ([this](int userId) {
        try {
            PlayerDAO player = getPlayerById(userId);
            if (player.GetId() == 0) {
                crow::json::wvalue res;
                res["error"] = "User not found";
                return crow::response(404, res);
            }

            GunDAO gun = getGunById(player.GetGunId());
            if (gun.GetId() == 0) {
                crow::json::wvalue res;
                res["error"] = "Gun not found for this player";
                return crow::response(404, res);
            }

            const float maxBulletSpeed = 0.5;
            const int requiredCrowns = 10;

            if (gun.GetBulletSpeed() >= maxBulletSpeed) {
                crow::json::wvalue res;
                res["error"] = "Bullet speed is already at maximum value";
                return crow::response(400, res);
            }


            if (player.GetCrowns() < requiredCrowns) {
                crow::json::wvalue res;
                res["error"] = "Not enough crowns to upgrade bullet speed";
                return crow::response(400, res);
            }


            gun.SetBulletSpeed(maxBulletSpeed);

            m_storage.UpdateGunDAO(gun);

            crow::json::wvalue res;
            res["message"] = "Bullet speed upgrade applied successfully!";
            res["newBulletSpeed"] = gun.GetBulletSpeed();
            res["remainingCrowns"] = player.GetCrowns();

            return crow::response(200, res);
        }
        catch (const std::exception& e) {
            crow::json::wvalue res;
            res["error"] = std::string("Database error: ") + e.what();
            return crow::response(500, res);
        }
            });
}
//void Routing::AddPlayerToGame()
//{
//    CROW_ROUTE(m_app, "/add_player").methods("POST"_method)([this](const crow::request& req, crow::response& res) {
//
//        try {
//            auto jsonBody = crow::json::load(req.body);
//            if (!jsonBody || !jsonBody.has("player_id")) {
//                res.code = 400;
//                res.body = "Invalid request! Missing or incorrect 'player_id'.";
//                res.end();
//                return;
//            }
//
//            int player_id = jsonBody["player_id"].i();
//
//            PlayerDAO player_data = m_storage.GetPlayerByID(player_id);
//
//            if (player_data.GetId() == 0) {
//                res.code = 404;
//                res.body = "Player not found!";
//                res.end();
//                return;
//            }
//
//            m_loggedInPlayers.push_back(player_id);
//
//
//            auto& players = m_gameLogic.getPlayers();
//
//            if (players.size() < 4) {
//
//                if (player_data.GetId() == 0) {
//                    res.code = 404;
//                    res.body = "Player not found!";
//                    return;
//                }
//
//                GunDAO gun_data = m_storage.GetGunById(player_data.GetGunId());
//
//                if (gun_data.GetId() == 0) {
//                    res.code = 404;
//                    res.body = "Gun not found!";
//                    return;
//                }
//
//                Gun player_gun;
//                player_gun.setFiringRate(std::chrono::seconds(static_cast<int>(gun_data.GetFireRate())));
//                player_gun.setBulletSpeed(gun_data.GetBulletSpeed());
//
//                Coordinate spawnpoint;
//                spawnpoint.i = m_gameLogic.GetMap().getRandomSpawnPoint().first;
//                spawnpoint.j = m_gameLogic.GetMap().getRandomSpawnPoint().second;
//
//                Player new_player(player_data.GetId(), player_data.GetName(), player_data.GetScore(), player_data.GetCrowns(), player_gun, spawnpoint);
//
//                m_gameLogic.addPlayer(new_player);
//
//                //if (m_gameLogic.GetPlayers().size() >= 2) m_gameLogic.startGame();
//
//                /*crow::json::wvalue response;
//                response["current_players"] = players.size();
//                res.body = response.dump();*/
//                res.code = 200;
//            }
//            else {
//                res.code = 400;
//                res.body = "Lobby is full!"; // Dacă sunt deja 4 jucători
//            }
//        }
//        catch (const std::exception& e) {
//            res.code = 500;
//            res.body = std::string("Internal server error: ") + e.what();
//        }
//
//        res.end();
//        });
//}
void Routing::AddPlayerToLobby()
{
    CROW_ROUTE(m_app, "/add_player").methods("POST"_method)([this](const crow::request& req, crow::response& res) {

        try {
            auto jsonBody = crow::json::load(req.body);
            if (!jsonBody || !jsonBody.has("player_id")) {
                res.code = 400;
                res.body = "Invalid request! Missing or incorrect 'player_id'.";
                res.end();
                return;
            }

            int player_id = jsonBody["player_id"].i();

            PlayerDAO player_data = m_storage.GetPlayerByID(player_id);

            if (player_data.GetId() == 0) {
                res.code = 404;
                res.body = "Player not found!";
                res.end();
                return;
            }

            CROW_LOG_INFO << "Adding player " << player_id << " to lobby.";
            m_games.addPlayerToLobby(player_id);
            //m_games.createNewGame();
            //m_games.endGames();

            res.code = 200;
        }
        catch (const std::exception& e) {
            res.code = 500;
            res.body = std::string("Internal server error: ") + e.what();
        }

        res.end();
        });
}

//void Routing::GetActivePlayers()
//{
//    CROW_ROUTE(m_app, "/get_active_players")
//        .methods(crow::HTTPMethod::POST)([&](const crow::request& req, crow::response& res) {
//        try {
//            int players = m_gameLogic.GetPlayers().size();
//            crow::json::wvalue response;
//            response["active_players"] = players;
//            res.body = response.dump();
//            res.code = 200;
//        }
//        catch (const std::exception& e) {
//            res.code = 500;
//            res.body = std::string("Internal server error: ") + e.what();
//        }
//            });
//}

void Routing::getActivePlayers()
{
    CROW_ROUTE(m_app, "/get_active_players")
        .methods(crow::HTTPMethod::GET)([&](const crow::request& req, crow::response& res) {
        try {
            int players = m_games.getLobbyPlayers().size();

            crow::json::wvalue response;
            response["active_players"] = players;
            res.body = response.dump();
            res.code = 200;
            res.end();
        }
        catch (const std::exception& e) {
            res.code = 500;
            res.body = std::string("Internal server error: ") + e.what();
            res.end();
        }
            });
}

void Routing::updateMap() {
    CROW_ROUTE(m_app, "/update_map")
        .methods(crow::HTTPMethod::POST)([&](const crow::request& req, crow::response& res) {
        try {
            auto jsonData = crow::json::load(req.body);

            if (!jsonData || !jsonData.has("id")) {
                res.code = 400;
                res.end();
                return;
            }

            int userId = jsonData["id"].i();
            auto game = m_games.getGameByPlayerId(userId);
            game->updateBullets();
            
            res.code = 200;
            res.end();
        }
        catch (const std::exception& e) {
            res.code = 500;
            res.body = std::string("Internal server error: ") + e.what();
            res.end();
        }
            });
}

//void Routing::SetDifficulty()
//{
//    CROW_ROUTE(m_app, "/send_difficulty").methods(crow::HTTPMethod::POST)
//        ([&](const crow::request& req, crow::response& res) {
//        auto jsonData = crow::json::load(req.body);
//        if (!jsonData) {
//            res.code = 400;
//            res.write("Invalid JSON data.");
//            res.end();
//            return;
//        }
//
//        int requestedDifficulty = jsonData["difficulty"].i();
//        int currentDifficulty = m_gameLogic.GetMap().getDifficulty();
//
//        if (currentDifficulty != 0) {
//            res.code = 403; // Forbidden
//            res.write("Difficulty already set by another client.");
//            res.end();
//            return;
//        }
//
//        m_gameLogic.GetMap().setDifficulty(requestedDifficulty);
//        m_gameLogic.GetMap().initialize();
//
//        res.code = 200;
//        res.write("Difficulty set successfully.");
//        res.end();
//            });
//
//    CROW_ROUTE(m_app, "/get_difficulty").methods(crow::HTTPMethod::GET)
//        ([&](const crow::request& req, crow::response& res) {
//        int currentDifficulty = m_gameLogic.GetMap().getDifficulty();
//        crow::json::wvalue jsonResponse;
//        jsonResponse["difficulty"] = currentDifficulty;
//
//        res.code = 200;
//        res.write(jsonResponse.dump());
//        res.end();
//            });
//}

void Routing::SetDifficulty()
{
    CROW_ROUTE(m_app, "/send_difficulty").methods(crow::HTTPMethod::POST)
        ([&](const crow::request& req, crow::response& res) {
        auto jsonData = crow::json::load(req.body);
        if (!jsonData) {
            res.code = 400;
            res.write("Invalid JSON data.");
            res.end();
            return;
        }

        int requestedDifficulty = jsonData["difficulty"].i();
        int playerId = jsonData["playerId"].i();
        auto game = m_games.getGameByPlayerId(playerId);

        if (!game) {
            res.code = 404; // Not Found
            res.write("Game not found for the player.");
            res.end();
            return;
        }

        //int currentDifficulty = game->GetMap().getDifficulty();

        auto& mapRef = game->GetMap();
        int currentDifficulty = mapRef.getDifficulty();

        CROW_LOG_INFO << "Current difficulty is: " << currentDifficulty;
        CROW_LOG_INFO << "Difficulty to set: " << requestedDifficulty;

        if (currentDifficulty != 0) {
            res.code = 403; // Forbidden
            res.write("Difficulty already set by another client.");
            res.end();
            return;
        }

        mapRef.setDifficulty(requestedDifficulty);
        mapRef.initialize();

        res.code = 200;
        res.write("Difficulty set successfully.");
        res.end();
            });

    CROW_ROUTE(m_app, "/get_difficulty").methods(crow::HTTPMethod::GET)
        ([&](const crow::request& req, crow::response& res) {
        auto jsonData = crow::json::load(req.body);
        if (!jsonData) {
            res.code = 400;
            res.write("Invalid JSON data.");
            res.end();
            return;
        }

        int playerId = jsonData["playerId"].i();
        auto game = m_games.getGameByPlayerId(playerId);

        if (!game) {
            res.code = 404; // Not Found
            res.write("Game not found for the player.");
            res.end();
            return;
        }

        int currentDifficulty = game->GetMap().getDifficulty();
        crow::json::wvalue jsonResponse;
        jsonResponse["difficulty"] = currentDifficulty;

        res.code = 200;
        res.write(jsonResponse.dump());
        res.end();
            });
}
//
//void Routing::HandlePlayerCommand()
//{
//    CROW_ROUTE(m_app, "/command")
//        .methods("POST"_method)([this](const crow::request& req) {
//
//        auto commandData = crow::json::load(req.body);
//        if (!commandData) {
//            return crow::response(400, "Invalid input");
//        }
//
//        std::string command = commandData["command"].s();
//        int id = commandData["id"].i();
//
//
//        auto it = std::find_if(
//            m_gameLogic.getPlayers().begin(),
//            m_gameLogic.getPlayers().end(),
//            [id](const Player& player) { return player.GetId() == id; }
//        );
//
//        if (it == m_gameLogic.getPlayers().end()) {
//            return crow::response(404, "Player not found");
//        }
//
//        Player& currentPlayer = *it;
//
//        if (command == "MOVE_UP") {
//            m_gameLogic.movePlayer(&currentPlayer, Direction::UP);
//        }
//        else if (command == "MOVE_LEFT") {
//            m_gameLogic.movePlayer(&currentPlayer, Direction::LEFT);
//        }
//        else if (command == "MOVE_DOWN") {
//            m_gameLogic.movePlayer(&currentPlayer, Direction::DOWN);
//        }
//        else if (command == "MOVE_RIGHT") {
//            m_gameLogic.movePlayer(&currentPlayer, Direction::RIGHT);
//        }
//        else if (command == "SHOOT") {
//            Direction dir = currentPlayer.GetFacingDirection();
//            currentPlayer.shoot(dir);
//        }
//        else {
//            return crow::response(400, "Invalid command");
//        }
//        //if (m_gameLogic.WinCondition()) {
//        //    return crow::response(200, crow::json::wvalue{
//        //        {"status", "game_over"},
//        //        {"message", "A player has won the game!"}
//        //        });
//        //}
//        return crow::response(200, "Command processed successfully");
//            });
//}

void Routing::HandlePlayerCommand()
{
    CROW_ROUTE(m_app, "/command")
        .methods("POST"_method)([this](const crow::request& req) {

        auto commandData = crow::json::load(req.body);
        if (!commandData) {
            return crow::response(400, "Invalid input");
        }
        std::cout << "Received JSON: " << req.body << std::endl;

        std::string command = commandData["command"].s();
        int id = commandData["id"].i();


        auto game = m_games.getGameByPlayerId(id);
        if (!game) {
            return crow::response(404, "Game not found for the player");
        }

        auto it = std::find_if(
            game->getPlayers().begin(),
            game->getPlayers().end(),
            [id](const Player& player) { return player.GetId() == id; }
        );

        if (it == game->getPlayers().end()) {
            return crow::response(404, "Player not found in this game");
        }

        Player& currentPlayer = *it;

        if (command == "MOVE_UP") {
            game->movePlayer(&currentPlayer, Direction::UP);
        }
        else if (command == "MOVE_LEFT") {
            game->movePlayer(&currentPlayer, Direction::LEFT);
        }
        else if (command == "MOVE_DOWN") {
            game->movePlayer(&currentPlayer, Direction::DOWN);
        }
        else if (command == "MOVE_RIGHT") {
            game->movePlayer(&currentPlayer, Direction::RIGHT);
        }
        else if (command == "SHOOT") {
            Direction dir = currentPlayer.GetFacingDirection();
            currentPlayer.shoot(dir);
        }
        else {
            return crow::response(400, "Invalid command");
        }

        return crow::response(200, "Command processed successfully");
            });
}

void Routing::CreateGame()
{
    CROW_ROUTE(m_app, "/start_game")
        .methods("POST"_method)([this](const crow::request& req)
            {
                m_games.createNewGame();
                return crow::response(200);
            });
}

//int GameInterface::getActivePlayers()
//{
//    auto response = cpr::Post(cpr::Url{ "http://localhost:18080/get_active_players" });
//
//    if (response.status_code == 200) {
//        auto jsonResponse = crow::json::load(response.text);
//        if (jsonResponse) {
//            return jsonResponse["active_players"].i();
//        }
//    }
//    return -1;
//}
//
//CROW_ROUTE(m_app, "/get_difficulty").methods(crow::HTTPMethod::GET)
//([&](const crow::request& req, crow::response& res) {
//    int currentDifficulty = m_gameLogic.GetMap().getDifficulty();
//    crow::json::wvalue jsonResponse;
//    jsonResponse["difficulty"] = currentDifficulty;
//
//    res.code = 200;
//    res.write(jsonResponse.dump());
//    res.end();
//    });
//
//void Routing::getActivePlayers()
//{
//    CROW_ROUTE(m_app, "/get_active_players").methods("GET"_method)([this](const crow::request& req)
//        {
//            int players = m_gameLogic.getPlayers().size();
//            crow::json::wvalue jsonResponse;
//            jsonResponse["active_players"] = players;
//            return crow::response{ jsonResponse };
//        });
//}

