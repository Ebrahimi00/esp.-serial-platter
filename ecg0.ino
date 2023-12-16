#include <dummy.h>

#include <driver/dac.h>
#include <driver/adc.h>
#include "esp_wifi.h"
#include <Arduino.h>
#include "SerialPlot.h"

//اشاره گرهای تایمر
hw_timer_t *Timer0_Cfg = NULL;

volatile int counter = 0;
volatile unsigned short adc = (analogRead(35)) >> 4;
float scaled_adc = adc * (2 * PI / 1023.0);
float sine_value = sin(scaled_adc);

 // adc/16 - 12bits to 8bits

//اجرای وقفه در زمانهای تعیین شده
void IRAM_ATTR Timer0_ISR() {
  dac_output_voltage(DAC_CHANNEL_1, adc);
  counter++;
}

void setup() {
  Serial.begin(9600);
  Serial.println("\nESP32 DAC sine wave");
//تنظیم زمان وقفه           
  Timer0_Cfg = timerBegin(0, 400, true);
  timerAttachInterrupt(Timer0_Cfg, &Timer0_ISR, true);
  timerAlarmWrite(Timer0_Cfg, 10, true);
  timerAlarmEnable(Timer0_Cfg);
  // Enable DAC1 Channel's Output
  dac_output_enable(DAC_CHANNEL_1);
  analogSetWidth(12);    // تنظیم رزولیشن 12
  analogSetClockDiv(255);  // تبدیل سریعترین زمان
    esp_wifi_stop();
}

void loop() {
  adc=adc1_get_raw(ADC1_CHANNEL_7)>>4; // GPIO32
 // adc=analogRead(35)>>4;
  static long timer = millis();
  if (millis() - timer > 1000) {
    Serial.println(counter);
    counter = 0;
    timer = millis();
  }
}



