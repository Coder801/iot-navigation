#ifndef BLE_SERVICE_H
#define BLE_SERVICE_H

#include <Arduino.h>

void initBLE();
void handleBLEConnection();
void sendBLENotification(const char *message);

bool isBLEConnected();
String getReceivedMessage();
void clearReceivedMessage();

#endif
