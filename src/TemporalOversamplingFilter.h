// TemporalOversamplingFilter.h

#ifndef _TEMPORAL_OVERSAMPLING_FILTER_h
#define _TEMPORAL_OVERSAMPLING_FILTER_h

#include <IFilter.h>
#include <RingBufCPP.h>

#define TEMPORAL_OVERSAMPLING_FILTER_ALIASING_FACTOR 10

#define TEMPORAL_OVERSAMPLING_FILTER_WEIGHT_DECAY_FACTOR_DEFAULT 18

#define TEMPORAL_OVERSAMPLING_FILTER_BASE_MULTIPLIER (TEMPORAL_OVERSAMPLING_FILTER_ALIASING_FACTOR * (_StackSize))

///StackSize equals the amount of samples before settle:
/// more sample, less harsh curve.
///The filter factor decides the importance of freshness of value:
/// bigger factor, faster response.
///Settle time is fixed depending on filter properties, input value delta will not change settle time.
template <int _StackSize, int _Factor>
class TemporalOversamplingFilter16 : public IFilter16
{
private:
	uint32_t Sum = 0;
	RingBufCPP<uint16_t, _StackSize> SampleStack;

	uint16_t WeightsTotal = 0;
	uint8_t WeightFactors[_StackSize];

private:
	inline uint8_t GetBaseWeight(const uint8_t factor)
	{
		if (factor > (TEMPORAL_OVERSAMPLING_FILTER_BASE_MULTIPLIER / UINT8_MAX))
		{
			return UINT8_MAX;
		}
		else
		{
			return constrain(TEMPORAL_OVERSAMPLING_FILTER_BASE_MULTIPLIER * factor, 0, UINT8_MAX);
		}
	}

	inline uint8_t GetNextWeight(const uint8_t current, const uint8_t factor)
	{
		return ceil((double)current / (((double)factor / (double)TEMPORAL_OVERSAMPLING_FILTER_ALIASING_FACTOR)));
	}

	inline void UpdateValue()
	{
		Sum = 0;
		for (uint8_t i = 0; i < _StackSize; i++)
		{
			Sum += (*SampleStack.peek(SampleStack.numElements() - 1 - i)) * WeightFactors[i];
		}
		Value = constrain(Sum / WeightsTotal, 0, UINT16_MAXVALUE);
	}

	void FillWeightFactors(const uint8_t factor)
	{
		uint8_t FillWeight = GetBaseWeight(factor);

		for (uint8_t i = 0; i < _StackSize; i++)
		{
			WeightFactors[i] = FillWeight;
			WeightsTotal += FillWeight;
			FillWeight = GetNextWeight(FillWeight, factor);
		}
	}

public:
	TemporalOversamplingFilter16(const uint16_t startingValue = UINT16_MIDDLE)
		: IFilter16(startingValue)
	{
		FillWeightFactors(_Factor);
		ForceReset(startingValue);
	}

	void StepValue()
	{
		SampleStack.addForce(InputValue);

		UpdateValue();
	}

	void ForceReset(const uint16_t input)
	{
		IFilter16::ForceReset(input);
		Sum = input * _StackSize;
		for (uint8_t i = 0; i < _StackSize; i++)
		{
			SampleStack.add(input);
		}
	}

	//void Debug()
	//{
	//	Serial.print(F("WeightFactors "));
	//	for (uint8_t i = 0; i < _StackSize; i++)
	//	{
	//		Serial.print('|');
	//		Serial.print(WeightFactors[i]);
	//	}
	//	Serial.println('|');

	//	Serial.print(F("WeightsTotal: "));
	//	Serial.println(WeightsTotal);
	//}
};
#endif