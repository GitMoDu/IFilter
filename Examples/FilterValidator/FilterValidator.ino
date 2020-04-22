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

const uint8_t LowPassFactor = 5;

EMAFilter8 FilterEMA8(255);
DEMAFilter8 FilterDEMA8(255);
LowPassFilter8<LowPassFactor> FilterLowPass8;
EMAFilter16 FilterEMA16(255);
DEMAFilter16 FilterDEMA16(255);
LowPassFilter16<LowPassFactor> FilterLowPass16;
EMAFilter32 FilterEMA32(255);
DEMAFilter32 FilterDEMA32(255);
LowPassFilter32<LowPassFactor> FilterLowPass32;

const uint16_t LinearTestSize = 200;
const uint16_t ImpulseTestSize = 200;
const uint8_t StepMultiplier = 1;
const uint16_t TestCount = 1000;


void DebugStepResponse(IFilter8* filter8, IFilter16* filter16, IFilter32* filter32)
{
	Serial.println(F("Step response"));

	filter8->ForceReset(0);
	filter16->ForceReset(0);
	filter32->ForceReset(0);
	filter8->Set(UINT8_MAX);
	filter16->Set(UINT16_MAX);
	filter32->Set(UINT32_MAX);

	for (uint16_t i = 0; i < ImpulseTestSize; i++)
	{
		for (uint8_t i = 0; i < StepMultiplier; i++)
		{
			filter8->Step();
			filter16->Step();
			filter32->Step();
		}
		Serial.print(i * StepMultiplier);
		Serial.print('\t');
		Serial.print(map(filter8->Get(), 0, UINT8_MAX, 0, UINT16_MAX));
		Serial.print('\t');
		Serial.print(filter16->Get());
		Serial.print('\t');
		Serial.println((uint32_t)filter32->Get() / UINT16_MAX);
	}
}

void DebugStepDuration(IFilter8* filter8, IFilter16* filter16, IFilter32* filter32)
{
	uint32_t DurationNanos = 0;
	filter8->ForceReset(UINT8_MAX);
	filter16->ForceReset(UINT16_MAX);
	filter32->ForceReset(UINT32_MAX);
	uint32_t DurationTotal = micros();

	Serial.print(F("Step duration (8 Bit)"));
	DurationTotal = micros();
	for (uint16_t i = 0; i < TestCount; i++)
	{
		filter8->Step();
	}
	DurationTotal = micros() - DurationTotal;
	Serial.print((DurationTotal * 1000L) / TestCount);
	Serial.println(F(" ns"));

	Serial.print(F("Step duration (16 Bit)"));
	DurationTotal = micros();
	for (uint16_t i = 0; i < TestCount; i++)
	{
		filter16->Step();
	}
	DurationTotal = micros() - DurationTotal;
	Serial.print((DurationTotal * 1000L) / TestCount);
	Serial.println(F(" ns"));

	Serial.print(F("Step duration (32 Bit)"));
	DurationTotal = micros();
	for (uint16_t i = 0; i < TestCount; i++)
	{
		filter32->Step();
	}
	DurationTotal = micros() - DurationTotal;
	Serial.print((DurationTotal * 1000L) / TestCount);
	Serial.println(F(" ns"));
}

void setup()
{
	Serial.begin(SERIAL_BAUD_RATE);
	while (!Serial)
		;
	delay(1000);


	Serial.println(F("Filter EMA"));
	DebugStepResponse(&FilterEMA8, &FilterEMA16, &FilterEMA32);
	DebugStepDuration(&FilterEMA8, &FilterEMA16, &FilterEMA32);

	Serial.println(F("Filter DEMA"));
	DebugStepResponse(&FilterDEMA8, &FilterDEMA16, &FilterDEMA32);
	DebugStepDuration(&FilterDEMA8, &FilterDEMA16, &FilterDEMA32);
	
	Serial.println(F("Filter Low Pass"));
	DebugStepResponse(&FilterLowPass8, &FilterLowPass16, &FilterLowPass32);
	DebugLowPassFactor();
	DebugStepDuration(&FilterLowPass8, &FilterLowPass16, &FilterLowPass32);
}

void DebugLowPassFactor()
{
	LowPassFilter16<1> Factor1;
	LowPassFilter16<2> Factor2;
	LowPassFilter16<3> Factor3;
	LowPassFilter16<4> Factor4;
	LowPassFilter16<5> Factor5;
	LowPassFilter16<6> Factor6;
	LowPassFilter16<7> Factor7;
	LowPassFilter16<8> Factor8;

	Factor1.ForceReset(0);
	Factor1.Set(UINT16_MAX);
	Factor2.ForceReset(0);
	Factor2.Set(UINT16_MAX);
	Factor3.ForceReset(0);
	Factor3.Set(UINT16_MAX);
	Factor4.ForceReset(0);
	Factor4.Set(UINT16_MAX);
	Factor5.ForceReset(0);
	Factor5.Set(UINT16_MAX);
	Factor6.ForceReset(0);
	Factor6.Set(UINT16_MAX);
	Factor7.ForceReset(0);
	Factor7.Set(UINT16_MAX);
	Factor8.ForceReset(0);
	Factor8.Set(UINT16_MAX);

	Serial.println("Low Pass Factor Step Response");
	Serial.println("Sample\t1\t2\t3\t4\t5\t6\t7\t8");

	for (uint16_t i = 0; i < ImpulseTestSize; i++)
	{
		Factor1.Step();
		Factor2.Step();
		Factor3.Step();
		Factor4.Step();
		Factor5.Step();
		Factor6.Step();
		Factor7.Step();
		Factor8.Step();

		Serial.print(i * StepMultiplier);
		Serial.print('\t');
		Serial.print(Factor1.Get());
		Serial.print('\t');
		Serial.print(Factor2.Get());
		Serial.print('\t');
		Serial.print(Factor3.Get());
		Serial.print('\t');
		Serial.print(Factor4.Get());
		Serial.print('\t');
		Serial.print(Factor5.Get());
		Serial.print('\t');
		Serial.print(Factor6.Get());
		Serial.print('\t');
		Serial.print(Factor7.Get());
		Serial.print('\t');
		Serial.print(Factor8.Get());
		Serial.println();
	}
}

void loop()
{
}
