#pragma once

class GunDAO 
{
public:
    int GetId() const;
    double GetFireRate() const;
    double GetBulletSpeed() const;

    void SetId(int id);
    void SetFireRate(double firingRate);
    void SetBulletSpeed(double bulletSpeed);

private:
    int m_id;
    float m_firingRate;
    float m_bulletSpeed;
};