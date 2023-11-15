#include <Servo.h>
Servo myServo; // Create a Servo object
const int trigPin = 9; // Trigger pin of the ultrasonic sensor
const int echoPin = 10; // Echo pin of the ultrasonic sensor
void setup() {
  Serial.begin(9600);
  myServo.attach(9); // Attach the servo to pin 9
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}
void loop() {
  long duration, distance;
  // Trigger the ultrasonic sensor to send a pulse
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Measure the duration of the pulse from the echo pin
  duration = pulseIn(echoPin, HIGH);

  // Calculate the distance based on the speed of sound
  distance = (duration * 0.0343) / 2;

  // Output the distance to the Serial Monitor
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  // Map the distance to the servo angle (adjust as needed)
  int servoAngle = map(distance, 5, 50, 0, 180);

  // Constrain the servo angle to prevent excessive movement
  servoAngle = constrain(servoAngle, 0, 180);

  // Move the servo motor to the calculated angle
  myServo.write(servoAngle);

  // Add a delay for stability
  delay(500);
}
