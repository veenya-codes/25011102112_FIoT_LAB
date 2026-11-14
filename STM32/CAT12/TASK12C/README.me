[← Back to STM32 Index](../../README.md) | [← Back to Root Repository](../../../README.md)

# CAT-12 TASK-12C

| Field | Details |
| :--- | :--- |
| **EXP** | Continuous Lab Evaluation-12 (`CAT12` / `TASK12C`) |
| **TASK NO** | **Task 12C — Short Press vs Long Press Pattern Control** |
| **DATE** | 15/10/2026 |
| **NAME OF EXP** | STM32F401RE Cortex-M4: GPIO and User Input Programming |

## HARDWARE SETUP / PLATFORM
- **Development Board:** STMicroelectronics NUCLEO-F401RE (`STM32F401RET6`) (ARM Cortex-M4, 84 MHz SYSCLK)
- **Toolchain / IDE:** STM32CubeMX + Keil MDK-ARM
- **Firmware Libraries:** STM32F4xx HAL Drivers, CMSIS
- **Peripherals:** Onboard Blue User Push-Button (`B1` on `PC13`) and Onboard Green User LED (`LD2` on `PA5`)
- **Pin Mapping:**
  - `PC13` — Onboard user push-button (`B1`) digital input (active-low)
  - `PA5` — Onboard user LED (`LD2`) digital output (active-high)

## Circuit Diagram

### Hardware Schematic
![Circuit Diagram](circuit.png)

### Internal Board Connections
*both `B1` and `LD2` are internally routed on the NUCLEO-F401RE PCB.)*

| MCU Pin | Internal Component | Configuration | Active State |
| :--- | :--- | :--- | :--- |
| `PC13` | Onboard User Push-Button (`B1`) | `GPIO_MODE_INPUT` (`GPIO_NOPULL`) | Active-Low (`GPIO_PIN_RESET` = Pressed) |
| `PA5` | Onboard Green LED (`LD2`) | `GPIO_MODE_OUTPUT_PP` | Active-High (`GPIO_PIN_SET` = ON) |

## Core Logic / Pseudocode / Code Base

### Working Principle
- `PC13` reads the active-low onboard user button (`B1`, `GPIO_PIN_RESET` when pressed), while `PA5` drives the active-high onboard user LED (`LD2`).
- Using non-blocking `HAL_GetTick()` timestamps, the firmware measures the elapsed millisecond duration between button press and release:
  - **Short Press (`duration < 1000 ms`):**
    - If `blinking == 1`, stops blinking mode (`blinking = 0`) and sets `PA5` `HIGH`.
    - Otherwise, toggles `PA5` (`LD2`) via `HAL_GPIO_TogglePin()`.
  - **Long Press (`duration >= 1000 ms`):** Enables continuous blinking mode (`blinking = 1`) and initializes `blink_timer`.
- While `blinking == 1`, `HAL_GetTick()` toggles `PA5` every `500 ms` without blocking execution.

### Pseudocode
- Initialize HAL (`HAL_Init`), 84 MHz system clock (`SystemClock_Config`), and GPIO (`MX_GPIO_Init`).
- Maintain state flags (`is_pressed`, `blinking`) and millisecond timestamps (`press_time`, `blink_timer`).
- Continuously execute in `while(1)`:
  - Read `PC13` state (`LOW` = pressed).
  - On press edge, set `is_pressed = 1` and record `press_time = HAL_GetTick()`.
  - On release edge, clear `is_pressed = 0` and calculate `duration = HAL_GetTick() - press_time`:
    - If `duration < 1000 ms`:
      - If `blinking == 1`, clear `blinking = 0` and set `PA5` `HIGH`.
      - Else, toggle `PA5`.
    - Else (`duration >= 1000 ms`):
      - Set `blinking = 1` and record `blink_timer = HAL_GetTick()`.
  - If `blinking == 1` and `HAL_GetTick() - blink_timer >= 500 ms`, toggle `PA5` and update `blink_timer`.

### Code Base
Key functions in `Core/Src/main.c`:
- `HAL_Init()` – Initializes HAL library and 1 ms SysTick timer.
- `SystemClock_Config()` – Configures HSI with PLL (`PLLM = 8`, `PLLN = 84`, `PLLP = 2`) to generate an 84 MHz system clock.
- `MX_GPIO_Init()` – Enables `GPIOC`, `GPIOH`, and `GPIOA` clocks and configures `PC13` as input and `PA5` as push-pull output.
- `HAL_GPIO_ReadPin()` – Detects active-low button press and release transitions on `PC13`.
- `HAL_GetTick()` – Provides non-blocking millisecond timestamps for press duration and 500 ms blink intervals.
- `HAL_GPIO_WritePin()` – Drives `PA5` `HIGH` when exiting continuous blinking mode.
- `HAL_GPIO_TogglePin()` – Toggles `PA5` (`LD2`) on short press and during 500 ms blink intervals.

## INFERENCE
- Implemented non-blocking short-press (`< 1 s`) and long-press (`≥ 1 s`) pattern control on the NUCLEO-F401RE using `HAL_GetTick()` timestamps.
- Verified that a long press on `B1` (`PC13`) triggers a 500 ms non-blocking blink mode on `LD2` (`PA5`), while a subsequent short press exits blink mode cleanly.
