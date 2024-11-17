
#pragma once
#include <string>
class PlayerDAO
{
public:
	PlayerDAO(std::string name, std::string password);
	PlayerDAO();
	std::string GetName() const;
	int GetScore() const;
	int GetPoints()const;
	std::string GetPassword() const;
private:
	int m_score;
	int m_points;
	std::string m_name;
	float m_gun;//defaft ar trebui un GunDAO
	std::string m_password;
};


