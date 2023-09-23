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
