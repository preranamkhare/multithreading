#ifndef AFBC161E_A2ED_4E3E_A6CD_0AE083E83C4T
#define AFBC161E_A2ED_4E3E_A6CD_0AE083E83C4T

#include <exception>

#define DEFINE_EXCEPTION(ClassName,Message) \
    class ClassName : public std::exception { \
    public: \
        const char* what() { return Message;} \
    };

DEFINE_EXCEPTION(TimeoutException, "operation timedout!")
DEFINE_EXCEPTION(PlayerNotFoundException, "Player not found!")
DEFINE_EXCEPTION(PlayerPresentException, "Player already present!")
DEFINE_EXCEPTION(MsgSendFailedException, "Message send failed!")
DEFINE_EXCEPTION(MsgReadFailedException, "Message read failed!")
DEFINE_EXCEPTION(PipeCreateFailedException, "FIFO create failed!")
DEFINE_EXCEPTION(PipeOpenFailedException, "FIFO open failed!")
DEFINE_EXCEPTION(InstanceNotInitialized, "Instance is not initialised!")
DEFINE_EXCEPTION(MsgDispatcherNotInitialized, "Message Dispatcher not initialized!")

#endif /* AFBC161E_A2ED_4E3E_A6CD_0AE083E83C4T */
