#ifndef D476D55C_A7B4_4ECC_B066_CE79B907B635
#define D476D55C_A7B4_4ECC_B066_CE79B907B635

#include <memory>
#include <chrono>
#include "Message.h"
#include "Exceptions.h"

//Abstract class for message queue. The interface provides 2 functions
// 1. push element
// 2. pop element
class IMsgQueue {
public:
    IMsgQueue(/* args */) { }
    virtual ~IMsgQueue() { }
    // Push pushes the element to the queue
    virtual void Push(MsgPtr ptr) = 0;
    // Pops element from the queue. waits on the queue for input timeout
    // Throws an exception if timeout occurs.
    virtual MsgPtr Pop(const std::chrono::milliseconds d) = 0;
};

typedef std::shared_ptr<IMsgQueue> IMsgQPtr;

#endif /* D476D55C_A7B4_4ECC_B066_CE79B907B635 */
