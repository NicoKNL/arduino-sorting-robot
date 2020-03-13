#include "Led.hh"
#include "Reporter.hh"
#include <wiringPi.h>
#include <dzn/locator.hh>
#include <dzn/runtime.hh>

int PIN = 5;
void Led::iLed_turnOff() {
	digitalWrite(PIN, LOW);
}
void Led::iLed_turnOn(){
	digitalWrite(PIN, HIGH);
}
