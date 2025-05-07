#include <OneWire.h>
#include <DallasTemperature.h>

#define ONE_WIRE_BUS 2     // DS18B20 data pin
#define HEATER_PIN 3       // Heater simulated with LED
#define BUZZER_PIN 4       // Optional buzzer

// Temperature thresholds
#define HEAT_ON_THRESHOLD 22.0
#define TARGET_TEMP 25.0
#define OVERHEAT_TEMP 30.0

enum State { IDLE, HEATING, STABILIZING, TARGET_REACHED, OVERHEAT };
State currentState = IDLE;

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

void setup() {
  Serial.begin(9600);
  sensors.begin();
  pinMode(HEATER_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  digitalWrite(HEATER_PIN, LOW);
  digitalWrite(BUZZER_PIN, LOW);
}

void loop() {
  sensors.requestTemperatures();
  float temp = sensors.getTempCByIndex(0);
  Serial.print("Temp: ");
  Serial.print(temp);
  Serial.print("°C, State: ");

  // Global overheat check
  if (temp >= OVERHEAT_TEMP) {
    currentState = OVERHEAT;
  }

  switch (currentState) {
    case IDLE:
      Serial.println("IDLE");
      digitalWrite(HEATER_PIN, LOW);
      if (temp < 0.0)
      {
          currentState = IDLE;
      }
      else if (temp < HEAT_ON_THRESHOLD) {
        currentState = HEATING;
      }
      break;

    case HEATING:
      Serial.println("HEATING");
      digitalWrite(HEATER_PIN, HIGH);
      if (temp >= TARGET_TEMP && temp < OVERHEAT_TEMP) {
        currentState = STABILIZING;
      }
      break;

    case STABILIZING:
      Serial.println("STABILIZING");
      digitalWrite(HEATER_PIN, LOW);
      if (temp >= TARGET_TEMP && temp < OVERHEAT_TEMP) {
        currentState = TARGET_REACHED;
      } else if (temp < HEAT_ON_THRESHOLD) {
        currentState = HEATING;
      }
      break;

    case TARGET_REACHED:
      Serial.println("TARGET_REACHED");
      digitalWrite(HEATER_PIN, LOW);
      if (temp < HEAT_ON_THRESHOLD) {
        currentState = HEATING;
      }
      break;

    case OVERHEAT:
      Serial.println("OVERHEAT");
      digitalWrite(HEATER_PIN, LOW);
      digitalWrite(BUZZER_PIN, HIGH);
      if (temp < OVERHEAT_TEMP - 2) {  // Add hysteresis to avoid rapid toggling
        digitalWrite(BUZZER_PIN, LOW);
        currentState = STABILIZING; // Go back to safe mode
      }
      break;
  }

  delay(1000); // Read every second
}
