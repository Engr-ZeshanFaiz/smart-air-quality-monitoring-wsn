/* * Project: Smart Air Quality Monitoring System
 * University: KFUEIT, Rahim Yar Khan
 * Sensors: MQ135, MQ7, PMS5003, DHT11
 */

#include <DHT.h>

#define DHTPIN 2
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  dht.begin();
  Serial.println("System Initialized");
}

void loop() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  int mq135_value = analogRead(A0); // Air Quality
  int mq7_value = analogRead(A1);   // CO Sensor

  Serial.print("Temp: "); Serial.print(t);
  Serial.print("C | Humidity: "); Serial.print(h);
  Serial.print("% | MQ135: "); Serial.print(mq135_value);
  Serial.print(" | MQ7: "); Serial.println(mq7_value);

  delay(2000); // 2 seconds delay
}
