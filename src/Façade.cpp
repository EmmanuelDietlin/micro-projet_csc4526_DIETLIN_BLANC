#include "Fa�ade.h"

Fa�ade::Fa�ade() : action_tokens(max_tokens_nb), day_count(1), distance_travelled(0), fishCount(starting_fish_number) {
	actions["fish"] = std::make_unique<FishingAction>(0);
	actions["row"] = std::make_unique<RowingAction>(0);
}

const int Fa�ade::getTokenNbr() {
	return action_tokens;
}

const int Fa�ade::getDayCount() {
	return day_count;
}

const int Fa�ade::getDistanceTravelled() {
	return distance_travelled;
}

void Fa�ade::executeRowingAction(int const tokens) {
	actions["row"]->addTokens(tokens);
	distance_travelled+= actions["row"]->execute();
	actions["row"]->clearTokens();
}

void Fa�ade::executeFishingAction(int const tokens) {
	actions["fish"]->addTokens(tokens);
	fishCount+= actions["fish"]->execute();
	actions["fish"]->clearTokens();
}

void Fa�ade::nextDay() {
	day_count++;
	//evnt = std::make_unique<>
	fishCount -= fish_eating_number;

}

const int Fa�ade::getFishCount() {
	return fishCount;
}
