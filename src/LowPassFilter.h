// LowPassFilter.h

// Low pass filtering without multiplication or division.
// Inspired by https://hackaday.io/project/158959-integer-low-pass-filter/log/147712-filtering-without-multiplication


#ifndef _LOWPASSFILTER_h
#define _LOWPASSFILTER_h

#include <IFilterTemplate.h>


template<class IFilterBase, typename HighType, const uint8_t Factor, const uint8_t MaxFactor = 8>
class TemplateLowPassFilter : public IFilterBase
{
protected:
	const uint8_t ConstrainedFactor = min(Factor, MaxFactor);
	HighType HighValue = 0;

private:
	using IFilterBase::InputValue;
	using IFilterBase::OutputValue;

public:
	TemplateLowPassFilter() : IFilterBase()
	{
	}

	//-V610_LEFT_SIGN_OFF
	virtual void Step()
	{
		HighValue = HighValue - (HighValue >> ConstrainedFactor) + InputValue;
		OutputValue = HighValue >> ConstrainedFactor;
	}
};

template<const uint8_t Factor = 4>
class LowPassFilter8 : public TemplateLowPassFilter<IFilter8, uint16_t, Factor>
{
private:
	using BaseClass = TemplateLowPassFilter<IFilter8, uint16_t, Factor>;
	using BaseClass::HighValue;
	using BaseClass::ConstrainedFactor;

public:
	LowPassFilter8() : BaseClass() {}

	virtual void ForceReset(const uint8_t input)
	{
		HighValue = input << ConstrainedFactor;
		BaseClass::ForceReset(input);
	}
};

template<const uint8_t Factor = 4>
class LowPassFilter16 : public TemplateLowPassFilter<IFilter16, uint32_t, Factor>
{
private:
	using BaseClass = TemplateLowPassFilter<IFilter16, uint32_t, Factor>;
	using BaseClass::HighValue;
	using BaseClass::ConstrainedFactor;

public:
	LowPassFilter16() : BaseClass() {}

	virtual void ForceReset(const uint16_t input)
	{
		HighValue = input << ConstrainedFactor;
		BaseClass::ForceReset(input);
	}
};

template<const uint8_t Factor = 4>
class LowPassFilter32 : public TemplateLowPassFilter<IFilter32, uint64_t, Factor>
{
private:
	using BaseClass = TemplateLowPassFilter<IFilter32, uint64_t, Factor>;
	using BaseClass::HighValue;
	using BaseClass::ConstrainedFactor;

public:
	LowPassFilter32() : BaseClass() {}

	virtual void ForceReset(const uint32_t input)
	{
		HighValue = input << ConstrainedFactor;
		BaseClass::ForceReset(input);
	}
};
#endif