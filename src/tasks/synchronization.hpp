#ifndef SYNCHRONIZATION_H
#define SYNCHRONIZATION_H

#include "tasks.h"

typedef struct Mutex {
    bool acquired;
    Task *acquired_by;
    PriorityTreeRoot *awaiting;
} Mutex;


template<class DataType>
class SharedData {
    private:
        DataType shared_data;
        Mutex mutex;
    public:
        SharedData(DataType shared_data)
        void acquire();
        void release();
        DataType *access_shared_data();
};

#endif