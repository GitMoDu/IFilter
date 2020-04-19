// DEMAFilter.h

#ifndef _DEMAFILTER_h
#define _DEMAFILTER_h

#include <EMAFilter.h>


class DEMAFilter8 : public IFilter8
{
private:
	EMAFilter8 First;
	EMAFilter8 Second;

public:
	DEMAFilter8(const uint8_t saturation = 127)
		: IFilter8()
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
		IFilter8::ForceReset(input);
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

class DEMAFilter16 : public IFilter16
{
private:
	EMAFilter16 First;
	EMAFilter16 Second;

public:
	DEMAFilter16(const uint8_t saturation = 127)
		: IFilter16()
		, First(saturation)
		, Second(saturation)
	{
	}

	void SetSaturation(const uint8_t saturation)
	{
		First.SetSaturation(saturation);
		Second.SetSaturation(saturation);
	}

	virtual void ForceReset(const uint16_t input)
	{
		IFilter16::ForceReset(input);
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

class DEMAFilter32 : public IFilter32
{
private:
	EMAFilter32 First;
	EMAFilter32 Second;

public:
	DEMAFilter32(const uint8_t saturation = 127)
		: IFilter32()
	{
	}

	void SetSaturation(const uint8_t saturation)
	{
		First.SetSaturation(saturation);
		Second.SetSaturation(saturation);
	}


	virtual void ForceReset(const uint32_t input)
	{
		IFilter32::ForceReset(input);
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
#endif