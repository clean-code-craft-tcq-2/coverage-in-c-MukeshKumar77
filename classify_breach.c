#include "check_and_alert.h"

bool BatteryStatus;

const double coolingTypeLimits[][2] = {{PASSIVE_COOLING_LOW_LIMIT, PASSIVE_COOLING_HI_LIMIT},
					{HI_ACTIVE_COOLING_LOW_LIMIT, HI_ACTIVE_COOLING_HI_LIMIT},
					{MED_ACTIVE_COOLING_LOW_LIMIT, MED_ACTIVE_COOLING_HI_LIMIT}};

BreachType classifyTemperatureBreach(BatteryTypeAndInfo batteryInfo)
{
	 double lowerLimit = coolingTypeLimits[batteryInfo.coolingType][0];
	 double upperLimit = coolingTypeLimits[batteryInfo.coolingType][1];

	 return inferBreach(batteryInfo.temperature, lowerLimit, upperLimit);
}

BreachType inferBreach(double value, double lowerLimit, double upperLimit)
{
	bool stBuffer = STATUS_OK;
	BreachType retVal = NORMAL;
	if(value < lowerLimit)
	{
		stBuffer =  STATUS_NOT_OK;
		retVal = TOO_LOW;
	}
	else if(value > upperLimit)
	{
		stBuffer =  STATUS_NOT_OK;
		retVal = TOO_HIGH;
	}
	BatteryStatus = stBuffer;
	return retVal;
}
