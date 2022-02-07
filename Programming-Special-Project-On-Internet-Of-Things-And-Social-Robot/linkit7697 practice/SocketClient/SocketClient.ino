#include <LWiFi.h>

// const char* ssid = "TELDAP-2";
// const char* password = "TELDAP4F";

char ssid[] = "NMSL";
char password[] = "987204886";

const uint16_t port = 8080;
const char* host = "192.168.0.100";  // TODO. WAIT FOR SERVER IP

WiFiClient client;

void serialSetup() { Serial.begin(9600); }

void wifiSetup() {
    Serial.println("Attempting to connect to WPA network...");
    Serial.print("SSID: ");
    Serial.println(ssid);

    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.println("...");
    }

    Serial.print("WiFi connected with IP: ");
    Serial.println(WiFi.localIP());

    while (!client.connect(host, port)) {
        Serial.println("trying connecting...");
        delay(1000);
    }
    Serial.println("socket created");
}

void wifiLoop() {
    if (client.connected() && (client.available() > 0)) {
        Serial.print("set brightness to: ");
        int size;
        int lightValue = 0;
        while ((size = client.available()) > 0) {
            uint8_t* msg = (uint8_t*)malloc(size);
            size = client.read(msg, size);
            String tmp = (char*)msg;
            lightValue *= 10;
            lightValue += tmp.toInt();
            // Serial.write(msg, size);
            free(msg);
        }
        setBrightness(lightValue);
        Serial.println(lightValue);
    }

    // Serial.println("Disconnecting...");
    // client.stop();
}

void setup() {
    serialSetup();
    wifiSetup();
}

void loop() {
    Serial.println("---echo---");
    wifiLoop();
    // printWifiStatus();
    delay(1000);
}

void printWifiStatus() {
    // print the SSID of the network you're attached to:
    Serial.print("SSID: ");
    Serial.println(WiFi.SSID());

    // print your WiFi shield's IP address:
    IPAddress ip = WiFi.localIP();
    Serial.print("IP Address: ");
    Serial.println(ip);

    // print the received signal strength:
    long rssi = WiFi.RSSI();
    Serial.print("signal strength (RSSI):");
    Serial.print(rssi);
    Serial.println(" dBm");
}

void setBrightness(int lightValue) {}
