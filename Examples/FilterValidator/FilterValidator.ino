/**
* Filter Validator
*
*
*/

#define DEBUG_LOG

#define SERIAL_BAUD_RATE 57600

#include <Arduino.h>
#include <IFilter.h>

#include <EMAFilter.h>
#include <TemporalOversamplingFilter.h>

DEMAFilter16 FilterEMA;
DEMAFilter16 FilterDEMA;


#define NOISE_RANGE_ABSOLUTE 1000

#define TEST_SIZE 256


void DebugImpulseResponse(IFilter* filter)
{
	Serial.println(F("Impulse response"));

	filter->ForceReset(0);
	

	Serial.println(UINT16_MAX);
	Serial.println(0);
	Serial.println(0);
	for (uint16_t i = 0; i < TEST_SIZE; i++)
	{
		Serial.println(filter->GetCurrentValue());
		filter->StepValue();

		if (i == 0)
		{
			filter->SetNextValue(UINT16_MAX);
		}else if (i == 1)
		{
			filter->SetNextValue(0);
		}	
	}
}

void DebugLinearResponse(IFilter* filter)
{
	Serial.println(F("Linear response"));

	filter->ForceReset(0);

	Serial.println(UINT16_MAX);
	Serial.println(0);
	Serial.println(0);
	for (uint16_t i = 0; i < TEST_SIZE; i++)
	{
		Serial.println(filter->GetCurrentValue());
		filter->StepValue();

		filter->SetNextValue(map(i, 0, TEST_SIZE, 0, UINT16_MAX));
	}
}

void DebugStepResponse(IFilter* filter)
{
	Serial.println(F("Step response"));

	filter->ForceReset(0);
	filter->SetNextValue(UINT16_MIDDLE);

	Serial.println(UINT16_MAX);
	Serial.println(0);
	Serial.println(0);
	for (uint16_t i = 0; i < TEST_SIZE; i++)
	{
		Serial.println(filter->GetCurrentValue());
		filter->StepValue();
	}
}

void DebugNoiseResponse(IFilter* filter)
{
	random(analogRead(A0));

	Serial.println(F("Noise response"));

	filter->ForceReset(UINT16_MIDDLE);

	Serial.println(UINT16_MAX);
	Serial.println(0);
	Serial.println(0);
	for (uint16_t i = 0; i < TEST_SIZE; i++)
	{
		filter->StepValue();
		Serial.println(filter->GetCurrentValue());
		if (i%2==0)
		{
			filter->SetNextValue(UINT16_MIDDLE + random(NOISE_RANGE_ABSOLUTE));
		}
		else
		{
			filter->SetNextValue(UINT16_MIDDLE - random(NOISE_RANGE_ABSOLUTE));
		}		
	}
}

void DebugFilterResponse(IFilter* filter)
{
	DebugLinearResponse(filter);

	DebugStepResponse(filter);

	DebugImpulseResponse(filter);

	DebugNoiseResponse(filter);
}

void setup()
{
	Serial.begin(SERIAL_BAUD_RATE);
	while (!Serial)
		;
	delay(1000);

	Serial.println(F("Filter Example"));

	FilterEMA.SetRatio(150);
	DebugFilterResponse(&FilterEMA);

	FilterDEMA.SetRatio(150);
	DebugFilterResponse(&FilterDEMA);
	
}

void loop()
{
}