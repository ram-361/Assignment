# Assignment
Heater Control System

This project implements a simple heater control system using an Arduino, DS18B20 temperature sensor, and output components like an LED (as a heater indicator) and buzzer (for overheat alert).

## 🧩 Features

- Monitors real-time temperature using DS18B20.
- Controls a simulated heater (LED) based on preset thresholds.
- Buzzer alert when temperature exceeds safe limit.
- State-based logic for Heater Operation:
  - `IDLE`
  - `HEATING`
  - `STABILIZING`
  - `TARGET_REACHED`
  - `OVERHEAT`
- Serial monitor output for debugging and logging.

## ⚙️ Components Used

| Component           | Description                 |
|---------------------|-----------------------------|
| Arduino Uno / Nano  | Microcontroller board       |
| DS18B20             | Digital temperature sensor  |
| LED (Heater Output) | Simulates heater ON/OFF     |
| Buzzer              | Alerts on overheat          |
| Resistor (4.7kΩ)    | Pull-up resistor for DS18B20|
| Breadboard & Wires  | For connections             |



## 🚦 Temperature Thresholds

| Condition        | Threshold        |
|------------------|------------------|
| Heat On          | < 22.0 °C        |
| Target Reached   | ≥ 25.0 °C        |
| Overheat Trigger | ≥ 30.0 °C        |
| Overheat Reset   | < 28.0 °C        |

## 🚀 How to Run

1. **Connect components** as described above.
2. Upload the code using the Arduino IDE.
3. Open the Serial Monitor to observe real-time temperature and state updates.
4. Simulate temperature changes to see state transitions and buzzer alerts.

## 🧪 Wokwi Simulation

You can simulate this project online using [Wokwi](https://wokwi.com/).  
> 🔗 https://wokwi.com/projects/430282363057123329

## 📁 File Structure



