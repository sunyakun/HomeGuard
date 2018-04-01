#include "func.h"
#include "Esp.h"
#include "Scanner.h"
#include "CommandParse.h"
#include <ArduinoJson.h>

EspCommand esp = EspCommand();
Scanner scanner = Scanner();
CommandParser commandParser = CommandParser();
StaticJsonBuffer<300> jsonBuffer;

String ssid = "syk-computer";
String password = "C1XVWRaU";
byte ip[] = {10, 42, 0, 1};

void registerSensor(int args, String* arg);
void processResp(String resp);

void setup(){
    Serial.begin(9600);
    Serial.println("init the network...");
    //Ethernet.begin(mac,ip,dns,gateway,subnet);
    esp.init();
    esp.STmode(ssid, password);
    Serial.println("OK");
    Serial.println("device is starting");

    /*Sensor s = Sensor("co2", "54", "0");
    scanner.registerSensor(s);*/

    for(int i=54; i<56; ++i)
    {
        pinMode(i, INPUT);
    }

    commandParser.reg("register", registerSensor, 3);
    commandParser.execute("register co 54");
    commandParser.execute("register ch2o 55");
    //esp.connect(ip, 80);
}

void loop(){
    esp.connect(ip, 8000);
    String jsonData = scanner.packSensorData();
    String responseBody = esp.print(jsonData);
    esp.stop();
    Serial.println(responseBody);
    processResp(responseBody);
    delay(1000);
}

void processResp(String resp){
    JsonObject& json = jsonBuffer.parseObject(resp.begin());
    const char* command = json["command"];
    if(strlen(command) > 0){
        commandParser.execute(command);
    }
}

void registerSensor(int argc, String* arg){
    Sensor s = Sensor(arg[1], atoi(arg[2].begin()));
    scanner.registerSensor(s);
}
