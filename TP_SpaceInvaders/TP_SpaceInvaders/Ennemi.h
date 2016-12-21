#pragma once
#include "Martien.h"
#include "ExtraTerrestre.h"

class Ennemi: public Martien {
private:
	Martien::Martien;
	int nbEnnemi;


public:
	Ennemi();
};