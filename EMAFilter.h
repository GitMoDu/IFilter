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
	int32_t State = 0;

public:
	EMAFilter16(const uint16_t startingValue = UINT16_MIDDLE)
		: IFilter16(startingValue)
	{
		ForceReset(startingValue);
	}

	void StepValue()
	{
		State = State + InputValue - Value;
		Value = constrain(State >> 4, 0, UINT16_MAXVALUE);
	}

	void ForceReset(const uint16_t input)
	{
		IFilter16::ForceReset(input);
		State = input << 4;
	}
};
#endif