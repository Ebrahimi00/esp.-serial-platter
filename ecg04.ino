#include <Arduino.h>
#include <BluetoothSerial.h>

// تعریف سه سیگنال
const int signal1Pin = 2;
const int signal2Pin = 3;
const int signal3Pin = 4;

BluetoothSerial SerialBT; 

void setup() {
  // شروع ارتباط سریال با سرعت 9600 بیت بر ثانیه
  Serial.begin(9600);

// شروع ارتباط بلوتوث
SerialBT.begin("Arduino Bluetooth"); // نام دستگاه بلوتوث

  // تنظیم پین‌ها به عنوان خروجی
  pinMode(signal1Pin, OUTPUT);
  pinMode(signal2Pin, OUTPUT);
  pinMode(signal3Pin, OUTPUT);
}

void loop() {
  // تولید سه سیگنال با الگوهای مختلف
  // می‌توانید الگوها و مقادیر دلخواه خود را اضافه کنید
  int signal1Value = map(millis(), 0, 2000, 0, 255);
  int signal2Value = map(millis(), 0, 3000, 0, 255);
  int signal3Value = map(millis(), 0, 4000, 0, 255);

  // ارسال سیگنال‌ها به Serial Plotter
  Serial.print(signal1Value);
  Serial.print('\t');
  Serial.print(signal2Value);
  Serial.print('\t');
  Serial.println(signal3Value);

  // تنظیم مقادیر سیگنال‌ها بر روی پین‌ها
  analogWrite(signal1Pin, signal1Value);
  analogWrite(signal2Pin, signal2Value);
  analogWrite(signal3Pin, signal3Value);

  // توقف برای مدت زمان کوتاه
  delay(10);
}
