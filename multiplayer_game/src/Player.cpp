#include<iostream>
#include <thread>
#include <functional>
#include "Player.h"
#include "MsgDispatcher.h"

using namespace std;

const chrono::milliseconds timewait(100);
const uint16_t msgLimit = 10;

void Player::Play() {
    if (threaded_) {
        std::function<void(void)> f = bind(&Player::InternalPlay, this);
        th_ = make_shared<ThreadWrapper>(f);
    } else {
        InternalPlay();
    }
}

void Player::SendMsg(const string &msg, const playerid_t to, bool ack) {
    if (!ack) {
        ++msgCnt_;
    }
    MsgDispatcher::SendMsg(msg, ack, id_, to);
}

void Player::EnqueMsg(const std::string &msg, bool ack, const playerid_t from) {
    q_->Push(MsgPtr(new Message(msg, from, ack)));
}

void Player::InternalPlay() {
    if (th_)
        th_->SetRunning(true);
    while (!shutDownSignal_) {
        try {
            MsgPtr msg = q_->Pop(timewait);
            if (msg) {
                cout << "Player " << msg->PlayerID() << "->" 
                    << id_ << " : " << msg->Msg() << endl;
                    /*<< " ack: " << 
                    (msg->Ack() ? "true" : "false") << endl;*/
                if (msg->Ack()) {
                    --msgCnt_;
                } else {
                    auto it = map_.find(msg->PlayerID());
                    if (it != map_.end()) {
                        ++it->second;
                    } else {
                        map_.insert(pair<playerid_t, uint16_t>(msg->PlayerID(), 1));
                    }
                    string newmsg = msg->Msg() + "#" + to_string(it->second);
                    SendMsg(newmsg, msg->PlayerID(), true);
                }
            }   
        } catch (TimeoutException &e)
        {
            continue;
        }
    }
    if (th_)
        th_->SetRunning(false);
}
