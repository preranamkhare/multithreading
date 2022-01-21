#ifndef D49364C2_0D6D_45F8_A970_4F76447CB4321
#define D49364C2_0D6D_45F8_A970_4F76447CB4321

#include <atomic>
#include <thread>
#include <memory>
#include <functional>
#include "IPlayer.h"

//Wrapper to thread. Uses joinable thread.
class ThreadWrapper : public std::thread {
public:
    ThreadWrapper(std::function<void(void)> f): std::thread(f),
        running_(false) { }
    ~ThreadWrapper() {
        join();
    }
    void SetRunning(const bool b) { running_ = b; }
    bool IsRunning() const { return running_; }
private:
    /* data */
    std::atomic<bool> running_; // flag indicating whether it is running a thread or not
};


#endif /* D49364C2_0D6D_45F8_A970_4F76447CB4321 */
