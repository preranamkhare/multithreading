#ifndef D3DAD783_BA62_4D16_B1C6_B9CE028806E5
#define D3DAD783_BA62_4D16_B1C6_B9CE028806E5

#include "CommonTypes.h"
#include "IMsgDispatcher.h"
#include <string>

//Encapsulating actual message dispatcher and providing
//an interface to player class.
class MsgDispatcher
{
public:
    ~MsgDispatcher() { }
    static void SetDispatcher(IMsgDispatcherPtr p) { ptr_ = p; }
    static void SendMsg(const std::string &msg, const bool ack, 
        const playerid_t from, const playerid_t to);
private:
    /* data */
    static IMsgDispatcherPtr ptr_; // pointer to actual dispatcher
    MsgDispatcher(/* args */) { }
    MsgDispatcher(const MsgDispatcher&) = delete;
    MsgDispatcher & operator=(const MsgDispatcher &) = delete;
};

#endif /* D3DAD783_BA62_4D16_B1C6_B9CE028806E5 */
