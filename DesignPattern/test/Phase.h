#ifndef _PHASE_H_
#define _PHASE_H_

class Phase {
public:
	virtual ~Phase() = default;
	virtual void work() = 0;
};

#endif

