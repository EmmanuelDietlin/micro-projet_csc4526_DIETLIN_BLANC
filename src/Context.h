#include "Action.h"
#include "Event.h"
#include <memory>

/**
Classe repr�sentant un contexte d'ex�cution.
Sert � impl�menter le patron de conception "Strategy", et contient donc pour ce faire un champ 
Action et un champ Event, que Context peut ex�cuter.
*/
class Context {
private:
	std::unique_ptr<Action> action = nullptr;
	std::weak_ptr<Event> evnt;

public:
	explicit Context() = default;
	void setAction(std::unique_ptr<Action> &&action);
	void setEvent(std::shared_ptr<Event> const &e);
	int executeAction();
	void executeEvent();
};