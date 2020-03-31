#include "Led.hh"
#include <wiringPi.h>
#include <iostream>

Led::Led(const dzn::locator& loc) : skel::Led(loc) {

}

void Led::led_initialise (int pin) {
  std::cout << "[Led] Initialising on pin: " << mPin << ".\n";
  mPin = pin;
}

void Led::led_turnOn() {
  std::cout << "[Led] gaat aan op: " << mPin << '\n';
	digitalWrite(mPin, HIGH);
}
void Led::led_turnOff(){
  std::cout << "[Led] gaat uit op: " << mPin << '\n';
	digitalWrite(mPin, LOW);
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
