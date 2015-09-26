#include <iostream>
#include "MsgStruct.h"

/********************
 * Constructors
 *******************/
//Default Constructor, with usuable values
MsgStruct::MsgStruct(int msgID){
    this->msgID = msgID;
    numParts = 0;
    nextPart = 0;
    data = "";
}

MsgStruct* MsgStruct::reset() {
    data = extend(msgID, 3);
    nextPart = 0;
    return this;
}

int MsgStruct::size() {
    return data.size();
}

bool MsgStruct::canHandle(char* d) {
    string data = string(d);
    int part = 1;
    int ind = 3;
    while (part <= numParts) {
        string mType = parts[part];
        int mLen = sizes[part];
        if (data.substr(ind).size() < mLen) {
            return false;
        }
        if (mType == "C"){
            ind += mLen;
        } else if (mType == "S") {
            int size = atoi(data.substr(ind, ind+mLen).c_str());
            ind += mLen;
            if (size > data.substr(ind).size()) {
                return false;
            }
            ind += size;
        }
        part += 1;
    }
    return true;
}

string MsgStruct::read() {
    nextPart += 1;
    string mType = parts[nextPart];
    int mLen = sizes[nextPart];
    string out = "";
    if (mType == "C") {
        out = data.substr(0, mLen);
    } else if (mType == "S") {
        int size = atoi(data.substr(0, mLen).c_str());
        out = data.substr(mLen, mLen+size);
        mLen += size;
    }
    data = data.substr(mLen);
    return out;
}

int MsgStruct::readInt() {
    return atoi(read().c_str());
}

MsgStruct* MsgStruct::fillFromData(char* d) {
    int part = 1;
    int ind = 3;
    while (part <= numParts) {
        string mType = parts[part];
        int mLen = sizes[part];
        if (mType == "C") {
            ind += mLen;
        } else if (mType == "S") {
            int size = atoi(data.substr(ind, ind+mLen).c_str());
            ind += mLen;
            ind += size;
        }
        part += 1;
    }
    data = data.substr(3, ind);
    nextPart = 0;
    return this;
}

MsgStruct* MsgStruct::write(string dataS) {
    nextPart += 1;
    string mType = parts[nextPart];
    int mLen = sizes[nextPart];
    if (mType == "C") {
        if (dataS.size() > mLen) {
            cout << "Incorrect msg write size";
            return this;
        }
        dataS = extend(dataS, mLen);
        data += dataS;
    } else if (mType == "S") {
        int sLen = dataS.size();
        dataS = extend(sLen, mLen) + dataS;
        data += dataS;
    }
    return this;
}

bool MsgStruct::readyToSend() {
    return nextPart == numParts;
}

string MsgStruct::getData() {
    return data;
}

MsgStruct* MsgStruct::addChars(int numChars) {
    numParts += 1;
    parts[numParts] = "C";
    sizes[numParts] = numChars;
    return this;
}

MsgStruct* MsgStruct::addString() {
    numParts += 1;
    parts[numParts] = "S";
    sizes[numParts] = 3;
    return this;
}


string extend(int v, int l) {
    return extend(to_string(v), l);
}

string extend(string v, int l) {
    while (v.size() < l) {
        v = "0" + v;
    }
    return v;
}
