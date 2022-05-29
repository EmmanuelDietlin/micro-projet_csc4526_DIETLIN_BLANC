#include "Action.h"

class RowingAction : public Action {
private:
	int baseDistance = 100;
public:
	explicit RowingAction(int const tokenNb);
	int execute() override;
};