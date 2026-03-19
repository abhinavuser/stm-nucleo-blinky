# STM32F303K8 Bare-Metal Blink (libopencm3)

This project blinks the onboard LED on **NUCLEO-F303K8** using **bare metal + libopencm3**.

## What this project uses

- MCU: `STM32F303K8T6`
- LED pin in code: `PB3` (user LED on NUCLEO-32)
- Library: `libopencm3`
- Build tool: `make`
- Flash/debug server: `OpenOCD` (ST-LINK over USB)

## Important note about COM5

Your `COM5` is the board's **virtual serial port**.

- Flashing/debugging is done through **ST-LINK** via OpenOCD, not directly by COM port number.
- You can still use `COM5` later for UART logging if needed.

## Prerequisites (Windows)

Install and ensure these are in `PATH`:

1. **Arm GNU Toolchain** (`arm-none-eabi-gcc`)
2. **make** (MSYS2 or equivalent)
3. **OpenOCD**
4. **Git**

Optional but useful:

- VS Code extension: `C/C++` (`ms-vscode.cpptools`)
- VS Code extension: `Cortex-Debug` (`marus25.cortex-debug`)

## One-time setup

From project root:

```powershell
powershell -ExecutionPolicy Bypass -File scripts/setup_libopencm3.ps1
```

This clones and builds `libopencm3` into `./libopencm3`.

## Build

```powershell
powershell -ExecutionPolicy Bypass -File scripts/build.ps1
```

Expected outputs:

- `build/blinky.elf`
- `build/blinky.bin`

## Flash

```powershell
powershell -ExecutionPolicy Bypass -File scripts/flash.ps1
```

If successful, the onboard LED starts blinking.

## Change blink interval or LED pin

Edit [src/main.c](src/main.c):

- `#define BLINK_INTERVAL_MS 2000U` -> set your desired interval in milliseconds.
- `#define LED_PORT`, `#define LED_PIN`, `#define LED_RCC` -> change these only if you move to a different LED pin/board.

After changing code, run:

```powershell
powershell -ExecutionPolicy Bypass -File scripts/build.ps1
powershell -ExecutionPolicy Bypass -File scripts/flash.ps1
```

That is your normal edit -> build -> upload cycle.

## Debug from VS Code

1. Run task: **build**
2. Start debug config: **Debug STM32F303K8 (OpenOCD)**

## Useful tasks in VS Code

- `setup libopencm3`
- `build`
- `flash`
- `openocd server`

## Troubleshooting

- `make: command not found` -> install make and reopen terminal.
- `arm-none-eabi-gcc not found` -> install Arm GNU Toolchain and reopen terminal.
- OpenOCD cannot connect -> confirm NUCLEO USB cable is data-capable and board is detected.
- No blink -> verify board is **NUCLEO-F303K8** and LED pin `PB3` is valid for your revision.
