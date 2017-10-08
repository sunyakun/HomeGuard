#ifndef __COMMANDPARSE__
#define __COMMANDPARSE__

#include <ArduinoJson.h>
#include <string.h>

typedef void (*performer)(int, String*);

struct methodMap{
    String command;
    performer method;
    int argc = 0;
    methodMap* next;
};

class CommandParser{
public:
    CommandParser();
    void execute(String);
    void reg(String, performer, int);
    void scan();
private:
    String* parseArg(String);
    String parseCommand(String);
    methodMap* find(String);
    methodMap* maps = NULL;

};

#endif