#pragma once
#include <variant>
#include "Wall.h"
#include "Player.h"

using CellType = std::variant<std::monostate, Wall>;