#ifndef SYNCHRONIZATION_H
#define SYNCHRONIZATION_H

#include "tasks.h"


typedef struct Mutex {
    Task *locked_by = nullptr;
    TaskQueue awaiting;
} Mutex;


template<typename DataType>
class SharedData {
    private:
        DataType &shared_data;
        Mutex mutex;
    public:
        SharedData(DataType &shared_data);
        void lock(Task *task);
        void release(Task *task);
        DataType *access_shared_data(Task* task);
};


class Signal {
    private:
        int run_flag;
    
    public:
        Signal(Task *task);
        int is_set();
        void set_high();
        void set_low();
}


class SystemCommons {

}


#endif