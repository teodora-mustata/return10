#pragma once

class GunDAO {
private:
    int m_id;
    float m_firingRate;
    float m_bulletSpeed;
public:
    int GetId() const;
    void SetId(int id);

    double GetFireRate() const;
    void SetFireRate(double firingRate);

    double GetBulletSpeed() const;
    void SetBulletSpeed(double bulletSpeed);
};