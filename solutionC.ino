const int photoresistorPin = A0; // Analog pin for the photoresistor
const int redPin = 9;           // Digital pin for the red leg of the RGB LED
const int greenPin = 10;         // Digital pin for the green leg of the RGB LED
const int bluePin = 11;          // Digital pin for the blue leg of the RGB LED

void setup() {
  pinMode(photoresistorPin, INPUT);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);

  // Initialize the RGB LED to an off state
  analogWrite(redPin, 0);
  analogWrite(greenPin, 0);
  analogWrite(bluePin, 0);
}

void loop() {
  // Read the analog value from the photoresistor
  int lightLevel = analogRead(photoresistorPin);

  // Map the analog reading to a range suitable for RGB LED control
  int brightness = map(lightLevel, 0, 1023, 255, 0);

  // Adjust the RGB LED based on the light level
  analogWrite(redPin, brightness);
  analogWrite(greenPin, brightness);
  analogWrite(bluePin, brightness);

  // Add a delay for stability and to prevent rapid changes
  delay(100);
}
