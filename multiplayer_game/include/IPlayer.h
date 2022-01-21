#ifndef C3B3BC7E_C9E2_47F1_97C4_78AEDD4C8259
#define C3B3BC7E_C9E2_47F1_97C4_78AEDD4C8259

#include <string>
#include <memory>
#include "CommonTypes.h"
#include "Message.h"

//Abstract class for player
//A player can send message to another player
// Or it can enque message to itself.
// returns counter of messages.
class IPlayer {
public:
    virtual ~IPlayer() { }
    virtual void Play() = 0;
    // send message to id
    virtual void SendMsg(const std::string &, const playerid_t to, bool ack = false) = 0;
    virtual void Shutdown() = 0;
    // receive message from id
    virtual void EnqueMsg(const std::string &, bool ack, const playerid_t from) = 0;
    virtual bool IsAckCountZero() const = 0;
};

typedef std::shared_ptr<IPlayer> IPlayerPtr;

#endif /* C3B3BC7E_C9E2_47F1_97C4_78AEDD4C8259 */
