#include "Context.h"

Context::Context(int const starting_tokens) {
	action = nullptr;
	evnt = nullptr;
	action_tokens = starting_tokens;
}

void Context::setAction(std::unique_ptr<Action> && action) {
	action = std::move(action);
}

void Context::setEvent(std::unique_ptr<Event>&& evnt) {
	evnt = std::move(evnt);
}

void Context::executeAction(int const nbTokens) {

}

void Context::executeEvent() {

}



