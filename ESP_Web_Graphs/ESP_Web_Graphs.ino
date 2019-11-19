//================================================================================
// This program reads from sensor, connects to a Wi-Fi device and displays three
// graphs to show magnetic flux changes in X, Y, Z axes.
//
//              Author: Azraful Awal Hamim
//              Project: Tactile Sensing Wireless Data Plotting
//              Supervisor: Dr. Lorenzo Jamone
//              Course: MSc Internet of Things (Data)
//              Sensor: MLX90393 Triaxis® Magnetic Field Sensor
//              Output: Forces in X,Y,Z axis
//              Microcontroller: ESP32              
//
// The initial code was taken from the following website, but was changed
// to suit the needs of the specific sensor used in this project: 
// https://randomnerdtutorials.com/esp32-esp8266-plot-chart-web-server/
//================================================================================
               
 
 int xMag ;
 int yMag ;
 int zMag ;

#include<Wire.h>
// MLX90393 I2C Address is 0x0F(15)
#define Addr 0x0F

// Import required libraries
#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <SPIFFS.h>

//=================== Wi-Fi details ========================

// Replace with your network credentials
const char* ssid = "connect";
const char* password = "12345678";

// Create AsyncWebServer object on port 80
AsyncWebServer server(80);
//====================== x axis ============================
String readxaxis() {
  // Read temperature as Celsius (the default)
  float x;
  x = xMag;
  
  if (isnan(x)) {    
    Serial.println("Failed to read from sensor!");
    return "";
  }
  else {
    Serial.println(x);
    return String(x);
  }
}
//======================== y axis ===========================
String readyaxis() {
  float y ;
  y = yMag;
  if (isnan(y)) {
    Serial.println("Failed to read from sensor!");
    return "";
  }
  else {
    Serial.println(y);
    return String(y);
  }
}
//======================== z axis ============================
String readzaxis() {
  float z;
  z = zMag;
  if (isnan(z)) {
    Serial.println("Failed to read from sensor!");
    return "";
  }
  else {
    Serial.println(z);
    return String(z);
  }
}

void setup(){
  // Serial port for debugging purposes
  Serial.begin(115200);
//============= MLX90393 setup initialisation ======================

// Initialise I2C communication as MASTER 
  Wire.begin();
  // Initialise serial communication, set baud rate = 9600
  Serial.begin(9600);

  // Start I2C Transmission
  Wire.beginTransmission(Addr);
  // Select Write register command
  Wire.write(0x60);
  // Set AH = 0x00, BIST disabled
  Wire.write(0x00);
  // Set AL = 0x5C, Hall plate spinning rate = DEFAULT, GAIN_SEL = 5  
  Wire.write(0x5C);
  // Select address register, (0x00 << 2)
  Wire.write(0x00);
  // Stop I2C Transmission
  Wire.endTransmission();

  // Request 1 byte of data
  Wire.requestFrom(Addr, 1);

  // Read status byte
  if(Wire.available() == 1) 
  {
    unsigned int c = Wire.read();
  }

  // Start I2C Transmission
  Wire.beginTransmission(Addr);
  // Select Write register command
  Wire.write(0x60);
  // Set AH = 0x02
  Wire.write(0x02);
  // Set AL = 0xB4, RES for magnetic measurement = 0
  Wire.write(0xB4);
  // Select address register, (0x02 << 2)
  Wire.write(0x08);
  // Stop I2C Transmission
  Wire.endTransmission();
  
  // Request 1 byte of data
  Wire.requestFrom(Addr, 1);

  // Read status byte
  if(Wire.available() == 1) 
  {
   unsigned int c = Wire.read();
  }
  delay(300);

//====================== MLX90393 setup END ========================
  // Initialize SPIFFS
  if(!SPIFFS.begin()){
    Serial.println("An Error has occurred while mounting SPIFFS");
    return;
  }

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }

  // Print ESP32 Local IP Address
  Serial.println(WiFi.localIP());

  // Route for root / web page
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/index.html");
  });
  server.on("/X", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", readxaxis().c_str());
  });
  server.on("/Y", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", readyaxis().c_str());
  });
  server.on("/Z", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", readzaxis().c_str());
  });

  // Start server
  server.begin();
}
 
void loop(){
  MLX90393();
}
