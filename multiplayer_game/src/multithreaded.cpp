#include <iostream>
#include <array>
#include <chrono>
#include <thread>
#include "PlayerManager.h"
#include "MsgDispatcher.h"

using namespace std;

int main() {
    cout << "Starting multithreaded" << endl;
    IMsgDispatcherPtr mgr = PlayerManager::GetInstance();
    MsgDispatcher::SetDispatcher(mgr);
    IPlayerPtr p1 = mgr->CreatePlayer(1);
    IPlayerPtr p2 = mgr->CreatePlayer(2);
    p1->Play();
    p2->Play();
    string msg = "Good morning ";
    for (int i=1; i<=10; ++i) {
        p1->SendMsg(msg + to_string(i), 2, false);
    }
    while (!p1->IsAckCountZero()) {
        this_thread::sleep_for(chrono::milliseconds(5));
    }
    return 0;
}