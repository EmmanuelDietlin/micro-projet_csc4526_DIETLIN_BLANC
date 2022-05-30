
class Data {
private:
	int fishCount;
	int distanceTravelled;
	int dayCount;
public:
	explicit Data(int const fishCount);
	void addFishes(int const fishNb);
	int consumeFishes(int const FishNb);
	void travelDistance(int const distance);
	void nextDay();
	const int getTravelledDistance();
	const int getFishCount();
	const int getDayCount();
};