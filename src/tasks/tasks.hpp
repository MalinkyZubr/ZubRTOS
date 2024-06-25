#include "memory_mgmt/memory.hpp"
#include <cstdint>
#include "utils.h"


enum ReturnFlag {
    TASK_AWAITING_SHARED_RESOURCE,
    TASK_NOT_COMPLETE,
    TASK_ERROR,
    TASK_COMPLETE,
    TASK_CREATED,
    TASK_AWAITING_EXECUTION,
    TASK_INTERRUPTED
};


typedef struct TaskRuntimeData {
    int execution_count;
    int current_execution_ticks;
    int ticks_from_last_execution; // 
    int ticks_from_last_action; // ticks since the task last occupied a single tick
    int adjusted_priority;

    ReturnFlag state;
} Task;


typedef ReturnFlag (*Operation)(Task *task);