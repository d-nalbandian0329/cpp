#ifndef _SUZUKI_H_
#define _SUZUKI_H_

#include <iostream>
#include <memory>
#include "Employee.h"
#include "Phase.h"

class Suzuki : public Employee {
public:
	void dress() override;

	void commute() override;

	void work() override;

private:
	std::unique_ptr<Phase> phase;
};

#endif

