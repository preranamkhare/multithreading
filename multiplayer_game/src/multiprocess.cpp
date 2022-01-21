#include <iostream>
#include <array>
#include <chrono>
#include <thread>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <vector>
#include "PlayerManager.h"
#include "MsgDispatcher.h"

using namespace std;

namespace {
    atomic<bool> shutdown(false);
}

static void sigintHandler(int sig)
{
    shutdown = true;
}

int main(int argc, char* argv[]) {
    if (signal(SIGINT, sigintHandler) == SIG_ERR) {
        perror("signal SIGINT");
        return 1;
    }
    if (argc < 4) {
        cout << "Usage: " << argv[0] << 
            "<1 if this user is initiater>  <player id of this user> "
            << " <player id of other users separated by space>" << endl;
        return 1;
    }
    try {
    IMsgDispatcherPtr mgr = PlayerManager::GetInstance();
    MsgDispatcher::SetDispatcher(mgr);
    int initiater = atoi(argv[1]);
    playerid_t thisId = atoi(argv[2]);
    cout << "Creating player for id " << thisId << endl;
    IPlayerPtr player = mgr->CreatePlayer(thisId);
    vector<int> ids;
    for (int i=3; i < argc; ++i)
    {
        playerid_t id = atoi(argv[i]);
        mgr->CreatePlayer(id);
        ids.push_back(id);
    }
    player->Play();
    if (initiater == 1) {
        string msg = "multiprocess msg";
        for (auto it = ids.begin(); it != ids.end(); ++it) {
            for (int i=1; i<=10; ++i) {
                player->SendMsg(msg + to_string(i), *it, false);
            }
        }
        while (!player->IsAckCountZero()) {
            this_thread::sleep_for(chrono::milliseconds(1));
        }
        shutdown = true;
    }
    while (!shutdown) {
        this_thread::sleep_for(chrono::milliseconds(5));
    }
    cout <<"leaving" << endl;
    } catch(exception &e) {
        cout << "Caught exception: " << e.what() << endl;
    }
    return 0;
}