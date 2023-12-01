#include <WiFiNINA.h>
#include <MKRIMU.h>

char ssid[] = "s23";        // your network SSID (name)
char pass[] = "1234567890"; // your network password (use for WPA, or use as key for WEP)
int status = WL_IDLE_STATUS; // the Wifi radio's status

void setup() {
  // Initialize serial and wait for port to open:
  Serial.begin(9600);
  while (!Serial);

  // Initialize IMU
  if (!IMU.begin()) {
    Serial.println("Failed to initialize IMU!");
    while (1);
  }

  // Attempt to connect to Wifi network:
  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to network: ");
    Serial.println(ssid);
    status = WiFi.begin(ssid, pass);
    delay(10000);
  }

  Serial.println("You're connected to the network");
  Serial.println("----------------------------------------");
  printWifiData();  // Print WiFi data only once after connection
  Serial.println("----------------------------------------");
}

void loop() {
  // Update IMU data more frequently
  printIMUData();

  // Small delay to make the output readable
  delay(500); 
}

void printWifiData() {
  // Print board and network information
  Serial.println("Board Information:");
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);
  Serial.println();
  Serial.println("Network Information:");
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.println(rssi);
  byte encryption = WiFi.encryptionType();
  Serial.print("Encryption Type:");
  Serial.println(encryption, HEX);
  Serial.println();
}

void printIMUData() {
  // Check if IMU data is available
  if (IMU.accelerationAvailable() && IMU.gyroscopeAvailable()) {
    float ax, ay, az;
    float gx, gy, gz;

    // Read acceleration and gyroscope
    IMU.readAcceleration(ax, ay, az);
    IMU.readGyroscope(gx, gy, gz);

    // Print IMU data
    Serial.print("Acceleration - X: ");
    Serial.print(ax);
    Serial.print(", Y: ");
    Serial.print(ay);
    Serial.print(", Z: ");
    Serial.println(az);
    Serial.print("Gyroscope - X: ");
    Serial.print(gx);
    Serial.print(", Y: ");
    Serial.print(gy);
    Serial.print(", Z: ");
    Serial.println(gz);
    Serial.println();
  }
}
