#include <Servo.h>

///////////////// DEBUG TOGGLE ////////////////////////////
// Note: When using the serial monitor make sure to disable
//       line endings by setting it to 'No line ending'.
//       Default is 'Newline'.
bool DEBUG = true;
char input;
bool black_debug_active;
bool white_debug_active;
///////////////////////////////////////////////////////////


// Nico: Potentially the OUT_PINs must be pin 9 and 10. Current config works on my funduino nano however.

// Pins for the black disk pusher
#define black_IN_PIN 4
#define black_OUT_PIN 5 

// Pins for the white disk pusher
#define white_IN_PIN 6
#define white_OUT_PIN 7

// Pins for debug output
#define black_DEBUG_PIN 9
#define white_DEBUG_PIN 10

// Servo objects which allow easy control of the servos
Servo sb; // servo black
Servo sw; // servo white


// The following values are guestimates of what looks to be correct. Please tweak.
int angle_inactive = 100;
int angle_active = 150;
int move_delay = 1000;

// Tracking position in logic
bool black_active;
bool white_active;


void setup() {
  // Setup input pins
  pinMode(black_IN_PIN, INPUT);
  pinMode(white_IN_PIN, INPUT);
  
  // Register pins to the servo objects
  sb.attach(black_OUT_PIN);
  sw.attach(white_OUT_PIN);

  //// Range of motion test.
  // Initialize to min position (0)
  moveBoth(0);
  // Initialize to max position (180)
  moveBoth(180);

  // Set as active to have good follow up behavior in the loop
  black_active = true;
  white_active = true;

  if (DEBUG) {
    // Enable the debug pins
    pinMode(black_DEBUG_PIN, OUTPUT);
    pinMode(white_DEBUG_PIN, OUTPUT);

    // Enable serial
    Serial.begin(9600);
    Serial.println("Char to send black signal: b");
    Serial.println("Char to send white signal: w");

    // Enable tracking for toggle behaviour
    black_debug_active = false;
    white_debug_active = false;
  }
}

void moveBoth(int angle) {
  sb.write(angle);
  sw.write(angle);
  delay(move_delay); // Time to allow the servos to go to the angle 
}

void moveWhite(int angle) {
  sw.write(angle);
  delay(move_delay); // Time to allow the servos to go to the angle 
}

void moveBlack(int angle) {
  sb.write(angle);
  delay(move_delay); // Time to allow the servos to go to the angle 
}

void loop() 
{
  if (DEBUG) {
    if (Serial.available()) {
      input = Serial.read();
      Serial.print("You typed: ");
      Serial.println(input);

      if (input == 'b') {
        black_debug_active = !black_debug_active;
        digitalWrite(black_DEBUG_PIN, black_debug_active);
      } else if (input == 'w') {
        white_debug_active = !white_debug_active;
        digitalWrite(white_DEBUG_PIN, white_debug_active);
      } else {
        Serial.println("Please use 'b' or 'w'.");
      }
    }
  }

  if (digitalRead(black_IN_PIN) && !black_active) {
    moveBlack(angle_active);
    black_active = true;
  } else if (!digitalRead(black_IN_PIN) && black_active) {
    moveBlack(angle_inactive);
    black_active = false;
  } else {
    // Do nothing...
  }

  if (digitalRead(white_IN_PIN) && !white_active) {
    moveWhite(angle_active);
    white_active = true;
  } else if (!digitalRead(white_IN_PIN) && white_active) {
    moveWhite(angle_inactive);
    white_active = false;
  } else {
    // Do nothing...
  }
}
