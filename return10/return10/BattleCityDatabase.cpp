#include "BattleCityDatabase.h"

bool GameStorage::Initialize() {
    // Sincronizeaza schema bazei de date, creând tabelele necesare, dar fara a adauga date
    m_db.sync_schema();

    std::cout << "Database schema synchronized. No players or guns were added initially." << std::endl;

    // Returneaza true pentru a confirma ca tabelele au fost create cu succes
    return true;
}


void GameStorage::AddPlayers(const std::vector<Player>& players)
{
    for (const Player& player : players)
    {
        int gunId;
        GunDAO gunDAO;
        const Gun& playerGun = player.getGun();

        gunDAO.SetFireRate(playerGun.GetFiringRate());
        gunDAO.SetBulletSpeed(playerGun.GetBulletSpeed());

        gunId = m_db.insert(gunDAO);  // Inseram gun-ul în baza de date
        // Cream PlayerDAO pentru a adauga player-ul în baza de date
        PlayerDAO playerDAO;
        playerDAO.SetName(player.GetName());
        playerDAO.SetPoints(player.GetScore());
        playerDAO.SetScore(player.GetCrowns());
        playerDAO.SetGunId(gunId);  // Setam gunId-ul asociat player-ului

        // Adaugam player-ul în baza de date
        m_db.insert(playerDAO);
    }
}



//void GameStorage::PopulateStorage()
//{
//	/*std::vector<Product> products{
//			Product{ -1, "Milk",  5.f },
//			Product{ -1, "Egg",   0.2f },
//			Product{ -1, "Flour", 2.f },
//			Product{ -1, "Butter", 8.f },
//			Product{ -1, "Salt",  2.f },
//			Product{ -1, "Jam",   5.f }
//	};*/
//	m_db.insert_range(products.begin(), products.end());
//}

