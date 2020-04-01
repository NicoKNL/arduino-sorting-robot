// Nico: Assumption is that the NEMA17 is configured to run 1/64 as stepsize

///////////////// DEBUG TOGGLE ////////////////////////////
// Note: When using the serial monitor make sure to disable
//       line endings by setting it to 'No line ending'.
//       Default is 'Newline'.
bool DEBUG = true;
char input;
bool motor_active;

// Pins for debug output
#define motor_DEBUG_PIN 9
///////////////////////////////////////////////////////////

// Define stepper motor connections
#define motor_IN_PIN 4  // For reading whether the motor should run
#define motor_OUT_PIN 5 // For sending the output to the stepper driver

// Additional config
int STEP_DELAY = 10; // Higher values = lower speed

void setup () {
  // Declare pins as input
  pinMode(motor_IN_PIN, INPUT);
  pinMode(motor_OUT_PIN, OUTPUT);
  
  if (DEBUG) {
    // Enable the debug pins
    pinMode(motor_DEBUG_PIN, OUTPUT);

    // Enable serial
    Serial.begin(9600);
    Serial.println("Char to send toggle motor signal: t");

    // Enable tracking for toggle behaviour
    motor_active = false;
  }
}

/*
 * Steps the motor 1 step ahead
 */
void stepMotor() {
  digitalWrite(motor_OUT_PIN, HIGH);
  delayMicroseconds(STEP_DELAY);
  digitalWrite(motor_OUT_PIN, LOW);
  delayMicroseconds(STEP_DELAY);
}

void loop() {
  if (DEBUG) {
    if (Serial.available()) {
      input = Serial.read();
      Serial.print("You typed: ");
      Serial.println(input);

      if (input == 't') {
        motor_active = !motor_active;
        digitalWrite(motor_DEBUG_PIN, motor_active);
      } else {
        Serial.println("Please use 't'.");
      }
    }
  }

  if (digitalRead(motor_IN_PIN) && !motor_active) {
    motor_active = true;
  } else if (!digitalRead(motor_IN_PIN) && motor_active) {
    motor_active = false;
  } else {
    // Do nothing...
  }

  if (motor_active) {
    stepMotor();
  }
}
