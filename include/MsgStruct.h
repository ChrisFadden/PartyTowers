#ifndef _MSGSTRUCT_H
#define _MSGSTRUCT_H

#include <iostream>
#include <string>
#include <map>

using namespace std;

string extend(int, int);
string extend(string, int);

class MsgStruct {
    public:
        MsgStruct(int); //Default Constructor

        MsgStruct* reset();
        int size();
        bool canHandle(char*);
        string read();
        int readInt();
        MsgStruct* fillFromData(char*);
        MsgStruct* write(string);
        bool readyToSend();
        string getData(); 
        MsgStruct* addChars(int);
        MsgStruct* addString();  

    private:
        int msgID;
        int numParts;
        int nextPart;
        string data;
        map<int,string> parts;
        map<int,int> sizes; 
};
#endif
