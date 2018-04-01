#ifndef __COMMANDPARSE__
#define __COMMANDPARSE__

#include <ArduinoJson.h>
#include <string.h>

typedef void (*performer)(int, String*);

/*
 * 一个链表节点，存储函数地址
 */
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
