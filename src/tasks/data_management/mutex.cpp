#include "data_sharing.hpp"
#include "tasks.h"


template<typename DataType>
SharedData<DataType>::SharedData(DataType &shared_data) : shared_data(shared_data) {
    this->mutex = Mutex();
    TaskQueue task_queue;
    this->mutex.awaiting = task_queue;
}


template<typename DataType>
void SharedData<DataType>::lock(Task *task) {
    int queued = 0;
    while(this->mutex.locked_by != task) {
        if(this->task_queue->lowest_priority == nullptr) {
            this->mutex.locked_by = task;
        }
        else if(queued == 0 && pi_queue_find_node(task, this->mutex.awaiting) == nullptr) {
            pi_queue_add_task(task, this->mutex.awaiting);
            queued = 1;
        }
    }
}


template<typename DataType>
void SharedData<DataType>::release(Task *task) {
    if(task == this->mutex.locked_by) {
        TaskNode *requested_node = pi_queue_find_node(task, this->mutex.awaiting);
        if(requested_node != nullptr) {
            this->mutex.locked_by = requested_node->lower_priority;
            pi_queue_delete_task(task, this->mutex.awaiting);
        }
    }
}


template<typename DataType>
DataType *SharedData<DataType>::access_shared_data(Task *task) {
    DataType *data = nullptr;

    if(task == this->mutex.locked_by) {
        data = this->shared_data;
    }

    return data;
}