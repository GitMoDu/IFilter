// FilterGroupTemplate.h

#ifndef _FILTERGROUP_h
#define _FILTERGROUP_h

#define FILTER_DEBUG
#include <IFilter.h>

#ifndef DEFAULT_FILTER_MAX_COUNT
#define DEFAULT_FILTER_MAX_COUNT 5
#endif // !FILTER_MAX_COUNT


template <const uint8_t MaxCount = DEFAULT_FILTER_MAX_COUNT>
class FilterGroupTemplate
{
private:
	IFilter * Filters[MaxCount];
	uint8_t FilterCount = 0;

public:
	FilterGroupTemplate()
	{
		for (uint8_t i = 0; i < MaxCount; i++)
		{
			Filters[i] = nullptr;
		}
		FilterCount = 0;
	}

	bool AddFilter(IFilter &newFilter)
	{
		if (FilterCount < MaxCount - 1)
		{
			Filters[FilterCount] = &newFilter;
			FilterCount++;

			return true;
		}

		return false;
	}

	void StepAll()
	{
		for (uint8_t i = 0; i < MaxCount; i++)
		{
			if (Filters[i] != nullptr)
			{
				Filters[i]->StepValue();
			}
		}
	}

#ifdef FILTER_DEBUG
	void Debug(Stream* serial)
	{
		uint32_t ComputeDuration = micros();

		StepAll();

		ComputeDuration = micros() - ComputeDuration;
		serial->print(F("Filters count: "));
		serial->print(FilterCount);
		serial->println(F("."));
		serial->print(F("Took "));
		serial->print(ComputeDuration);
		serial->print(F(" us. ("));
		serial->print(ComputeDuration / FilterCount);
		serial->println(F(" us per filter)"));
	}
#endif
};
#endif