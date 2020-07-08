#include <Arduino.h>
#include <NTPClient.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <WiFiUdp.h>
#include <Wire.h>
#include <SPI.h>
#include <WEMOS_Matrix_GFX.h>
#include <TimeLib.h>
#include "wifi_settings.h"

ESP8266WiFiMulti wifiMulti;
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "jp.pool.ntp.org", 3600 * 9, 3600000);
MLED matrix(0);

const unsigned char loading [] = { 0x00, 0x54, 0x50, 0x74, 0x54, 0x54, 0x00, 0x00 };
const int hourY = 0;
const int hourBits = 5;
const int minuteY = 2;
const int minuteBits = 6;
const int secondY = 4;
const int secondBits = 6;
const int dayY = 6;
const int dayBits = 5;
const int monthY = 7;
const int monthBits = 4;

void setupWifi() {
  ESP.eraseConfig();
  Serial.print("Connecting to WiFi");

  for (int i = 0; i < 2; i++) {
    wifiMulti.addAP(ssid[i], password[i]);
  }

  while (wifiMulti.run() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("WiFi connected to ");
  Serial.println(WiFi.SSID().c_str());
}

void setupClock() {
  timeClient.begin();
  timeClient.update();
  Serial.println(timeClient.getFormattedTime());
}

void setup()
{
  Serial.begin(115200);
  Serial.println("Hi!");

  // Display loading screen while setting up wifi and clock
  matrix.clear();
  matrix.drawBitmap(0, 0, loading, 8, 8, LED_ON);
  matrix.writeDisplay();

  setupWifi();
  setupClock();
}

void drawTimeUnit(int value, int row, int length) {
  int binary [6] = {};
  for (int i = 0; value > 0; i++) {
    binary[i] = value % 2;
    value = value / 2;
  }

  for (int i = 0; i < length; i++) {
    if (binary[i]) {
      matrix.drawPixel(i, row, LED_ON);
    }
  }
}

void loop()
{
  matrix.clear();
  setTime(timeClient.getEpochTime());
  time_t t = now();

  drawTimeUnit(hour(t), hourY, hourBits);
  drawTimeUnit(minute(t), minuteY, minuteBits);
  drawTimeUnit(second(t), secondY, secondBits);
  drawTimeUnit(day(t), dayY, dayBits);
  drawTimeUnit(month(t), monthY, monthBits);
  matrix.drawPixel(7, weekday(t) - 1, LED_ON);

  matrix.writeDisplay();
  delay(500);
}