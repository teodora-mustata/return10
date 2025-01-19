
#include "PlayerDAO.h"

PlayerDAO::PlayerDAO(int id,std::string name, std::string password) :m_id(id),m_name(name), m_password(password)
{
}

PlayerDAO::PlayerDAO(std::string name, std::string password): m_name(name), m_password(password)
{
}

std::string PlayerDAO::getName() const
{
	return m_name;
}

int PlayerDAO::getCrowns() const
{
	return m_crowns;
}

int PlayerDAO::getScore() const
{
	return m_score;
}

std::string PlayerDAO::getPassword() const
{
	return m_password;
}

int PlayerDAO::getId() const
{
	return m_id;
}

int PlayerDAO::getGunId() const
{
	return m_gunId;
}

void PlayerDAO::setId(int id)
{
	this->m_id = id;
}

void PlayerDAO::setName(std::string name) 
{
	this->m_name = name;
}

void PlayerDAO::setCrowns(int crowns)
{
	this->m_crowns = crowns;
}

void PlayerDAO::setScore(int score)
{
	this->m_score = score;
}

void PlayerDAO::setPassword(std::string password)
{
	this->m_password = password;
}

void PlayerDAO::setGunId(int gunId)
{
	this->m_gunId = gunId;
}



