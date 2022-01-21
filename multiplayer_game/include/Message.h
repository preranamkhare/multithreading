#ifndef A4A4A121_712B_40E4_9E0D_D1819C0A2CE5
#define A4A4A121_712B_40E4_9E0D_D1819C0A2CE5

#include <string>
#include <memory>
#include "CommonTypes.h"

// Concrete class representing a string based message.
class Message {
public:
    Message(const std::string &msg, const playerid_t pid,
        const bool ack = false): 
        msg_(msg), fromPlayerId_(pid), ack_(ack) { }
    Message(const Message &m): msg_(m.msg_), fromPlayerId_(m.fromPlayerId_),
        ack_(m.ack_) { }
    Message & operator =(const Message &m) {
        msg_ = m.msg_;
        fromPlayerId_ = m.fromPlayerId_;
        ack_ = m.ack_;
        return *this;
    }
    ~Message() {}
    //Accessors
    playerid_t PlayerID() const { return fromPlayerId_; }
    std::string Msg() const { return msg_; }
    bool Ack() const { return ack_; }
protected:
private:
    /* data */
    std::string msg_; // actual message
    playerid_t fromPlayerId_; // from player id
    bool ack_; // whether this is acknowledgement
};

typedef std::shared_ptr<Message> MsgPtr;

#endif /* A4A4A121_712B_40E4_9E0D_D1819C0A2CE5 */
