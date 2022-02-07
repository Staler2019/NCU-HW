#include "Ultrasonic.h"
#include <LBLE.h>
#include <LBLEPeriphral.h>
#include <SeeedOLED.h>
#include <Wire.h>
#include <bits/stdc++.h>

using namespace std;

int data;
int loudness;
int range1, range2;
static int CARLEFT90 = 241;

LBLEService counterService("4e38e0c3-ab04-4c5d-b54a-852900379bb3");
LBLECharacteristicInt counterCharacteristic("4e38e0c4-ab04-4c5d-b54a-852900379bb3", LBLE_READ | LBLE_WRITE);
Ultrasonic __ultrasonic1(4);
Ultrasonic __ultrasonic2(5);

void carStop()
{
    digitalWrite(10, LOW);
    digitalWrite(11, LOW);
    digitalWrite(12, LOW);
    digitalWrite(13, LOW);
}

void carForward()
{
    digitalWrite(10, HIGH);
    digitalWrite(11, LOW);
    digitalWrite(12, HIGH);
    digitalWrite(13, LOW);
}

void carBackward()
{
    digitalWrite(10, LOW);
    digitalWrite(11, HIGH);
    digitalWrite(12, LOW);
    digitalWrite(13, HIGH);
}

void carLeft()
{
    digitalWrite(10, HIGH);
    digitalWrite(11, LOW);
    digitalWrite(12, LOW);
    digitalWrite(13, HIGH); // right back
}

void carRight()
{
    digitalWrite(10, LOW);
    digitalWrite(11, HIGH); // left back
    digitalWrite(12, HIGH);
    digitalWrite(13, LOW);
}

void setup()
{
    Serial.begin(9600);
    LBLE.begin();
    while (!LBLE.ready()) {
        delay(100);
    }

    counterService.addAttribute(counterCharacteristic);

    LBLEPeripheral.addService(counterService);
    LBLEPeripheral.begin();
    LBLEAdvertisementData __advertisement;
    __advertisement.configAsConnectableDevice("guai guai");
    LBLEPeripheral.advertise(__advertisement);

    Wire.begin();
    SeeedOled.init();
    SeeedOled.deactivateScroll();
    SeeedOled.setPageMode();

    Serial.println("success");
    while (!counterCharacteristic.isWritten()) {
        ;
    }
}

void loop()
{
    range1 = __ultrasonic1.MeasureInCentimeters(); // D4
    range2 = __ultrasonic2.MeasureInCentimeters(); // D5

    if (range1 < 30 && range2 < 30) {
        carStop();
        delay(100);

        carBackward();
        delay(1000);

        carStop();
        delay(100);

        carRight();
    }
    else if (range1 < 30) {
        carStop();
        delay(100);

        carBackward();
        delay(200);

        carStop();
        delay(100);

        carLeft();
    }
    else if (range2 < 30) {
        carStop();
        delay(100);

        carBackward();
        delay(200);

        carStop();
        delay(100);

        carRight();
    }
    else {
        carForward();
    }

    loudness = analogRead(0);
    Serial.println(loudness);

    if (loudness > 10) {
        carStop();
        counterCharacteristic.setValue(loudness);
        LBLEPeripheral.notifyAll(counterCharacteristic);

        while (!counterCharacteristic.isWritten()) {
            ;
        }
        data = counterCharacteristic.getValue();
        Serial.println(data);

        SeeedOled.clearDisplay();
        SeeedOled.setTextXY(0, 0);
        SeeedOled.putNumber(data);
        SeeedOled.setTextXY(1, 0);
        SeeedOled.putString(" is too loud!");
        Serial.println("end");

        int time = 0;
        int arr[4] = {};

        for (int i = 0; i < 4; i++) {
            carLeft();
            delay(CARLEFT90);
            carStop();
            delay(500);
            arr[i] = analogRead(0);
            Serial.print(i);
            Serial.print(": ");
            Serial.println(arr[i]);
            delay(500);
        }

        int maxNum = arr[0], maxIndex = 0;
        for (int i = 1; i < 4; i++) {
            if (maxNum < arr[i]) {
                maxNum = arr[i];
                maxIndex = i;
            }
        }

        carLeft();
        delay(CARLEFT90 * (maxIndex + 1));
        carStop();

        // carForward();
    }
    delay(CARLEFT90);
}
