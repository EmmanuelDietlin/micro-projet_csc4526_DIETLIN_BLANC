#pragma once

class Action {
public:
	explicit Action(int const tokenNb);
	virtual ~Action() = default;
	virtual int execute() = 0;
	void addTokens(int const tokens);
	void clearTokens();
	int getTokenNb() const ;
protected:
	int tokenNb;
};