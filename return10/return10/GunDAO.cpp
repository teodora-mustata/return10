#include "GunDAO.h"

int GunDAO::getId() const
{
	return m_id;
}
void GunDAO::setId(int id)
{
	this->m_id = id;
}

double GunDAO::getFireRate() const
{
	return m_firingRate;
}
void GunDAO::setFireRate(double fireRate_) {
	this->m_firingRate = fireRate_;
}

double GunDAO::getBulletSpeed() const {
	return m_bulletSpeed;
}
void GunDAO::setBulletSpeed(double bulletSpeed) {
	this->m_bulletSpeed = bulletSpeed;
}

