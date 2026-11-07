/*
  REFERENCE FIRMWARE - air quality node (Arduino Uno + ESP8266 + PMS5003 + MQ-7 + MQ-135 + DHT11 -> ThingSpeak)

  STATUS: reference implementation written for documentation and tested by the authors on the assembled node
  (November 2026). It is NOT the original sketch used to collect the field dataset (that sketch was not archived).
  Match the pin map below to your own wiring before use (see README.md).

  Libraries (Arduino IDE 2.x Library Manager): "DHT sensor library" (Adafruit) + "Adafruit Unified Sensor".
  Board: Arduino Uno. Serial Monitor: 9600 baud.

  Credentials: copy ../credentials_example.h to credentials.h (same folder as this sketch), enter your values,
  never upload credentials.h.
*/
#include <SoftwareSerial.h>
#include <DHT.h>
#include "credentials.h"          // defines SSID, PASSWORD, API_KEY

// ---------------- PIN MAP: set to match YOUR wiring ----------------
const uint8_t DHT_PIN   = 2;      // DHT11 data
const uint8_t MQ7_PIN   = A0;     // MQ-7 analogue out
const uint8_t MQ135_PIN = A1;     // MQ-135 analogue out
const uint8_t ESP_RX    = 10;     // Arduino RX  <- ESP8266 TX
const uint8_t ESP_TX    = 11;     // Arduino TX  -> ESP8266 RX (use a level shifter / divider: ESP8266 is 3.3 V)
const uint8_t PMS_RX    = 4;      // Arduino RX  <- PMS5003 TX
const uint8_t PMS_TX    = 5;      // not used by PMS5003 in active mode (keep free)
// -------------------------------------------------------------------
const unsigned long INTERVAL_MS = 30000UL;   // upload every 30 s

SoftwareSerial espSerial(ESP_RX, ESP_TX);
SoftwareSerial pmsSerial(PMS_RX, PMS_TX);
DHT dht(DHT_PIN, DHT11);

bool waitFor(const char* expect, unsigned long timeoutMs) {
  unsigned long start = millis();
  String resp;
  while (millis() - start < timeoutMs) {
    while (espSerial.available()) {
      resp += (char)espSerial.read();
      if (resp.indexOf(expect) >= 0) return true;
    }
  }
  return false;
}

bool sendAT(const char* cmd, const char* expect, unsigned long timeoutMs) {
  espSerial.listen();
  while (espSerial.available()) espSerial.read();
  espSerial.println(cmd);
  return waitFor(expect, timeoutMs);
}

bool connectWiFi() {
  if (!sendAT("AT", "OK", 2000)) return false;
  sendAT("AT+CWMODE=1", "OK", 2000);
  String c = F("AT+CWJAP=\"");
  c += SSID; c += F("\",\""); c += PASSWORD; c += F("\"");
  return sendAT(c.c_str(), "OK", 15000);
}

int readAnalogAvg(uint8_t pin) {
  long sum = 0;
  for (uint8_t i = 0; i < 10; i++) { sum += analogRead(pin); delay(10); }
  return (int)(sum / 10);
}

// PMS5003 active-mode frame: 32 bytes, header 0x42 0x4D, checksum = sum of first 30 bytes.
// Bytes 10-15 are the "atmospheric environment" PM1.0 / PM2.5 / PM10 values (ug/m3).
bool readPMS(uint16_t &pm1, uint16_t &pm25, uint16_t &pm10) {
  pmsSerial.listen();
  while (pmsSerial.available()) pmsSerial.read();
  unsigned long start = millis();
  uint8_t buf[32];
  while (millis() - start < 3000) {
    if (pmsSerial.available() && pmsSerial.read() == 0x42) {
      unsigned long t = millis();
      while (!pmsSerial.available() && millis() - t < 100) {}
      if (pmsSerial.read() != 0x4D) continue;
      buf[0] = 0x42; buf[1] = 0x4D;
      uint8_t n = 2; t = millis();
      while (n < 32 && millis() - t < 200) { if (pmsSerial.available()) buf[n++] = pmsSerial.read(); }
      if (n < 32) continue;
      uint16_t sum = 0;
      for (uint8_t i = 0; i < 30; i++) sum += buf[i];
      uint16_t chk = ((uint16_t)buf[30] << 8) | buf[31];
      if (sum != chk) continue;
      pm1  = ((uint16_t)buf[10] << 8) | buf[11];
      pm25 = ((uint16_t)buf[12] << 8) | buf[13];
      pm10 = ((uint16_t)buf[14] << 8) | buf[15];
      return true;
    }
  }
  return false;
}

