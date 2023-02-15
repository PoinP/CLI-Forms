#ifndef OUTPUT_CONTROL_H

#define OUTPUT_CONTROL_H

#include "Control.h"

class OutputControl : virtual public Control
{
public:
	virtual ~OutputControl() = default;

	virtual void modifyText(String text) = 0;
};

#endif // !OUTPUT_CONTROL_H