#include "ble_service.h"
#include "config.h"
#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>

static BLEServer *pServer = nullptr;
static BLECharacteristic *pTxCharacteristic = nullptr;
static bool deviceConnected = false;
static bool oldDeviceConnected = false;
static String receivedMessage = "";

class ServerCallbacks : public BLEServerCallbacks {
	void onConnect(BLEServer *pServer) {
		deviceConnected = true;
		Serial.println("BLE: Client connected");
	}

	void onDisconnect(BLEServer *pServer) {
		deviceConnected = false;
		Serial.println("BLE: Client disconnected");
	}
};

class RxCallbacks : public BLECharacteristicCallbacks {
	void onWrite(BLECharacteristic *pCharacteristic) {
		std::string value = pCharacteristic->getValue();
		if (value.length() > 0) {
			receivedMessage = String(value.c_str(), value.length());
			Serial.print("BLE received: ");
			Serial.println(receivedMessage);
		}
	}
};

void initBLE() {
	BLEDevice::init(BLE_DEVICE_NAME);
	pServer = BLEDevice::createServer();
	pServer->setCallbacks(new ServerCallbacks());

	BLEService *pService = pServer->createService(SERVICE_UUID);

	pTxCharacteristic = pService->createCharacteristic(
		CHARACTERISTIC_UUID_TX,
		BLECharacteristic::PROPERTY_NOTIFY
	);
	pTxCharacteristic->addDescriptor(new BLE2902());

	BLECharacteristic *pRxCharacteristic = pService->createCharacteristic(
		CHARACTERISTIC_UUID_RX,
		BLECharacteristic::PROPERTY_WRITE
	);
	pRxCharacteristic->setCallbacks(new RxCallbacks());

	pService->start();

	BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
	pAdvertising->addServiceUUID(SERVICE_UUID);
	pAdvertising->setScanResponse(true);
	pAdvertising->setMinPreferred(0x06);
	pAdvertising->setMinPreferred(0x12);
	BLEDevice::startAdvertising();

	Serial.println("BLE ready! Name: " BLE_DEVICE_NAME);
}

void handleBLEConnection() {
	if (!deviceConnected && oldDeviceConnected) {
		delay(500);
		pServer->startAdvertising();
		Serial.println("Advertising restarted");
		oldDeviceConnected = deviceConnected;
	}
	if (deviceConnected && !oldDeviceConnected) {
		oldDeviceConnected = deviceConnected;
	}
}

void sendBLENotification(const char *message) {
	if (pTxCharacteristic) {
		pTxCharacteristic->setValue((uint8_t*)message, strlen(message));
		pTxCharacteristic->notify();
	}
}

bool isBLEConnected() {
	return deviceConnected;
}

String getReceivedMessage() {
	return receivedMessage;
}

void clearReceivedMessage() {
	receivedMessage = "";
}
