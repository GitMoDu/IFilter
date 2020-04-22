/**
* Filter Validator
*
*
*/

#define DEBUG_LOG

#define SERIAL_BAUD_RATE 115200

#include <Arduino.h>
#include <IFilter.h>
#include <IFilterStepperTask.h>

#include <EMAFilter.h>
#include <LowPassFilter.h>

#define _TASK_OO_CALLBACKS


#include <TaskScheduler.h>

Scheduler SchedulerBase;

const uint8_t LowPassFactor = 5;
EMAFilter8 FilterEMA8(255);
LowPassFilter16<LowPassFactor> FilterLowPass16;

// <StepPeriodMillis, FilterCount>
class DebugStepperTask : public IFilterStepperTask<10, 2>
{
private: 
	uint64_t StepCount = 0;

public:
	DebugStepperTask(Scheduler* scheduler)
		: IFilterStepperTask<10, 2>(scheduler)
	{
	}

protected:
	void OnFiltersStepped()
	{
		StepCount++;
	}
};

DebugStepperTask StepperTask(&SchedulerBase);

void setup()
{
	Serial.begin(SERIAL_BAUD_RATE);
	while (!Serial)
		;
	delay(1000);


	StepperTask.enable();
}


void loop()
{
	SchedulerBase.execute();
}
