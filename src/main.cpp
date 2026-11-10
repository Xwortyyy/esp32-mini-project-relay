#include <Arduino.h>

#define ldr_pin 4
#define tranz_base_pin 2

constexpr uint32_t intervalMillis = 500;
uint32_t perviousMillis = 0;
constexpr uint32_t threshold_dark = 1000;
constexpr uint32_t threshold_light = 2000;

void setup() {
  Serial.begin(115200);
  digitalWrite(tranz_base_pin, LOW);
  pinMode(tranz_base_pin, OUTPUT);
  analogReadResolution(12);
}

void loop() {
  uint32_t current_millis = millis();
  if(current_millis - perviousMillis >= intervalMillis){
    perviousMillis = current_millis;
    const uint32_t measured_mv = analogReadMilliVolts(ldr_pin);
    if(measured_mv < threshold_dark){
      digitalWrite(tranz_base_pin, HIGH);
    }
    else if(measured_mv > threshold_light){
      digitalWrite(tranz_base_pin, LOW);
    }
    Serial.printf("LDR: %4u mV | Relay: %d\n", measured_mv, digitalRead(tranz_base_pin));
  }
}