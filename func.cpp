#include <string.h>
#include "func.h"

String int2String(int value){
	int* stack = new int[20];
	int* top = stack;
	String r = "";
	while( value !=0 ){
		*top = value%10;
		top ++;
		value /= 10;
	}
	int size = top - stack;
	for(int i=0;i<size;++i){
		if(top > stack){
			top --;
			r += *top;
		}
	}
	delete stack;
	return r;
}

//ssid=syk&password=sunyakun2
char* parsePassword(char* res){
	char* begin = strstr(res,"password=") + 9;
	char* password = new char[strlen(begin)];
	memcpy(password, begin, strlen(begin)+1);
	return password;
}

char* parseSSID(char* res){
	char* begin = strstr(res,"ssid=") + 5;
	char* end = strstr(res,"&");
	int len = end - begin;
	char* ssid = new char[len];
	memcpy(ssid, begin, len);
	strcat(ssid, "");
	return ssid;
}

String pack2http(String body){
	//TODO
	String header = "GET / HTTP/1.1\n\n";
	String response = header + body + "\n";
	return response;
}

String* split(String str, char flag){
    int c = 0;
    int l=0,r=0;
	for(int i=0;i<str.length();++i){
		if(str[i] == flag) ++c;
    }
    String* result = new String[c+1];
    c=0;
    
    int pre=0,now=0;
    while(now<str.length()){
        if(str[now] == flag){
            if(pre != now){
                result[c] = str.substring(pre, now);
                ++c;
            }
            pre = now + 1;
            now = pre + 1;
        }
        else{
            now ++;
        }
    }
    result[c] = str.substring(pre, now);
    return result;
}