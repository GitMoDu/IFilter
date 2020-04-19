// IFilter.h

#ifndef _IFILTER_h
#define _IFILTER_h


#include <stdint.h>

class IFilter
{
public:
	IFilter() {}

	virtual void Step() {}
};
#endif