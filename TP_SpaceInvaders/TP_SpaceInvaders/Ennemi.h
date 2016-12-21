#pragma once
#include "Martien.h"

class Ennemi : public ExtraTerrestre {
public:
	Ennemi();
	void jiggleMartien(bool jiggle);
	void setEnnemi(int type, int valeur);
	void setPositionAlien(int positionY, int symbole, int incrementation);
};