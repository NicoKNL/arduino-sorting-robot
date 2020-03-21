// Pin definitions
byte sensorColourReflection = A0;   // Disk colour detector, reflection
byte sensorColourPresence = A1;     // Disk colour detector, presence
byte sensorWhitePresence = A2;      // Disk presence at white basket
byte sensorBlackPresence = A3;      // Disk presence at black basket
byte sensorFactoryPresence = A4;    // Disk presence at factory belt
byte sensorWheelRotation = A5;      // Sense one-push rotation --> needs debouncing (done in this arduino program)

byte outputRotateWheel = 3;         // Output pin to rotate wheel

// Configuration using variables
byte wheelMotorMaxSpeed = 96;       // Integer in range [0, 255] to define the PWM cycle at which the motor for the wheel runs

// Debug configuration
boolean DEBUG = true;               // Enable logging to serial console
long debugDelay = 3000;             // The delay in ms between two subsequent debug messages
long lastDebugMessage = millis();   // No touchy plz

// auxiliary for analog sensor readings
int sensorColourReflectionValue = 0;
int sensorColourPresenceValue = 0;
int sensorWhitePresenceValue = 0;
int sensorBlackPresenceValue = 0;
int sensorFactoryPresenceValue = 0;

void setup() {
  // Initialize pins in correct mode
  pinMode(sensorColourReflection, INPUT);
  pinMode(sensorColourPresence, INPUT);
  pinMode(sensorWhitePresence, INPUT);
  pinMode(sensorBlackPresence, INPUT);
  pinMode(sensorFactoryPresence, INPUT);
  pinMode(sensorWheelRotation, INPUT);

  pinMode(outputRotateWheel, OUTPUT);

  // Start serial connection to computer
  Serial.begin(9600);

}

void loop() {
  //analogWrite(outputRotateWheel, 0);
  //delay(1500);
  //analogWrite(outputRotateWheel, wheelMotorMaxSpeed);
  //delay(1500);

  // Update analog sensor readings
  sensorColourReflectionValue = analogRead(sensorColourReflection);
  sensorColourPresenceValue = analogRead(sensorColourPresence);
  sensorWhitePresenceValue = analogRead(sensorWhitePresence);
  sensorBlackPresenceValue = analogRead(sensorBlackPresence);
  sensorFactoryPresenceValue = analogRead(sensorFactoryPresence);

  // Log these values to console
  if (DEBUG && millis() - lastDebugMessage > debugDelay) {
    Serial.print("Colour Reflection: "); Serial.println(sensorColourReflectionValue);
    Serial.print("Colour Presence: "); Serial.println(sensorColourPresenceValue);
    Serial.print("White Presence: "); Serial.println(sensorWhitePresenceValue);
    Serial.print("Black Presence: "); Serial.println(sensorBlackPresenceValue);
    Serial.print("Factory Presence: "); Serial.println(sensorFactoryPresenceValue);
    Serial.println();
    lastDebugMessage = millis();
  }

  // Parse colour gate readings
  if (sensorColourPresenceValue < 500) {
    //Disk detected in gate
    if (sensorColourReflectionValue > 900) {
      Serial.println("White disk detected at colour sensor");
    } else if (sensorColourReflectionValue < 450) {
      Serial.println("Black disk detected at colour sensor");
    } else {
      Serial.println("Object of unknown colour detected at colour sensor"); 
    }
  }

  // Parse white presence sensor
  if (sensorWhitePresenceValue < 200) {
    Serial.println("Disk detected at white basket");
  }

  // Parse black presence sensor
  if (sensorBlackPresenceValue < 200) {
    Serial.println("Disk detected at black basket");
  }

  // Parse factory presence sensor
  if (sensorFactoryPresenceValue < 200) {
    Serial.println("Disk detected at factory floor");
  }
  
}
