# 25011102112 — Fundamentals of Internet of Things Lab (`FIoT_LAB`)

**Course:** 25CS2741 — Fundamentals of Internet of Things + Lab  
**Student:** Veenya M (`25011102112`)  
**Program:** B.Tech CSE (IoT) 
**Institution:** Shiv Nadar University, Chennai  

This repository contains bare-metal Embedded C and HAL-based microcontroller laboratory experiments, peripheral interfacing implementations, and an end-to-end IoT mini-project developed across the **8051 (`AT89S52`)** and **STM32 (`STM32F103C8T6`, `STM32F401RE`, `STM32F410RB`)** platforms.

---

## Repository Sections

| Directory | Target Architecture / Boards | Toolchain & Framework | Coverage |
| :--- | :--- | :--- | :--- |
| **[`8051/`](./8051/README.md)** | Atmel `AT89S52` (8-bit 8051) | Keil µVision • Bare-Metal Embedded C (Direct SFR Access) | `CAT-2` to `CAT-7` (GPIO, Keypad, 7-Segment, Hardware Timers, Interrupts, Stepper Motor, UART, 16×2 LCD) |
| **[`STM32/`](./STM32/README.md)** | `STM32F103C8T6` (`Blue Pill`), `NUCLEO-F401RE`, `NUCLEO-F410RB` | STM32CubeMX + Keil MDK-ARM • STM32 HAL Drivers | `CAT-8` to `CAT-15` (GPIO, UART, ESP8266 AT Commands, HTTP Server, BME280 I2C, MQTT, Node-RED Mini Project) |

---

## Repository Structure

```text
25011102112_FIoT_LAB/
├── README.md
├── 8051/
│   ├── README.md
│   ├── CAT2/TASK2B/
│   ├── CAT3/TASK3A/
│   ├── CAT4/TASK4A/
│   ├── CAT5/
│   │   ├── TASK5A/
│   │   ├── TASK5B/
│   │   │   ├── TASK5B.1/
│   │   │   ├── TASK5B.2/
│   │   │   └── TASK5B.3/
│   │   └── TASK5C/
│   ├── CAT6/
│   │   ├── TASK6A/
│   │   └── TASK6B/
│   └── CAT7/
│       ├── TASK7A/
│       ├── TASK7B/
│       └── TASK7C/
└── STM32/
    ├── README.md
    ├── CAT8/
    │   ├── TASK8A/
    │   ├── TASK8B/
    │   └── TASK8C/
    ├── CAT9/
    │   ├── TASK9A/
    │   └── TASK9B/
    ├── CAT10/
    │   ├── TASK10A/
    │   ├── TASK10B/
    │   └── TASK10C/
    ├── CAT11/
    │   ├── TASK11A/
    │   └── TASK11B/
    ├── CAT12/
    │   ├── TASK12A/
    │   ├── TASK12B/
    │   └── TASK12C/
    ├── CAT13/TASK13/
    ├── CAT14/TASK14/
    └── CAT15/
```

---

## Documentation & Submission Standards
- Every experiment folder includes its own `README.md` containing the experiment metadata (`EXP`, `TASK NO`, `DATE`, `NAME OF EXP`), hardware setup and pin mappings, schematic (`circuit.png`), wiring interconnects (`connections.png`), working principle, pseudocode, code base breakdown, and inference.
- All `8051` firmware is written in register-level Embedded C (`<reg51.h>`) without third-party abstraction libraries.
