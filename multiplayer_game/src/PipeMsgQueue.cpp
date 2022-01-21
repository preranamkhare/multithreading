#include <unistd.h>
#include <errno.h>
#include <poll.h>
#include <string.h>
#include <iostream>
#include <stdio.h>
#include "PipeMsgQueue.h"

using namespace std;

namespace {
    struct Msg {
        bool ack_;
        playerid_t id_;
        char msg[MSGSIZE];
        
        Msg(bool a, playerid_t id, const string &str):
            ack_(a), id_(id) {
                memset(msg, '\0', MSGSIZE);
                strncpy(msg, str.c_str(), MSGSIZE-1);
            }
        Msg(): ack_(false), id_(0) {
            memset(msg, '\0', MSGSIZE);
        }
    };
}

PipeMsgQueue::~PipeMsgQueue() {
    if (inFd_ >= -1) {
        close(inFd_);
        inFd_ = -1;
    }
    if (outFd_ >= -1) {
        close(outFd_);
        outFd_ = -1;
    }
}

void PipeMsgQueue::Push(MsgPtr ptr) {
    Msg m(ptr->Ack(), ptr->PlayerID(), ptr->Msg());
    if (-1 != outFd_ && -1 == write(inFd_, (const void *)&m, sizeof(struct Msg)))
    {
        cout << "Failed to send message errno: " << errno << endl;
        throw MsgSendFailedException();
    }
}

MsgPtr PipeMsgQueue::Pop(const std::chrono::milliseconds d) {
    struct pollfd fdarray[1];
    fdarray [0].fd = inFd_;
    fdarray [0].events = POLLIN ;
    int rc = poll (fdarray , 1 , d.count());
    if (rc == 1 && fdarray[0].revents == POLLIN) {
        Msg m;
        rc = read(inFd_, &m, sizeof(struct Msg));
        if (rc > 0) {
            return MsgPtr(new Message(string(m.msg), m.id_, m.ack_));
        }
    }
    if (rc == 0) {
        throw TimeoutException();
    }
    if (rc < 0) {
        int errorno = errno;
        if (errorno == EAGAIN || errorno == EWOULDBLOCK)
            throw TimeoutException();
        else
            throw MsgReadFailedException();
    }
    return nullptr;
}
