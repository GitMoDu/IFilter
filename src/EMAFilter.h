// EMAFilter.h


#ifndef _EMAFILTER_h
#define _EMAFILTER_h

#include <IFilterTemplate.h>

template<class IFilterBase, typename UnsignedType, const uint8_t MaxSaturation>
class TemplateEMAFilter : public IFilterBase
{
private:
	uint8_t Saturation = 0;

	using IFilterBase::InputValue;
	using IFilterBase::OutputValue;

public:
	TemplateEMAFilter(const uint8_t saturation = 127)
		: IFilterBase()
	{
		SetSaturation(saturation);
	}

	void SetSaturation(const uint8_t saturation)
	{
		Saturation = (saturation * (MaxSaturation)) / UINT8_MAX;
	}

	virtual void Step()
	{
		OutputValue = ((Saturation * ((UnsignedType)OutputValue - InputValue)) / UINT8_MAX) + InputValue;
	}
};

class EMAFilter8 : public TemplateEMAFilter<IFilter8, int16_t, 253>
{
public:
	EMAFilter8(const uint8_t saturation = 127)
		: TemplateEMAFilter<IFilter8, int16_t, 253>(saturation)
	{}
};

class EMAFilter16 : public TemplateEMAFilter<IFilter16, int32_t, 254>
{
public:
	EMAFilter16(const uint8_t saturation = 127)
		: TemplateEMAFilter<IFilter16, int32_t, 254>(saturation)
	{}
};

class EMAFilter32 : public TemplateEMAFilter<IFilter32, int64_t, 254>
{
public:
	EMAFilter32(const uint8_t saturation = 127)
		: TemplateEMAFilter<IFilter32, int64_t, 254>(saturation)
	{}
};

#endif
