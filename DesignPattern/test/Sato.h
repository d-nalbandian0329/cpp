#ifndef _SATO_H_
#define _SATO_H_

#include <iostream>
#include "Employee.h"

class Sato : public Employee {
public:
	void dress() override;

	void commute() override;

	void work() override;
};

#endif

