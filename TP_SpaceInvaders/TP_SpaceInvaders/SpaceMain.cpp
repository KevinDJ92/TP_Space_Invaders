#include "UIKit.h"
#include "Vaisseau.h"
#include "Laser.h"
#include "Martien.h"
#include "Ennemi.h"

#include <conio.h>			// _kbhit() et _getch()
#include <time.h>	 // clock();

#define NOMBRE_COLONNES 80
#define NOMBRE_LIGNES 42

// declaration de fonction
void afficherTerrain(int nbColonnes, int nbLignes);
int directionTouche(int touche);
void titreDeroulant();
void bougerEnnemi(Ennemi race[], int nbAlien, bool &gauche);

// declaration des constants
const int nbColonnes = NOMBRE_COLONNES, nbLignes = NOMBRE_LIGNES;

#define MAX_LASER 15
#define NB_VENUSIEN 5
#define NB_SATURIEN 5

int main() {
	// titre Space Invaders qui descend progressivement 
	titreDeroulant();

	afficherTerrain(nbColonnes, nbLignes);

	// mettre le vaiseau sur le terrain de jeux
	Vaisseau monVaisseau;

	Laser mesLaser[MAX_LASER];

	// Ennemi
	int timerEnnemi = clock();
	int delaiEnnemi = 500;

	// Laser
	int timerLaser = clock();
	int delaiLaser = 70;

	char direction;
	char touche;
	int compteur = 0;

	Ennemi venusien[NB_VENUSIEN];
	Ennemi saturien[NB_SATURIEN];

	// mettre les extraterrestres a leur position de depart
	UIKit::color(FOREGROUND_RED + FOREGROUND_GREEN);
	for (int i = 0; i < NB_VENUSIEN; i++) {
		venusien[i].setPositionAlien(10, '@', i);
	}
	//UIKit::color(FOREGROUND_BLUE + FOREGROUND_GREEN);
	for (int i = 0; i < NB_VENUSIEN; i++) {
		saturien[i].setPositionAlien(12, '#', i);
	}
	bool gauche = false;

	while (1) {
		if (clock() >= timerEnnemi + delaiEnnemi) {
			bougerEnnemi(venusien, NB_VENUSIEN, gauche);
			bougerEnnemi(saturien, NB_SATURIEN, gauche);
			timerEnnemi = clock();
		}
			/*
		if (venusien[0].coord.getPositionX() == 20) {
			gauche = true;
			for (int i = 0; i < MAX_ENNEMIS; i++) {
				venusien[i].removeExtraTerrestre();
				venusien[i].coord.setPositionY(venusien[i].coord.getPositionY() + 1);
			}
		}
		else if (venusien[0].coord.getPositionX() == 10) {
			gauche = false;
			for (int i = 0; i < MAX_ENNEMIS; i++) {
				venusien[i].removeExtraTerrestre();
				venusien[i].coord.setPositionY(venusien[i].coord.getPositionY() + 1);
			}
		}

		for (int j = 0; j < MAX_ENNEMIS; j++) {
			venusien[j].jiggleMartien(gauche);
		}
		timerEnnemi = clock();
	}*/

		if (clock() >= timerLaser + delaiLaser) {
			// on affiche un compteur en haut à gauche de l'écran
			UIKit::gotoXY(0, 0);
			cout << compteur;
			compteur++;

			for (int i = 0; i < MAX_LASER; i++)
				if (mesLaser[i].isAlive)
					if (mesLaser[i].coord.getPositionY() != 2)
						mesLaser[i].moveLaser();
					else
						mesLaser[i].killLaser();

			// gestion des touches du clavier
			if (_kbhit() != 0) {
				touche = _getch();

				// si la touche espace est pesée
				if (touche == ' ') {
					int i = 0;

					//	recherche d'une instance de laser non utilisée
					while (i < MAX_LASER && mesLaser[i].isAlive)
						i++;
					// creer un laser si le maximum n'est pas atteint
					if (i < MAX_LASER)
						mesLaser[i].startLaser(monVaisseau.coord.getPositionX());
				}
				else {
					direction = directionTouche(touche);

					if (direction != -1) {
						if (monVaisseau.coord.getPositionX() == 2) {
							if (direction != 'k')
								monVaisseau.modifierPosition(direction);
						}
						else if (monVaisseau.coord.getPositionX() == nbColonnes - 1) {
							if (direction != 'l')
								monVaisseau.modifierPosition(direction);
						}
						else
							monVaisseau.modifierPosition(direction);
					}
				}
			}
			timerLaser = clock();
		}
	}
	return 0;
}

void titreDeroulant() {
	int positionMenuY = 3;
	int delaiMenu = 150;
	int timerMenu = clock();
	bool jouerPartie = false;

	while (!jouerPartie) {
		if (clock() >= timerMenu + delaiMenu) {
			// titre SPACE INVADERS
			system("cls");
			UIKit::gotoXY(0, positionMenuY);
			cout << " _______  _____  _______ _______ _______      _____ __   _ _    _ _______ ______  _______  ______ "<< endl;
			cout << "	| ______ | _____] | _____ | | | ______ | | \ | \ / | _____ | | \ | ______ | _____ / | ______   " << endl;
			cout << "	______ | | | | | _____ | ______      __ | __ | \_ | \ / | | | _____ / | ______ | \_ ______ |   " << endl;

			positionMenuY += 1;

			if (positionMenuY == 11) {
				jouerPartie = true;
				system("cls");
			}
			timerMenu = clock();
		}
	}
}


void afficherTerrain(int nbColonnes, int nbLignes) {

	// definir les dimensions de la console
	UIKit::setDimensionFenetre(0, 0, 108, 45); // x1, y1, x2, y2

	// afficher le cadre du jeux
	UIKit::cadre(1, 1, nbColonnes, nbLignes, FOREGROUND_BLUE);
	UIKit::cadre(nbColonnes + 1, 1, nbColonnes + 25, nbLignes, FOREGROUND_GREEN);

	// ecrire les commandes de jeux dans le cadre de droite
	UIKit::gotoXY(nbColonnes + 4, 4);
	cout << "Commande: " << endl;
	UIKit::gotoXY(nbColonnes + 4, 6);
	cout << "gauche -> a" << endl;
	UIKit::gotoXY(nbColonnes + 4, 8);
	cout << "droite -> d" << endl;
	UIKit::gotoXY(nbColonnes + 4, 10);
	cout << "tirer -> espace" << endl;

	UIKit::color(FOREGROUND_RED);

	UIKit::curseurVisible(false);
}

int directionTouche(int touche) {
	char direction;

	switch (touche) {
	case 'd': direction = 'l';
		break;
	case 'D': direction = 'l';
		break;
	case 'a': direction = 'k';
		break;
	case 'A': direction = 'k';
		break;
	default: direction = -1;
	}

	return direction;
}
void bougerEnnemi(Ennemi race[], int nbAlien, bool &gauche) {
		if (race[0].coord.getPositionX() == 40) {
			gauche = true;
			for (int i = 0; i < nbAlien; i++) {
				race[i].removeExtraTerrestre();
				race[i].coord.setPositionY(race[i].coord.getPositionY() + 1);
			}
		}
		else if (race[0].coord.getPositionX() == 30) {
			gauche = false;
			for (int i = 0; i < nbAlien; i++) {
				race[i].removeExtraTerrestre();
				race[i].coord.setPositionY(race[i].coord.getPositionY() + 1);
			}
		}

		for (int j = 0; j < nbAlien; j++) {
			race[j].jiggleMartien(gauche);
		}
}