#include "Common.h"
#include "IRremote.h"

extern void RecvSet();
extern void RecvLoop();

const uint16_t RECV_PIN = 14;
IRrecv recv(RECV_PIN);
decode_results results;