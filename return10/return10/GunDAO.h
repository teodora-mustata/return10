#pragma once

class GunDAO 
{
public:
    int getId() const;
    double getFireRate() const;
    double getBulletSpeed() const;

    void setId(int id);
    void setFireRate(double firingRate);
    void setBulletSpeed(double bulletSpeed);

private:
    int m_id;
    float m_firingRate;
    float m_bulletSpeed;
};