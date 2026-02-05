#include <Arduino.h>
#include "config.h"
#include "display.h"
#include "ble_service.h"

static unsigned long lastUpdate = 0;

void setup() {
	Serial.begin(115200);
	Serial.println("Initializing...");

	initDisplay();
	updateDisplay("Starting...");

	initBLE();
	updateDisplay("BLE Ready");
}

void loop() {
	handleBLEConnection();

	String msg = getReceivedMessage();
	if (msg.length() > 0) {
		String echo = "Echo: " + msg;
		sendBLENotification(echo.c_str());
		updateDisplay(isBLEConnected() ? "Connected" : "Waiting...", msg.c_str());
		clearReceivedMessage();
	}

	if (millis() - lastUpdate >= 1000) {
		lastUpdate = millis();

		if (isBLEConnected()) {
			updateDisplay("Connected");
		} else {
			updateDisplay("Waiting...");
		}
	}
}
