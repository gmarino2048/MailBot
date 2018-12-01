#include <stdbool.h>
#include <pthread/pthread.h>

namespace Control {

    pthread_t * control_thread;
    pthread_mutex_t * control_lock;
    bool control_thread_complete;

    struct Turtlebot_Movements;

    void setup ();

    bool thread_complete ();
    bool start_process();

    bool lock ();
    bool unlock ();
};