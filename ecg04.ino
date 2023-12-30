#include <Arduino.h>
#include <BluetoothSerial.h>

// Definition of three signals
const int signal1Pin = 2;
const int signal2Pin = 3;
const int signal3Pin = 4;

BluetoothSerial SerialBT; 

void setup() {
  // Start of serial communication with a speed of 9600 bits per second
  Serial.begin(9600);

//Start Bluetooth connection
SerialBT.begin("Arduino Bluetooth"); // نام دستگاه بلوتوث

  // Set pins as outputs
  pinMode(signal1Pin, OUTPUT);
  pinMode(signal2Pin, OUTPUT);
  pinMode(signal3Pin, OUTPUT);
}

void loop() {
  // Generating three signals with different patterns
  // You can add your own patterns and values
  int signal1Value = map(millis(), 0, 2000, 0, 255);
  int signal2Value = map(millis(), 0, 3000, 0, 255);
  int signal3Value = map(millis(), 0, 4000, 0, 255);

  // Sending signals to Serial Plotter
  Serial.print(signal1Value);
  Serial.print('\t');
  Serial.print(signal2Value);
  Serial.print('\t');
  Serial.println(signal3Value);

  // Setting the values ​​of the signals on the pins
  analogWrite(signal1Pin, signal1Value);
  analogWrite(signal2Pin, signal2Value);
  analogWrite(signal3Pin, signal3Value);

  // توقف برای مدت زمان کوتاه
  delay(10);
}
