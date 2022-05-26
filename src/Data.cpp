#include "Data.h"


Data::Data(int const fishCount) fishCount(fishCount) {}

void Data::addFishes(int const fishNb) {
	fishCount += fishNb;
}

/*
M�thode consommant un certain nombre de poissons, qui est le nombre de poissons que 
l'on doit consommer par jour. S'il y a moins de poissons dans la reserve que le nombre 
qu'on est cens� consommer, alors le joueur prend des d�g�t proportionnels au nombres de poissons
manquants.
*/
int Data::consumeFishes(int const fishNb) {
	fishCount -= fishNb;
	if (fishCount < 0) {
		int dmg = 10 * -1 * fishCount;
		fishCount = 0;
		return dmg;
	}
	return 0;
}