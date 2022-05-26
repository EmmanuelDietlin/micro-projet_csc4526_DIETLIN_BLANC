#include "Action.h"
#include "Event.h"
#include <memory>

class Context {
private:
	std::unique_ptr<Action> action;
	std::unique_ptr<Event> evnt;
public:
	Context();
	void setAction(std::unique_ptr<Action> &&action);
	void setEvent(std::unique_ptr<Event> && evnt);

};