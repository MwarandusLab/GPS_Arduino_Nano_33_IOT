// Use Serial1 for the GPS module (hardware serial)
#define GPS_SERIAL Serial1

void setup() {
  Serial.begin(9600);  // Start the serial communication with the computer
  GPS_SERIAL.begin(9600); // Start the hardware serial communication with the GPS module
}

void loop() {
  if (GPS_SERIAL.available()) {
    String sentence = GPS_SERIAL.readStringUntil('\n'); // Read a line from GPS module

    // Check if the sentence contains latitude and longitude
    if (sentence.startsWith("$GPGGA")) {
      // Split the sentence into individual parts
      char data[100];
      sentence.toCharArray(data, 100);

      // Extract latitude and longitude
      char *token = strtok(data, ",");
      for (int i = 0; i < 6; i++) {
        token = strtok(NULL, ",");
      }
      if (token != NULL) {
        float latitude = atof(token);
        token = strtok(NULL, ",");
        if (token != NULL) {
          float longitude = atof(token);
          Serial.print("Latitude: ");
          Serial.print(latitude, 6); // Print latitude with 6 decimal places
          Serial.print(", Longitude: ");
          Serial.println(longitude, 6); // Print longitude with 6 decimal places
        }
      }
    }
  }
}
