# Firmware

`reference_firmware/air_node_reference.ino` is a reference implementation of the node's acquisition and ThingSpeak upload logic
(Arduino Uno + ESP8266 AT commands + PMS5003 + MQ-7 + MQ-135 + DHT11). The sketch used during the field campaign was not archived.
Read `reference_firmware/README.md` before use. If the original sketch is recovered, add it here and say which campaign it covers.

Rules: never commit Wi-Fi passwords or API keys (use `credentials_example.h` -> `credentials.h`, which must not be uploaded).
