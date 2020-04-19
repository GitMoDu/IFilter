/**
* Filter Validator
*
*
*/

#define DEBUG_LOG

#define SERIAL_BAUD_RATE 115200

#include <Arduino.h>
#include <IFilter.h>

#include <EMAFilter.h>
#include <DEMAFilter.h>
#include <LowPassFilter.h>
#include "FourierTransformAnalyser.h"

EMAFilter8 FilterEMA8(255);
DEMAFilter8 FilterDEMA8(255);
LowPassFilter8<255> FilterLowPass8;
EMAFilter16 FilterEMA16(255);
DEMAFilter16 FilterDEMA16(255);
LowPassFilter16<> FilterLowPass16;
EMAFilter32 FilterEMA32(255);
DEMAFilter32 FilterDEMA32(255);
LowPassFilter32<20> FilterLowPass32;

FourierTransformAnalyser FFT;

const uint16_t LinearTestSize = 255;
const uint16_t ImpulseTestSize = 200;
const uint8_t StepMultiplier = 1;
const uint16_t TestCount = 1000;


void DebugLinearResponse(IFilter8* filter)
{
	Serial.println(F("Linear response"));

	filter->ForceReset(0);

	for (uint16_t i = 0; i < LinearTestSize; i++)
	{
		filter->Set(map(i, 0, LinearTestSize, 0, UINT8_MAX));

		for (uint8_t i = 0; i < StepMultiplier; i++)
		{
			filter->Step();
		}

		Serial.print(i);
		Serial.print('\t');
		Serial.print(filter->GetTarget());
		Serial.print('\t');
		Serial.println(filter->Get());
	}
}

void DebugLinearResponse(IFilter16* filter)
{
	Serial.println(F("Linear response"));

	filter->ForceReset(0);

	for (uint16_t i = 0; i < LinearTestSize; i++)
	{
		filter->Set(map(i, 0, LinearTestSize, 0, UINT16_MAX));

		for (uint8_t i = 0; i < StepMultiplier; i++)
		{
			filter->Step();
		}

		Serial.print(i);
		Serial.print('\t');
		Serial.print(filter->GetTarget());
		Serial.print('\t');
		Serial.println(filter->Get());
	}
}

void DebugLinearResponse(IFilter32* filter)
{
	Serial.println(F("Linear response"));

	filter->ForceReset(0);

	for (uint16_t i = 0; i < LinearTestSize; i++)
	{
		//filter->Set(map(i, 0, LinearTestSize, 0, UINT32_MAX));
		filter->Set(((uint64_t)i* UINT32_MAX) / LinearTestSize);

		for (uint8_t i = 0; i < StepMultiplier; i++)
		{
			filter->Step();
		}

		Serial.print(i);
		Serial.print('\t');
		Serial.print(filter->GetTarget());
		Serial.print('\t');
		Serial.println(filter->Get());
	}
}

void DebugStepResponse(IFilter8* filter)
{
	Serial.println(F("Step response"));

	filter->ForceReset(0);
	filter->Set(UINT8_MAX);

	for (uint16_t i = 0; i < LinearTestSize; i++)
	{
		for (uint8_t i = 0; i < StepMultiplier; i++)
		{
			filter->Step();
		}
		Serial.print(i);
		Serial.print('\t');
		Serial.println(filter->Get());
	}
}

void DebugStepDuration(IFilter* filter)
{
	uint32_t DurationNanos = 0;
	uint32_t DurationTotal = micros();

	for (uint16_t i = 0; i < TestCount; i++)
	{
		filter->Step();
	}

	DurationTotal = micros() - DurationTotal;
	DurationNanos = DurationTotal / (TestCount / 1000);

	Serial.print(F("Step duration "));
	Serial.print(DurationNanos);
	Serial.println(F(" ns"));
}

void DebugStepResponse(IFilter16* filter)
{
	Serial.println(F("Step response"));

	filter->ForceReset(0);
	filter->Set(UINT16_MAX);

	for (uint16_t i = 0; i < ImpulseTestSize; i++)
	{
		for (uint8_t i = 0; i < StepMultiplier; i++)
		{
			filter->Step();
		}
		Serial.print(i);
		Serial.print('\t');
		Serial.println(filter->Get());
	}
}

void DebugStepResponse(IFilter32* filter)
{
	Serial.println(F("Step response"));

	filter->ForceReset(0);
	filter->Set(UINT32_MAX);

	for (uint16_t i = 0; i < ImpulseTestSize; i++)
	{
		for (uint8_t i = 0; i < StepMultiplier; i++)
		{
			filter->Step();
		}
		Serial.print(i);
		Serial.print('\t');
		Serial.println(filter->Get());
	}
}

void DebugFilterResponse(IFilter8* filter)
{
	DebugLinearResponse(filter);

	DebugStepResponse(filter);
}

void DebugFilterResponse(IFilter16* filter)
{
	DebugLinearResponse(filter);

	DebugStepResponse(filter);
}

void DebugFilterResponse(IFilter32* filter)
{
	DebugLinearResponse(filter);

	DebugStepResponse(filter);
}

void setup()
{
	Serial.begin(SERIAL_BAUD_RATE);
	while (!Serial)
		;
	delay(1000);


	Serial.println(F("Filter EMA"));

	DebugFilterResponse(&FilterEMA8);
	DebugFilterResponse(&FilterEMA16);
	FilterEMA32.Set(UINT8_MAX);
	DebugStepDuration(&FilterEMA8);
	FilterEMA32.Set(UINT16_MAX);
	DebugStepDuration(&FilterEMA16);
	FilterEMA32.Set(UINT32_MAX);
	DebugStepDuration(&FilterEMA32);


	Serial.println(F("Filter DEMA"));
	DebugFilterResponse(&FilterDEMA8);
	DebugFilterResponse(&FilterDEMA16);
	DebugStepDuration(&FilterDEMA8);
	DebugStepDuration(&FilterDEMA16);
	DebugStepDuration(&FilterDEMA32);

	Serial.println(F("Filter LowPass"));
	DebugFilterResponse(&FilterLowPass8);
	DebugFilterResponse(&FilterLowPass16);
	DebugStepDuration(&FilterLowPass8);
	DebugStepDuration(&FilterLowPass16);
	DebugStepDuration(&FilterLowPass32);
}

void loop()
{
}
