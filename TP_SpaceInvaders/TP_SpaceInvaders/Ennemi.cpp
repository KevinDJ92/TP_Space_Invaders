#include "Ennemi.h"

Ennemi::Ennemi()
	:ExtraTerrestre(0, 0)
{

}

void Ennemi::jiggleMartien(bool gauche)
{
	removeExtraTerrestre();

	if (gauche)
		coord.setPositionX(coord.getPositionX() - 1);
	else
		coord.setPositionX(coord.getPositionX() + 1);

	gauche = !gauche;

	putExtraTerrestre();
}

void Ennemi::setEnnemi(int type, int valeur)
{
	this->typeExtraTerrestre = type;
	this->valeurExtraTerrestre = valeur;
	putExtraTerrestre();
}

