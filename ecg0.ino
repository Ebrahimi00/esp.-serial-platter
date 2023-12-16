#include <driver/dac.h>
#include "esp_wifi.h"
#include <Arduino.h>


//Timer pointers
hw_timer_t *Timer0_Cfg = NULL;

volatile int counter = 0;
volatile unsigned short adc = (analogRead(35)) >> 4;
 // adc/16 - 12bits to 8bits

//float scaled_adc = adc * (2 * PI / 1023.0);
//float sine_value = sin(scaled_adc);


//Execution of interruptions at designated times
void IRAM_ATTR Timer0_ISR() {
  dac_output_voltage(DAC_CHANNEL_1, adc);
  counter++;
}

void setup() {
  Serial.begin(9600);
  Serial.println("\nESP32 DAC sine wave");
//Set timeout           
  Timer0_Cfg = timerBegin(0, 400, true);
  timerAttachInterrupt(Timer0_Cfg, &Timer0_ISR, true);
  timerAlarmWrite(Timer0_Cfg, 10, true);
  timerAlarmEnable(Timer0_Cfg);
  // Enable DAC1 Channel's Output
  dac_output_enable(DAC_CHANNEL_1);
  analogSetWidth(12);    //Setting the resolution 12
  analogSetClockDiv(255);  // Fastest conversion time
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



