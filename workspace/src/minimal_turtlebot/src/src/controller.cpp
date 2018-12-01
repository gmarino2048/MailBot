#include <stdint.h>
#include <pthread/pthread.h>
#include "../lib/controller.hpp"

namespace Control {

    struct Turtlebot_Movements {
        float vel;
        float ang_vel;
        uint8_t sound;
    };

    bool thread_complete () {
        return control_thread_complete;
    }

    bool start_process (void *(* function)(void *)) {
        bool thread_create = pthread_create(control_thread, NULL, function, NULL);
        bool mutex_create = pthread_mutex_init(control_lock, NULL);

        control_thread_complete = false;

        return thread_create && mutex_create;
    }

    bool lock () {
        return pthread_mutex_lock(control_lock);
    }

    bool unlock () {
        return pthread_mutex_unlock(control_lock);
    }
};