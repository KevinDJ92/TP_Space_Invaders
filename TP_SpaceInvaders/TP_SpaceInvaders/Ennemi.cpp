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
	isAlive = true;
	putExtraTerrestre();
	nombreExtraTerrestre++;
}


void Ennemi::setPositionAlien(int positionY, int symbole, int incrementation)
{
	coord.setPositionY(positionY);
	coord.setPositionX(31 + (incrementation) * 3);
	setEnnemi(symbole, 3);
}
void Ennemi::deadEnnemi() {
	this->valeurExtraTerrestre = 0;
	isAlive = false;
	removeExtraTerrestre();
	nombreExtraTerrestre--;
}
