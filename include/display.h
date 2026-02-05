#ifndef DISPLAY_H
#define DISPLAY_H

#include <U8g2lib.h>

void initDisplay();
void updateDisplay(const char *status, const char *message = nullptr);

#endif
