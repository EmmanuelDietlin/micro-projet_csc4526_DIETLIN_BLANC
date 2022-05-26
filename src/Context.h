#include "Action.h"
#include "Event.h"
#include <memory>
#include "Player.h"
#include "Boat.h"

class Context {
private:
	std::unique_ptr<Action> action;
	std::unique_ptr<Event> evnt;

public:
	explicit Context(int const starting_tokens);
	void setAction(std::unique_ptr<Action> &&action);
	void setEvent(std::unique_ptr<Event> && evnt);
	void executeAction(int const nbTokens);
	void executeEvent();
};