// ThingSpeak fields: 1 temp, 2 humidity, 3 MQ-135 (raw ADC), 4 MQ-7 (raw ADC), 5 PM1.0, 6 PM2.5, 7 PM10
bool uploadThingSpeak(float t, float h, int mq135, int mq7, uint16_t p1, uint16_t p25, uint16_t p10) {
  String get = F("GET /update?api_key=");
  get += API_KEY;
  get += F("&field1="); get += String(t, 1);
  get += F("&field2="); get += String(h, 1);
  get += F("&field3="); get += mq135;
  get += F("&field4="); get += mq7;
  get += F("&field5="); get += p1;
  get += F("&field6="); get += p25;
  get += F("&field7="); get += p10;
  if (!sendAT("AT+CIPSTART=\"TCP\",\"api.thingspeak.com\",80", "CONNECT", 5000)) return false;
  String cmd = F("AT+CIPSEND=");
  cmd += (get.length() + 2);
  if (!sendAT(cmd.c_str(), ">", 3000)) { sendAT("AT+CIPCLOSE", "OK", 1000); return false; }
  espSerial.println(get);
  bool ok = waitFor("SEND OK", 5000);
  sendAT("AT+CIPCLOSE", "OK", 1000);
  return ok;
}

void setup() {
  Serial.begin(9600);
  espSerial.begin(9600);
  pmsSerial.begin(9600);
  dht.begin();
  Serial.println(F("Air node (reference firmware) starting..."));
  Serial.println(F("Warm up MQ sensors before trusting readings."));
  if (connectWiFi()) Serial.println(F("Connected to WiFi")); else Serial.println(F("WiFi connection FAILED"));
}

void loop() {
  static unsigned long last = 0;
  if (last != 0 && millis() - last < INTERVAL_MS) return;
  last = millis();

  float t = dht.readTemperature();
  float h = dht.readHumidity();
  if (isnan(t) || isnan(h)) { t = -1; h = -1; Serial.println(F("DHT11 read failed")); }
  int mq7 = readAnalogAvg(MQ7_PIN);
  int mq135 = readAnalogAvg(MQ135_PIN);
  uint16_t p1 = 0, p25 = 0, p10 = 0;
  bool pmsOk = readPMS(p1, p25, p10);
  if (!pmsOk) Serial.println(F("PMS5003 read failed (check wiring/baud)"));

  Serial.print(F("Temperature: ")); Serial.print(t, 1); Serial.println(F(" C"));
  Serial.print(F("Humidity: ")); Serial.print(h, 1); Serial.println(F(" %"));
  Serial.print(F("PM 1.0: ")); Serial.println(p1);
  Serial.print(F("PM 2.5: ")); Serial.println(p25);
  Serial.print(F("PM 10: ")); Serial.println(p10);
  Serial.print(F("MQ7 (raw ADC 0-1023): ")); Serial.println(mq7);
  Serial.print(F("MQ135 (raw ADC 0-1023): ")); Serial.println(mq135);

  if (uploadThingSpeak(t, h, mq135, mq7, p1, p25, p10)) Serial.println(F("ThingSpeak upload OK"));
  else Serial.println(F("ThingSpeak upload FAILED"));
}
