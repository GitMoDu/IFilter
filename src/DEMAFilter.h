// DEMAFilter.h

#ifndef _DEMAFILTER_h
#define _DEMAFILTER_h

#include <EMAFilter.h>

template<class IFilterBase, class EMAFilter>
class TemplateDEMAFilter : public IFilterBase
{
private:
	EMAFilter First;
	EMAFilter Second;

	using IFilterBase::InputValue;
	using IFilterBase::OutputValue;

public:
	TemplateDEMAFilter(const uint8_t saturation = 127)
		: IFilterBase()
		, First(saturation)
		, Second(saturation)
	{
	}

	void SetSaturation(const uint8_t saturation)
	{
		First.SetSaturation(saturation);
		Second.SetSaturation(saturation);
	}

	virtual void ForceReset(const uint8_t input)
	{
		IFilterBase::ForceReset(input);
		First.ForceReset(input);
		Second.ForceReset(input);
	}

	virtual void Step()
	{
		First.Set(InputValue);
		First.Step();
		Second.Set(First.Get());
		Second.Step();

		OutputValue = Second.Get();
	}
};

class DEMAFilter8 : public TemplateDEMAFilter<IFilter8, EMAFilter8>
{
public:
	DEMAFilter8(const uint8_t saturation = 127)
		: TemplateDEMAFilter<IFilter8, EMAFilter8>(saturation)
	{}
};

class DEMAFilter16 : public TemplateDEMAFilter<IFilter16, EMAFilter16>
{
public:
	DEMAFilter16(const uint8_t saturation = 127)
		: TemplateDEMAFilter<IFilter16, EMAFilter16>(saturation)
	{}
};

class DEMAFilter32 : public TemplateDEMAFilter<IFilter32, EMAFilter32>
{
public:
	DEMAFilter32(const uint8_t saturation = 127)
		: TemplateDEMAFilter<IFilter32, EMAFilter32>(saturation)
	{}
};
#endif