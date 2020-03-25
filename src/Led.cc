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


// #include <iostream>
// #include <wiringPi.h>

// #define s0 3 // GPIO 22
// #define s1 2 // GPIO 27
// #define s2 0 // GPIO 17
// #define LOW 0
// #define HIGH 1

// int main() {
//     wiringPiSetup();
//     pinMode(s0, OUTPUT);
//     pinMode(s1, OUTPUT);
//     pinMode(s2, OUTPUT);

//     for (int i = 0; i < 10; ++i){
//         // 0
//         digitalWrite(s0, LOW);
//         digitalWrite(s1, LOW);
//         digitalWrite(s2, LOW);

//         delay(500);
//         std::cout << "next\n";
//         // 1
//         digitalWrite(s0, HIGH);
//         digitalWrite(s1, LOW);
//         digitalWrite(s2, LOW);

//         delay(500);
//         std::cout << "next\n";

//         // 2
//         digitalWrite(s0, LOW);
//         digitalWrite(s1, HIGH);
//         digitalWrite(s2, LOW);

//         delay(500);
//         std::cout << "next\n";

//         // 3
//         digitalWrite(s0, HIGH);
//         digitalWrite(s1, HIGH);
//         digitalWrite(s2, LOW);

//         delay(500);
//         std::cout << "next\n";

//         // 4
//         digitalWrite(s0, LOW);
//         digitalWrite(s1, LOW);
//         digitalWrite(s2, HIGH);

//         delay(500);
//         std::cout << "next\n";

//         // 5
//         digitalWrite(s0, HIGH);
//         digitalWrite(s1, LOW);
//         digitalWrite(s2, HIGH);

//         delay(500);
//         std::cout << "next\n";
//         // 0
//         digitalWrite(s0, LOW);
//         digitalWrite(s1, LOW);
//         digitalWrite(s2, LOW);
//     }
//     return 0;
// }
