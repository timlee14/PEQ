#include <Arduino_MKRGPS.h>

void setup() {
  Serial.begin(9600);
  while (!Serial);
  Serial.println("I AM SETUP");

  // If the GPS module does not initialize, print an error message
  if (!GPS.begin(GPS_MODE_SHIELD)) {
    Serial.println("Failed to initialize GPS!");
    while (1);
  }
}

void loop() {
  Serial.println("I AM LOOP");
  // Check if new GPS data is available
  if (GPS.available()) {
    // Print latitude and longitude
    Serial.print("Latitude: ");
    Serial.println(GPS.latitude(), 7);
    Serial.print("Longitude: ");
    Serial.println(GPS.longitude(), 7);

    // Optional: You can also get other data like speed, altitude, etc.
  }

  delay(1000);  // Update rate
}
