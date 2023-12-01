#include <WiFiNINA.h>
#include <MKRIMU.h>
#include <Firebase_Arduino_WiFiNINA.h>

char ssid[] = "s23";        // your network SSID (name)
char pass[] = "1234567890"; // your network password (use for WPA, or use as key for WEP)
#define FIREBASE_HOST "https://realtime-imu-default-rtdb.firebaseio.com/" // Replace with your Firebase database domain
#define FIREBASE_AUTH "PKbdVFzXV3X5SeqVb2QhGVbvkS0ZACLU1WcCUFE2"           // Replace with your Firebase database secret

int status = WL_IDLE_STATUS; // the Wifi radio's status

FirebaseData firebaseData;

void setup() {
  Serial.begin(9600);

  // Connect to WiFi
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");

  // Connect to Firebase
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH, ssid, pass);

  // Initialize IMU
  if (!IMU.begin()) {
    Serial.println("Failed to initialize IMU!");
    while (1);
  }
}

void loop() {
  float ax, ay, az;

  if (IMU.accelerationAvailable()) {
    IMU.readAcceleration(ax, ay, az);

    // Send data to Firebase
    Firebase.setFloat(firebaseData, "/imu/ax", ax);
    Firebase.setFloat(firebaseData, "/imu/ay", ay);
    Firebase.setFloat(firebaseData, "/imu/az", az);
  }

  delay(2000); // Delay between updates
}
