#include "GunDAO.h"

int GunDAO::GetId() const
{
	return m_id;
}
void GunDAO::SetId(int id)
{
	this->m_id = id;
}

double GunDAO::GetFireRate() const
{
	return m_firingRate;
}
void GunDAO::SetFireRate(double fireRate_) {
	this->m_firingRate = fireRate_;
}

double GunDAO::GetBulletSpeed() const {
	return m_bulletSpeed;
}
void GunDAO::SetBulletSpeed(double bulletSpeed) {
	this->m_bulletSpeed = bulletSpeed;
}

