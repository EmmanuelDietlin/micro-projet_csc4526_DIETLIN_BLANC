#include "Action.h"
#include "Event.h"
#include <memory>

class Context {
private:
	std::unique_ptr<Action> action = nullptr;
	std::weak_ptr<Event> evnt;

public:
	explicit Context();
	void setAction(std::unique_ptr<Action> &&action);
	void setEvent(std::shared_ptr<Event> const &evnt);
	int executeAction();
	void executeEvent();
};