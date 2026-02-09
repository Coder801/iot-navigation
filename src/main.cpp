#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

#include "config.h"
#include "display.h"
// #include "ble_service.h"

static unsigned long lastUpdate = 0;
const char* ssid = WIFI_SSID;
const char* password = WIFI_PASSWORD;

void setup() {
	Serial.begin(115200);
	Serial.println("Initializing...");

	initDisplay();
	updateDisplay("Starting...");

	// initBLE();
	// updateDisplay("BLE Ready");

	WiFi.begin(ssid, password);
	updateDisplay("Connecting to WiFi...");

	while (WiFi.status() != WL_CONNECTED) {
		delay(500);
		Serial.print(".");
	}
	IPAddress ip = WiFi.localIP();
	updateDisplay(ip.toString().c_str());

	HTTPClient http;
	http.begin("https://time.now/developer/api/timezone/Europe/Kiev");

	int httpCode = http.GET();
	if (httpCode == 200) {
		String payload = http.getString();
		JsonDocument doc;
		deserializeJson(doc, payload);
		const char* timezone = doc["timezone"];
		updateDisplay(timezone);
	} else {
		Serial.printf("HTTP GET failed, error: %s\n", http.errorToString(httpCode).c_str());
	}
	http.end();
}

void loop() {
	// handleBLEConnection();

	// String msg = getReceivedMessage();
	// if (msg.length() > 0) {
	// 	String echo = "Echo: " + msg;
	// 	sendBLENotification(echo.c_str());
	// 	updateDisplay(isBLEConnected() ? "Connected" : "Waiting...", msg.c_str());
	// 	// clearReceivedMessage();
	// }

	// if (millis() - lastUpdate >= 1000) {
	// 	lastUpdate = millis();

	// 	if (isBLEConnected()) {
	// 		updateDisplay("Connected");
	// 	} else {
	// 		updateDisplay("Waiting...");
	// 	}
	// }

	// printWifiData();
}

