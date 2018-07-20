// ProcessFilterManager.h

#ifndef _PROCESSFILTERMANAGER_h
#define _PROCESSFILTERMANAGER_h



#define _TASK_OO_CALLBACKS
#include <TaskSchedulerDeclarations.h>

#include <FilterGroup.h>

#ifndef FILTER_UPDATE_INTERVAL
#define FILTER_UPDATE_INTERVAL 10
#endif // !FILTER_UPDATE_INTERVAL


class ProcessFilterManager : public Task
{
private:
	void(*OnValuesUpdated)(void) = nullptr;
	FilterGroup Filters;

public:
	ProcessFilterManager(Scheduler* scheduler, void(&onValuesUpdated)())
		: Task(FILTER_UPDATE_INTERVAL, TASK_FOREVER, scheduler, false)
	{
	}

public:
	bool Callback()
	{
		Filters.StepAll();

		if (OnValuesUpdated != nullptr)
		{
			OnValuesUpdated();
		}

		return false;
	}
};
#endif