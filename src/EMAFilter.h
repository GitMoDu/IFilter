// EMAFilter.h

//https://forum.arduino.cc/index.php?topic=445844.0
//Takes around 500 steps to reach 97% target value and around 1000 to reach 99%.
//At 1500 steps it is at most 1 or 2 units out.

#ifndef _EMAFILTER_h
#define _EMAFILTER_h

#include <IFilter.h>


class EMAFilter : public IFilterTemplate
{
private:
	uint8_t Saturation = 127;

public:
	EMAFilter(const uint8_t saturation = 127)
		: IFilterTemplate()
	{
		Saturation = saturation;
	}

	virtual void SetSaturation(const uint8_t saturation)
	{
		Saturation = saturation;
	}

	virtual void Step()
	{
		OutputValue = map((uint16_t)Saturation, UINT8_MAX, 0, 0, InputValue) + map(Saturation, 0, UINT8_MAX, 0, OutputValue);
	}
};

class DEMAFilter : public IFilter
{
private:
	EMAFilter First;
	EMAFilter Second;

	uint16_t OutputValue = 0;

public:
	DEMAFilter(const uint8_t saturation = 127)
		: IFilter()
		, First(saturation)
		, Second(saturation)
	{
	}

	void ForceReset(const uint16_t input)
	{
		First.ForceReset(input);
		Second.ForceReset(input);
	}

	void SetSaturation(const uint8_t saturation)
	{
		First.SetSaturation(saturation);
		Second.SetSaturation(saturation);
	}

	uint16_t GetTarget()
	{
		return First.GetTarget();
	}

	void Set(const uint16_t input)
	{
		First.Set(input);
	}

	void Step()
	{		
		First.Step();
		Second.Set(First.Get());
		Second.Step();
		OutputValue = 2*First.Get() - Second.Get();
	}
};

#endif
