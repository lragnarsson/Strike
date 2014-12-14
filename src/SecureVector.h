//
//  SecureVector.h
//  Strike
//
//  Created by Isak Wiberg on 2014-12-10.
//  Copyright (c) 2014 Isak Wiberg. All rights reserved.
//

#ifndef __Strike__SecureVector__
#define __Strike__SecureVector__

#include <stdio.h>
#include <vector>

#include <boost/thread/mutex.hpp>

#include "Messages.h"

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
#endif /* defined(__Strike__SecureVector__) */
