#include "Context.h"

Context::Context()
{
}

void Context::setAction(std::unique_ptr<Action> && a) {
	action = std::move(a);
}

int Context::executeAction() {
	return action->execute();
}
