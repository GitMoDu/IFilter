// LowPassFilter.h

// Low pass filtering without multiplication or division.
// Inspired by https://hackaday.io/project/158959-integer-low-pass-filter/log/147712-filtering-without-multiplication


#ifndef _LOWPASSFILTER_h
#define _LOWPASSFILTER_h

#include <IFilterTemplate.h>

/* Max Factor = 16*/
template<const uint8_t Factor = 3>
class LowPassFilter8 : public IFilter8
{
private:
	const uint8_t MaxFactor = 6;
	const uint8_t ConstrainedFactor = min(Factor, MaxFactor);

	uint16_t HighValue = 0;

public:
	LowPassFilter8() : IFilter8()
	{
	}

	//-V610_LEFT_SIGN_OFF
	virtual void Step()
	{
		HighValue = HighValue - (HighValue >> ConstrainedFactor) + InputValue;
		OutputValue = HighValue >> ConstrainedFactor;
	}
};

/* Max Factor = 16*/
template<const uint8_t Factor = 3>
class LowPassFilter16 : public IFilter16
{
private:
	const int32_t MaxFactor = 7;
	const uint8_t ConstrainedFactor = min(Factor, MaxFactor);

	uint32_t HighValue = 0;

public:
	LowPassFilter16() : IFilter16()
	{
	}

	virtual void Step()
	{
		HighValue = HighValue - (HighValue >> ConstrainedFactor) + InputValue;
		OutputValue = HighValue >> ConstrainedFactor;
	}
};

/* Max Factor = 64*/
template<const uint8_t Factor = 3>
class LowPassFilter32 : public IFilter32
{
private:
	const int32_t MaxFactor = 7;
	const uint8_t ConstrainedFactor = min(Factor, MaxFactor);

	uint64_t HighValue = 0;

public:
	LowPassFilter32() : IFilter32()
	{
	}

	virtual void Step()
	{
		HighValue = HighValue - (HighValue >> ConstrainedFactor) + InputValue;
		OutputValue = HighValue >> ConstrainedFactor;
	}
};
#endif
