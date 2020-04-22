// LowPassFilter.h

// Low pass filtering without multiplication or division.
// Inspired by https://hackaday.io/project/158959-integer-low-pass-filter/log/147712-filtering-without-multiplication


#ifndef _LOWPASSFILTER_h
#define _LOWPASSFILTER_h

#include <IFilterTemplate.h>


template<class IFilterBase, typename HighType, const uint8_t Factor, const uint8_t MaxFactor>
class TemplateLowPassFilter : public IFilterBase
{
private:
	const uint8_t ConstrainedFactor = min(Factor, MaxFactor);

	HighType HighValue = 0;

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
class LowPassFilter8 : public TemplateLowPassFilter<IFilter8, uint16_t, Factor, 8>
{
public:
	LowPassFilter8() : TemplateLowPassFilter<IFilter8, uint16_t, Factor, 8>() {}
};

template<const uint8_t Factor = 4>
class LowPassFilter16 : public TemplateLowPassFilter<IFilter16, uint32_t, Factor, 8>
{
public:
	LowPassFilter16() : TemplateLowPassFilter<IFilter16, uint32_t, Factor, 8>() {}
};

template<const uint8_t Factor = 4>
class LowPassFilter32 : public TemplateLowPassFilter<IFilter32, uint64_t, Factor, 8>
{
public:
	LowPassFilter32() : TemplateLowPassFilter<IFilter32, uint64_t, Factor, 8>() {}
};
#endif