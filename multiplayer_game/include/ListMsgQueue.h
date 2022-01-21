#ifndef DE72648A_0A32_4C77_8AE6_BE987DC0B56E
#define DE72648A_0A32_4C77_8AE6_BE987DC0B56E

#include "IMsgQueue.h"
#include <queue>
#include <list>
#include <mutex>
#include <condition_variable>

typedef std::queue<MsgPtr, std::list<MsgPtr> > ListQueue;

//Concrete thread safe queue class which implements
//queue with linked list.
class ListMsgQueue : public IMsgQueue {
public:
    ListMsgQueue(/* args */) { }
    ~ListMsgQueue() { }
    void Push(MsgPtr ptr);
    MsgPtr Pop(const std::chrono::milliseconds timewait);
private:
    /* data */
    ListQueue q_; // queue to store element
    std::mutex m_; // mutual exclusion
    std::condition_variable cond_; // condition variable
};

#endif /* DE72648A_0A32_4C77_8AE6_BE987DC0B56E */
