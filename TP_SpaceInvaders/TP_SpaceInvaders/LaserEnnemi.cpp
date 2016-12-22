#include "LaserEnnemi.h"

#define NOMBRE_LIGNES 42

void LaserEnnemi::movelaser()
{
	removeLaser();
	if (coord.getPositionY() < NOMBRE_LIGNES)
	{
		coord.setPositionY(coord.getPositionY() + 1);
		putLaser();
	}
	else
		isAlive = false;
}
