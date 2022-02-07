// rfid
#include <MFRC522.h>
#include <SPI.h>
// oled
#include <SeeedOLED.h>
#include <Wire.h>
// moda
#include <Servo.h>

// device
MFRC522 rfid(/*SS_PIN*/ 10, /*RST_PIN*/ 9);
Servo servo14;

// var
String read_id;
String rfids[4] = {};
bool readRFIDFlag, checkRFIDFlag;
int rfidIndex, displayCounter;

void initFlags()
{
    printOLED("init...");
    Serial.println("init...");
    delay(1000);
    printOLED("");

    readRFIDFlag = true;
    checkRFIDFlag = false;
    rfids[0] = rfids[1] = rfids[2] = rfids[3] = "";
    rfidIndex = displayCounter = 0;
}

String mfrc522_readID()
{
    String ret;
    if (rfid.PICC_IsNewCardPresent() && rfid.PICC_ReadCardSerial()) {
        MFRC522::PICC_Type piccType = rfid.PICC_GetType(rfid.uid.sak);

        for (byte i = 0; i < rfid.uid.size; i++) {
            ret += (rfid.uid.uidByte[i] < 0x10 ? "0" : "");
            ret += String(rfid.uid.uidByte[i], HEX);
        }
    }

    // Halt PICC
    rfid.PICC_HaltA();

    // Stop encryption on PCD
    rfid.PCD_StopCrypto1();
    return ret;
}

void printOLED(String str)
{
    SeeedOled.clearDisplay();
    SeeedOled.setTextXY(0, 0);
    SeeedOled.putString(str.c_str());
}

void readRFID()
{
    read_id = mfrc522_readID();
    if (read_id != "") {
        rfids[rfidIndex++] = read_id;

        if (rfidIndex > 1 && rfids[rfidIndex - 2] == read_id) {
            rfidIndex--;
        }
        else {
            Serial.print("The "); // debug
            Serial.print(rfidIndex);
            Serial.print(" th RFID: ");
            Serial.println(read_id.c_str());
            printOLED(read_id);
        }
    }

    if (rfidIndex == 4) { // end
        readRFIDFlag = false;
        checkRFIDFlag = true;
    }
}

void checkRFID()
{
    if (rfids[0] == "15a6f23c" && rfids[1] == "c59baa37" && rfids[2] == "f5b4013c" && rfids[3] == "855f613d") {
        printOLED("Pass!!!");

        servo14.write(0);
        delay(2000);
        servo14.write(180);
        delay(2000);

        exit(0);
    }
    else {
        static int displayCounter = 0;

        printOLED("Fail XD");

        if (++displayCounter == 7) {
            initFlags();
        }
    }
}

void setup()
{
    // putty: uart
    Serial.begin(9600);

    // rfid
    SPI.begin();
    rfid.PCD_Init();

    // OLED
    Wire.begin();
    SeeedOled.init();
    SeeedOled.deactivateScroll();
    SeeedOled.setPageMode();
    SeeedOled.clearDisplay();

    // servo
    servo14.attach(14);

    // GPIO
    pinMode(6, INPUT); // user button

    // main control
    initFlags();
}

void loop()
{
    if (digitalRead(6) == HIGH) { // please press longer than 1 sec
        initFlags();
    }
    else {
        if (readRFIDFlag) {
            // Serial.println("reading");
            readRFID();
        }
        else if (checkRFIDFlag) {
            // Serial.println("checking");
            checkRFID();
        }
    }
    delay(1000);
}