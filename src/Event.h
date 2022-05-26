
class Event {
public:
	virtual ~Event() = default;
	virtual int execute() = 0;
};