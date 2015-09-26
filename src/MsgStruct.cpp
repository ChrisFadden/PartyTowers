#include <iostream>
#include "MsgStruct.h"

extern char buffer[512];
extern int bufferSize;

/********************
 * Constructors
 *******************/
//Default Constructor, with usuable values
MsgStruct::MsgStruct(int msgID){
    this->msgID = msgID;
    numParts = 0;
    nextPart = 0;
    pID = 0;
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

int MsgStruct::getMsgID() {
    return msgID;
}

int MsgStruct::getPID() {
    return pID;
}

bool MsgStruct::canHandle(string dat) {
    //cout << "Parsing data " << dat << "\n";
    int part = 1;
    int ind = 3;
    while (part <= numParts) {
        string mType = parts[part];
        int mLen = sizes[part];
        if (dat.substr(ind).size() < mLen) {
            return false;
        }
        if (mType == "C"){
            ind += mLen;
        } else if (mType == "S") {
            int size = atoi(dat.substr(ind, mLen).c_str());
            ind += mLen;
            if (size > dat.substr(ind).size()) {
                return false;
            }
            ind += size;
        }
        part += 1;
    }
    //cout << "We can handle it!\n";
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
        out = data.substr(mLen, size);
        mLen += size;
    }
    data = data.substr(mLen);
    return out;
}

int MsgStruct::readInt() {
    return atoi(read().c_str());
}

MsgStruct* MsgStruct::fillFromData(bool confirmed) {
    string dataS = string(buffer).substr(0, bufferSize);
    int part = 1;
    int offset = 3;
    int ind = 3;
    if (confirmed) {
        pID = atoi(dataS.substr(0,2).c_str());
        ind = 5;
        offset = 5;
    }
    while (part <= numParts) {
        string mType = parts[part];
        int mLen = sizes[part];
        if (mType == "C") {
            ind += mLen;
        } else if (mType == "S") {
            int size = atoi(dataS.substr(ind, mLen).c_str());
            ind += mLen;
            ind += size;
        }
        part += 1;
    }
    data = dataS.substr(offset, ind-offset);
    //cout << "Our data: " + data + "\n";
    nextPart = 0;
    int count = 0;
    //cout << "Old buffer: " + string(buffer) + "\n";
    for (int i=ind; i<bufferSize; i++) {
        buffer[count] = buffer[i];
        count++; 
    }
    bufferSize -= ind;
    /*
    cout << "New buffer: " + string(buffer) + "\n";
    cout << "New buffer size: ";
    cout << bufferSize;
    cout << "\n";
    */
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
