#include "Shop.h"
#include <iostream>


const int SPEED_UPGRADE_COST = 10;
const int RELOAD_UPGRADE_COST = 500;

Shop::Shop() {}

void Shop::buySpeedUpgrade(Player player) {
    Gun gun = player.getGun();
    if (player.GetCrowns() >= SPEED_UPGRADE_COST)
    {
        float currentSpeed = gun.GetBulletSpeed();
        gun.setBulletSpeed(currentSpeed * 2.0f);
        player.addScore(-SPEED_UPGRADE_COST);
        std::cout << "Bullet speed has been doubled! New speed: " << gun.GetBulletSpeed() << std::endl;
    }
}

void Shop::buyReloadUpgrade(Player player)
{
    Gun gun = player.getGun();
    if (player.GetCrowns() < RELOAD_UPGRADE_COST) {
        std::cout << "Insufficient crowns to buy upgrade!" << std::endl;
        return;
    }

    auto currentFiringRate = gun.getFiringRate();
    if (currentFiringRate <= std::chrono::duration<float>(0.25)) {
        std::cout << "Gun is already fully upgraded!" << std::endl;
        return;
    }

    gun.setFiringRate(currentFiringRate / 2);

    player.addScore(-RELOAD_UPGRADE_COST);

    std::cout << "Gun upgraded! New firing rate: " << currentFiringRate.count() / 2 << " seconds" << std::endl;
}
