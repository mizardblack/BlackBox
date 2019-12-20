#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <EEPROM.h>
#include <Ticker.h>

#include "index.h"  //Web page header file

#define DATA_OFFSET 10
#define ANALOG_HIGH 1024
#define ANALOG_LOW 8

ESP8266WebServer server(80); //Server on port 80
//Enter your SSID and PASSWORD
const char* ssid = "skateboard";
const char* password = "skateboard";

Ticker life_time_writer;

int counter;
int previousWheelState;
int startupRotations;

//===============================================================
// sensor function
//===============================================================

// "input" from globals: previousWheelState
// "output" to globals: previousWheelState, counter
void updateCounter() {
  // read state from sensors
  int state = analogRead(A0);
  // if previousWheelState was never initialized (first time), set to HIGH so
  // that when we check for HIGH below, we dont potentially increment
  // counter before one full wheel rotation.
  if (previousWheelState == 0) {
    previousWheelState = ANALOG_HIGH;
  }

  // compare the buttonState to its previous state
  if (state != previousWheelState) {
    if (state == ANALOG_HIGH) {
      // if the current state is HIGH then the button went from off to on:
      counter++;
      Serial.print("counter=");
      Serial.println(counter);
    } else {
      // if the current state is LOW then the button went from on to off:
    }
  }
  // save the current state as the last state, for next time through the loop
  previousWheelState = state;
}

int lifetimeRotations() {
  return startupRotations + counter;
}

//===============================================================
// server functions
//===============================================================

void handleRoot() {
  Serial.println("WEBSERVER: handling HTTP request for root");
  server.send(200, "text/html", String(MAIN_page)); //Send web page
}

void handleLifetimeRequest() {
  Serial.println("WEBSERVER: handling HTTP request for lifetime data");
  server.send(200, "text/plain", String(lifetimeRotations())); //Send ADC value only to client ajax request
}

void handleDataRequest() {
  Serial.println("WEBSERVER: handling HTTP request for big data");
  // build the JSON formatted string
  char data[80]; // current max ~67; char data[80] is a String/array with 80 characters
  sprintf(data, "{\"lifetime_rotations\": %d, \"session_rotations\": %d}", lifetimeRotations(), counter);//print to the String data with formatting
  Serial.println(data); // for additional debugging temporary
  server.send(200, "application/json", data); //Send web page
}

//===============================================================
// eeprom functions
//===============================================================

void updateWrite() {
  int life_time_value = lifetimeRotations();
  writeValue(life_time_value, 0);
  Serial.print("Writing input: ");
  Serial.println(life_time_value);
}

// Writes an integer value to EEPROM at position 'pos'
void writeValue(int value, int pos) {
  EEPROM.write(DATA_OFFSET + pos, value); //EEPROM.write(adress, value);
  EEPROM.commit();
}

// Returns memory value from EEPROM beginning at position 'pos'
int readValue(int pos) {
  return EEPROM.read(DATA_OFFSET + pos);
}

//===============================================================
// Setup & main loop
//===============================================================

void setup() {
  Serial.begin(115200);
  delay(1000);
  EEPROM.begin(4096);

  // set ticker to write data every 60s
  life_time_writer.attach(60,  updateWrite);

  // Initialize stored lifetime value from flash memory (EEPROM library)
  startupRotations = readValue(0);
  Serial.printf("\nReading previous lifetime value from memory: %d\n", startupRotations);
  // ^^ homework: replaced with a single Serial.printf function
  
  // Start up a local WiFi access point
  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid, password);

  // If startup successful show IP address in serial monitor
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("HotSpot IP: ");
  Serial.println(myIP);

  // Configure and start web server
  server.on("/", handleRoot);      //This is display page
  server.on("/readLifetime", handleLifetimeRequest);
  server.on("/bigData", handleDataRequest);  
  server.begin();                  //Start server
}

void loop() {
  server.handleClient();
  updateCounter();
  delay(100);
}
