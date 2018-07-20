// IFilter.h

#ifndef _IFILTER_h
#define _IFILTER_h


#include <Arduino.h>


#ifndef UINT16_MIDDLE
#define UINT16_MIDDLE 32767
#endif

class IFilter
{
public:
	IFilter(const uint16_t startingValue = UINT16_MIDDLE) {}
public:
	virtual void StepValue();
	uint16_t GetCurrentValue();
	virtual void ForceReset(const uint16_t input);
	virtual void SetNextValue(const uint16_t input);


	virtual void AddStepValue(const uint16_t input) { SetNextValue(input); }
	virtual uint16_t GetUpdateValue() { return GetCurrentValue(); }
};

class BlankFilter16 : public IFilter
{
private:
	uint16_t Value = 0;

public:
	BlankFilter16(const uint16_t startingValue = UINT16_MIDDLE) 
	{
		Value = startingValue;
	}
public:
	void StepValue() {}
	uint16_t GetCurrentValue() const { return Value; }
	void ForceReset(const uint16_t input) { Value = input; }
};

class IFilter16 : public IFilter
{
protected:
	uint16_t Value = 0;
	uint16_t InputValue = 0;

public:
	IFilter16(const uint16_t startingValue = UINT16_MIDDLE)
	{
		ForceReset(startingValue);
	}

	virtual void StepValue() {}

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

	//class DEMAFilter16 : public IFilter16
	//{
	//	///https://www.norwegiancreations.com/2016/08/double-exponential-moving-average-filter-speeding-up-the-ema/
	//	//Currently not working.
	//private:
	//	EMAFilter16 FirstPass;
	//	EMAFilter16 SecondPass;
	//
	//	uint16_t EmaTimes2Grunt;
	//
	//public:
	//	DEMAFilter16(const uint16_t startingValue = UINT16_MIDDLE)
	//		: IFilter16(startingValue)
	//		, FirstPass(startingValue)
	//		, SecondPass(startingValue)
	//	{
	//
	//	}
	//
	//	void SetNextValue(const uint16_t input)
	//	{
	//		IFilter16::SetNextValue(input);
	//		FirstPass.SetNextValue(input);
	//	}
	//
	//	void StepValue()
	//	{
	//		FirstPass.StepValue();
	//
	//		SecondPass.SetNextValue(FirstPass.GetCurrentValue());
	//		SecondPass.StepValue();
	//
	//		EmaTimes2Grunt = FirstPass.GetCurrentValue();
	//
	//		//Clamps the first pass up to UINT16_MAX
	//		if (EmaTimes2Grunt > UINT16_MIDDLE)
	//		{
	//			EmaTimes2Grunt = UINT16_MAX;
	//		}
	//		else
	//		{
	//			EmaTimes2Grunt = FirstPass.GetCurrentValue() * 2;
	//		}
	//
	//		//Clamps to from 0.
	//		if (EmaTimes2Grunt >= SecondPass.GetCurrentValue())
	//		{
	//			Value = 2 * EmaTimes2Grunt - SecondPass.GetCurrentValue();
	//		}
	//		else
	//		{
	//			Value = 0;
	//		}
	//	}
	//};
#endif