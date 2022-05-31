#include "Player.h"
#include "Boat.h"


class Data {
private:
	int fishCount;
	int distanceTravelled = 0;
	int dayCount = 1;
	std::unique_ptr<Boat> boat;
	std::unique_ptr<Player> player;
public:
	explicit Data(int const fishCount, int const boatBaseHp, int const playerBaseHp);
	void addFishes(int const fishNb);
	int consumeFishes(int const FishNb);
	void travelDistance(int const distance);
	void nextDay();
	int getTravelledDistance() const;
	int getFishCount() const;
	int getDayCount() const;
};