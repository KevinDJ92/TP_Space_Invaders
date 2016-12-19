#include "UIKit.h"
#include "Vaisseau.h"
#include <conio.h>			// _kbhit() et _getch()

#define NOMBRE_COLONNES 70
#define NOMBRE_LIGNES 42

// declaration de fonction
void afficherTerrain(int nbColonnes, int nbLignes);
int recupererTouche();
int directionTouche(int touche);

// declaration des constants
const int nbColonnes = NOMBRE_COLONNES, nbLignes = NOMBRE_LIGNES;

int main(){

	afficherTerrain(nbColonnes, nbLignes);

	// mettre le vaiseau sur le terrain de jeux
	Vaisseau();
	
	recupererTouche();

	return 0;
}

void afficherTerrain(int nbColonnes, int nbLignes) {
	// afficher le cadre du jeux
	UIKit::cadre(0, 1, nbColonnes, nbLignes, FOREGROUND_RED);
	
	UIKit::curseurVisible(false);
}

int recupererTouche() {
	int touche = -1;
		
	if (_kbhit())
		touche = _getch();

	return touche;
}

int directionTouche(int touche) {
	int direction;

	switch (touche) {
	case 100: direction = 0; // 'd' = droite
		break;
	case 68: direction = 0; // 'D' = droite
		break;
	case 97: direction = 1; // 'a' = gauche
		break;
	case 65: direction = 1; // 'A' = gauche
		break;
	default: direction = -1;	
	}

	return direction;
}
