# esp32.serialplatter
serial platter with timer interrupt with micro esp32

In this repository, Part of the project is to build an ecg device using an esp32 micro and through the desired pin (here pin 35), display the signal with an interval so that the micro works with a frequency of 1 kHz.

Also, this code has a memory and according to the ecg device, it stores and displays the signal from the beginning to the stop of the program.

![ecg1](https://github.com/Ebrahimi00/esp.serialplatter/assets/121750125/7f4fa7f5-29f4-4ebe-93a3-8c0e71dcb98a)

To read the input analog value from the item pin, comment here we use pin 35.
and create an adc variable and get its value using the analogRead(35) function.

esp32 has only 2 dacs and analog sine can only be displayed on 2 bases at the same time.
The only way is to make pwm and with the Rc filter it will become sinusoidal. DAC can only be used for 2 bases.
