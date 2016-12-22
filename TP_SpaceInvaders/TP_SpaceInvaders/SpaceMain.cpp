#include "UIKit.h"
#include "Vaisseau.h"
#include "Laser.h"
#include "LaserEnnemi.h"
#include "Ennemi.h"

#include <conio.h>	 // _kbhit() et _getch()
#include <time.h>	 // clock();

#define NOMBRE_COLONNES 80
#define NOMBRE_LIGNES 42

// declaration de fonction
void afficherTerrain(int nbColonnes, int nbLignes);
int directionTouche(int touche);
void titreDeroulant();
void bougerEnnemi(Ennemi race[], int nbAlien, bool &gauche);
void testerCollision(Ennemi race[], Laser mesLaser[], int nbAliens, int &points);

// declaration des constants
const int nbColonnes = NOMBRE_COLONNES, nbLignes = NOMBRE_LIGNES;

#define MAX_LASER 15
#define MAX_LASER_ENNEMI 10
#define NB_VENUSIEN 10
#define NB_SATURIEN 10


int main() {
	srand((unsigned int)time(NULL));

	// definir les dimensions de la console
	UIKit::setDimensionFenetre(0, 0, 108, 45); // x1, y1, x2, y2

	// titre Space Invaders qui descend progressivement 
	titreDeroulant();

	afficherTerrain(nbColonnes, nbLignes);

	// mettre le vaiseau sur le terrain de jeux
	Vaisseau monVaisseau;

	Laser mesLaser[MAX_LASER];
	LaserEnnemi laserEnnemi[MAX_LASER_ENNEMI];

	int timer = clock();

	// Ennemi
	int delaiEnnemi = 600;
	int delaiLaserEnnemi = 1000 + rand() % 500;

	// Laser
	int delaiLaser = 50;

	char direction;
	char touche;
	int compteur = 0;

	Ennemi venusien[NB_VENUSIEN];
	Ennemi saturien[NB_SATURIEN];

	int nbVenusien = 5;
	int nbSaturien = 5;

	int alienTireur;
	bool alienTir = false;

	// mettre les extraterrestres a leur position de depart
	UIKit::color(FOREGROUND_RED + FOREGROUND_GREEN);
	for (int i = 0; i < nbVenusien; i++) {
		venusien[i].setPositionAlien(14, 29, i);
	}
	//UIKit::color(FOREGROUND_BLUE + FOREGROUND_GREEN);
	for (int i = 0; i < nbSaturien; i++) {
		saturien[i].setPositionAlien(16, 31, i);
	}
	bool gauche = false;
	int points = 0;

	UIKit::gotoXY(10, 0);
	cout << ExtraTerrestre::getNombreExtraTerrestre();
	while (ExtraTerrestre::getNombreExtraTerrestre()) {
		if (clock() >= timer + delaiEnnemi) {
			bougerEnnemi(venusien, nbVenusien, gauche);
			bougerEnnemi(saturien, nbSaturien, gauche);
			timer = clock();
		}

		if (clock() >= timer + delaiLaser) {
			// on affiche un compteur en haut à gauche de l'écran
			UIKit::gotoXY(0, 0);
			cout << compteur;
			compteur++;

			for (int i = 0; i < MAX_LASER; i++) {
				if (mesLaser[i].isAlive)
					if (mesLaser[i].coord.getPositionY() != 2) {
						mesLaser[i].moveLaser();
						testerCollision(venusien, mesLaser, nbVenusien, points);
						testerCollision(saturien, mesLaser, nbSaturien, points);
					}
					else
						mesLaser[i].killLaser();
			}

			//if (clock() >= timer + delaiLaserEnnemi) {
			//	alienTir = false;
			//	while (!alienTir) {
			//		alienTireur = rand() % nbVenusien;
			//		if (venusien[alienTireur].isAlive) {
			//			for (int i = 0; i < MAX_LASER; i++) {
			//				if (laserEnnemi[i].isAlive) {
			//					laserEnnemi[i].coord.setPositionX(venusien[alienTir].coord.getPositionX());
			//					laserEnnemi[i].coord.setPositionY(venusien[alienTir].coord.getPositionY() - 1);
			//					laserEnnemi[i].moveLaser();
			//					alienTir = true;
			//				}
			//			}
			//		}
			//	}
			//}
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
					timer = clock();
				}
			}
			return 0;
		}

		void titreDeroulant() {
			int positionMenuY = 10;
			int delaiMenu = 50;
			int timerMenu = clock();
			bool jouerPartie = false;

			while (!jouerPartie) {
				if (clock() >= timerMenu + delaiMenu) {
					// titre SPACE INVADERS
					system("cls");
					UIKit::gotoXY(1, positionMenuY);
					cout << "\t\t\t\t____  _____  ______  _____  _____\n";
					cout << "\t\t\t\t|___  |____| |_____| |	   |____\n";
					cout << "\t\t\t\t____| |      | | | | |____  |____\n\n";
					cout << "\t\t\t_____  __    __   __  ______   ____   _____  ____\n";
					cout << "\t\t\t  |    | \ |  \ _ /   |_____|  |   |  |____  |___|\n";
					cout << "\t\t\t__|__  |  \|   \ /    | | | |  |___|  |____  |\__" << endl;

					positionMenuY += 1;

					if (positionMenuY == 16) {
						jouerPartie = true;
						system("cls");
					}
					timerMenu = clock();
				}
			}
		}

		void afficherTerrain(int nbColonnes, int nbLignes) {
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
			int index = 0;
			while (race[index].isAlive != true)
				index++;

			if (race[index].coord.getPositionX() == 40 + (index * 3)) {
				gauche = true;
				for (int i = 0; i < nbAlien; i++) {
					race[i].removeExtraTerrestre();
					if (race[i].isAlive == true) {
						race[i].coord.setPositionY(race[i].coord.getPositionY() + 1);
					}
				}
			}
			else if (race[index].coord.getPositionX() == 30 + (index * 3)) {
				gauche = false;
				for (int i = 0; i < nbAlien; i++) {
					race[i].removeExtraTerrestre();
					if (race[i].isAlive == true) {
						race[i].coord.setPositionY(race[i].coord.getPositionY() + 1);
					}
				}
			}

			for (int j = 0; j < nbAlien; j++) {
				if (race[j].isAlive) {
					race[j].jiggleMartien(gauche);
				}
			}
		}
		// Tester la meme fonction du serpant (modifier pour les valueurs)
		void testerCollision(Ennemi race[], Laser laser[], int nbAliens, int &points) {
			// si le i et plus petite que le nombre total d alien et qu'il n'a pas de collision
			for (int j = 0; j < MAX_LASER; j++) {
				if (laser[j].isAlive) {
					for (int i = 0; i < nbAliens; i++) {
						if (race[i].isAlive) {
							if (laser[j].coord.getPositionY() == race[i].coord.getPositionY() &&
								laser[j].coord.getPositionX() == race[i].coord.getPositionX()) {
								laser[j].killLaser();
								race[i].deadEnnemi();
							}
						}
					}
				}
			}
		}