#include <Ethernet.h>
#include <Arduino.h>
#include "Esp.h"
#ifndef __NETWORK__
#define __NETWORK__

class Network:public EspCommand{
public:
    Network(){
        
    }
private:
    byte mac[6] = {0x00,0x01,0x02,0x00,0x01,0x02};
    byte ip[4] = {10,10,41,100};
    byte dns[4] = {114,114,114,114};
    byte subnet[4] = {255,255,255,0};
    byte gateway[4] = {10,10,41,254};
};
#endif