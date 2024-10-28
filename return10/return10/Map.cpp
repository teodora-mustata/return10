#include "Map.h"

CellType Map::get_cell_type(int x, int y)
{
	return board[x][y];
}
