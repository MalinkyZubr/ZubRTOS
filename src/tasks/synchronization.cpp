#include "synchronization.hpp"


template<typename DataType>
SharedData<DataType>::SharedData(DataType &shared_data) : shared_data(shared_data) {
    this->mutex = Mutex();
    TaskQueue task_queue;
    this->mutex.awaiting = task_queue;
}


template<typename DataType>
void SharedData<DataType>::lock() {
    if(this->task_queue->lowest_priority == nullptr) {
        
    }
}


template<typename DataType>
void SharedData<DataType>::release() {
    
}


template<typename DataType>
DataType *SharedData<DataType>::access_shared_data() {

}