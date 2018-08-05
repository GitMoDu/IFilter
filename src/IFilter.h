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
	IFilter(const uint16_t startingValue = UINT16_MIDDLE) {}
public:
	virtual void StepValue() {}
	virtual uint16_t GetCurrentValue() { return 0; }
	virtual void ForceReset(const uint16_t input) {}
	virtual void SetNextValue(const uint16_t input) {}
};

class IFilter16 : public IFilter
{
protected:
	uint16_t Value = 0;
	uint16_t InputValue = 0;

public:
	IFilter16(const uint16_t startingValue = UINT16_MIDDLE) : IFilter(startingValue)
	{
		ForceReset(startingValue);
	}

	virtual void SetNextValue(const uint16_t input)
	{
		InputValue = input;
	}

	uint16_t GetCurrentValue()
	{
		return Value;
	}

	uint16_t GetTargetValue()
	{
		return InputValue;
	}

	virtual void ForceReset(const uint16_t input)
	{
		Value = input;
		InputValue = input;
	}
};
#endif