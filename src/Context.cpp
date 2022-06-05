#include "Context.h"

Context::Context()
{
}

void Context::setAction(std::unique_ptr<Action> && a) {
	action = std::move(a);
}

void Context::setEvent(std::shared_ptr<Event> const& e) {
	evnt = e;
}

int Context::executeAction() {
	return action->execute();
}

void Context::executeEvent() {
	evnt.lock()->execute();
}
