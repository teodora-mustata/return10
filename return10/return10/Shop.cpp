#include "Shop.h"
#include <iostream>


Shop::Shop() {}
//wouldnt it make more sens if we had a bulletSpeed for each actual gun not each individual bullet that can be modified because 
//this basically only speeds up existing fired bullets but we need an effect that modifies the speed of any incoming bullets for a time
void Shop::buySpeedUpgrade(Player& player) {
    Gun* gun = player.getGun(); //i need a getter for a gun so i can update that player's bullet speed for his certain gun i think

    if (gun != nullptr) {
        Bullet* bullet = gun->getBullets();

        if (bullet != nullptr && player.GetScore() >= 100) { //i think i actually need the crowns here which i dont have a getter and setter for yet
            // Double the speed of the bullet
            float currentSpeed = bullet->getSpeed();
            bullet->setSpeed(currentSpeed * 2.0f);
            //player.SetScore(player.GetScore() - 100); //take away the crowns/score not sure

            std::cout << "Bullet speed has been doubled! New speed: " << bullet->getSpeed() << std::endl;
        }
        else {
            std::cout << "No bullet found for this gun." << std::endl;
        }
    }
    else {
        std::cout << "Player has no gun equipped." << std::endl;
    }
}

void Shop::buyReloadUpgrade(Player& player)
{
    // Accesam arma jucatorului
    Gun& gun = player.getGun();//am nevoie de getGun in player

    // Verificam daca jucatorul are suficient scor
    if (player.GetScore() < 500) {
        std::cout << "Insufficient score to buy upgrade!" << std::endl;
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
    player.addScore(-500);

    std::cout << "Gun upgraded! New firing rate: " << currentFiringRate.count() / 2 << " seconds" << std::endl;
}
