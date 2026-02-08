#include <WiFi.h>
#include <ThingSpeak.h>

// WiFi and ThingSpeak Credentials
const char* ssid = "YOUR_WIFI_SSID";      // Apne WiFi ka naam yahan likhen
const char* pass = "YOUR_WIFI_PASSWORD";  // Apne WiFi ka password yahan likhen
unsigned long myChannelNumber = 123456;   // Apna ThingSpeak Channel ID likhen
const char * myWriteAPIKey = "YOUR_API_KEY"; // Apna Write API Key likhen

WiFiClient  client;

// Sensor Pins
#define MQ135_PIN 34
#define MQ7_PIN 35

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  ThingSpeak.begin(client);
  
  Serial.println("System Initializing...");
}

void loop() {
  // Connect to WiFi
  if (WiFi.status() != WL_CONNECTED) {
    Serial.print("Attempting to connect to SSID: ");
    while (WiFi.status() != WL_CONNECTED) {
      WiFi.begin(ssid, pass);
      Serial.print(".");
      delay(5000);
    }
    Serial.println("\nConnected.");
  }

  // Reading Analog Sensors
  int mq135_raw = analogRead(MQ135_PIN);
  int mq7_raw = analogRead(MQ7_PIN);
  
  // Mapping raw data to approximate PPM (Simplified for Open Hardware)
  float mq135_ppm = map(mq135_raw, 0, 4095, 0, 1000); 
  float mq7_ppm = map(mq7_raw, 0, 4095, 0, 500);

  // Note: PM2.5 readings are usually taken via Serial from PMS5003
  // Here we use placeholder logic for demonstration
  float pm25 = random(10, 150); 

  // Setting ThingSpeak Fields
  ThingSpeak.setField(1, mq135_ppm);
  ThingSpeak.setField(2, mq7_ppm);
  ThingSpeak.setField(3, pm25);

  // Write to ThingSpeak
  int x = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
  
  if(x == 200){
    Serial.println("Channel update successful.");
  }
  else{
    Serial.println("Problem updating channel. HTTP error code " + String(x));
  }

  delay(20000); // Wait 20 seconds before next update
}