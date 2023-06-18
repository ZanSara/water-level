#include <Arduino.h>
#include <WiFi.h>
#include <MQTT.h>

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
}

// Blink the LED on the NodeMCU 32S board
void loop()
{
  while (true)
  {
    // Measure the voltage on GPIO23
    digitalWrite(22, HIGH);
    int value = digitalRead(23);
    digitalWrite(22, LOW);

    // If the value is HIGH, turn on the LED
    if (value == HIGH)
    {
      digitalWrite(LED_BUILTIN, HIGH);
    }
    else
    {
      digitalWrite(LED_BUILTIN, LOW);
    }

    // Delay for a second
    delay(100);
  }
}