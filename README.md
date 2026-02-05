# IoT Navigation

ESP32-based IoT device with BLE connectivity and OLED display.

## Hardware

- **MCU**: ESP32 DevKit
- **Display**: Waveshare 1.5" OLED 128x128 (SSD1327)

## Wiring

| Display Pin | ESP32 Pin |
|-------------|-----------|
| VCC         | VIN       |
| GND         | GND       |
| DIN (MOSI)  | GPIO23    |
| CLK (SCLK)  | GPIO18    |
| CS          | GPIO5     |
| DC          | GPIO27    |
| RST         | GPIO26    |

Display mode: 4-wire SPI

## Features

- BLE UART service (Nordic UART compatible)
- OLED display status updates
- Echo received BLE messages
- Counter notification every second

## Project Structure

```
src/
├── main.cpp          # Main application logic
├── display.cpp       # OLED display functions
├── ble_service.cpp   # BLE service implementation
include/
├── config.h          # Pin definitions and constants
├── display.h         # Display function declarations
├── ble_service.h     # BLE function declarations
```

## Building

```bash
pio run
```

## Flashing

```bash
pio run --target upload
```

## BLE Service

- **Service UUID**: `6E400001-B5A3-F393-E0A9-E50E24DCCA9E`
- **RX Characteristic**: `6E400002-B5A3-F393-E0A9-E50E24DCCA9E` (write)
- **TX Characteristic**: `6E400003-B5A3-F393-E0A9-E50E24DCCA9E` (notify)
