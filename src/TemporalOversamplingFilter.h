// TemporalOversamplingFilter.h

#ifndef _TEMPORAL_OVERSAMPLING_FILTER_h
#define _TEMPORAL_OVERSAMPLING_FILTER_h

#include <IFilter.h>
#include <RingBufCPP.h>


#define TEMPORAL_OVERSAMPLING_FILTER_WEIGHT_DECAY_FACTOR_DEFAULT 18


///StackSize equals the amount of samples before settle:
/// more sample, less harsh curve.
///The filter factor decides the importance of freshness of value:
/// bigger factor, faster response.
///Settle time is fixed depending on filter properties, input value delta will not change settle time.
template <uint8_t StackSize, uint8_t Factor>
class TemporalOversamplingFilter16 : public IFilter16
{
private:
	uint32_t Sum = 0;
	RingBufCPP<uint16_t, StackSize> SampleStack;

	uint16_t Value = 0;

	uint16_t WeightsTotal = 0;
	uint8_t WeightFactors[StackSize];

private:
	inline uint8_t GetNextWeight(const uint8_t current, const uint8_t factor)
	{
		return ceil((double)current / ((double)factor));
	}

	uint8_t DebugCount = 0;
	inline void UpdateValue()
	{
		Sum = 0;
		if (SampleStack.isFull())
		{
			if (DebugCount > 0)
			{
				Serial.println("Sum____\tPeek_____\tWeight____");
			}
			for (uint8_t i = 0; i < StackSize; i++)
			{
				if (DebugCount > 0)
				{
					Serial.print(Sum);
					Serial.print('\t');
					Serial.print(*SampleStack.peek(SampleStack.numElements() - 1 - i));
					Serial.print('\t');
					Serial.println(((uint16_t)WeightFactors[i]));
				}

				Sum += (uint32_t)(*SampleStack.peek(SampleStack.numElements() - 1 - i)) * ((uint16_t)WeightFactors[i]);
			}
		}
		else
		{
			Sum = 0;//No value ready yet;
		}

		if (DebugCount > 0)
		{
			DebugCount--;
		}

		Value = constrain(Sum / WeightsTotal, 0, UINT16_MAX);
	}

	void FillWeightFactors(const uint8_t factor)
	{
		uint8_t FillWeight = UINT8_MAX;

		WeightsTotal = 0;

		for (uint8_t i = 0; i < StackSize; i++)
		{
			WeightFactors[i] = FillWeight;
			WeightsTotal += FillWeight;
			FillWeight = GetNextWeight(FillWeight, factor);
		}
	}

public:
	TemporalOversamplingFilter16(const uint16_t startingValue = UINT16_MIDDLE)
		: IFilter16(startingValue)
		, SampleStack()
	{
		FillWeightFactors(Factor);
		ForceReset(startingValue);
	}

	//This filter does not change output when you step it, only when you feed it.
	void StepValue()
	{
		UpdateValue();
	}

	uint16_t GetCurrentValue()
	{
		UpdateValue();

		return Value;
	}

	void SetNextValue(const uint16_t input)
	{
		SampleStack.addForce(input);
	}

	void ForceReset(const uint16_t input)
	{
		IFilter16::ForceReset(input);
		for (uint8_t i = 0; i < StackSize; i++)
		{
			SampleStack.addForce(input);
		}
	}

	void Debug()
	{
		Serial.print(F("WeightFactors "));
		for (uint8_t i = 0; i < StackSize; i++)
		{
			Serial.print('|');
			Serial.print(WeightFactors[i]);
		}
		Serial.println('|');

		Serial.print(F("WeightsTotal "));
		Serial.println(WeightsTotal);

	}
};
#endif