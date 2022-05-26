
class Action {
public:
	virtual ~Action() = default;
	virtual int execute(int const nbTokens) = 0;
};