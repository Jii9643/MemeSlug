#pragma once

#include <vector>
#include "Observer.h"

class Subject {
public:
	virtual void Attach(Observer*o) = 0;
	virtual void Detach(Observer*o) = 0;
	virtual void Notify() const = 0;
	virtual ~Subject() {};
};
