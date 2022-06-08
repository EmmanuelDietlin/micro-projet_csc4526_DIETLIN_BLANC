#include "Context.h"

/**
Ajoute une action.
@param a lvalue de l'Action
*/
void Context::setAction(std::unique_ptr<Action> && a) {
	action = std::move(a);
}

/**
Ajoute un Event.
@param e pointeur partagé de l'Event
*/
void Context::setEvent(std::shared_ptr<Event> const& e) {
	evnt = e;
}

/**
Execute l'action.
@return entier renvoyé par l'exécution de l'Action
*/
int Context::executeAction() {
	return action->execute();
}
/**
Execute l'Event.
*/
void Context::executeEvent() {
	evnt.lock()->execute();
}
