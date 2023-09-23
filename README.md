# Classroom VU Meter with Arduino Nano

This project is a VU meter designed for classroom use. It utilizes an Arduino Nano, a 2-pin buzzer, a KY-037 microphone module, a WS2812 LED strip with 24 LEDs, and a 10k potentiometer. The VU meter provides a graphical representation of the classroom noise level, and a buzzer sounds an alarm when the noise level exceeds a set threshold.

## Table of Contents

- [Hardware Components](#hardware-components)
- [Wiring Description](#wiring-description)
- [Arduino Sketch](#arduino-sketch)

## Hardware Components

1. Arduino Nano
2. 2-Pin Buzzer
3. KY-037 Microphone Module
4. WS2812 LED Strip (24 LEDs)
5. 10k Potentiometer

## Wiring Description

### Arduino Nano to 2-Pin Buzzer
- Connect one pin of the buzzer to `D2` on the Arduino.
- Connect the other pin of the buzzer to `GND` on the Arduino.

### Arduino Nano to KY-037 Microphone Module
- Connect the `VCC` of the KY-037 to `5V` on the Arduino.
- Connect the `GND` of the KY-037 to `GND` on the Arduino.
- Connect the `AOUT` (Analog Output) pin of the KY-037 to `A0` on the Arduino.

### Arduino Nano to WS2812 LEDs
- Connect the `VCC` of the LED strip to `5V` on the Arduino.
- Connect the `GND` of the LED strip to `GND` on the Arduino.
- Connect the `Data In` of the LED strip to `D3` on the Arduino.

### Arduino Nano to 10k Potentiometer
- Connect one outer pin of the potentiometer to `5V` on the Arduino.
- Connect the other outer pin to `GND` on the Arduino.
- Connect the middle pin (wiper) of the potentiometer to `A1` on the Arduino.

## Arduino Sketch

Here's the complete Arduino code for the VU meter:

```arduino
#include <Adafruit_NeoPixel.h>

#define PIN            3
#define NUMPIXELS      24
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

const int buzzerPin = 2;
const int micPin = A0;
const int potPin = A1;

int threshold = 0;
int soundLevel = 0;

void setup() {
  pinMode(buzzerPin, OUTPUT);
  pinMode(micPin, INPUT);
  pinMode(potPin, INPUT);
  strip.begin();
  strip.show();
}

void loop() {
  threshold = analogRead(potPin);  // Read the potentiometer value
  soundLevel = analogRead(micPin); // Read the KY-037 microphone level

  int scaledThreshold = map(threshold, 0, 1023, 0, NUMPIXELS);
  int scaledSound = map(soundLevel, 0, 1023, 0, NUMPIXELS);

  // Update LEDs
  for (int i = 0; i < NUMPIXELS; i++) {
    if (i < scaledSound) {
      if (i >= scaledThreshold) {
        strip.setPixelColor(i, strip.Color(255, 0, 0)); // Red
      } else {
        strip.setPixelColor(i, strip.Color(0, 255, 0)); // Green
      }
    } else {
      strip.setPixelColor(i, strip.Color(0, 0, 0)); // Off
    }
  }
  strip.show();

  // Check if sound level exceeds threshold
  if (scaledSound >= scaledThreshold) {
    digitalWrite(buzzerPin, HIGH); // Turn on buzzer
  } else {
    digitalWrite(buzzerPin, LOW);  // Turn off buzzer
  }
}
```

---
