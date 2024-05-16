#ifndef TASKS_H
#define TASKS_H

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

typedef ReturnFlag (*Operation)(TaskManager *task_manager, Task *task);

typedef struct TaskRuntimeData {
    int execution_count;
    int current_execution_ticks;
    int ticks_from_last_execution; // 
    int ticks_from_last_action; // ticks since the task last occupied a single tick
    ReturnFlag state;
} Task;

typedef struct Task {
    const 
    const uint8_t priority; // priority value from 0 to 255
    const int tick_interval; // how many ticks apart should each execution be, ideally
    const Operation task_opt; // what function should be run by task
    const int max_executions; // how many times should the task execute before it fails? 
    const int ticks_per_execution; // how many ticks is the task allowed to use in a single execution?
    const uint8_t repeat; 

    TaskRuntimeData runtime_data;

    Task *lower_priority = NULL;
    Task *higher_priority = NULL;
} Task;

typedef struct TaskManager {
    int ticks_from_resort; // ticks since adjusted priorities were calculated and resorted
    int resort_threshold; // the number of ticks that should elapse before recalculation of priorities and resorting.
    Task *root_task = NULL
} TaskManager;

TaskRuntimeData generate_task_runtime_data(int execution_count, int current_execution_ticks, int ticks_from_last_execution, ReturnFlag return_flag);

Task *generate_task(const uint8_t priority, const int tick_interval, const Operation task_opt, const int max_executions, const uint8_t repeat);

uint8_t calculate_task_ticks_execution(uint8_t priority);

int check_task_within_tick_limit(const Task *task);

int increment_task_execution_count(Task *task);

int increment_task_current_execution_ticks(Task *task);

int increment_task_ticks_from_last_execution(Task *task);

int check_task_previous_state(Task *task, TaskManager *task_manager);

int dynamic_task_priority_calculator(Task *task);

void pi_queue_run_task(Task *task, TaskManager *task_manager);

void pi_queue_sort(TaskManager *task_manager);

void pi_queue_add_task(Task *task, TaskManager *task_manager);

void pi_queue_delete_task(Task *task, TaskManager *task_manager)

#endif