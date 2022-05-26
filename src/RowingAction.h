#include "Action.h"

class RowingAction : public Action {
private:
	int baseDistance = 100;
public:
	int execute(int const nbTokens) override;
};