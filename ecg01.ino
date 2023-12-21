#include <driver/dac.h>
#include <driver/adc.h>

const int SIGNAL_PIN1 = 23;
const int SIGNAL_PIN2 = 22;
const int SIGNAL_PIN3 = 21;
const int SIGNAL_PIN4 = 19;
const int SIGNAL_PIN5 = 18;
const int SIGNAL_PIN6 = 5;
const int SIGNAL_PIN7 = 4;
const int SIGNAL_PIN8 = 2;
const int SIGNAL_PIN9 = 15;
const int SIGNAL_PIN10 = 14;

hw_timer_t *Timer0_Cfg = NULL;

volatile int counter = 0;
volatile unsigned short int adc[10];

void IRAM_ATTR Timer0_ISR() {
  dac_output_voltage(DAC_CHANNEL_1, adc[counter]);
  counter++;
  if (counter >= 10) {
    counter = 0;
  }
}

void SignalSetup() {
  pinMode(SIGNAL_PIN1, OUTPUT);
  pinMode(SIGNAL_PIN2, OUTPUT);
  pinMode(SIGNAL_PIN3, OUTPUT);
  pinMode(SIGNAL_PIN4, OUTPUT);
  pinMode(SIGNAL_PIN5, OUTPUT);
  pinMode(SIGNAL_PIN6, OUTPUT);
  pinMode(SIGNAL_PIN7, OUTPUT);
  pinMode(SIGNAL_PIN8, OUTPUT);
  pinMode(SIGNAL_PIN9, OUTPUT);
  pinMode(SIGNAL_PIN10, OUTPUT);
}

void setup() {
  Serial.begin(9600);
  Serial.println("\nESP32 WiFi Receiver.");
  dac_output_enable(DAC_CHANNEL_1);
  dac_output_voltage(DAC_CHANNEL_1, 0);
  Timer0_Cfg = timerBegin(0, 80, true); // Timer 0 for generating DAC signals.
  timerAttachInterrupt(Timer0_Cfg, &Timer0_ISR, true);
  timerAlarmWrite(Timer0_Cfg, 5000, true); // Generate an interrupt every 5000us (1kHz frequency).
  timerAlarmEnable(Timer0_Cfg);
  SignalSetup();
}

void loop() {
  static long timer = millis();
  if (millis() - timer > 1000) {
    for (int i = 0; i < 10; i++) {
      adc[i] = analogRead(i);
    }
    Serial.println("ADC Values:");
    for (int i = 0; i < 10; i++) {
      Serial.print("Channel ");
      Serial.print(i);
      Serial.print(": ");
      Serial.println(adc[i]);
    }
    counter = 0;
    timer = millis();
  }
}
