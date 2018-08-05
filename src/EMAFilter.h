// EMAFilter.h

//https://forum.arduino.cc/index.php?topic=445844.0
//Takes around 500 steps to reach 97% target value and around 1000 to reach 99%.
//At 1500 steps it is at most 1 or 2 units out.

#ifndef _EMAFILTER_h
#define _EMAFILTER_h

#include <IFilter.h>

class EMAFilter16 : public IFilter16
{
private:
	uint8_t Ratio = 127;

public:
	EMAFilter16(const uint16_t startingValue = UINT16_MIDDLE)
		: IFilter16(startingValue)
	{
	}

	virtual void SetRatio(const uint8_t ratio)
	{
		Ratio = ratio;
	}

	virtual void StepValue()
	{
		Value = map(Ratio, UINT8_MAX, 0, 0, InputValue) + map(Ratio, 0, UINT8_MAX, 0, Value);
	}
};

class DEMAFilter16 : public IFilter16
{
private:
	EMAFilter16 First;
	EMAFilter16 Second;

public:
	DEMAFilter16(const uint16_t startingValue = UINT16_MIDDLE)
		: IFilter16(startingValue)
		, First(startingValue)
		, Second(startingValue)
	{
	}

	void ForceReset(const uint16_t input)
	{
		IFilter16::ForceReset(input);
		First.ForceReset(input);
		Second.ForceReset(input);
	}

	void SetRatio(const uint8_t ratio)
	{
		First.SetRatio(ratio);
		Second.SetRatio(ratio);
	}

	void SetNextValue(const uint16_t input)
	{
		IFilter16::SetNextValue(input);
		First.SetNextValue(input);
	}

	void StepValue()
	{		
		First.StepValue();
		Second.SetNextValue(First.GetCurrentValue());
		Second.StepValue();
		Value = Second.GetCurrentValue();
	}
};

#endif