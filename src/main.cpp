#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>

// Setup PubSubClient 
WiFiClient espClient;
PubSubClient client(espClient);

void setup()
{
  // Sets up LED as OUTPUT
  pinMode(LED_BUILTIN, OUTPUT);
  // Sets up GPIO22 as OUTPUT
  pinMode(22, OUTPUT);
  // Sets up GPIO23 as INPUT
  pinMode(23, INPUT);
  // Enable serial communication
  Serial.begin(9600);

  // Connect to WiFi
  WiFi.begin("Linguini", "Circa 1000 linguini sono buoni!");

  Serial.print("Connecting to WiFi..");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(100);
  }
  Serial.println();
  Serial.println("Connected");

  // Print the IP address
  Serial.println(WiFi.localIP());

  // Configure the MQTT server
  client.setServer("automation.server.lan", 1883);
}

// Blink the LED on the NodeMCU 32S board
void loop()
{
  while (true)
  {
    // Connect to MQTT broker
    while (!client.connected())
    {
      Serial.println("Connecting to MQTT broker...");
      if (client.connect("ESP32Client"))
      {
        Serial.println("connected");
      }
      else
      {
        Serial.print("failed with state ");
        Serial.print(client.state());
        delay(2000);
      }
    }
    
    // Measure the voltage on GPIO23
    digitalWrite(22, HIGH);
    int value = digitalRead(23);
    digitalWrite(22, LOW);

    // If the value is HIGH, turn on the LED
    if (value == HIGH)
    {
      digitalWrite(LED_BUILTIN, HIGH);
      client.publish("kitchen/waterLevel", "HIGH");
      // Serial.print("-");
    }
    else
    {
      digitalWrite(LED_BUILTIN, LOW);
      client.publish("kitchen/waterLevel", "LOW");
      // Serial.print(".");
    }

    // Delay for ten seconds
    delay(10000);
  }
}