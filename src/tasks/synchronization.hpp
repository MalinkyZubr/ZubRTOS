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
        void lock();
        void release();
        DataType *access_shared_data();
};

#endif