/***************************************
SecureVector.cpp

Thread-safe class for vectors.

Written by:
Isak Wiberg
***************************************/

#include "./SecureVector.h"

std::vector<Message*> SecureVector::stealNewMessages() {
    std::vector<Message*> tmp;
    guardian_.lock();
    tmp.swap(messages_);
    guardian_.unlock();
    return tmp;
}

void SecureVector::push_back(Message* newMessage) {
    guardian_.lock();
    messages_.push_back(newMessage);
    guardian_.unlock();
}


void SecureVector::append(std::vector<Message*> newMessages) {
    guardian_.lock();
    messages_.insert(messages_.end(), newMessages.begin(), newMessages.end());
    guardian_.unlock();
}
