#ifndef AFBC161E_A2ED_4E3E_A6CD_0AE083E83C4T112
#define AFBC161E_A2ED_4E3E_A6CD_0AE083E83C4T112

#include <memory>
#include "CommonTypes.h"
#include "IPlayer.h"

// Provides an interface for message dispatcher used for 
// sending messages accross the players
class IMsgDispatcher {
public:
    virtual ~IMsgDispatcher() { }
    // create player with id. Throws exception if the player already exists.
    virtual IPlayerPtr CreatePlayer(const playerid_t id) = 0;
    // send message (msg) to queue of player (id) from player (pid.)
    virtual void SendMsg(const std::string &msg, const bool ack, 
        const playerid_t from, const playerid_t to) = 0;
};

typedef std::shared_ptr<IMsgDispatcher> IMsgDispatcherPtr;
#endif /* AFBC161E_A2ED_4E3E_A6CD_0AE083E83C4T112 */
