#include "UIKit.h"
#include "Vaisseau.h"
#include "Laser.h"

#include <conio.h>			// _kbhit() et _getch()
#include <windows.h> // Sleep();
#include <time.h>	 // clock();

#define NOMBRE_COLONNES 80
#define NOMBRE_LIGNES 42

// declaration de fonction
void afficherTerrain(int nbColonnes, int nbLignes);
int directionTouche(int touche);


// declaration des constants
const int nbColonnes = NOMBRE_COLONNES, nbLignes = NOMBRE_LIGNES;

#define MAX_LASER 15

int main(){
	afficherTerrain(nbColonnes, nbLignes);

	// constructeur sans parametre et mettre le vaiseau sur le terrain de jeux
	Vaisseau monVaisseau;
	Laser mesLaser[MAX_LASER];
	int compteur = 0;
	int timerLaser = clock();
	int delaiLaser = 70;

	char direction;
	char touche;

	while (1) {
		// on affiche un compteur en haut à gauche de l'écran
		UIKit::gotoXY(0, 0);
		cout << compteur;
		compteur++;

		if (clock() >= timerLaser + delaiLaser) {
			for (int i = 0; i < MAX_LASER; i++) 
				if (mesLaser[i].isAlive)
					mesLaser[i].moveLaser();

			// gestion des touches du clavier
			if (_kbhit() != 0) {
				touche = _getch();
				direction = directionTouche(touche);


				if (touche == ' ') {
					int i = 0;
					while (i < MAX_LASER && mesLaser[i].isAlive) {
						i++;
					}
					if (i < MAX_LASER) {
						mesLaser[i].startLaser(monVaisseau.coord.getPositionX());
					}
				}
				else if (direction != -1)
					monVaisseau.modifierPosition(direction);
			}
			timerLaser = clock();
		}
	}
	return 0;
}

void afficherTerrain(int nbColonnes, int nbLignes) {
	
	// definir les dimensions de la console
	UIKit::setDimensionFenetre(0, 0, 110, 45); // x1, y1, x2, y2
	
	// afficher le cadre du jeux
	UIKit::cadre(0, 1, nbColonnes, nbLignes, FOREGROUND_RED);
	UIKit::cadre(nbColonnes + 1, 1, nbColonnes + 25, nbLignes, FOREGROUND_GREEN);

	UIKit::curseurVisible(false);

}

int directionTouche(int touche) {
	char direction;

	switch (touche) {
	case 'd': direction = 'l'; // 100 = 'd' (droite)
		break;
	case 68: direction = 'l'; //   68 = 'D' (droite)
		break;
	case 97: direction = 'k'; //   97 = 'a' (gauche)
		break;
	case 65: direction = 'k'; //   65 = 'A' (gauche)
		break;
	default: direction = -1;	
	}

	return direction;
}
