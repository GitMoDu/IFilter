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

EMAFilter16 Filter1;


#define TEST_SIZE 512

void Halt()
{
	Serial.println("Critical Error");
	delay(1000);
	while (1);;
}

void DebugImpulseResponse(IFilter* filter)
{
	Serial.println(F("Impulse response"));

	filter->ForceReset(0);
	filter->SetNextValue(UINT16_MAX);

	DebugFilter(filter);
}

void DebugNoiseResponse(IFilter* filter)
{
#define NOISE_RANGE_ABSOLUTE 10000

	random(analogRead(A0));

	Serial.println(F("Impulse response"));

	filter->ForceReset(UINT16_MIDDLE);

	for (uint16_t i = 0; i < TEST_SIZE; i++)
	{
		Serial.println(filter->GetCurrentValue());
		filter->StepValue();

		if (random(1))
		{
			filter->SetNextValue(map(random(100), 0, 100, 0, NOISE_RANGE_ABSOLUTE));
		}
		else
		{
			filter->SetNextValue(map(random(100), 0, 100, 0, -NOISE_RANGE_ABSOLUTE));
		}
		
	}

	DebugFilter(filter);
}

void DebugFilter(IFilter* filter)
{
	for (uint16_t i = 0; i < TEST_SIZE; i++)
	{
		Serial.println(filter->GetCurrentValue());
		filter->StepValue();
	}
}

void setup()
{
}

void loop()
{
	Serial.begin(SERIAL_BAUD_RATE);
	while (!Serial)
		;
	delay(1000);

	Serial.println(F("Filter Validator"));

	DebugImpulseResponse(&Filter1);

	DebugNoiseResponse(&Filter1);
}