# Firmware

**Upload here the sketch that was actually used for the field data** (Arduino IDE 2.3.6, Arduino Uno + ESP8266 over
SoftwareSerial, PMS5003, MQ-7, MQ-135, DHT11, ThingSpeak upload). The file `Smart_Air_Monitor_Code.ino` in this
folder is only a 30-line serial-print test (DHT11 + two analogue reads) and does not contain PMS5003 or Wi-Fi/ThingSpeak code.

## Rules before uploading
1. **Never commit Wi-Fi passwords or ThingSpeak API keys.** Use placeholders as in `credentials_example.h`.
2. Pin mapping must match the real wiring (see `Documentation/BUILD_GUIDE.md`).
3. State the Arduino IDE version and libraries used.
