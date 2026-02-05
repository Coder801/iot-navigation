#include "display.h"
#include "config.h"
#include <SPI.h>

// Waveshare 1.5" OLED 128x128
static U8G2_SSD1327_WS_128X128_F_4W_HW_SPI display(U8G2_R0, CS_PIN, DC_PIN, RST_PIN);

void initDisplay() {
	display.begin();
	display.setContrast(255);
}

void updateDisplay(const char *status, const char *message) {
	display.clearBuffer();

	display.setFont(u8g2_font_ncenB14_tr);
	display.drawStr(10, 25, "ESP32 BLE");

	display.drawLine(0, 35, 128, 35);

	display.setFont(u8g2_font_ncenB08_tr);
	display.drawStr(10, 55, status);

	if (message && strlen(message) > 0) {
		display.drawStr(10, 75, "Msg:");
		display.drawStr(10, 90, message);
	}

	display.sendBuffer();
}
