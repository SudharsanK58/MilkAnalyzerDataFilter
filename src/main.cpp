#include <Arduino.h>
#include "BluetoothSerial.h"
BluetoothSerial SerialBT;
String previousData = "";  // Variable to store previous data
void setup() {
  Serial.begin(9600);   // Start the serial monitor
  Serial2.begin(2400);  // Start Serial2 with baud rate of 2400
  SerialBT.begin("ESP32_Robojax"); //Bluetooth device name
  Serial.println("The device started, now you can pair it with bluetooth!");
}

void loop() {
  if (Serial2.available()) {
    char incomingData = Serial2.read();
    if (incomingData == '(') {
      String data;
      while (incomingData != ')') {
        if (Serial2.available()) {
          incomingData = Serial2.read();
          if (incomingData != ')') {
            data += incomingData;
          }
        }
      }
      if (data.length() == 29 && (data != previousData)) {
        Serial.println(data);
        previousData = data;
        const char* charData = data.c_str();
        SerialBT.println(charData);
      }
    }
  }
}
