#include "Event.h"

class StormEvent : public Event {
public:
	const int damage = 20;
private:
	int execute() override;
};