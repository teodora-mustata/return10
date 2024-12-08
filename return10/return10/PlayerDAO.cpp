
#include "PlayerDAO.h"

PlayerDAO::PlayerDAO(int id,std::string name, std::string password) :m_id(id),m_name(name), m_password(password)
{
}

PlayerDAO::PlayerDAO(std::string name, std::string password): m_name(name), m_password(password)
{
}

std::string PlayerDAO::GetName() const
{
	return m_name;
}

int PlayerDAO::GetCrowns() const
{
	return m_score;
}

int PlayerDAO::GetScore() const
{
	return m_crowns;
}

std::string PlayerDAO::GetPassword() const
{
	return m_password;
}

int PlayerDAO::GetId() const
{
	return m_id;
}

int PlayerDAO::GetGunId() const
{
	return m_gunId;
}

void PlayerDAO::SetId(int id)
{
	this->m_id = id;
}

void PlayerDAO::SetName(std::string name) 
{
	this->m_name = name;
}

void PlayerDAO::SetCrowns(int score)
{
	this->m_score = score;
}

void PlayerDAO::SetPoints(int points)
{
	this->m_crowns = points;
}

void PlayerDAO::SetPassword(std::string password)
{
	this->m_password = password;
}

void PlayerDAO::SetGunId(int gunId)
{
	this->m_gunId = gunId;
}



