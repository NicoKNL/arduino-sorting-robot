// Define stepper motor connections
#define dirPin 4
#define stepPin 3

// Define joystick inputs
#define JoyStick_X 1
#define JoyStick_Y 2

int SPEED = 10; // Higher values = lower speed
int DEADZONE = 15;

// NOTE: Assumption is that the NEMA17 is configured to run 1/64 as stepsize

void setup () {
  pinMode(JoyStick_X, INPUT);
  pinMode(JoyStick_Y, INPUT);

  // Declare pins as output:
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  
  Serial.begin(9600); // 9600 bps
}

void loop() {
  int x = analogRead(JoyStick_X); 
  int y = analogRead(JoyStick_Y); 
  
  //  Serial.print(x, DEC); Serial.print( ","); // For when you also want to use the other direction of the stick
  Serial.println(y, DEC);

  // Early out for when nothing needs to be done
  if (512 - DEADZONE < y && y < 512 + DEADZONE) {
    return;
  } else {
    // Set the direction of the belt
    if (y > 512) {
      digitalWrite(dirPin, HIGH);
    } else {
      digitalWrite(dirPin, LOW);
    }

    // While we not re-enter the deadzone
    while(y < 512 - DEADZONE || y > 512 + DEADZONE) {
      // KEEP MOVING BABY!!
      digitalWrite(stepPin, HIGH);
      delayMicroseconds(SPEED);
      digitalWrite(stepPin, LOW);
      delayMicroseconds(SPEED);

      y = analogRead(JoyStick_Y);
    }
  }
}
