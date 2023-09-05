#include <WiFi.h>

#define TEMP_PIN 34 // Anolog pin for connecting a thermal sensor
const char* ssid = ""; // Ur network name
const char* password = ""; // Ur network password
const char* host = "0.0.0.0"; // IP of the server in the network
const int port = 8000; // free port
float temp;

void setup() {
  Serial.begin(9600);
  Serial.print("Connecting to ");
  Serial.println(ssid);
  /* connect to your WiFi */
  WiFi.begin(ssid, password);
  /* wait until ESP32 connect to WiFi*/
  while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected with IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  WiFiClient client;

  if (!client.connect(host, port)) {
    Serial.println("connection failed");
    delay(2000);
    return;
  }

  float sum = 0;
  //cycle for more accurate values
  for (int i = 0; i < 50; i++){
    // U need seting these parameters
    temp = analogRead(TEMP_PIN) - 1490; // -1000 on 3.3v
    temp = temp/4095*5; // conversion to volts, temp/4095*3.3 on 3.3v
    temp = temp*100-273.15; // conversion to Celsius degree, temp*100 -178 on 3.3v
    sum = sum + temp;
    delay(20);
  }
  sum /= 50;


  String text = "External: " + String(sum);
  client.print(text);
  Serial.println(sum);
  delay(500);
}