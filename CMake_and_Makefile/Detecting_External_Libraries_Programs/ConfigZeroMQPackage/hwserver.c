/*!
 *  \file       hwserver.c
 *  \brief
 *
 */



#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>

#if (_MSC_VER && !__INTEL_COMPILER)
    #include <WinSock2.h>
    #include <Windows.h>
#else
    #include <unistd.h>
#endif

#include <zmq.h>


int main(void)
{
    // Report version
    int major, minor, patch;
    zmq_version(&major, &minor, &patch);
    printf("Current ZeroMQ version is %d.%d.%d\n", major, minor, patch);

    // Socket to talk to clients
    void* context = zmq_ctx_new();
    void* responder = zmq_socket(context, ZMQ_REP);
    int rc = zmq_bind(responder, "tcp://*:5555");
    assert(rc == 0);

    while (true)
    {
        char buffer[10];
        zmq_recv(responder, buffer, 10, 0);
        printf("Received Hello\n\n");

#if (_MSC_VER && !__INTEL_COMPILER)
        Sleep(1 * 1000);    // Do some other work during this sleep peroid
#else
        sleep(1);       // Allow CPU to do some other work.
#endif
        zmq_send(responder, "world", 5, 0);
    }

    return EXIT_SUCCESS;
}