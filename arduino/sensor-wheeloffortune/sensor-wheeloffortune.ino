// Hardware Pin definitions
byte sensorColourReflection = A0;   // Disk colour detector, reflection
byte sensorColourPresence = A1;     // Disk colour detector, presence
byte sensorWhitePresence = A2;      // Disk presence at white basket
byte sensorBlackPresence = A3;      // Disk presence at black basket
byte sensorFactoryPresence = A4;    // Disk presence at factory belt
byte sensorWheelRotation = A5;      // Sense one-push rotation --> needs debouncing (done in this arduino program)

byte actuatorRotateWheel = 3;       // Output pin to rotate wheel

// I/O Pin definitions
byte inputRotateWheel = 4;          // If pin high, then the wheel will be rotated

byte outputWheelRotated = 5;        // Will be made high if one rotation is sensed (after debouncing)
byte outputFactoryPresence = 7;     // Will be made high if disk is detected as present on factory belt
byte outputBlackPresence = 11;      // Will be made high if disk is detected as present at black basket
byte outputWhitePresence = 6;       // Will be made high if disk is detected as present at white basket
byte outputColour0 = 10;            // The colour sensor has encoded output as follows:
byte outputColour1 = 8;             // No disk present        <=> !outputColour0 && !outputColour1
                                    // Black disk present     <=>  outputColour0 && !outputColour1
                                    // White disk present     <=> !outputColour0 &&  outputColour1
                                    // Other colour detected  <=>  outputColour0 &&  outputColour1

// Configuration using variables
byte wheelMotorMaxSpeed = 96;       // Integer in range [0, 255] to define the PWM cycle at which the motor for the wheel runs

// Debug configuration
boolean DEBUG = true;               // Enable logging to serial console
long debugDelay = 3000;             // The delay in ms between two subsequent debug messages
long lastDebugMessage = millis();   // No touchy plz

// Auxiliary for analog sensor readings
int sensorColourReflectionValue = 0;
int sensorColourPresenceValue = 0;
int sensorWhitePresenceValue = 0;
int sensorBlackPresenceValue = 0;
int sensorFactoryPresenceValue = 0;
int sensorWheelRotationValue = 0;

byte wheelRotatedState;
byte lastWheelRotatedState = LOW;
unsigned long lastWheelRotatedDebounceTime = 0;   // the last time the wheel rotation switch state changed
unsigned long wheelRotatedDebounceDelay = 10;     // the debounce time in ms for the wheel rotation input to be considered stable; increase if the output flickers

void setup() {
  // Initialize hardware pins in correct mode
  pinMode(sensorColourReflection, INPUT);
  pinMode(sensorColourPresence, INPUT);
  pinMode(sensorWhitePresence, INPUT);
  pinMode(sensorBlackPresence, INPUT);
  pinMode(sensorFactoryPresence, INPUT);
  pinMode(sensorWheelRotation, INPUT);

  pinMode(actuatorRotateWheel, OUTPUT);

  // Initialize I/O pins in correct mode
  pinMode(inputRotateWheel, INPUT);

  pinMode(outputWheelRotated, OUTPUT);
  pinMode(outputFactoryPresence, OUTPUT);
  pinMode(outputBlackPresence, OUTPUT);
  pinMode(outputWhitePresence, OUTPUT);
  pinMode(outputColour0, OUTPUT);
  pinMode(outputColour1, OUTPUT);

  // Start serial connection to computer
  Serial.begin(9600);

}

void loop() {
  // Update analog sensor readings
  sensorColourReflectionValue = analogRead(sensorColourReflection);
  sensorColourPresenceValue = analogRead(sensorColourPresence);
  sensorWhitePresenceValue = analogRead(sensorWhitePresence);
  sensorBlackPresenceValue = analogRead(sensorBlackPresence);
  sensorFactoryPresenceValue = analogRead(sensorFactoryPresence);
  sensorWheelRotationValue = analogRead(sensorWheelRotation);
  

  // Log these values to console
  if (DEBUG && millis() - lastDebugMessage > debugDelay) {
    Serial.print("Colour Reflection: "); Serial.println(sensorColourReflectionValue);
    Serial.print("Colour Presence: "); Serial.println(sensorColourPresenceValue);
    Serial.print("White Presence: "); Serial.println(sensorWhitePresenceValue);
    Serial.print("Black Presence: "); Serial.println(sensorBlackPresenceValue);
    Serial.print("Factory Presence: "); Serial.println(sensorFactoryPresenceValue);
    Serial.print("Wheel Rotation: "); Serial.println(sensorWheelRotationValue);
    Serial.println();
    lastDebugMessage = millis();
  }

  // Parse colour gate readings
  if (sensorColourPresenceValue < 500) {
    //Disk detected in gate
    if (sensorColourReflectionValue > 900) {
      Serial.println("White disk detected at colour sensor");
      digitalWrite(outputColour0, LOW);
      digitalWrite(outputColour1, HIGH);
    } else if (sensorColourReflectionValue < 450) {
      Serial.println("Black disk detected at colour sensor");
      digitalWrite(outputColour0, HIGH);
      digitalWrite(outputColour1, LOW);
    } else {
      Serial.println("Object of unknown colour detected at colour sensor"); 
      digitalWrite(outputColour0, HIGH);
      digitalWrite(outputColour1, HIGH);
    }
  } else {
    digitalWrite(outputColour0, LOW);
    digitalWrite(outputColour1, LOW);
  }

  // Parse white presence sensor
  if (sensorWhitePresenceValue < 200) {
    Serial.println("Disk detected at white basket");
    digitalWrite(outputWhitePresence, HIGH);
  } else {
    digitalWrite(outputWhitePresence, LOW);
  }

  // Parse black presence sensor
  if (sensorBlackPresenceValue < 200) {
    Serial.println("Disk detected at black basket");
    digitalWrite(outputBlackPresence, HIGH);
  } else {
    digitalWrite(outputBlackPresence, LOW);
  }

  // Parse factory presence sensor
  if (sensorFactoryPresenceValue < 200) {
    Serial.println("Disk detected at factory floor");
    digitalWrite(outputFactoryPresence, HIGH);
  } else {
    digitalWrite(outputFactoryPresence, LOW);
  }

  // Check if the wheel of fortune should rotate
  if (digitalRead(inputRotateWheel) == HIGH) {
    analogWrite(actuatorRotateWheel, wheelMotorMaxSpeed);
  } else {
    analogWrite(actuatorRotateWheel, 0);
  }
  
  // Debounce and parse wheel rotated sensor
  // Translate rotation sensor information to digital signal
  byte currentWheelRotatedState = (sensorWheelRotationValue > 511);

  // Check if the input has changed to debounce the input
  if (currentWheelRotatedState != lastWheelRotatedState) {
    // The input has changed, so reset the debounce timer
    lastWheelRotatedDebounceTime = millis();
  }

  // Check if the wheel rotation input has been stable for long enough, indicating a stable reading
  if (millis() - lastWheelRotatedDebounceTime > wheelRotatedDebounceDelay) {
    // Update the last stable state of the wheel rotation input sensor
    wheelRotatedState = currentWheelRotatedState;
  }

  // Update the last-read input state for the wheel rotation input
  lastWheelRotatedState = currentWheelRotatedState;

  // Update the output regarding the debounced wheel rotated sensor
  if (wheelRotatedState) {
    digitalWrite(outputWheelRotated, HIGH);
  } else {
    digitalWrite(outputWheelRotated, LOW);
  }
}
