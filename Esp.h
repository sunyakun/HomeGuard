#ifndef __ESP__
#define __ESP__

#define serial Serial3

#include <string.h>
#include <Arduino.h>

class EspCommand{
public:
    bool init();
    bool mode(int);
    int getMode(); // TODO

    String scan();
    bool STmode(String, String);
    bool APmode(String, String, String, String);
    bool stopST();

    bool connect(byte[], int);
    bool connected();
    String print(String);
    bool stop();
    String getIp();
    String read(long timeout=500);
    bool available();
    bool executeCommand(String command, String resp = "", long timeout=100, int dly=500);
    String getResponse();
private:
    bool OK = false;
    String resp;
    String AT = "AT";
    String AT_MODE = "AT+CWMODE";
    String AT_LAP = "AT+CWLAP";
    String AT_JAP = "AT+CWJAP";
    String AT_QAP = "AT+CWQAP";
    String AT_SAP = "AT+CWSAP";
    String AT_TCP = "AT+CIPSTART=\"TCP\",\"";
    String AT_SEND = "AT+CIPSEND=";
    String AT_CLOSE = "AT+CIPCLOSE";
    String AT_IP = "AT+CIFSR";
    String AT_IPSTATUS = "AT+CIPSTATUS";
};
#endif