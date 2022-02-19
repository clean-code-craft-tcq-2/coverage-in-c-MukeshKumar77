#include "check_and_alert.h"

char* EmailRecepient;

const char* temperatureMessage[] = {"Temperature is normal",
									   "Error: Temperature is too low",
									   "Error: Temperature is too high"};

bool (*const ReceiverTarget[]) (BreachType breachType) =
{
	&sendToController,
	&sendToEmail
};

void setEmailRecepient(char* recepient)
{
	EmailRecepient = recepient;
}

bool checkAndAlert(AlertTarget alertTarget, BatteryTypeAndInfo batteryInfo)
{
	BreachType breachType = classifyTemperatureBreach(batteryInfo);
	(*ReceiverTarget[alertTarget])(breachType);
    return BatteryStatus;
}

bool sendToController(BreachType breachType)
{
	const unsigned short header = 0xfeed;
	printf("%x : %x\n", header, breachType);
	return true;
}

bool sendToEmail(BreachType breachType)
{
	printf("To: %s\n", EmailRecepient);
	printf("%s\n", temperatureMessage[breachType]);
	return true;
}
