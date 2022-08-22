#pragma once

#include "Common.h"
#include <WiFi.h>

#define ssid       "office1"
#define password   "qwer1234!@#$"
#define IFTTT_HOST "maker.ifttt.com"
#define IFTTT_KEY  "U4XT_bwbUbZDuKg-Z-0di"

void send_event(const char *event);
void Wifi_Init();