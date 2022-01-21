#ifndef AFBC161E_A2ED_4E3E_A6CD_0AE083E83C4A1
#define AFBC161E_A2ED_4E3E_A6CD_0AE083E83C4A1

#include <string>
#include "IMsgQueue.h"

// Helper class to support IPC functions.
class IPCHelper {
public:
    // Creates a message queue based on fifo.
    // Opens a fifon and provides it to the Q object.
    // fifo fd must be closed by the Q.
    static IMsgQPtr CreateMsgQ(const std::string &fifo);
};

#endif /* AFBC161E_A2ED_4E3E_A6CD_0AE083E83C4A1 */
