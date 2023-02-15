#ifndef INPUT_CONTROL_H

#define INPUT_CONTROL_H

#include "Control.h"

class InputControl : virtual public Control
{
public:
	virtual ~InputControl() = default;

	virtual String state() const = 0;
	virtual void modifyState(String command) = 0;
	virtual void modifyStateUserInput() = 0;
};

#endif // !INPUT_CONTROL_H