#include "Action.h"
#include "Event.h"
#include <memory>

class Context {
private:
	std::unique_ptr<Action> action = nullptr;
	std::unique_ptr<Event> evnt = nullptr;

public:
	explicit Context();
	void setAction(std::unique_ptr<Action> &&action);
	void setEvent(std::unique_ptr<Event> &&evnt);
	int executeAction();
	void executeEvent();
};