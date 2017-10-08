#ifndef __FUNC__
#define __FUNC__

#include <Arduino.h>
#include <string.h>

extern String int2String(int);
extern String pack2http(String);
extern char* parsePassword(char*);
extern char* parseSSID(char*);
extern String* split(String, char);

#endif
