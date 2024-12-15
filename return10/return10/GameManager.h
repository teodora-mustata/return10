#pragma once
#include <vector>
#include <thread>

class GameManager
{
public:

private:
	std::vector<int> loggedPlayers; // all players connected to the server
	std::vector<int> inGamePlayers; // players currently playing a game
	std::vector<std::thread> games;
};

