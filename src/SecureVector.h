/***************************************
SecureVector.h

Thread-safe class for vectors.

Written by:
Isak Wiberg
***************************************/

#ifndef _SECURE_VECTOR_
#define _SECURE_VECTOR_

#include "./Messages.h"

#include <stdio.h>
#include <vector>

#include <boost/thread/mutex.hpp>

class SecureVector {
public:
    SecureVector() = default;
    SecureVector(const SecureVector&) = delete;

    std::vector<Message*> stealNewMessages();
    void push_back(Message*);
    void append(std::vector<Message*>);
private:
    boost::mutex guardian_;
    std::vector<Message*> messages_;
};
#endif // _SECURE_VECTOR_
