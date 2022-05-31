#include "Data.h"

Data::Data(int const fishCount, int const boatBaseHp, int const playerBaseHp) : fishCount(fishCount) {
	boat = std::make_unique<Boat>(boatBaseHp);
	player = std::make_unique<Player>(playerBaseHp);
}

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

int Data::getFishCount() const {
	return fishCount;
}

void Data::travelDistance(int const distance) {
	distanceTravelled += distance;
}

int Data::getTravelledDistance() const {
	return distanceTravelled;
}

void Data::nextDay() {
	dayCount++;
}

int Data::getDayCount() const{
	return dayCount;
}