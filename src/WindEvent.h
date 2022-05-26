#include "Event.h"

class WindEvent : public Event {
private:
	const int distance = 50;
public:
	int execute() override;
};