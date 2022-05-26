
class Data {
private:
	int fishCount;
public:
	explicit Data(int const fishCount);
	void addFishes(int const fishNb);
	int consumeFishes(int const FishNb);
};