// ProcessFilterManager.h

#ifndef _PROCESSFILTERMANAGER_h
#define _PROCESSFILTERMANAGER_h

#define _TASK_OO_CALLBACKS
#define _TASK_SLEEP_ON_IDLE_RUN
#include <TaskSchedulerDeclarations.h>

#include <IFilter.h>


class StepperListener
{
public:
	virtual void OnFiltersStepped() {}
};

template <const uint32_t UpdatePeriod,
	const uint8_t MaxCount = 5>
	class IFilterStepperTask : public Task
{
private:
	IFilter* Filters[MaxCount];
	uint8_t FilterCount = 0;

	StepperListener* Listener = nullptr;

public:
	IFilterStepperTask(Scheduler* scheduler, StepperListener* listener = nullptr)
		: Task(UpdatePeriod, TASK_FOREVER, scheduler, false)
	{
		for (uint8_t i = 0; i < MaxCount; i++)
		{
			Filters[i] = nullptr;
		}
		FilterCount = 0;
	}

	virtual bool Callback()
	{
		for (uint8_t i = 0; i < FilterCount; i++)
		{
			Filters[i]->Step();
		}

		if (Listener != nullptr)
		{
			Listener->OnFiltersStepped();
		}

		return true;
	}

	bool AddFilter(IFilter& newFilter)
	{
		if (FilterCount < MaxCount)
		{
			Filters[FilterCount] = &newFilter;
			FilterCount++;

			return true;
		}

		return false;
	}

	bool AddFilter(IFilter* newFilter)
	{
		if (FilterCount < MaxCount)
		{
			Filters[FilterCount] = newFilter;
			FilterCount++;

			return true;
		}

		return false;
	}

#ifdef FILTER_DEBUG
	void Debug(Stream* serial)
	{
		uint32_t ComputeDuration = micros();

		for (uint8_t i = 0; i < FilterCount; i++)
		{
			Filters[i]->Step();
		}

		ComputeDuration = micros() - ComputeDuration;
		serial->print(F("Filters count: "));
		serial->print(FilterCount);
		serial->println(F("."));
		serial->print(F("Took "));
		serial->print(ComputeDuration);
		serial->print(F(" us. (Average "));
		serial->print(ComputeDuration / FilterCount);
		serial->println(F(" us per filter)"));
	}
#endif
};
#endif