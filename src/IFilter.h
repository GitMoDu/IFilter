// IFilter.h

#ifndef _IFILTER_h
#define _IFILTER_h


#include <stdint.h>


#ifndef UINT16_MIDDLE
#define UINT16_MIDDLE 32767
#endif

class IFilter
{
public:
	IFilter() {}
public:
	virtual void Step() {}
	virtual uint16_t Get() { return 0; }
	virtual void ForceReset(const uint16_t input) {}
	virtual void Set(const uint16_t input) {}
};

class IFilterTemplate : public IFilter
{
protected:
	uint16_t OutputValue = 0;
	uint16_t InputValue = 0;

public:
	IFilterTemplate() : IFilter()
	{
	}

	virtual void Set(const uint16_t input)
	{
		InputValue = input;
	}

	uint16_t Get()
	{
		return OutputValue;
	}

	uint16_t GetTarget()
	{
		return InputValue;
	}

	virtual void ForceReset(const uint16_t input)
	{
		OutputValue = input;
		InputValue = input;
	}
};
#endif