//
// Created by major-kellogs on 13.04.22.
//

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ctime>
#include "Credentials.h"

#define PIN_LED 2

struct tm timeInfo{};
const char *ntpServer = "pool.ntp.org";
const long gmtOffset_sec = 3600;
const int daylightOffset_sec = 3600;

IPAddress local_IP(0, 0, 0, 0);
IPAddress gateway(0, 0, 0, 0);
IPAddress subnet(255, 255, 255, 0);
IPAddress primaryDNS(8, 8, 8, 8);   //optional
IPAddress secondaryDNS(8, 8, 4, 4); //optional

bool getLocalTime(struct tm *info, uint32_t ms) {
    uint32_t start = millis();
    time_t now;
    while ((millis() - start) <= ms) {
        time(&now);
        localtime_r(&now, info);
        if (info->tm_year > (2016 - 1900)) {
            return true;
        }
        delay(10);
    }
    return false;
}


void adjustTimeOverNTP() {
    configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
}

void controlLEDs() {
    if (!getLocalTime(&timeInfo, 5000)) {
        Serial.println("Failed to obtain time");
        return;
    }

    //Adjust the conditions to define the time. This was initially built for a small fish tank. So I didn't needed anything special.
    uint8 isLEDBright =
            (timeInfo.tm_hour >= 10 && timeInfo.tm_hour < 15) ||
            (timeInfo.tm_hour >= 18 && timeInfo.tm_hour < 23);

    digitalWrite(PIN_LED, isLEDBright);
    digitalWrite(PIN_LED, 1);

//    Serial.println(String(timeInfo.tm_hour) + String(":") + String(timeInfo.tm_min) + ":" + String(timeInfo.tm_sec));
}


void setup() {
    pinMode(PIN_LED, OUTPUT);
    Serial.begin(9600);

    // Connect to Wi-Fi
    if (!WiFi.config(local_IP, gateway, subnet, primaryDNS, secondaryDNS)) {
        Serial.println("STA Failed to configure");
    }

    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.println("Connecting to WiFi..");
    }

    Serial.println(WiFi.localIP());

    adjustTimeOverNTP();
}

void loop() {
    controlLEDs();
    Serial.println("hallo");
}