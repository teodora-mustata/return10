#pragma once
#include <variant>
#include "Wall.h"
#include "Player.h"
//#include"TeleportTrap.h"
//#include"DisableGunTrap.h"
//#include"StunTrap.h"

using CellType = std::variant<std::monostate, Wall/*, TeleportTrap, DisableGunTrap, StunTrap*/>;