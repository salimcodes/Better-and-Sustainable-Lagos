#include <SPI.h>
#include <MFRC522.h>
#include <Servo.h>

#define SS_PIN 10    // Slave Select pin for RFID module
#define RST_PIN 9    // Reset pin for RFID module

MFRC522 mfrc522(SS_PIN, RST_PIN); // Create MFRC522 instance

Servo myServo; // Create a Servo instance

void setup() {
  Serial.begin(9600);
  SPI.begin();
  mfrc522.PCD_Init(); // Initialize RFID module
  myServo.attach(11); // Attach the servo to pin 11
  Serial.println("Place your RFID tag near the reader.");
}

void loop() {
  // Look for new RFID cards
  if (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial()) {
    Serial.println("RFID card detected!");

    // Print UID of the card
    Serial.print("UID: ");
    for (byte i = 0; i < mfrc522.uid.size; i++) {
      Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
      Serial.print(mfrc522.uid.uidByte[i], HEX);
    }
    Serial.println();

    // Check if the detected card has the correct UID (replace with your UID)
    if (isCardAuthorized()) {
      Serial.println("Access granted!");

      // Move the servo motor to a specific angle (adjust as needed)
      myServo.write(90);
      delay(2000); // Wait for 2 seconds

      // Return the servo to the initial position
      myServo.write(0);
    } else {
      Serial.println("Unauthorized card. Access denied!");
    }

    delay(1000); // Avoid rapid card detection
  }
}

bool isCardAuthorized() {
  // Replace the following UID with the UID of your authorized RFID tag
  byte authorizedCardUID[] = {0xAA, 0xBB, 0xCC, 0xDD};

  // Check if the detected card's UID matches the authorized UID
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    if (mfrc522.uid.uidByte[i] != authorizedCardUID[i]) {
      return false; // UID doesn't match
    }
  }

  return true; // UID matches, card is authorized
}
