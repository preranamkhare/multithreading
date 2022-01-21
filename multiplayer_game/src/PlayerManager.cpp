#include <iostream>
#include "PlayerManager.h"

using namespace std;

#ifdef MULTIPROCESS
    #include "PipeMsgQueue.h"
    #include "IPCHelper.h"
    typedef PipeMsgQueue QType;
    const string FIFOPREFIX = "/tmp/Player";
#else
    #include "ListMsgQueue.h"
    typedef ListMsgQueue QType;
#endif

PlayerManager::~PlayerManager() {
    m_.clear();
}

IPlayerPtr PlayerManager::CreatePlayer(const playerid_t id) {
    auto it = m_.find(id);
    if (it != m_.end())
        throw PlayerPresentException();
#ifdef MULTIPROCESS
    string fifo = FIFOPREFIX + to_string(id);
    shared_ptr<IMsgQueue> ptr = IPCHelper::CreateMsgQ(fifo);
#else
    shared_ptr<IMsgQueue> ptr(new QType());
#endif
    IPlayerPtr player(new Player(id, ptr, true));
    m_.insert(pair<playerid_t, IPlayerPtr>(id, player));
    return player;
}

void PlayerManager::SendMsg(const std::string &msg, const bool ack, 
    const playerid_t from, const playerid_t to) {
    auto it = m_.find(to);
    if (it == m_.end() || m_.find(from) == m_.end())
        throw PlayerNotFoundException();
    it->second->EnqueMsg(msg, ack, from);
}
