#include "UIKit.h"
#include "Vaisseau.h"
#include "Laser.h"
#include "Martien.h"
#include "Ennemi.h"

#include <iostream>
#include <conio.h>			// _kbhit() et _getch()
#include <time.h>	 // clock();

#define NOMBRE_COLONNES 80
#define NOMBRE_LIGNES 42

// declaration de fonction
void afficherTerrain(int nbColonnes, int nbLignes);
int directionTouche(int touche);
void titreDeroulant();

// declaration des constants
const int nbColonnes = NOMBRE_COLONNES, nbLignes = NOMBRE_LIGNES;

#define MAX_LASER 15
#define MAX_ENNEMIS	15
 

int main() {
	// titre Space Invaders qui descend progressivement 
	//titreDeroulant();

	afficherTerrain(nbColonnes, nbLignes);

	// mettre le vaiseau sur le terrain de jeux
	Vaisseau monVaisseau;

	Laser mesLaser[MAX_LASER];

	//Martien martien(31, 2);
	//martien.jiggleMartien();

	//martien.coord.setPositionY(5);

	Ennemi ennemi[MAX_ENNEMIS];
	
	// mettre les extraterrestres a leur position de depart
	
	// Ennemi
	int timerEnnemi = clock();
	int delaiEnnemi = 4000;
	
	//int positionX = 15;

	//for (int i = 0; i < 10; i++) {
	//	martien.coord.setPositionX(positionX);
	//	martien.putExtraTerrestre();
	//	positionX += 3;
	//}

	int compteur = 0;

	// Laser
	int timerLaser = clock();
	int delaiLaser = 70;
	

	char direction;
	char touche;

	for (int i = 0; i < MAX_ENNEMIS; i++) {
		ennemi[i].coord.setPositionY(10);
		ennemi[i].coord.setPositionX(15 + (i * 3));
		ennemi[i].setEnnemi('@', 3);
	}

	while (1) {
		if (clock() >= timerEnnemi + delaiEnnemi) {
			for (int i = 0; i < 10; i++) {
				for (int j = 0; j < MAX_ENNEMIS; j++) {
					ennemi[j].jiggleMartien(false);
				}
			}
			timerEnnemi = clock();
		}

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
	int delaiMenu = 300;
	int timerMenu = clock();
	bool jouerPartie = false;

	while (!jouerPartie) {
		if (clock() >= timerMenu + delaiMenu) {
			// titre SPACE INVADERS
			system("cls");
			UIKit::gotoXY(0, positionMenuY);
			cout << "  _________                           .___                         .___                       " << endl;
			cout << "	/ _____ / __________    ____  ____ | | _______  _______     __ | _ / ___________  ______   " << endl;
			cout << "\_____  \\____ \__  \ _ / ___\ / __ \ | | / \  \ / / \__  \ / __ | / __ \_  __ \ / ___ /      " << endl;
			cout << "/ \ | _> > __ \\  \__\  ___ / | | | \ / / __ \_ / / _ / \  ___ / | | \ / \___ \			   " << endl;
			cout << "/ _______ / __(____ / \___  >___  > | ___ | ___ | / \_ / (____ / \____ | \___  >__ | / ____  >" << endl;
			cout << "\ / | __ | \ / \ / \ / \ / \ / \ / \ / \ " << endl;

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
