#include "func.h"
#include "Esp.h"
#include "Scanner.h"
#include "CommandParse.h"
#include <ArduinoJson.h>

EspCommand esp = EspCommand();
Scanner scanner = Scanner();
CommandParser commandParser = CommandParser();
StaticJsonBuffer<300> jsonBuffer;

String ssid = "syk";
String password = "sunyakun";
byte ip[] = {192,168,43,165};

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

    commandParser.reg("register", registerSensor, 3);
}

void loop(){
    esp.connect(ip, 80);
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