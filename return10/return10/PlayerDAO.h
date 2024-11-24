#pragma once
#include <string>
class PlayerDAO
{
public:
	PlayerDAO(int id, std::string name, std::string password);
	PlayerDAO(std::string name, std::string password);
	PlayerDAO() = default;
	std::string GetName() const;
	int GetScore() const;
	int GetPoints()const;
	std::string GetPassword() const;
	int GetId() const;
	int GetGunId()const;
	void SetId(int id);
	void SetName(std::string name);
	void SetScore(int score);
	void SetPoints(int points);
	void SetPassword(std::string password);
	void SetGunId(int gunId);
private:
	int m_id;
	int m_score;
	int m_points;
	std::string m_name;
	int m_gunId;//defaft ar trebui un GunDAO
	std::string m_password;
};


