#ifndef _EMPLOYEE_H_
#define _EMPLOYEE_H_

class Employee {
public:
	virtual ~Employee() = default;

	virtual void dress() = 0;

	virtual void commute() = 0;

	virtual void work() = 0;

	void doit() {
		dress();

		commute();

		work();
	}
};

#endif

