#ifndef _COMPANYA_H_
#define _COMPANYA_H_

#include <memory>
#include "Company.h"
#include "Employee.h"


class CompanyA : public Company {
public:

private:
	std::unique_ptr<Employee> employee;
};

#endif	// _COMPANYA_H_

