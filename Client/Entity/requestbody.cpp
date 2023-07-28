#include "requestbody.h"
#include <iostream>

RequestBody::RequestBody() {}
void RequestBody::setAccount(const string account) {
    RequestBody::account = account;
}

string RequestBody::toString() {
    return account+"|"+path+"|"+ to_string(beginPos)+"|"+ to_string(isSendKey);
}

void RequestBody::setBeginPos(int beginPos) {
    RequestBody::beginPos = beginPos;
}

void RequestBody::setIsSendKey(bool isSendKey) {
    RequestBody::isSendKey = isSendKey;
}

void RequestBody::setPath(const string path) {
    RequestBody::path = path;
}

