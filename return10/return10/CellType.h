#pragma once
#include <variant>
#include "Wall.h"
using CellType = std::variant<std::monostate, Wall>;