[← Back to Root Repository](../README.md) | [→ View STM32 Experiments](../STM32/README.md)

# 8051 Microcontroller Experiments (`AT89S52`)

This directory contains bare-metal Embedded C laboratory experiments developed for the **Atmel `AT89S52` (8051)** microcontroller using **Keil µVision**. All implementations use direct Special Function Register (`SFR`) and bit-addressable (`sbit`) access without high-level abstraction frameworks.

---

## Experiment Index

| Category | Task Folder | Date | Task Title | Experiment Title | Keil Project |
| :--- | :--- | :--- | :--- | :--- | :--- |
| **CAT-2** | [TASK2B](./CAT2/TASK2B/README.md) | 24/07/2026 | Bare-Metal LED Blink & Custom Delay Library | Bare-Metal LED Blink | `blinker.uvproj` |
| **CAT-3** | [TASK3A](./CAT3/TASK3A/README.md) | 31/07/2026 | Multi-Mode LED Pattern Generator & Switch Control | Timer-Based LED Pattern Generator and Button Interrupt Controller | `led_button.uvproj` |
| **CAT-4** | [TASK4A](./CAT4/TASK4A/README.md) | 07/08/2026 | Matrix Keypad, LEDs & Seven-Segment HMI | Human-Machine Interface using Matrix Keypad, LEDs, and Seven-Segment Display | `led_keypad_display.uvproj` |
| **CAT-5** | [TASK5A](./CAT5/TASK5A/README.md) | 14/08/2026 | Hardware Timer-Based LED Blinking (`Timer 0` Polling) | Hardware Timer and Interrupt-Based Timing for LED Fading, Pulse Generation, and Stepper Motor Control | `led_timer.uvproj` |
| **CAT-5** | [TASK5B.1](./CAT5/TASK5B/TASK5B.1/README.md) | 14/08/2026 | Timer-Based Software PWM LED Fading | Hardware Timer and Interrupt-Based Timing for LED Fading, Pulse Generation, and Stepper Motor Control | `TASK5B.1` |
| **CAT-5** | [TASK5B.2](./CAT5/TASK5B/TASK5B.2/README.md) | 14/08/2026 | Timer-Driven Multi-Frequency Square Wave Generator | Hardware Timer and Interrupt-Based Timing for LED Fading, Pulse Generation, and Stepper Motor Control | `TASK5B.2` |
| **CAT-5** | [TASK5B.3](./CAT5/TASK5B/TASK5B.3/README.md) | 14/08/2026 | Timer 1 Interrupt-Driven Waveform & PWM Generation | Hardware Timer and Interrupt-Based Timing for LED Fading, Pulse Generation, and Stepper Motor Control | `TASK5B.3` |
| **CAT-5** | [TASK5C](./CAT5/TASK5C/README.md) | 14/08/2026 | Interrupt-Driven Stepper Motor Speed Controller | Hardware Timer and Interrupt-Based Timing for LED Fading, Pulse Generation, and Stepper Motor Control | `cat5_stepmtr.uvproj` |
| **CAT-6** | [TASK6A](./CAT6/TASK6A/README.md) | 21/08/2026 | UART Initialization & Character Transmission | UART Driver and Serial Debugging | `toPC.uvproj` |
| **CAT-6** | [TASK6B](./CAT6/TASK6B/README.md) | 21/08/2026 | Full-Duplex UART Echo | UART Driver and Serial Debugging | `fromPC.uvproj` |
| **CAT-7** | [TASK7A](./CAT7/TASK7A/README.md) | 28/08/2026 | 4-Bit LCD Initialization & Character/String Display | 16×2 LCD Driver Development and Dynamic Display Control | `lcd_display.uvproj` |
| **CAT-7** | [TASK7B](./CAT7/TASK7B/README.md) | 28/08/2026 | Cursor Positioning & Dynamic Numeric Output | 16×2 LCD Driver Development and Dynamic Display Control | `lcd_cursor.uvproj` |
| **CAT-7** | [TASK7C](./CAT7/TASK7C/README.md) | 28/08/2026 | 4×4 Keypad-Controlled Character Navigation on 16×2 LCD | 16×2 LCD Driver Development and Dynamic Display Control | `lcd_keypad.uvproj` |
