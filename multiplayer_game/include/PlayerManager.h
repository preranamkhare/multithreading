#ifndef CB4F5C11_DA65_4885_B426_B2D6BC81A1B4
#define CB4F5C11_DA65_4885_B426_B2D6BC81A1B4

#include <unordered_map>
#include <thread>
#include "CommonTypes.h"
#include "Player.h"
#include "IMsgDispatcher.h"

typedef std::unordered_map<playerid_t, IPlayerPtr> PlayerMap;

//Concrete class which provides message dispatching and user creation
//functionality. It also keeps player cache
//A singletone class
class PlayerManager : public IMsgDispatcher {
public:
    ~PlayerManager();
    static IMsgDispatcherPtr & GetInstance() {
        static IMsgDispatcherPtr mgr(new PlayerManager());
        return mgr;
    }
    IPlayerPtr CreatePlayer(const playerid_t id);
    // send message (msg) to queue of player (id) from player (pid.)
    void SendMsg(const std::string &msg, const bool ack, 
        const playerid_t from, const playerid_t to);

private:
    /* data */
    PlayerMap m_; // player map
    PlayerManager(/* args */) { }
    PlayerManager(const PlayerManager&) = delete;
    PlayerManager & operator=(const PlayerManager&) = delete;
};

#endif /* CB4F5C11_DA65_4885_B426_B2D6BC81A1B4 */
