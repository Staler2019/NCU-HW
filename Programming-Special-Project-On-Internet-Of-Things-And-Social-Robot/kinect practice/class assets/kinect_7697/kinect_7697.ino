#include "Ultrasonic.h"
#include <Arduino_JSON.h>
#include <LWiFi.h>

int range;
Ultrasonic __ultrasonic2(2);

const char *ssid = "TELDAP-2";
const char *password = "TELDAP4F";

const uint16_t port = 8002;
const char *host = "10.50.2.97";
WiFiClient client;

void setup()
{
    // put your setup code here, to run once:
    Serial.begin(9600);

    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.println("...");
    }
    Serial.print("WiFi connected with IP: ");
    Serial.println(WiFi.localIP());
}

void loop()
{
    // put your main code here, to run repeatedly:
    if (client.connected()) {
        range = __ultrasonic2.MeasureInCentimeters();
        Serial.println(range);
        JSONVar instructionObj;
        JSONVar materialObj;
        if (range < 5) {
            materialObj["background"] = "playground.jpg";
            materialObj["shift_x"] = 80.0;
            materialObj["shift_y"] = 80.0;
            materialObj["foreground"] = "fire.png";
            materialObj["scale"] = 1.0;
            materialObj["prop"] = "gun.png";
            instructionObj["instruction"] = "Scene";
            instructionObj["material"] = materialObj;
        }
        else {
            materialObj["background"] = "gym.jpg";
            materialObj["shift_x"] = 80.0;
            materialObj["shift_y"] = 80.0;
            materialObj["foreground"] = "fire.png";
            materialObj["scale"] = 1.0;
            materialObj["prop"] = "gun.png";
            instructionObj["instruction"] = "Scene";
            instructionObj["material"] = materialObj;
        }
        String jsonString = JSON.stringify(instructionObj) + "\n";
        // Serial.println (jsonString);
        client.print(jsonString);
        delay(1000);
    }
    else {
        if (!client.connect(host, port)) {
            Serial.println("Connection to host failed");
            delay(1000);
            return;
        }
        else {
            Serial.println("Connected to server successful!");
        }
    }
}
