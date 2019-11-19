//===========================================================================================
// This function starts i2c communication of sensor and this is called from the main code.
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
// https://github.com/ControlEverythingCommunity/MLX90393/blob/master/Arduino/MLX90393.ino
//===========================================================================================

void MLX90393() 
{
  unsigned int data[7];
  
  // Start I2C Transmission
  Wire.beginTransmission(Addr);
  // Start single meaurement mode,  ZYX enabled
  Wire.write(0x3E);
  // Stop I2C Transmission
  Wire.endTransmission();
  
  // Request 1 byte of data
  Wire.requestFrom(Addr, 1);
  
  // Read status byte
  if(Wire.available() == 1) 
  {
   unsigned int c = Wire.read();
  }
  delay(100);

  // Start I2C Transmission
  Wire.beginTransmission(Addr);
  // Send read measurement command, ZYX enabled
  Wire.write(0x4E);
  // Stop I2C Transmission
  Wire.endTransmission();
  
  // Request 7 bytes of data
  Wire.requestFrom(Addr, 7);

  // Read 7 bytes of data
  // status, xMag msb, xMag lsb, yMag msb, yMag lsb, zMag msb, zMag lsb
  if(Wire.available() == 7);
  {
    data[0] = Wire.read();
    data[1] = Wire.read();
    data[2] = Wire.read();
    data[3] = Wire.read();
    data[4] = Wire.read();
    data[5] = Wire.read();
    data[6] = Wire.read();
  }

  // Convert the data
  xMag = data[1] * 256 + data[2];
  yMag = data[3] * 256 + data[4];
  zMag = data[5] * 256 + data[6];

  // Output data to serial monitor
  Serial.print("Magnetic Field in X-Axis : ");
  Serial.println(xMag);
  Serial.print("Magnetic Field in Y-Axis : ");
  Serial.println(yMag);
  Serial.print("Magnetic Field in Z-Axis : ");
  Serial.println(zMag);
  delay(500);
}
