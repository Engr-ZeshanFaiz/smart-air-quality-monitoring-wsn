# Reference firmware (read this first)

`air_node_reference.ino` is a **reference implementation** of the node's data-acquisition logic
(DHT11, MQ-7, MQ-135, PMS5003 -> ESP8266 AT commands -> ThingSpeak, one upload every 30 s).

**It is not the original sketch used to collect the field dataset.** The original sketch was not archived.
Field-dataset values therefore come from an earlier sketch whose exact code is unavailable.

## Test procedure (the authors have run this on the assembled node; repeat it on your own build)
1. Wire exactly as in the pin map at the top of the sketch (or edit the pin map to your wiring).
2. Copy `../credentials_example.h` to `credentials.h`, fill in Wi-Fi and a NEW ThingSpeak write key.
3. Upload to an Arduino Uno; open Serial Monitor at 9600 baud.
4. Confirm: temperature/humidity look right, PM values satisfy PM1.0 <= PM2.5 <= PM10, MQ values change when exposed to smoke, and "ThingSpeak upload OK" appears.
5. Confirm 7 fields appear in the ThingSpeak channel (1 temp, 2 humidity, 3 MQ-135, 4 MQ-7, 5 PM1.0, 6 PM2.5, 7 PM10).
6. Only if all pass, rely on the readings.

MQ outputs are raw 10-bit ADC counts here; no ppm conversion is performed.
