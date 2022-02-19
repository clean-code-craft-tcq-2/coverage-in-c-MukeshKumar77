#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include "test/catch.hpp"
#include "check_and_alert.h"

BatteryTypeAndInfo batteryData;

	TEST_CASE("check email recipient set is correctly"){
	setEmailRecepient("Kratos.GodOfWar@sony.com");
	assert(!strcmp(EmailRecepient, "Kratos.GodOfWar@sony.com"));
  }

	TEST_CASE("test of check_and_alert method working") {
	batteryData.coolingType = PASSIVE_COOLING;
	batteryData.temperature = 24;
	assert(checkAndAlert(TO_CONTROLLER, batteryData) == STATUS_OK);

	batteryData.coolingType = PASSIVE_COOLING;
	batteryData.temperature = 99;
	assert(checkAndAlert(TO_EMAIL, batteryData) == STATUS_NOT_OK);
  }

	TEST_CASE("infers the breach according to limits") {
	assert(inferBreach(12, 20, 30) == TOO_LOW);
	assert(inferBreach(25, 20, 30) == NORMAL);
	assert(inferBreach(31, 20, 30) == TOO_HIGH);
  }

	TEST_CASE("check working of cooling type classification") {
	batteryData.coolingType = PASSIVE_COOLING;
	batteryData.temperature = 36;
	assert(classifyTemperatureBreach(batteryData) == TOO_HIGH);

	batteryData.coolingType = HI_ACTIVE_COOLING;
	batteryData.temperature = 46;
	assert(classifyTemperatureBreach(batteryData) == TOO_HIGH);

	batteryData.coolingType = MED_ACTIVE_COOLING;
	batteryData.temperature = 41;
	assert(classifyTemperatureBreach(batteryData) == TOO_HIGH);
  }

	TEST_CASE("check of sending message to either email or controller") {
	assert(sendToController(TOO_HIGH) == true);
	assert(sendToEmail(TOO_HIGH) == true);
  }

