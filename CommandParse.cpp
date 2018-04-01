#include "CommandParse.h"
#include "func.h"
#include <Arduino.h>

CommandParser::CommandParser(){

}

/*
 * 注册一个命令
 */
void CommandParser::reg(String command, performer fun, int argc){
    if(maps == NULL){
        maps = new methodMap();
        maps->command = command;
        maps->method = fun;
        maps->argc = argc;
        maps->next = NULL;
    }
    else if(maps->command == command){
        maps->method = fun;
        maps->argc = argc;
    }
    else{
        methodMap* p = maps;
        while(p->next->command != command && p->next != NULL){
            p = p->next;
        }
        delete p->next;
        p->next = new methodMap();
        p->next->command = command;
        p->next->method = fun;
        p->next->argc = argc;
        p->next->next = NULL;
    }
}

/*
 * 寻找一个命令对应的函数
 */
methodMap* CommandParser::find(String command){
    methodMap* p = maps;
    while(p != NULL){
        if(p->command == command){
            return p;
        }
        p = p->next;
    }
    return NULL;
}

/*
 * 从字符串中解析出命令
 */
String CommandParser::parseCommand(String command){
    int p = command.indexOf(" ");
    return command.substring(0, p);
}

String* CommandParser::parseArg(String command){
    String* arg = split(command, ' ');
    return arg;
}

/*
 * 执行一个命令
 */
void CommandParser::execute(String command){
    String com = parseCommand(command);
    //Serial.println(com);
    String* arg = parseArg(command);
    methodMap* m = find(com);
    if(m != NULL){
        (m->method)(m->argc, arg);
    }
    else{
        Serial.println("[ERROR]:does not have this command");
    }
    
}

void CommandParser::scan(){
    methodMap* p = maps;
    while(p!= NULL){
        Serial.println(p->command);
        p = p->next;
    }
}

