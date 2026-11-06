# Build guide (DRAFT - authors must complete the lines marked TO COMPLETE)

## 1. Parts and tools
See `BOM.csv`. Tools: soldering iron, wire, USB cable, computer with Arduino IDE (2.3.6 used), Wi-Fi network, ThingSpeak account. Optional: MATLAB R2022b+ with Image Processing Toolbox.

## 2. Sensor burn-in
Power the MQ-7 and MQ-135 for 24-48 h before first measurements.

## 3. Wiring (Arduino Uno)
| Sensor / module | Connection | Source |
|---|---|---|
| DHT11 data | D2 | `Smart_Air_Monitor_Code.ino` |
| MQ-7 analogue out | A0 | Arduino IDE screenshot of the field sketch (**the repo .ino has A0/A1 swapped: verify**) |
| MQ-135 analogue out | A1 | same |
| ESP8266 (SoftwareSerial) | pins 10 and 11 (RX, TX per sketch comment) | field sketch screenshot |
| PMS5003 TX/RX | TO COMPLETE (pin numbers) | - |
| ESP32-CAM | separate unit, powered separately | TO COMPLETE |
| SD-card module (optional) | TO COMPLETE (SPI pins) | - |

Notes: the Uno outputs 5 V logic; the ESP8266 is 3.3 V logic, so use a level shifter or voltage divider on the line into the ESP8266 RX pin, and supply the ESP8266 from a regulated 3.3 V source that can deliver enough current.

## 4. Firmware
Open the sketch in `Firmware/`, copy `credentials_example.h` to `credentials.h` and enter your Wi-Fi and ThingSpeak write key, select board "Arduino Uno" and upload. TO COMPLETE: list required libraries and versions.

## 5. ThingSpeak channel
Create a channel and add one field per measurement. TO COMPLETE: field order (temperature, humidity, MQ-135, MQ-7, PM1.0, PM2.5, PM10 or as used).

## 6. First-run test
Open the Serial Monitor at 9600 baud; readings must print, then appear in the ThingSpeak channel. Compare temperature/humidity with a handheld thermo-hygrometer.

## 7. Optional smog classification
Run `Matlab/smog_classifier.m` on a field image.

## 8. Known limitations
Gas values are uncalibrated relative indicators; PMS5003 columns in the dataset violate PM1.0 <= PM2.5 <= PM10 in 74% of samples (see paper and `Data/README.md`).
