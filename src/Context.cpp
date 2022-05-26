#include "Context.h"

Context::Context() {
	action = nullptr;
	evnt = nullptr;
}

void Context::setAction(std::unique_ptr<Action> && action) {
	action = std::move(action);
}

void Context::setEvent(std::unique_ptr<Event>&& evnt) {
	evnt = std::move(evnt);
}