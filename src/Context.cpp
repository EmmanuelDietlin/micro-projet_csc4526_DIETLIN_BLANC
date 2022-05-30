#include "Context.h"

Context::Context()
{
}

void Context::setAction(std::unique_ptr<Action> && a) {
	action = std::move(a);
}

void Context::setEvent(std::unique_ptr<Event>&& e) {
	evnt = std::move(e);
}

int Context::executeAction() {
	return action->execute();
}

int Context::executeEvent() {
	return evnt->execute();
}



