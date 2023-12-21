#include <Arduino.h>

const int signalCount = 10;
const int signalFrequency = 1000;  // 1 kHz
const int signalAmplitude = 100;   // Adjust as needed

void setup() {
  Serial.begin(115200);
  setupSinSignals();
}

void loop() {
  // Your main code goes here
}

void setupSinSignals() {
  for (int i = 0; i < signalCount; ++i) {
    float frequency = signalFrequency * (i + 1);
    float period = 1.0 / frequency * 1000000; // Convert to microseconds
    
    // Configure Timer
    timerBegin(i, period);

    // Attach ISR to Timer
    timerAttachInterrupt(i, onTimer, true);

    // Set the timer alarm
    timerAlarmWrite(i, period, true);

    // Enable the timer
    timerAlarmEnable(i);
  }
}

void onTimer() {
  // Handle timer interrupt, generate sinusoidal signal, and display
  for (int i = 0; i < signalCount; ++i) {
    float frequency = signalFrequency * (i + 1);
    float sinValue = signalAmplitude * sin(micros() * 2 * PI / frequency);
    
    // Print or display sinValue as needed
    Serial.print(sinValue);
    Serial.print("\t");
  }
  Serial.println();
}

void timerBegin(int timerIndex, float period) {
  // Initialize and configure the timer
  timerConfig_t config;
  config.divider = 80; // 80 prescaler for 80MHz clock
  config.counter_dir = TIMER_COUNT_UP;
  config.counter_en = TIMER_PAUSE;
  config.alarm_en = TIMER_ALARM_EN;
  config.bit_width = TIMER_BIT_WIDTH_16;
  config.auto_reload = true;

  timer_init(timerGroupToUse, timerIndex, &config);
  timer_set_counter_value(timerGroupToUse, timerIndex, 0x0000ULL);
  timer_set_alarm_value(timerGroupToUse, timerIndex, period);
}
