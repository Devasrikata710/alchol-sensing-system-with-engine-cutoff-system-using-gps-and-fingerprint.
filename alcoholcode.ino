// Alchol sensing system with engine cutoff using fingerprint and gps
#include <Adafruit_Fingerprint.h>
#include <SoftwareSerial.h>
#include <LiquidCrystal_I2C.h>
#include <TinyGPS++.h>

// --- Pins ---
const int alcoholPin = A0;
const int relayPin = 7;
const int buzzerPin = 5;
const int threshold = 400; // Adjust based on real-time values

// --- Modules ---
SoftwareSerial fingerSerial(2, 3); // Fingerprint
Adafruit_Fingerprint finger(&fingerSerial);

SoftwareSerial gpsSerial(8, 9);   // GPS
TinyGPSPlus gps;

LiquidCrystal_I2C lcd(0x27, 16, 2);

// --- State ---
bool motorRunning = false;

void setup() {
  pinMode(relayPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);

  Serial.begin(9600);
  gpsSerial.begin(9600);
  finger.begin(57600);
  lcd.init();
  lcd.backlight();

  // Fingerprint check
  if (finger.verifyPassword()) {
    Serial.println("Fingerprint sensor initialized.");
  } else {
    lcd.setCursor(0, 0);
    lcd.print("Fingerprint Err");
    Serial.println("Fingerprint sensor not found.");
    while (true); // Halt
  }

  // Warm-up Sensor
  lcd.setCursor(0, 0);
  lcd.print("Warming MQ-3...");
  delay(15000);
  lcd.clear();

  // Start motor
  digitalWrite(relayPin, LOW); // Motor ON
  motorRunning = true;
  lcd.setCursor(0, 0);
  lcd.print("Motor Started");
  beep();
  delay(2000);
  lcd.clear();
}

void loop() {
  int alcoholValue = analogRead(alcoholPin);
  Serial.print("Alcohol Value: ");
  Serial.println(alcoholValue);

  lcd.setCursor(0, 0);
  lcd.print("Alcohol:");
  lcd.setCursor(9, 0);
  lcd.print("     "); // Clear old digits
  lcd.setCursor(9, 0);
  lcd.print(alcoholValue);

  // If alcohol exceeds threshold
  if (motorRunning && alcoholValue > threshold) {
    lcd.setCursor(0, 1);
    lcd.print("Alcohol Detected");
    Serial.println(">> Alcohol detected");
    delay(2000);

    // Stop motor
    digitalWrite(relayPin, HIGH); // Motor OFF
    motorRunning = false;
    beep();

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Motor Stopping");
    delay(2000);

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Show Fingerprint");
    Serial.println(">> Waiting for fingerprint...");

    if (getFingerprint(15000)) {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Fingerprint OK");
      Serial.println(">> Fingerprint matched");
      delay(2000);

      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Rechecking...");
      delay(2000);

      int recheck = analogRead(alcoholPin);
      Serial.print("Recheck Alcohol: ");
      Serial.println(recheck);

      if (recheck <= threshold) {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Alcohol Cleared");
        lcd.setCursor(0, 1);
        lcd.print("Motor Restarted");
        digitalWrite(relayPin, LOW); // Motor ON
        motorRunning = true;
        beep();
        Serial.println(">> Alcohol cleared. Motor ON");
        delay(3000);
      } else {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Alcohol Still HI");
        lcd.setCursor(0, 1);
        lcd.print("Motor OFF");
        Serial.println(">> Alcohol still high. Motor OFF");
        delay(3000);
      }
    } else {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("No Fingerprint");
      lcd.setCursor(0, 1);
      lcd.print("Activating GPS");
      Serial.println(">> No fingerprint. Sending GPS");
      beep();
      delay(2000);
      printGPSLocation();
    }
    lcd.clear();
  }

  // Feed GPS data
  while (gpsSerial.available()) {
    gps.encode(gpsSerial.read());
  }

  delay(300); // Fast loop for quicker detection
}

bool getFingerprint(unsigned long timeout) {
  unsigned long start = millis();
  while (millis() - start < timeout) {
    if (finger.getImage() == FINGERPRINT_OK) {
      if (finger.image2Tz() != FINGERPRINT_OK) continue;
      if (finger.fingerSearch() == FINGERPRINT_OK) {
        Serial.print("Fingerprint ID: ");
        Serial.println(finger.fingerID);
        return true;
      }
    }
    delay(100);
  }
  return false;
}

void printGPSLocation() {
  unsigned long start = millis();
  bool found = false;

  while (millis() - start < 5000) {
    while (gpsSerial.available()) {
      gps.encode(gpsSerial.read());
    }

    if (gps.location.isValid()) {
      float lat = gps.location.lat();
      float lon = gps.location.lng();

      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Lat:");
      lcd.print(lat, 2);
      lcd.setCursor(0, 1);
      lcd.print("Lon:");
      lcd.print(lon, 2);

      Serial.print("Latitude: ");
      Serial.println(lat, 6);
      Serial.print("Longitude: ");
      Serial.println(lon, 6);

      found = true;
      delay(4000);
      break;
    }
  }

  if (!found) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("No GPS Signal");
    Serial.println(">> No valid GPS data.");
    delay(3000);
  }
}

void beep() {
  digitalWrite(buzzerPin, HIGH);
  delay(200);
  digitalWrite(buzzerPin, LOW);
}
