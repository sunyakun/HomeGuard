#include <Arduino.h>
#include "Esp.h"
#include "func.h"
bool EspCommand::init(){
    Serial.println("[DEBUG]:initial the esp8266");
    String resp;
    serial.begin(115200);
    while(resp.indexOf("OK") == -1){
        serial.println(AT);
        resp = read();
    }
    Serial.println("[DEBUG]:finish initial");
}

String EspCommand::read(long timeout = 500){
    timeout = timeout + millis();
    while(timeout > millis()){
        while(serial.available()){
            resp = serial.readString();
        }
    }
    Serial.println("[DEBUG]:esp response:");
    Serial.println("==============================");
    Serial.println(resp);
    Serial.println("==============================");
    return resp;
}

String EspCommand::getResponse(){
    int b = resp.indexOf(":");
    int e = resp.indexOf("CLOSED");
    Serial.println(resp.substring(b+1, e));
    return resp.substring(b+1, e);
    //return "{\"command\":\"register co2 54 0\"}";
}

bool EspCommand::mode(int m){
    if(m>=1 && m <= 3){
        String c = AT_MODE + "=" + (m + '0');
        serial.println(c);
        if(read().indexOf("OK") == -1) return false;
        else return true;
    }
    else return false;
}

bool EspCommand::APmode(String ssid, String password, String channel, String enctype){
    String c = AT_SAP +
        "=\"" + 
        ssid + "\",\"" + 
        password + "\",\"" + 
        channel + "\",\"" + 
        enctype + "\"";

    serial.println(c);
    if(read().indexOf("OK") == -1) return false;
    else return true;
}

bool EspCommand::STmode(String ssid, String password){
    String c = AT_JAP + "=\"" + ssid + "\",\"" + password + "\"";
    
    if(executeCommand("AT+CWJAP?", "No AP")){
        executeCommand(c);
        
        if(!executeCommand("AT+CWJAP?", "OK")){
            Serial.println("[DEBUG]:wifi connect fail!(code:001)");
            return false;
        }
        else{
            Serial.println("[DEBUG]:wifi connect suucess!");
            return true;
        }
    }
    else if(executeCommand("AT+CWJAP?", ssid)){
        return true;
    }
    else{
        executeCommand(AT_QAP);
        executeCommand("AT+RST");
        executeCommand(c);
        if(!executeCommand("AT+CWJAP?", "OK")){
            Serial.println("[DEBUG]:wifi connect fail!(code:002)");
            return false;
        }
        else{
            Serial.println("[DEBUG]:wifi connect suucess!");
            return true;
        }
    }
}

bool EspCommand::executeCommand(String command, String _resp = "", long timeout, int dly){
    serial.println(command);
    resp = read(timeout);
    while(resp.indexOf("busy") != -1 && resp.indexOf("OK") == -1){
        init();
        serial.println(command);
        resp = read(timeout);
    }
    delay(dly);
    if(resp.indexOf(_resp) != -1){
        return true;
    }
    else{
        return false;
    }
}

bool EspCommand::connect(byte ip[], int port){
    String ips = "";
    for(int i=0;i<4;++i){
        ips += int2String(ip[i]);
        ips += ".";
    }
    ips = ips.substring(0, ips.length() - 1);
    String c = AT_TCP + ips + "\"," + int2String(port);
    
    Serial.print("[DEBUG]:send command:");
    Serial.println(c);
    
    serial.println(c);
    if(read().indexOf("OK") == -1){
        Serial.println("[DEBUG]:connect to remote server fail");
        return false;
    }
    else{
        Serial.println("[DEBUG]:connect to remote server success");
        return true;
    }
}

bool EspCommand::connected(){
    serial.println(AT_IPSTATUS);
    if(read().indexOf("CONNECTED") != -1) return true;
    else return false;
}

String EspCommand::print(String data){
    bool flag = false;
    if(executeCommand(AT_SEND + int2String(data.length()), "OK")){
        if(executeCommand(data, "OK")){
            Serial.println("OK");
            return getResponse();
        }
        else{
            Serial.println("data send fail");
            return "";
        }
    }
    return "";
}

int EspCommand::getMode(){

}

String EspCommand::scan(){
    serial.println(AT_LAP);
    return read(10000);
}

String EspCommand::getIp(){
    serial.println(AT_IP);
    return read();
}

bool EspCommand::stop(){
    serial.println(AT_CLOSE);
    if(read().indexOf("CLOSE OK") != -1) return true;
    else return false;
}

bool EspCommand::stopST(){
    serial.println(AT_QAP);
    if(read().indexOf("OK") != -1) return true;
    else return false;
}

bool EspCommand::available(){
    return true;
}