#include "Shop.h"
#include <iostream>


const int SPEED_UPGRADE_COST = 10;
const int RELOAD_UPGRADE_COST = 500;

Shop::Shop() {}

void Shop::buySpeedUpgrade(Player player) {
    Gun gun = player.getGun();
    if (player.GetCrowns() >= SPEED_UPGRADE_COST)
    {
        // Double the speed of the bullet
        float currentSpeed = gun.GetBulletSpeed();
        gun.SetBulletSpeed(currentSpeed * 2.0f);
        player.addCrowns(-SPEED_UPGRADE_COST);
        std::cout << "Bullet speed has been doubled! New speed: " << gun.GetBulletSpeed() << std::endl;
    }
}

void Shop::buyReloadUpgrade(Player player)
{
    // Accesam arma jucatorului
    Gun gun = player.getGun();//am nevoie de getGun in player

    // Verificam daca jucatorul are suficient scor
    if (player.GetCrowns() < RELOAD_UPGRADE_COST) {
        std::cout << "Insufficient crowns to buy upgrade!" << std::endl;
        return;
    }

    // Verificam daca arma poate fi upgradata
    auto currentFiringRate = gun.getFiringRate();//am nevoie de getFiringRate in Gun
    if (currentFiringRate <= std::chrono::duration<float>(0.25)) {
        std::cout << "Gun is already fully upgraded!" << std::endl;
        return;
    }

    // Realizam upgrade-ul
    gun.setFiringRate(currentFiringRate / 2);//am nevoie de setFiringRate in Gun

    // Scadem 500 din scorul jucatorului
    player.addCrowns(-RELOAD_UPGRADE_COST);

    std::cout << "Gun upgraded! New firing rate: " << currentFiringRate.count() / 2 << " seconds" << std::endl;
}
