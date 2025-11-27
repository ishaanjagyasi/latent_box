#include <Wire.h>
#include "Adafruit_MPR121.h"
#include "Adafruit_seesaw.h"

// MPR121 Setup
#define MPR121_Y_ADDR 0x5A
#define MPR121_X_ADDR 0x5B

Adafruit_MPR121 mpr121_y = Adafruit_MPR121();
Adafruit_MPR121 mpr121_x = Adafruit_MPR121();
int sliderValues[5] = {0, 0, 0, 0, 0};

// Velostat Setup 
const int velostatPin1 = A1;
const int velostatPin2 = A2;

int baseline1 = 0;
int baseline2 = 0;
float averagePressure = 0.0;

// Potentiometer
const int potPin = A0;
int potValue = 0;

// Rotary Encoder
Adafruit_seesaw seesaw;
#define SEESAW_ADDR 0x37
int lastEncoder = 0;
int encoderValue = 0;

// Timing
unsigned long lastUpdate = 0;
const unsigned long updateInterval = 50;  // 50 ms

void setup() {
  Serial.begin(9600);
  while (!Serial);

  // MPR121 Initialization
  if (!mpr121_y.begin(MPR121_Y_ADDR)) {
    Serial.println("MPR121 Y-axis (0x5A) not found!");
    while (1);
  }
  if (!mpr121_x.begin(MPR121_X_ADDR)) {
    Serial.println("MPR121 X-axis (0x5B) not found!");
    while (1);
  }
  mpr121_y.setThresholds(5, 2);
  mpr121_x.setThresholds(5, 2);

  // Seesaw Rotary Encoder
  if (!seesaw.begin(SEESAW_ADDR)) {
    Serial.println("Could not find seesaw on 0x37!");
    while (1);
  }
  lastEncoder = seesaw.getEncoderPosition();

  // Velostat Baseline Calibration
  baseline1 = analogRead(velostatPin1);
  baseline2 = analogRead(velostatPin2);

  Serial.println("All devices initialized.");
}

void loop() {
  unsigned long currentMillis = millis();
  if (currentMillis - lastUpdate >= updateInterval) {
    lastUpdate = currentMillis;

    // MPR121 Slider Matrix
    uint16_t touched_y = mpr121_y.touched() & 0x1F;
    uint16_t touched_x = mpr121_x.touched() & 0x1F;

    for (uint8_t physicalX = 0; physicalX < 5; physicalX++) {
      if ((touched_x >> physicalX) & 0x01) {
        for (uint8_t physicalY = 0; physicalY < 5; physicalY++) {
          if ((touched_y >> physicalY) & 0x01) {
            uint8_t logicalX = 4 - physicalX;
            uint8_t logicalY = 4 - physicalY;
            sliderValues[logicalX] = logicalY;
          }
        }
      }
    }

    // Potentiometer
    potValue = analogRead(potPin); // 0–1023

    // Rotary Encoder
    int newEncoder = seesaw.getEncoderPosition();
    int delta = newEncoder - lastEncoder;
    if (delta != 0) {
      encoderValue += delta;
      encoderValue = constrain(encoderValue, 0, 127);
      lastEncoder = newEncoder;
    }

    // Velostat Pressure (Averaged, No Smoothing)
    int raw1 = analogRead(velostatPin1);
    int raw2 = analogRead(velostatPin2);

    int pressure1 = max(raw1 - baseline1, 0);
    int pressure2 = max(raw2 - baseline2, 0);

    averagePressure = (pressure1 + pressure2) / 2.0;

    // Serial Output
    for (uint8_t i = 0; i < 5; i++) {
      Serial.print(sliderValues[i]);
      Serial.print(" ");
    }

    Serial.print(potValue); Serial.print(" ");
    Serial.print(encoderValue); Serial.print(" ");
    Serial.println(averagePressure);
  }
}