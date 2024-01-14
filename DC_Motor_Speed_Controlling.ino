const int motorPWM = 11;   // Motor PWM pin connected to L298N
const int motorEnableA = 13;  // Motor direction pin 1
const int motorEnableB = 12;  // Motor direction pin 2
const int optoCoupler = 10;   // Optocoupler sensor input pin

void setup() {
  Serial.begin(9600);
  pinMode(motorPWM, OUTPUT);
  pinMode(motorEnableA, OUTPUT);
  pinMode(motorEnableB, OUTPUT);
  pinMode(optoCoupler, INPUT);

  // Initialize motor control
  digitalWrite(motorEnableA, HIGH);
  digitalWrite(motorEnableB, LOW);
}

void loop() {
  // Motor control - set the motor to full speed
  analogWrite(motorPWM, 255);

  // Optional: Measure and display motor speed in Serial Monitor
  unsigned long pulses = 0;
  unsigned long startTime = millis();

  while (millis() - startTime < 1000) {  // Measure for 1 second
    if (digitalRead(optoCoupler) == HIGH) {
      pulses++;
      delayMicroseconds(10);  // Debouncing
    }
  }

  double rpm = (pulses / 2.0) / (1000 / 60.0);  // Calculate RPM
  Serial.print("Motor Speed: ");
  Serial.print(rpm);
  Serial.println(" RPM");

  // Stop the motor (optional)
  // analogWrite(motorPWM, 0);

  delay(1000);  // Wait for 1 second before repeating
}
