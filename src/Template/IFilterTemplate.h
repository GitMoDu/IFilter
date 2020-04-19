// IFilterTemplate.h

#ifndef _IFILTERTEMPLATE_h
#define _IFILTERTEMPLATE_h


#include <IFilter.h>

template<typename ValueType>
class IFilterTemplate : public virtual IFilter
{
protected:
	ValueType OutputValue = 0;
	ValueType InputValue = 0;

public:
	IFilterTemplate() : IFilter()
	{
	}

	void Set(const ValueType input)
	{
		InputValue = input;
	}

	ValueType Get()
	{
		return OutputValue;
	}

	ValueType GetTarget()
	{
		return InputValue;
	}

	virtual void ForceReset(const ValueType input)
	{
		OutputValue = input;
		InputValue = input;
	}
};

template<typename ValueType, typename SignedType, const ValueType OffsetValue>
class IFilterSignedTemplate : public IFilterTemplate<ValueType>
{
protected:
	using IFilterTemplate<ValueType>::InputValue;
	using IFilterTemplate<ValueType>::OutputValue;

public:
	IFilterSignedTemplate() : IFilterTemplate<ValueType>()
	{
	}

	void SetSigned(const SignedType input)
	{
		InputValue = (uint8_t)(input + OffsetValue);
	}

	SignedType GetSigned()
	{
		return (SignedType)(OutputValue - OffsetValue);
	}
};

class IFilter8 : public IFilterSignedTemplate<uint8_t, int8_t, INT8_MAX>
{
public:
	IFilter8() : IFilterSignedTemplate<uint8_t, int8_t, INT8_MAX>()
	{
	}
};

class IFilter16 : public IFilterSignedTemplate<uint16_t, int16_t, INT16_MAX>
{
public:
	IFilter16() : IFilterSignedTemplate<uint16_t, int16_t, INT16_MAX>()
	{
	}
};

class IFilter32 : public IFilterSignedTemplate<uint32_t, int32_t, INT32_MAX>
{
public:
	IFilter32() : IFilterSignedTemplate<uint32_t, int32_t, INT32_MAX>()
	{
	}
};
#endif