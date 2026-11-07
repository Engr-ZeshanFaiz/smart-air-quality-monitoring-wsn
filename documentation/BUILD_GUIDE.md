# Build guide

## 1. Parts and tools
See `BOM.csv`. Tools: soldering iron, wire, USB cable, computer with Arduino IDE (2.3.6 used), Wi-Fi network, ThingSpeak account. Optional: MATLAB R2022b+ with Image Processing Toolbox.

## 2. Sensor burn-in
Power the MQ-7 and MQ-135 for 24-48 h before first measurements.

## 3. Wiring (pin map of the reference sketch - edit the sketch header if your wiring differs)
| Sensor / module | Arduino Uno pin |
|---|---|
| DHT11 data | D2 |
| MQ-7 analogue out | A0 |
| MQ-135 analogue out | A1 |
| ESP8266 TX -> Arduino RX / ESP8266 RX <- Arduino TX | D10 / D11 (ESP8266 RX through a level divider or shifter, it is a 3.3 V device) |
| PMS5003 TX -> Arduino RX | D4 |
| ESP32-CAM | separate unit, powered separately |
| SD-card module (optional) | not used by the reference sketch |

Power the ESP8266 from a stable 3.3 V supply that can deliver current peaks; common ground for all modules.

## 4. Firmware
Open the sketch in `firmware/`, copy `credentials_example.h` to `credentials.h` and enter your Wi-Fi and ThingSpeak write key, select board "Arduino Uno" and upload. Libraries: DHT sensor library and Adafruit Unified Sensor (Adafruit), SoftwareSerial. The ESP8266 needs AT-command firmware.

## 5. ThingSpeak channel
Create a channel with 7 fields: 1 temperature, 2 humidity, 3 MQ-135 (raw ADC), 4 MQ-7 (raw ADC), 5 PM1.0, 6 PM2.5, 7 PM10.

## 6. First-run test
Open the Serial Monitor at 9600 baud; readings must print, then appear in the ThingSpeak channel. Compare temperature/humidity with a handheld thermo-hygrometer.

## 7. Optional smog classification
Run `matlab/smog_classifier.m` on a field image.

## 8. Known limitations
Gas values are uncalibrated relative indicators; PMS5003 columns in the dataset violate PM1.0 <= PM2.5 <= PM10 in 74% of samples (see paper and `data/README.md`).
