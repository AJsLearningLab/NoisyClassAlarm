#include <Adafruit_NeoPixel.h>

#define N_PIXELS  24  // Number of pixels in strand
#define MIC_PIN   A0  // Microphone is attached to this analog pin
#define LED_PIN   3  // NeoPixel LED strand is connected to this pin
#define POT_PIN   A1  // Potentiometer is attached to this analog pin
#define BUZZER_PIN 2  // Buzzer is attached to this digital pin

int threshold = 0;
int lvl = 0;
Adafruit_NeoPixel strip = Adafruit_NeoPixel(N_PIXELS, LED_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  pinMode(BUZZER_PIN, OUTPUT);  // Set buzzer pin as output
  pinMode(POT_PIN, INPUT);      // Set potentiometer pin as input
  Serial.begin(9600);           // Initialize Serial communication for debugging
  strip.begin();
}

void loop() {
  // Read the potentiometer value
  threshold = analogRead(POT_PIN);

  // Read the microphone level
  int n = analogRead(MIC_PIN);
  lvl = abs(n - 512);

  // Debugging: Output values to Serial Monitor
  Serial.print("lvl: "); Serial.print(lvl);
  Serial.print("\tThreshold: "); Serial.println(threshold);

  // Buzzer logic
  if (lvl >= threshold) {
    digitalWrite(BUZZER_PIN, HIGH);
  } else {
    digitalWrite(BUZZER_PIN, LOW);
  }

  // LED logic
  int height = map(lvl, 0, 1023, 0, N_PIXELS);
  for(int i = 0; i < N_PIXELS; i++) {
    if(i < height) {
      strip.setPixelColor(i, Wheel(map(i, 0, N_PIXELS - 1, 30, 150)));
    } else {
      strip.setPixelColor(i, 0);
    }
  }
  strip.show();
}

uint32_t Wheel(byte WheelPos) {
  if(WheelPos < 85) {
    return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } else if(WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else {
    WheelPos -= 170;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}
