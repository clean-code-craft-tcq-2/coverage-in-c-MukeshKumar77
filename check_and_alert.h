#include <stdio.h>
#include <stdbool.h>

#pragma once

#define PASSIVE_COOLING_LOW_LIMIT 			0
#define PASSIVE_COOLING_HI_LIMIT			 35
#define HI_ACTIVE_COOLING_LOW_LIMIT			0
#define HI_ACTIVE_COOLING_HI_LIMIT 			45
#define MED_ACTIVE_COOLING_LOW_LIMIT		0
#define MED_ACTIVE_COOLING_HI_LIMIT			40

#define STATUS_OK							0
#define STATUS_NOT_OK						1

typedef enum {
  PASSIVE_COOLING,
  HI_ACTIVE_COOLING,
  MED_ACTIVE_COOLING
} CoolingType;

typedef enum {
  NORMAL,
  TOO_LOW,
  TOO_HIGH
} BreachType;

typedef enum {
  TO_CONTROLLER,
  TO_EMAIL
} AlertTarget;

typedef struct {
  CoolingType coolingType;
  float temperature;
} BatteryTypeAndInfo;

extern bool (*const ReceiverTarget[]) (BreachType breachType);

extern bool BatteryStatus;
extern char* EmailRecepient;

bool checkAndAlert(AlertTarget alertTarget, BatteryTypeAndInfo batteryInfo);
BreachType classifyTemperatureBreach(BatteryTypeAndInfo batteryInfo);
BreachType inferBreach(double value, double lowerLimit, double upperLimit);
bool sendToController(BreachType breachType);
void setEmailRecepient(char* recepient);
bool sendToEmail(BreachType breachType);
