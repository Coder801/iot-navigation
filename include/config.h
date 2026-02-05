#ifndef CONFIG_H
#define CONFIG_H

// SPI display pins
#define SCLK_PIN 18
#define MOSI_PIN 23
#define DC_PIN   27
#define CS_PIN   5
#define RST_PIN  26

// BLE UART Service (Nordic UART Service)
#define SERVICE_UUID           "6E400001-B5A3-F393-E0A9-E50E24DCCA9E"
#define CHARACTERISTIC_UUID_RX "6E400002-B5A3-F393-E0A9-E50E24DCCA9E"
#define CHARACTERISTIC_UUID_TX "6E400003-B5A3-F393-E0A9-E50E24DCCA9E"

// BLE device name
#define BLE_DEVICE_NAME "iot-navigation"

#endif
