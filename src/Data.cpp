#include "Data.h"

Data::Data(int const fishCount) : fishCount(fishCount), distanceTravelled(0), dayCount(0) {}

void Data::addFishes(int const fishNb) {
	fishCount += fishNb;
}

/*
Méthode consommant un certain nombre de poissons, qui est le nombre de poissons que 
l'on doit consommer par jour. S'il y a moins de poissons dans la reserve que le nombre 
qu'on est censé consommer, alors le joueur prend des dégât proportionnels au nombres de poissons
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

const int Data::getFishCount() {
	return fishCount;
}

void Data::travelDistance(int const distance) {
	distanceTravelled += distance;
}

const int Data::getTravelledDistance() {
	return distanceTravelled;
}

void Data::nextDay() {
	dayCount++;
}

const int Data::getDayCount() {
	return dayCount;
}