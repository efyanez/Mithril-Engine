#ifndef _CommandBase
#define _CommandBase

class CommandBase
{
public:
	CommandBase() {};
	~CommandBase() {};
	CommandBase(const CommandBase&) = delete;
	CommandBase& operator=(const CommandBase&) = delete;
	//! Pure virtual function. Execute to be overridden.
	virtual void Execute() {};
};

#endif // !_CommandBase
