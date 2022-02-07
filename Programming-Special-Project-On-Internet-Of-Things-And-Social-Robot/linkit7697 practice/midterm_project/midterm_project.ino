// arduino: linkit 7697
#include "Ultrasonic.h"
#include <LBLE.h>
#include <LBLEPeriphral.h>
#include <SeeedOLED.h>
#include <Wire.h>

// c++
#include <bits/stdc++.h>
using namespace std;

// global var
int oledData;
int loudness;
int range1, range2;
int dirLoudness[4]{};
static int CARLEFT90 = 241;

LBLEService counterService("4e38e0c3-ab04-4c5d-b54a-852900379bb3");
LBLECharacteristicInt counterCharacteristic("4e38e0c4-ab04-4c5d-b54a-852900379bb3", LBLE_READ | LBLE_WRITE);
Ultrasonic __ultrasonic1(4); // D4
Ultrasonic __ultrasonic2(5); // D5

// functions definition
void carStop();
void carForward();
void carBackward();
void carLeft();
void carRight();
void lbleSetup();
void oledSetup();
void carActions();
void readUltrasonicRange();
void displayOledData();
void readDirLoudness();
void readLoudness();
void writeLoudness();
void readLbleData();
void car2LoudestDir();
void tooLoud();
void waitLbleStartingWord();

// main
void setup()
{
    Serial.begin(9600);

    lbleSetup();

    oledSetup();

    Serial.println("success");

    waitLbleStartingWord();
}

void loop()
{
    readUltrasonicRange();

    carActions();

    readLoudness();

    if (loudness > 10) {
        tooLoud();
    }
}

// functions
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

void lbleSetup()
{
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
}

void oledSetup()
{
    Wire.begin();
    SeeedOled.init();
    SeeedOled.deactivateScroll();
    SeeedOled.setPageMode();
}

void carActions()
{
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
    delay(CARLEFT90);
}

void readUltrasonicRange()
{
    range1 = __ultrasonic1.MeasureInCentimeters(); // D4
    range2 = __ultrasonic2.MeasureInCentimeters(); // D5
}

void displayOledData()
{
    SeeedOled.clearDisplay();
    SeeedOled.setTextXY(0, 0);
    SeeedOled.putNumber(oledData);
    SeeedOled.setTextXY(1, 0);
    SeeedOled.putString(" is too loud!");
}

void readDirLoudness() // four directions
{
    for (int i = 0; i < 4; i++) {
        carLeft();
        delay(CARLEFT90);
        carStop();
        delay(500);

        dirLoudness[i] = analogRead(0);

        Serial.print(i);
        Serial.print(": ");
        Serial.println(dirLoudness[i]);

        delay(500);
    }
}

void readLoudness()
{
    loudness = analogRead(0);
    Serial.println(loudness);
}

void writeLoudness()
{
    counterCharacteristic.setValue(loudness);
    LBLEPeripheral.notifyAll(counterCharacteristic);
}

void readLbleData() // data store to oledData
{
    while (!counterCharacteristic.isWritten()) {
        ;
    }
    oledData = counterCharacteristic.getValue();
    Serial.println(oledData);
}

void car2LoudestDir()
{
    int maxNum = dirLoudness[0], maxIndex = 0;
    for (int i = 1; i < 4; i++) {
        if (maxNum < dirLoudness[i]) {
            maxNum = dirLoudness[i];
            maxIndex = i;
        }
    }

    carLeft();
    delay(CARLEFT90 * (maxIndex + 1));
    carStop();
    delay(CARLEFT90);
}

void tooLoud()
{
    carStop();

    writeLoudness();

    readLbleData();

    displayOledData();

    Serial.println("end");

    readDirLoudness();

    car2LoudestDir();
}

void waitLbleStartingWord()
{
    while (!counterCharacteristic.isWritten()) {
        ;
    }
}