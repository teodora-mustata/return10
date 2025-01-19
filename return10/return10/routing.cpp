#include "routing.h"
#include "Map.h"

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

Routing::Routing(GameStorage& storage, GameManager& gameLogic):m_storage(storage),m_games(gameLogic)
{
}

void Routing::run() {

    setupLoginRoutes();
    getTheBestPlayersByCrowns();
    getTheBestPlayersByScore();
    buyReloadSpeedUpgrade();
    buyBulletSpeedUpgrade();
    setupGameRoute();
    getActivePlayers();
    setDifficulty();
    addPlayerToLobby();
    createGame();
    handlePlayerCommand();
    updateMap();
    checkWinCondition();
    m_app.port(18080).multithreaded().run();
}

void Routing::getTheBestPlayersByScore() {
    CROW_ROUTE(m_app, "/leaderboard/score/<int>")
        ([this](int userId) {
        try {
            auto players = m_storage.getPlayersDAO();

            std::sort(players.begin(), players.end(), [](const PlayerDAO& a, const PlayerDAO& b) {
                return a.getScore() > b.getScore();
                });

            crow::json::wvalue res;
            std::vector<crow::json::wvalue> topPlayers;
            bool isUserInTop10 = false;
            int userRank = -1;

            for (size_t i = 0; i < players.size(); ++i) {
                if (i < 10) {
                    crow::json::wvalue playerJson;
                    playerJson["rank"] = i + 1;
                    playerJson["name"] = players[i].getName();
                    playerJson["score"] = players[i].getScore();
                    topPlayers.push_back(std::move(playerJson));
                }
                if (players[i].getId() == userId) {
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
                res["currentUser"]["name"] = players[userRank - 1].getName();
                res["currentUser"]["score"] = players[userRank - 1].getScore();
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
    auto players = m_storage.getPlayersDAO();
    for (const auto& player : players) {
        if (player.getId() == userId) {
            return player;
        }
    }
    throw std::runtime_error("Player not found with ID: " + std::to_string(userId));
}


GunDAO Routing::getGunById(int gunId)
{
    auto guns = m_storage.getGunsDAO();
    for (const auto& gun : guns) {
        if (gun.getId() == gunId) {
            return gun;
        }
    }
    throw std::runtime_error("Gun not found with ID: " + std::to_string(gunId));
}

void Routing::getTheBestPlayersByCrowns() {
    CROW_ROUTE(m_app, "/leaderboard/<int>")
        ([this](int userId) {
        try {
            auto players = m_storage.getPlayersDAO();

            std::sort(players.begin(), players.end(), [](const PlayerDAO& a, const PlayerDAO& b) {
                return a.getCrowns() > b.getCrowns();
                });

            crow::json::wvalue res;
            std::vector<crow::json::wvalue> topPlayers;
            bool isUserInTop10 = false;
            int userRank = -1;

            for (size_t i = 0; i < players.size(); ++i) {
                if (i < 10) {
                    crow::json::wvalue playerJson;
                    playerJson["rank"] = i + 1;
                    playerJson["name"] = players[i].getName();
                    playerJson["crowns"] = players[i].getCrowns();
                    topPlayers.push_back(std::move(playerJson));
                }
                if (players[i].getId() == userId) {
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
                res["currentUser"]["name"] = players[userRank - 1].getName();
                res["currentUser"]["crowns"] = players[userRank - 1].getCrowns();
            }

            return crow::response(200, res);
        }
        catch (const std::exception& e) {
            return crow::response(500, std::string("Database error: ") + e.what());
        }
            });
}

void Routing::setupLoginRoutes()
{
    CROW_ROUTE(m_app, "/login").methods("POST"_method)([this](const crow::request& req) {
        auto body = crow::json::load(req.body);
        if (!body) {
            return crow::response(400, "Invalid JSON format");
        }

        std::string username = body["username"].s();
        std::string password = body["password"].s();

        try {
            auto players = m_storage.getPlayersDAO();
            auto it = std::find_if(players.begin(), players.end(), [&](const PlayerDAO& player) {
                return player.getName() == username && player.getPassword() == password;
                });

            if (it == players.end()) {
                return crow::response(401, "Invalid username or password!");
            }

            const auto& user = *it;

            crow::json::wvalue gunDetails;
            if (user.getGunId() != -1) {
                auto gun = m_storage.getGunById(user.getGunId());
                gunDetails["fireRate"] = gun.getFireRate();
                gunDetails["bulletSpeed"] = gun.getBulletSpeed();
            }
            else {
                gunDetails = crow::json::wvalue();
            }

            crow::json::wvalue res;
            res["message"] = "Welcome " + user.getName() + "!";
            res["score"] = user.getScore();
            res["crowns"] = user.getCrowns();
            res["gunDetails"] = std::move(gunDetails);
            res["userId"] = user.getId();
            return crow::response(200, res);
        }
        catch (const std::exception& e) {
            return crow::response(500, std::string("Database error: ") + e.what());
        }
        });

    CROW_ROUTE(m_app, "/signup").methods("POST"_method)([this](const crow::request& req) {
        auto body = crow::json::load(req.body);

        if (!body) {
            return crow::response(400, "Invalid JSON format");
        }

        std::string username = body["username"].s();
        std::string password = body["password"].s();

        std::regex passwordRegex("^(?=.*[A-Z])(?=.*[0-9])(?=.*[!@#$%^&*]).{8,}$");
        if (!std::regex_match(password, passwordRegex)) {
            return crow::response(400, "Password does not meet complexity requirements");
        }

        auto players = m_storage.getPlayersDAO();
        for (const auto& player : players) {
            if (player.getName() == username) {
                return crow::response(409, "Username already exists");
            }
        }

        GunDAO newGun;
        newGun.setFireRate(4);
        newGun.setBulletSpeed(0.25);

        int gunId = m_storage.addGunDAO(newGun);

        PlayerDAO newPlayer;
        newPlayer.setName(username);
        newPlayer.setPassword(password);
        newPlayer.setCrowns(0); 
        newPlayer.setScore(0);
        newPlayer.setGunId(gunId);

        m_storage.addPlayerDAO(newPlayer);

        return crow::response(201, "Account created successfully!");
        });
}


void Routing::sendMap(crow::response& res, int playerId)
{
    try {
        auto game = m_games.getGameByPlayerId(playerId);

        if (!game) {
            CROW_LOG_INFO << "Game not found for player ID: " << playerId;
            res.code = 404;
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
        res.set_header("Content-Type", "application/json");
        res.write(mapJson.dump());
        res.code = 200;
    }
    catch (const std::exception& e) {
        CROW_LOG_ERROR << "Error in sendMap: " << e.what();
        res.code = 500;
        res.write(std::string("Internal server error: ") + e.what());
    }
    res.end();
}

void Routing::setupGameRoute()
{
    CROW_ROUTE(m_app, "/map").methods(crow::HTTPMethod::POST)([this](const crow::request& req, crow::response& res) {
        auto jsonData = crow::json::load(req.body);
        if (!jsonData || !jsonData.has("playerId")) {
            res.code = 400;
            res.write("Invalid JSON data.");
            res.end();
            return;
        }

        int playerId = jsonData["playerId"].i();
        CROW_LOG_INFO << "Fetching map for player ID: " << playerId;

        sendMap(res, playerId);
        });

}


void Routing::buyReloadSpeedUpgrade() {

    CROW_ROUTE(m_app, "/upgrade/reload_speed/<int>")
        ([this](int userId) {
        try {
            PlayerDAO player = m_storage.getPlayerByID(userId);

            if (player.getId() == 0) {
                crow::json::wvalue res;
                res["error"] = "User not found";
                return crow::response(404, res);
            }

            GunDAO gun = m_storage.getGunById(player.getGunId());
            if (gun.getId() == 0) {
                crow::json::wvalue res;
                res["error"] = "Gun not found for this player";
                return crow::response(404, res);
            }



            const int upgradeCost = 500;
            const double minReloadSpeed = 0.25;

            if (gun.getFireRate() <= minReloadSpeed) {
                crow::json::wvalue res;
                res["error"] = "Reload speed is already at minimum value";
                return crow::response(400, res);
            }


            if (player.getScore() < upgradeCost) {
                crow::json::wvalue res;
                res["error"] = "Not enough score to buy upgrade";
                return crow::response(400, res);
            }

            player.setScore(player.getScore() - upgradeCost);
            gun.setFireRate(std::max(gun.getFireRate() / 2.0, minReloadSpeed));

            m_storage.updatePlayerDAO(player);
            m_storage.updateGunDAO(gun);

            crow::json::wvalue res;
            res["message"] = "Reload speed upgrade purchased successfully!";
            res["remainingScore"] = player.getScore();
            res["newReloadSpeed"] = gun.getFireRate();

            return crow::response(200, res);
        }
        catch (const std::exception& e) {
            crow::json::wvalue res;
            res["error"] = std::string("Database error: ") + e.what();
            return crow::response(500, res);
        }
            });
}

void Routing::buyBulletSpeedUpgrade() {
    CROW_ROUTE(m_app, "/upgrade/bullet_speed/<int>")
        ([this](int userId) {
        try {
            PlayerDAO player = getPlayerById(userId);
            if (player.getId() == 0) {
                crow::json::wvalue res;
                res["error"] = "User not found";
                return crow::response(404, res);
            }

            GunDAO gun = getGunById(player.getGunId());
            if (gun.getId() == 0) {
                crow::json::wvalue res;
                res["error"] = "Gun not found for this player";
                return crow::response(404, res);
            }

            const float maxBulletSpeed = 0.5;
            const int requiredCrowns = 10;

            if (gun.getBulletSpeed() >= maxBulletSpeed) {
                crow::json::wvalue res;
                res["error"] = "Bullet speed is already at maximum value";
                return crow::response(400, res);
            }


            if (player.getCrowns() < requiredCrowns) {
                crow::json::wvalue res;
                res["error"] = "Not enough crowns to upgrade bullet speed";
                return crow::response(400, res);
            }


            gun.setBulletSpeed(maxBulletSpeed);

            m_storage.updateGunDAO(gun);

            crow::json::wvalue res;
            res["message"] = "Bullet speed upgrade applied successfully!";
            res["newBulletSpeed"] = gun.getBulletSpeed();
            res["remainingCrowns"] = player.getCrowns();

            return crow::response(200, res);
        }
        catch (const std::exception& e) {
            crow::json::wvalue res;
            res["error"] = std::string("Database error: ") + e.what();
            return crow::response(500, res);
        }
            });
}

void Routing::addPlayerToLobby()
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

            PlayerDAO player_data = m_storage.getPlayerByID(player_id);

            if (player_data.getId() == 0) {
                res.code = 404;
                res.body = "Player not found!";
                res.end();
                return;
            }

            CROW_LOG_INFO << "Adding player " << player_id << " to lobby.";
            m_games.addPlayerToLobby(player_id);

            res.code = 200;
        }
        catch (const std::exception& e) {
            res.code = 500;
            res.body = std::string("Internal server error: ") + e.what();
        }

        res.end();
        });
}


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
        .methods("POST"_method)([&](const crow::request& req, crow::response& res) {
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

void Routing::checkWinCondition()
{
    CROW_ROUTE(m_app, "/check_win_condition")
        .methods("GET"_method)([&](const crow::request& req, crow::response& res) {
        try {
            auto jsonData = crow::json::load(req.body);

            if (!jsonData || !jsonData.has("id")) {
                res.code = 400;
                res.end();
                return;
            }

            int userId = jsonData["id"].i();

            auto game = m_games.getGameByPlayerId(userId);
            if (!game) {
                std::cerr << "Error: game pointer is null!" << std::endl;
                res.code = 500;
                res.body = "Internal server error: Game not found.";
                res.end();
                return;
            }

            int winCondition = game->checkIfRunning();
            std::cout << "Win condition: " << winCondition << std::endl;
                
            if (winCondition == 0)
            {
                game->giveCrowns();
                for (auto player : game->getPlayers())
                {
                    m_games.updatePlayerScore(player);
                }
            }

            crow::json::wvalue response;
            response["win_condition"] = winCondition;

            res.code = 200;
            res.body = response.dump();
            res.end();
        }
        catch (const std::exception& e) {
            res.code = 500;
            res.body = std::string("Internal server error: ") + e.what();
            res.end();
        }
            });
}


void Routing::setDifficulty()
{
http://localhost:18080/send_difficulty
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
            res.code = 404;
            res.write("Game not found for the player.");
            res.end();
            return;
        }

        auto& mapRef = game->GetMap();
        int currentDifficulty = mapRef.getDifficulty();

        CROW_LOG_INFO << "Current difficulty is: " << currentDifficulty;
        CROW_LOG_INFO << "Difficulty to set: " << requestedDifficulty;

        if (currentDifficulty != 0) {
            res.code = 403;
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
            res.code = 404;
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


void Routing::handlePlayerCommand()
{
    CROW_ROUTE(m_app, "/command").methods("POST"_method)([this](const crow::request& req, crow::response& res) {
        try {
            auto commandData = crow::json::load(req.body);
            if (!commandData || !commandData.has("command") || !commandData.has("id")) {
                res.code = 400;
                res.write("Invalid input");
                res.end();
                return;
            }

            std::string command = commandData["command"].s();
            int playerId = commandData["id"].i();

            auto game = m_games.getGameByPlayerId(playerId);
            if (!game) {
                res.code = 404;
                res.write("Game not found for the player");
                res.end();
                return;
            }

            auto it = std::find_if(
                game->getPlayers().begin(),
                game->getPlayers().end(),
                [playerId](const Player& player) { return player.getId() == playerId; });

            if (it == game->getPlayers().end()) {
                res.code = 404;
                res.write("Player not found in this game");
                res.end();
                return;
            }

            Player& currentPlayer = *it;
            Direction dir;

            if (command == "MOVE_UP") dir = Direction::UP;
            else if (command == "MOVE_LEFT") dir = Direction::LEFT;
            else if (command == "MOVE_DOWN") dir = Direction::DOWN;
            else if (command == "MOVE_RIGHT") dir = Direction::RIGHT;
            else if (command == "SHOOT") {
                dir = currentPlayer.getFacingDirection();
                Coordinate nextPosition = game->getNextPosition(currentPlayer.getPosition(), dir);
                if (!game->isInsideMap(nextPosition)) {
                    res.code = 400;
                    res.write("Cannot shoot outside the map");
                    res.end();
                    return;
                }
                currentPlayer.shoot(dir);
                res.code = 200;
                res.write("Command processed successfully");
                res.end();
                return;
            }
            else {
                res.code = 400;
                res.write("Invalid command");
                res.end();
                return;
            }

            game->movePlayer(&currentPlayer, dir);
            res.code = 200;
            res.write("Command processed successfully");
        }
        catch (const std::exception& e) {
            CROW_LOG_ERROR << "Error in HandlePlayerCommand: " << e.what();
            res.code = 500;
            res.write(std::string("Internal server error: ") + e.what());
        }
        res.end();
        });
}

void Routing::createGame()
{
    CROW_ROUTE(m_app, "/start_game")
        .methods("POST"_method)([this](const crow::request& req)
            {
                m_games.createNewGame();
                return crow::response(200);
            });
}

