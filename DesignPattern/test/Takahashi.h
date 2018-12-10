#ifndef _TAKAHASHI_H_
#define _TAKAHASHI_H_

#include <iostream>
#include "Employee.h"

class Takahashi : public Employee {
public:
	void dress() override;

	void commute() override;

	void work() override;
};

#endif

