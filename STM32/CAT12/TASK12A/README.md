[← Back to STM32 Index](../../README.md) | [← Back to Root Repository](../../../README.md)

# CAT-12 TASK-12A

| Field | Details |
| :--- | :--- |
| **EXP** | Continuous Lab Evaluation-12 (`CAT12` / `TASK12A`) |
| **TASK NO** | **Task 12A — Onboard LED Blink (GPIO Output)** |
| **DATE** | 15/10/2026 |
| **NAME OF EXP** | STM32F401RE Cortex-M4: GPIO and User Input Programming |

## HARDWARE SETUP / PLATFORM
- **Development Board:** STMicroelectronics NUCLEO-F401RE (`STM32F401RET6`) (ARM Cortex-M4, 84 MHz SYSCLK)
- **Toolchain / IDE:** STM32CubeMX + Keil MDK-ARM
- **Firmware Libraries:** STM32F4xx HAL Drivers, CMSIS
- **Peripherals:** Onboard user LED (`LD2` on `PA5`)
- **Pin Mapping:**
  - `PA5` — Onboard user LED (`LD2`) digital output

## Circuit Diagram

### Hardware Schematic
![Circuit Diagram](circuit.png)

### Internal Board Connections
*(`LD2` is internally routed on the NUCLEO-F401RE PCB.)*

| MCU Pin | Internal Component | Configuration | Active State |
| :--- | :--- | :--- | :--- |
| `PA5` | Onboard Green LED (`LD2`) | `GPIO_MODE_OUTPUT_PP` | Active-High (`GPIO_PIN_SET` = ON) |

## Core Logic / Pseudocode / Code Base

### Working Principle
- `PA5` on the STM32F401RE is configured as a push-pull digital output (`GPIO_MODE_OUTPUT_PP`) internally connected to the onboard user LED (`LD2`).
- Inside the continuous `while(1)` loop, `HAL_GPIO_TogglePin()` inverts the logic state of `PA5` and `HAL_Delay(500)` inserts a `500 ms` blocking SysTick delay, producing a `1 Hz` (`500 ms` ON / `500 ms` OFF) blink cycle.

### Pseudocode
- Initialize HAL (`HAL_Init`), 84 MHz system clock (`SystemClock_Config`), and GPIO (`MX_GPIO_Init`).
- Configure `PA5` as a push-pull digital output initialized to `LOW`.
- Continuously loop in `while(1)`:
  - Toggle `PA5` state using `HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5)`.
  - Wait `500 ms` using `HAL_Delay(500)`.

### Code Base
Key functions in `Core/Src/main.c`:
- `HAL_Init()` – Initializes HAL library and 1 ms SysTick timer.
- `SystemClock_Config()` – Configures HSI with PLL (`PLLM = 8`, `PLLN = 84`, `PLLP = 2`) to generate an 84 MHz system clock.
- `MX_GPIO_Init()` – Enables `GPIOA` and `GPIOH` clocks and configures `PA5` as `GPIO_MODE_OUTPUT_PP`.
- `HAL_GPIO_TogglePin()` – Toggles the logic state of `PA5` (`LD2`).
- `HAL_Delay()` – Provides a 500 ms blocking delay between state transitions.

## INFERENCE
- Verified the STM32F401RE Cortex-M4 project workflow in STM32CubeMX and Keil MDK-ARM at an 84 MHz system clock.
- Demonstrated digital GPIO output toggling (`HAL_GPIO_TogglePin`) and SysTick-based timing (`HAL_Delay`) on the onboard `PA5` LED (`LD2`).
