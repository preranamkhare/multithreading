#include "MsgDispatcher.h"
#include "Exceptions.h"

IMsgDispatcherPtr MsgDispatcher::ptr_;

void MsgDispatcher::SendMsg(const std::string &msg, const bool ack, 
    const playerid_t from, const playerid_t to) {
    if (!ptr_)
        throw MsgDispatcherNotInitialized();
    ptr_->SendMsg(msg, ack, from, to);
}
