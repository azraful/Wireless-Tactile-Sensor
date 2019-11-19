# Wireless Tactile Sensing Module For Internet of Things Applications

A wireless tactile sensing module using ESP32 micro-controller, magnetometer and 3D printed soft shape, that measures 3-axis normal and shear forces with high sensitivity upon physical contact and visualises the data in real-time on a Wi-Fi connected device locally.

## Setup

1. Download Arduino IDE from https://www.arduino.cc/en/Main/Software.
2. Copy the folders into the local Arduino IDE directory.
3. Copy the folders inside the libraries folder into the Arduino IDE local directory libraries folder.
4. Install the ESP32 board in Arduino IDE:
	      Go to File> Preferences.
	      In Additional Board Manager URLs, type https://dl.espressif.com/dl/package_esp32_index.json.
	      Go to Tools> Boards Manager, search ESP32 and install it.
	      Finally, from Tools> Board, scroll down and select ESP32 Dev Module.
5. Install the file system uploader plugin on Arduino IDE:
	      Download ESP32FS-1.0.zip file from https://github.com/me-no-dev/arduino-esp32fs-plugin/releases/.
	      Go to local computer's Arduino IDE directory and inside Tools, unzip the folder.
	      Restart Arduino IDE and check if under Tools, there is a ESP32 Sketch Data Upload option.
5. Open ESP_Web_Graphs.ino file from its folder on Arduino IDE.
6. Replace Network Credentials (SSID & Password) to connect to WiFi or Hotspot device.
7. Go to Tools> ESP32 Sketch Data Upload to upload the HTML file.
	      When uploading code, press and hold Boot button on ESP32 to load code into it.
8. Click on the right-arrow button to compile and upload the sketch into ESP32.
	      When uploading code, press and hold Boot button on ESP32 to load code into it.
9. Open Serial Monitor of Arduino IDE to check status:
	      Set Baud Rate to 9600. 
	      Wait for ESP32 to connect to WiFi, while Hotspot device is turned on. 
	      When connected, sensor readings will be shown.
10. Open a Browser on viewing device and go to http://192.168.43.206/.
 	      Wait for some time for the graphs to be updated.
	      They will update every 500 milliseconds (half a second) and store 40 data points.
 	      Test changes in forces by touching the soft sensor.

## Device


## Output


## Demo

