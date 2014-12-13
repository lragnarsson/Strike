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
#include <mutex>
#include "Messages.h"

#include <windows.h>
#include <WinBase.h>
#include <system_error>
#include "mingw.mutex.h"

class SecureVector {
public:
    SecureVector() = default;
    SecureVector(const SecureVector&) = delete;

    std::vector<Message*> stealNewMessages();
    void push_back(Message*);
    void append(std::vector<Message*>);
private:
    std::mutex guardian_;
    std::vector<Message*> messages_;
};
#endif /* defined(__Strike__SecureVector__) */
