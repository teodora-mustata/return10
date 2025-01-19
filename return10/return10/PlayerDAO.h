#pragma once
#include <string>
class PlayerDAO
{
public:
	PlayerDAO(int id, std::string name, std::string password);
	PlayerDAO(std::string name, std::string password);
	PlayerDAO() = default;

	std::string getName() const;
	int getCrowns() const;
	int getScore() const;
	std::string getPassword() const;
	int getId() const;
	int getGunId()const;

	void setId(int id);
	void setName(std::string name);
	void setCrowns(int crowns);
	void setScore(int score);
	void setPassword(std::string password);
	void setGunId(int gunId);

private:
	int m_id;
	int m_score;
	int m_crowns;
	std::string m_name;
	int m_gunId;
	std::string m_password;
};


