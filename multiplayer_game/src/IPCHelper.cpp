#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <iostream>
#include "IPCHelper.h"
#include "PipeMsgQueue.h"
#include "Exceptions.h"

using namespace std;

IMsgQPtr IPCHelper::CreateMsgQ(const string &fifo) {
    if (mkfifo(fifo.c_str(), 0600) == -1 ) {
        int errnum = errno;
        if (errnum != EEXIST) {
            cout << "Failed to open a Fifo " << fifo << " Error:" << strerror(errnum) << endl;
            throw PipeOpenFailedException();
        }
    }
    int fd = open(fifo.c_str(), O_RDWR, 0644);
    if (-1 == fd) {
        int errnum = errno;
        cout << "Failed to open a Fifo " << fifo << " Error:" << strerror(errnum) << endl;
        throw PipeCreateFailedException();
    }
    return IMsgQPtr((IMsgQueue*)(new PipeMsgQueue(fifo, fd, fd)));
}