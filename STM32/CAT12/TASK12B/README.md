[← Back to STM32 Index](../../README.md) | [← Back to Root Repository](../../../README.md)

# CAT-12 TASK-12B

| Field | Details |
| :--- | :--- |
| **EXP** | Continuous Lab Evaluation-12 (`CAT12` / `TASK12B`) |
| **TASK NO** | **Task 12B — User Push-Button Controlled LED** |
| **DATE** | 15/10/2026 |
| **NAME OF EXP** | STM32F401RE Cortex-M4: GPIO and User Input Programming |

## HARDWARE SETUP / PLATFORM
- **Development Board:** STMicroelectronics NUCLEO-F401RE (`STM32F401RET6`) (ARM Cortex-M4, 84 MHz SYSCLK)
- **Toolchain / IDE:** STM32CubeMX + Keil MDK-ARM
- **Firmware Libraries:** STM32F4xx HAL Drivers, CMSIS
- **Peripherals:** Onboard Blue User Push-Button (`B1` on `PC13`) and Onboard Green User LED (`LD2` on `PA5`)
- **Pin Mapping:**
  - `PC13` — Onboard user push-button (`B1`) digital input
  - `PA5` — Onboard user LED (`LD2`) digital output

## Circuit Diagram

### Hardware Schematic
![Circuit Diagram](circuit.png)

### Internal Board Connections
*(both `B1` and `LD2` are internally routed on the NUCLEO-F401RE PCB.)*

| MCU Pin | Internal Component | Configuration | Active State |
| :--- | :--- | :--- | :--- |
| `PC13` | Onboard User Push-Button (`B1`) | `GPIO_MODE_INPUT` (`GPIO_NOPULL`) | Active-High in Firmware (`GPIO_PIN_SET`) |
| `PA5` | Onboard Green LED (`LD2`) | `GPIO_MODE_OUTPUT_PP` | Active-High (`GPIO_PIN_SET` = ON) |

## Core Logic / Pseudocode / Code Base

### Working Principle
- `PC13` is configured as a digital input (`GPIO_MODE_INPUT`) reading the onboard `B1` user button, and `PA5` is configured as a push-pull digital output (`GPIO_MODE_OUTPUT_PP`) driving the onboard `LD2` LED.
- When `PC13` reads `HIGH` (`GPIO_PIN_SET`), the firmware waits `10 ms` via `HAL_Delay(10)` to eliminate mechanical contact bounce and re-checks `PC13`.
- Upon confirming a valid press, `HAL_GPIO_TogglePin()` toggles `PA5` (`LD2`), and a blocking `while` loop waits until `PC13` returns `LOW` so each button press causes only one toggle.

### Pseudocode
- Initialize HAL (`HAL_Init`), 84 MHz system clock (`SystemClock_Config`), and GPIO (`MX_GPIO_Init`).
- Configure `PC13` as digital input and `PA5` as push-pull digital output.
- Continuously loop in `while(1)`:
  - Check if `PC13` reads `HIGH` (`GPIO_PIN_SET`).
  - Delay `10 ms` (`HAL_Delay(10)`) for switch debouncing and re-verify `PC13 == HIGH`.
  - Toggle `PA5` (`LD2`) using `HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5)`.
  - Wait in a `while` loop until `PC13` returns `LOW` before accepting the next press.

### Code Base
Key functions in `Core/Src/main.c`:
- `HAL_Init()` – Initializes HAL library and 1 ms SysTick timer.
- `SystemClock_Config()` – Configures HSI with PLL (`PLLM = 8`, `PLLN = 84`, `PLLP = 2`) to generate an 84 MHz system clock.
- `MX_GPIO_Init()` – Enables `GPIOC`, `GPIOH`, and `GPIOA` clocks and configures `PC13` as input and `PA5` as push-pull output.
- `HAL_GPIO_ReadPin()` – Reads the digital logic state of `PC13` (`B1`).
- `HAL_Delay()` – Provides a 10 ms software debounce delay.
- `HAL_GPIO_TogglePin()` – Toggles the `PA5` (`LD2`) LED state once per valid button press.

## INFERENCE
- Implemented debounced GPIO input polling (`PC13`) and LED toggle control (`PA5`) on the NUCLEO-F401RE board using STM32F4xx HAL drivers.
- Verified that 10 ms software debouncing and release-wait synchronization prevent multiple unintended LED toggles during a single button press.
