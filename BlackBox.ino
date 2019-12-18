
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include "index.h"  //Web page header file

#include <EEPROM.h>
#include <Ticker.h>
#define DATA_OFFSET     10

ESP8266WebServer server(80); //Server on port 80
//Enter your SSID and PASSWORD
const char* ssid = "skateboard";
const char* password = "skateboard";

Ticker life_time_writer;
//int ticker = 0;

int counter;
int diameter;
int state;
int previousState;

int life_time_value;
int previous_lifetime_value;

//===============================================================
// sensor function
//===============================================================

int updateCounter() {
  state = analogRead(A0);
  //   Serial.println(state);

  // compare the buttonState to its previous state
  if (state != previousState) {
    if (state == 1024) {
      // if the current state is HIGH then the button went from off to on:
      counter ++;
      //debug
      Serial.println("on");
      Serial.print("counter= ");
      Serial.println(counter);
    } else {
      // if the current state is LOW then the button went from on to off:
      //      Serial.println("off");
    }
  }
  // save the current state as the last state, for next time through the loop
  previousState = state;
  return counter;
}

//===============================================================
// server functions
//===============================================================
void handleRoot() {
  Serial.println("handling HTTP request for root");
  String s = MAIN_page; //Read HTML contents
  server.send(200, "text/html", s); //Send web page
}
void handleLifetimeRequest() {
  int a = life_time_value;
  String string_life_time_value = String(a);
  Serial.print("sending data to web browser:");
  Serial.println(string_life_time_value);
  server.send(200, "text/plain", string_life_time_value); //Send ADC value only to client ajax request
  Serial.print("sending data to web browser:");
  Serial.println(string_life_time_value);
}

//===============================================================
// Setup & main loop
//===============================================================

void setup() {
  Serial.begin(115200);
  delay(1000);
  EEPROM.begin(4096);

  int counter = 0;
  state = 1024;
  previousState = 1024;

  // write data every 60s
  life_time_writer.attach(60,  updateWrite);

  // Read data from flash memory (EEPROM library)
  int output = readValue(0); //readString(adress);
  Serial.print("Reading output: ");
  Serial.println(output);

  life_time_value = output;
  previous_lifetime_value = output; // copy current value of lifetime_counter at startup

  //ESP32 connects to your wifi ----------------------------------------------------------------------
  WiFi.mode(WIFI_AP);           //Only Access point
  WiFi.softAP(ssid, password);  //Start HOTspot removing password will disable security  WiFi.softAPConfig(myIP, myIP, IPAddress(255, 255, 255, 0));

  //If connection successful show IP address in serial monitor
  IPAddress myIP = WiFi.softAPIP(); //Get IP address
  Serial.print("HotSpt IP:");
  Serial.println(myIP);

  server.on("/", handleRoot);      //This is display page
  server.on("/readLifetime", handleLifetimeRequest);
  server.begin();                  //Start server
  //  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();
  updateCounter();
  delay(100);
}


//===============================================================
// eeprom functions
//===============================================================

void updateWrite() {
  counter = updateCounter();
  life_time_value = previous_lifetime_value + counter;
  int input = life_time_value;
  writeValue(input, 0);
  Serial.print("Writing input: ");
  Serial.println(input);
//
//  ++ticker;
//  // when the ticker reaches a certain value, start write value onto eeprom memory
//  if (ticker == 20) {
//    life_time_writer.attach(0.1, updateWrite);
//  }
//  // when the ticker reaches yet another value, stop writing
//  else if (ticker == 22) {
//    life_time_writer.detach();
//  }
}

void writeValue(int value, int pos) {
  int s = value;
  EEPROM.write( pos + DATA_OFFSET, s); //EEPROM.write(adress, value);
  //  EEPROM.write( pos + DATA_OFFSET + 1, s, '\0' )
  EEPROM.commit();
  Serial.println();
}

// Set 'pos' parameter to specify begin position of the string in memory
int readValue(int pos) {
  int output = EEPROM.read(pos + DATA_OFFSET);
  return output;
}
