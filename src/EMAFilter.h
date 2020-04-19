// EMAFilter.h


#ifndef _EMAFILTER_h
#define _EMAFILTER_h

#include <IFilterTemplate.h>

class EMAFilter8 : public IFilter8
{
private:
	uint8_t Saturation = 0;
	const uint8_t MaxSaturation = 255;

public:
	EMAFilter8(const uint8_t saturation = 127)
		: IFilter8()
	{
		SetSaturation(saturation);
	}

	void SetSaturation(const uint8_t saturation)
	{
		Saturation = (saturation * (MaxSaturation)) / UINT8_MAX;
	}

	virtual void Step()
	{
		OutputValue = ((Saturation * ((int16_t)OutputValue - InputValue)) / UINT8_MAX) + InputValue;
	}
};

class EMAFilter16 : public IFilter16
{
private:
	uint8_t Saturation = 0;
	const uint8_t MaxSaturation = 253;

public:
	EMAFilter16(const uint8_t saturation = 127)
		: IFilter16() 
	{
		SetSaturation(saturation);
	}

	void SetSaturation(const uint8_t saturation)
	{
		Saturation = (saturation * (MaxSaturation)) / UINT8_MAX;
	}

	virtual void Step()
	{
		OutputValue = ((Saturation * ((int32_t)OutputValue - InputValue)) / UINT8_MAX) + InputValue;
	}
};

class EMAFilter32 : public IFilter32
{
private:
	uint8_t Saturation = 0;
	const uint8_t MaxSaturation = 251;

public:
	EMAFilter32(const uint8_t saturation = 127)
		: IFilter32()
	{
		SetSaturation(saturation);
	}

	void SetSaturation(const uint8_t saturation)
	{
		Saturation = (saturation * (MaxSaturation)) / UINT8_MAX;
	}

	virtual void Step()
	{
		OutputValue = (((uint32_t)Saturation * ((int64_t)OutputValue - InputValue)) / UINT8_MAX) + InputValue;
	}
};
#endif
