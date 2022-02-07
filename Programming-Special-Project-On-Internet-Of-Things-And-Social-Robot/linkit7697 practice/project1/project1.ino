/*
 * Generated using BlocklyDuino:
 *
 * https://github.com/MediaTek-Labs/BlocklyDuino-for-LinkIt
 *
 * Date: Wed, 13 Oct 2021 12:45:50 GMT
 */

#include "Ultrasonic.h"

int dist;

float yelDist;

Ultrasonic __ultrasonic3(3);

void setup()
{
    Serial.begin(9600);

    pinMode(15, OUTPUT);
    pinMode(16, OUTPUT);
    pinMode(17, OUTPUT);
}

void loop()
{
    dist = __ultrasonic3.MeasureInCentimeters();
    yelDist = (analogRead(14) / 4095) * 5 + 1;
    if ((float)dist < yelDist) { // red
        digitalWrite(15, HIGH);
        digitalWrite(16, HIGH);
        digitalWrite(17, LOW);
    }
    else if ((float)dist <= (yelDist + 2)) { // yellow
        digitalWrite(15, HIGH);
        digitalWrite(16, LOW);
        digitalWrite(17, LOW);
    }
    else { // green
        digitalWrite(15, HIGH);
        digitalWrite(16, LOW);
        digitalWrite(17, HIGH);
    }
    delay(500);
}
