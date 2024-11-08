
#include "PlayerDAO.h"

PlayerDAO::PlayerDAO(std::string name, std::string password) :m_name(name), m_password(password)
{
}

std::string PlayerDAO::GetName() const
{
	return m_name;
}

int PlayerDAO::GetScore() const
{
	return m_score;
}

int PlayerDAO::GetPoints() const
{
	return m_points;
}

std::string PlayerDAO::GetPassword() const
{
	return m_password;
}

