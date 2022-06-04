#include "Action.h"
#include <memory>
#include "Player.h"
#include "Boat.h"

class Context {
private:
	std::unique_ptr<Action> action = nullptr;

public:
	explicit Context();
	void setAction(std::unique_ptr<Action> &&action);
	int executeAction();
};