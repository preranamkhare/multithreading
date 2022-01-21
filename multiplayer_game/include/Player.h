#ifndef D49364C2_0D6D_45F8_A970_4F76447CB4323
#define D49364C2_0D6D_45F8_A970_4F76447CB4323

#include <atomic>
#include <thread>
#include <memory>
#include <atomic>
#include <map>
#include <mutex>
#include <condition_variable>
#include <iostream>
#include "IPlayer.h"
#include "IMsgQueue.h"
#include "ThreadWrapper.h"

//Concrete class implementing Player functionality.
class Player : public IPlayer {
public:
    // shutdown at the end.
    ~Player() {
        Shutdown();
    }
    //Player can be threaded or non-threaded.
    Player(const playerid_t pid, IMsgQPtr q, bool threaded): 
        id_(pid), q_(q), threaded_(threaded), shutDownSignal_(false),
        msgCnt_(0)  { }
    // starts a thread when threaded.
    void Play();
    // returns true if thread is running. else returns false;
    bool IsRunning() const { 
        if (th_)
            return th_->IsRunning();
        return false;
     }
    // sends message to other player.
    void SendMsg(const std::string &msg, const playerid_t pid, bool ack = false);
    // sends shutdown signal
    void Shutdown() { shutDownSignal_ = true; }
    // enques a message to it's queue
    void EnqueMsg(const std::string &msg, bool ack, const playerid_t pid);
    // returns true when player gets all the acks for sent messages. Else false.
    bool IsAckCountZero() const { return (msgCnt_ == 0);}
protected:
    void InternalPlay(); // handles looping of read message
    private:
    /* data */
    playerid_t id_; // id
    IMsgQPtr q_; // queue
    bool threaded_; // is it threaded or not
    std::atomic<int> msgCnt_; // counter of messages for which there is no ack
    std::atomic<bool> shutDownSignal_; // shutdown signal
    std::shared_ptr<ThreadWrapper> th_; // wrapper to thread
    std::map<playerid_t, msgcount_t> map_; // keeps counter for each player which has sent message to it
};

#endif /* D49364C2_0D6D_45F8_A970_4F76447CB4323 */
