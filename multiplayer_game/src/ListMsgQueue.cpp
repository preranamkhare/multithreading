#include "ListMsgQueue.h"
#include "Exceptions.h"

using namespace std;

void ListMsgQueue::Push(MsgPtr ptr) {
    if (ptr) {
        unique_lock<mutex> lk(m_);
        q_.push(ptr);
        cond_.notify_one();
    }
}

MsgPtr ListMsgQueue::Pop(const chrono::milliseconds timewait) {
    unique_lock<mutex> lk(m_);
    if (q_.empty()) {
        if (!cond_.wait_for(lk, timewait, [this] { return !q_.empty();}))
            throw TimeoutException();
    }
    MsgPtr ptr = q_.front();
    q_.pop();
    return ptr;
}