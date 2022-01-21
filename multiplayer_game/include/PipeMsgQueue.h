#ifndef E9C41C91_1622_46C0_9873_601CABE709AC
#define E9C41C91_1622_46C0_9873_601CABE709AC

#include "CommonTypes.h"
#include "IMsgQueue.h"

//Concrete class which uses pipe communication
//to send and receive messages.
class PipeMsgQueue : IMsgQueue {
public:
    PipeMsgQueue(const std::string &fifo = "", int in = -1, int out = -1): 
        fifo_(fifo), inFd_(in), outFd_(out) { }
    ~PipeMsgQueue();
    void Push(MsgPtr ptr);
    MsgPtr Pop(const std::chrono::milliseconds d);
private:
    /* data */
    std::string fifo_; //name of the fifo
    int inFd_; //fd to read from
    int outFd_; //fd to write
};


#endif /* E9C41C91_1622_46C0_9873_601CABE709AC */
