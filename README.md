# Bluetooth RC Car — Arduino

![Arduino](https://img.shields.io/badge/Arduino-00979D?style=for-the-badge&logo=arduino&logoColor=white)
![C++](https://img.shields.io/badge/C++-00599C?style=for-the-badge&logo=cplusplus&logoColor=white)
![Bluetooth](https://img.shields.io/badge/Bluetooth-0082FC?style=for-the-badge&logo=bluetooth&logoColor=white)
![Android](https://img.shields.io/badge/Android-3DDC84?style=for-the-badge&logo=android&logoColor=white)

A 3-wheeled remote-controlled car built on a wooden chassis, driven by two rear DC gear motors and balanced by a front ball caster wheel. The car is controlled wirelessly over Bluetooth via a smartphone app, with an Arduino Uno as the brain, HC-05 for communication, and an L298N motor driver handling motor control.

---

## Demo

[Watch working demo](working_video.mp4)

---

## Images

**Front View**

![Front](components%20-%20front.jpeg)

**Connection Diagram**

![Wiring](connection%20diagram.jpeg)

---

## Components

| Component | Model / Spec | Purpose |
|---|---|---|
| Microcontroller | Arduino Uno (ATmega328P) | Processes Bluetooth commands and drives motor logic |
| Bluetooth Module | HC-05 | Receives serial commands from smartphone over RFCOMM |
| Motor Driver | L298N Dual H-Bridge | Controls direction of two DC motors independently |
| Motors | DC Gear Motors ×2 | Drives the rear left and right wheels |
| Caster Wheel | Ball caster (front) | Provides balance and free-rolling front support |
| Battery Pack | 7.4V–9V (6×AA or Li-ion) | Powers both the motor driver and Arduino |
| Chassis | Wooden base | Holds all components |

---

## How It Works

1. A smartphone app sends single-character commands over Bluetooth serial to the HC-05 module.
2. HC-05 forwards the data to the Arduino via TX/RX pins.
3. The Arduino reads the character and sets the appropriate HIGH/LOW signals on the L298N input pins.
4. The L298N drives current through the motors in the correct direction.
5. Differential speed between the left and right motors enables turning.

---

## Pin Connections

### Arduino → L298N Motor Driver

| Arduino Pin | L298N Pin | Description |
|---|---|---|
| D3 (PWM) | ENA | Left motor speed control |
| D4 | IN1 | Left motor direction A |
| D5 | IN2 | Left motor direction B |
| D6 | IN3 | Right motor direction A |
| D7 | IN4 | Right motor direction B |
| D9 (PWM) | ENB | Right motor speed control |
| GND | GND | Common ground |

### Arduino → HC-05 Bluetooth Module

| Arduino Pin | HC-05 Pin | Description |
|---|---|---|
| TX (D1) | RX | Serial data from Arduino to HC-05 |
| RX (D0) | TX | Serial data from HC-05 to Arduino |
| 3.3V | VCC | Power supply for HC-05 |
| GND | GND | Common ground |

> **Note:** HC-05 operates on 3.3V logic. To protect the module, use a voltage divider (1kΩ + 2kΩ) on the Arduino TX → HC-05 RX line, since Arduino TX outputs 5V.

### Battery → Power Rails

| Battery Terminal | Connected To | Description |
|---|---|---|
| Positive (7.4–9V) | L298N 12V pin | Motor power supply |
| Positive (via L298N 5V out) | Arduino Vin | Logic power |
| Negative | GND (common) | Shared ground across all components |

---

## Control Commands

Send these characters from any Bluetooth serial app (e.g. **Bluetooth RC Controller** or **Serial Bluetooth Terminal** on Android):

| Character | Action |
|---|---|
| `F` | Move Forward |
| `B` | Move Backward |
| `L` | Turn Left (left motor slows, right motor full) |
| `R` | Turn Right (right motor slows, left motor full) |
| `S` | Stop |

---

## Circuit Overview

```
Battery Pack (7.4V–9V)
    ├──────────────→ L298N (12V pin)              [motor power]
    └──────────────→ Arduino Vin                  [logic power]

Arduino Uno
    ├── D3, D4, D5, D6, D7, D9 ──→ L298N IN1–IN4, ENA, ENB
    ├── TX (D1) ──→ HC-05 RX                      [send commands]
    ├── RX (D0) ←── HC-05 TX                      [receive commands]
    └── 3.3V ──→ HC-05 VCC

L298N Motor Driver
    ├── OUT1, OUT2 ──→ Left DC Motor (rear left)
    └── OUT3, OUT4 ──→ Right DC Motor (rear right)
```

---

## Pairing the Bluetooth Module

1. Power on the car.
2. On your Android phone, go to **Settings → Bluetooth** and scan for devices.
3. Connect to **HC-05**.
4. Default pairing PIN: `1234` or `0000`.
5. Open a Bluetooth serial app, connect to HC-05, and start sending commands.

---

## File Structure

```
bluetooth-rc-car/
├── rc_car_bluetooth.ino         # Main Arduino sketch
├── components - front.jpeg      # Front view of the car
├── components-back.png          # Back view of the car
├── connection diagram.jpeg      # Wiring/connection diagram
├── working_video.mp4            # Demo video
└── README.md
```

---
