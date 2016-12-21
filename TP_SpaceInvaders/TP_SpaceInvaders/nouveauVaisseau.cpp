#include "nouveauVaisseau.h"
#include <iostream>
using namespace std;

nouveauVaisseau::nouveauVaisseau() 
{
	vaisseau = "_/\/\_";
}

void nouveauVaisseau::putNouveauVaisseau() const
{
	coord.gotoXY(coord.getPositionX(), coord.getPositionY());
	cout << vaisseau;
}
void nouveauVaisseau::removeVaisseau() const
{
	coord.gotoXY(coord.getPositionX(), coord.getPositionY());
	cout << "     ";
}