# IFilter

A collection of, Arduino compatible, integer-only signal processing filters.
Extra process task to update values using common interface.

Templates and filters are provided in 8, 16 and 32 bit unsigned integers.


IFilterStepperTask - Useful for scheduled filter step.

IFilter - Common interface to all filters and base class for new filters.



Available filters:

EMA (Exponential Moving Average) - 8 Bit version has a distorted response.

![](https://raw.githubusercontent.com/GitMoDu/IFilter/master/Media/EMA.png)

DEMA (Double Exponential Moving Average) - 8 Bit version has a distorted response.

![](https://raw.githubusercontent.com/GitMoDu/IFilter/master/Media/DEMA.png)

Low Pass.

![](https://raw.githubusercontent.com/GitMoDu/IFilter/master/Media/LowPass.png)
![](https://raw.githubusercontent.com/GitMoDu/IFilter/master/Media/LowPassFactor.png)