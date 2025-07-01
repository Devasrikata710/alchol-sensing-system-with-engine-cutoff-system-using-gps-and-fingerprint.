# 🚗 Revolutionizing Road Safety with Intelligent Alcohol Detection and Engine Control System

 *Alcohol Detection System with Engine Cutoff Using Fingerprint and GPS* — a smart solution designed to reduce drunk driving incidents and prevent vehicle misuse.

---
## 🔎 Project Overview

The system is designed to:

- Detect the driver's alcohol concentration when the vehicle is turned on.
- Automatically shut off the engine if alcohol concentration is above the safe threshold.
- Require the driver to verify their identity via fingerprint to restart the vehicle.
- Recheck alcohol levels after fingerprint authentication before enabling the engine.
- Send alerts with location information via GPS if invalid or delayed fingerprint input is detected.
- Prevent vehicle misuse with added security against theft or unauthorized use.

🔐 This not only ensures the driver is fit to drive but also adds an extra layer of anti-theft and unconscious-driver protection.
---

🛠 Technologies Used

- Embedded Systems (Microcontroller-based design)
- *MQ-3 Alcohol Sensor*
- *R307 Fingerprint Sensor*
- *GPS Module*
- *Relay Module* (Controls engine power cutoff)
- *DC Motor* (Simulates vehicle engine in testing phase)
- *16x2 LCD Display* (Shows sensor readings and system status)
- C/C++ (Embedded programming for microcontroller)

---

 ⚙ Components & Modules

| Component               | Purpose                                                             
| ----------------------- | --------------------------------------------------------------------     |
| MQ-3 Alcohol Sensor     | Measures driver’s breath alcohol concentration                           |
| R307 Fingerprint Sensor | Authenticates driver’s fingerprint before enabling the engine            |
| GPS Module              | Sends alert messages with live location in case of misuse or danger      |
| Relay Module            | Cuts off engine power when alcohol level is high or authentication fails |
| DC Motor                | Acts as a simulated engine for testing engine cutoff functionality       |
| 16x2 LCD Display        | Displays alcohol level, fingerprint status, and system messages          |

---

 📸 How It Works

- When the vehicle is turned on, the system immediately measures the driver’s alcohol level using the MQ-3 sensor.
- If alcohol concentration is above the threshold, the engine is disabled by controlling the relay module.
- To restart the engine, the driver must pass fingerprint authentication using the R307 sensor.
- The system rechecks alcohol levels after fingerprint verification before enabling the relay.
- If the fingerprint is invalid or not provided within the allowed time, the engine remains disabled and a GPS alert is sent to predefined contacts.
- The LCD screen provides real-time feedback on alcohol levels, fingerprint status, and system warnings.

---

🚀 Getting Started

 Prerequisites

- Arduino IDE installed
- Libraries:
  - Adafruit_Fingerprint.h
  - SoftwareSerial.h
  - LiquidCrystal.h

## Uploading the Code

1. Connect your Arduino UNO.
2. Open alcoholEngineCutoff.ino in Arduino IDE.
3. Install the necessary libraries.
4. Upload the code and monitor using the Serial Monitor.

---

## 🎯 Key Takeaways

💡 This project gave me my first hands-on experience with sensors, real-time inputs, fingerprint authentication, and GPS integration — combining safety, automation, and innovation into one solution.

Looking forward to applying these learnings to even more impactful innovations!

---
![image alt](https://github.com/Devasrikata710/alchol-sensing-system-with-engine-cutoff-system-using-gps-and-fingerprint./blob/64632ddfc59c42670b29bb15d80a2f094b92a6dc/working%20model-2.jpg)

