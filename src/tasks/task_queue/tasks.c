#include "tasks.h"


uint8_t calculate_task_ticks_execution(uint8_t priority) {
    uint8_t tick_per_execution = ((64 * priority) / 255);
    return ticks_per_execution;
}

TaskRuntimeData generate_runtime_data(int execution_count, int current_execution_ticks, int ticks_from_last_execution, int adjusted_priority, ReturnFlag return_flag) {
    TaskRuntimeData runtime_data;
    runtime_data.execution_count = execution_count;
    runtime_data.current_execution_ticks = current_execution_ticks;
    runtime_data.ticks_from_last_execution = ticks_from_last_execution;
    runtime_data.adjusted_priority = adjusted_priority
    runtime_data.state = TASK_CREATED;
}

Task *generate_task(const uint8_t priority, const int tick_interval, const Operation task_opt, const int max_executions, const uint8_t repeat) {
    Task *to_return = (Task*)malloc(sizeof(Task));
    to_return->priority = priority;
    if(repeat == 1) {
        if(tick_interval >= 10)
            to_return->tick_interval = tick_interval;
        else {
            to_return->tick_interval = 10;
        }
    } 
    else {
        to_return->tick_interval = tick_interval;
    }
    to_return->task_opt = task_opt;
    to_return->max_executions = max_executions;
    to_return->ticks_per_execution = calculate_ticks_execution(priority);

    to_return->runtime_data = generate_runtime_data(0, 0, 0, priority, TASK_CREATED);
    to_return->repeat = repeat;
    return to_return;
}

int check_task_within_tick_limit(const Task *task) {
    return task->runtime_data.current_execution_ticks < task->ticks_per_execution;
}

int increment_task_execution_count(Task *task) {
    task->runtime_data.execution_count++;
}

int increment_task_current_execution_ticks(Task *task) {
    task->runtime_data.current_execution_ticks++;
}

int increment_task_ticks_from_last_execution(Task *task) {
    task->runtime_data.ticks_from_last_execution++;
}

int dynamic_task_priority_calculator(Task *task) {
    int exponent = task->runtime_data.ticks_from_last_action + (16 * task->repeat);
    int adjusted_priority = modular_exponent(task->priority * ((1.02 - (0.0001 * task->runtime_data.current_execution_ticks))), exponent);
}

int check_task_previous_state(Task *task, TaskManager *task_manager) {
    switch(task->runtime_data.previous_state) {
        case TASK_AWAITING_SHARED_RESOURCE:
            break;
        case TASK_NOT_COMPLETE:

            break;
        case TASK_ERROR:
            if(task->repeat == 1) {
                Task *restarted_task = generate_task(task->priority, task->tick_interval, task->task_opt, task->max_executions, task->repeat);
                pi_queue_delete_task(task, task_manager);
                pi_queue_add_task(task, task_manager);
            }
            else {
                pi_queue_delete_task(task, task_manager);
            }
            break;
        case TASK_COMPLETE:
            if(task->repeat == 0) {
                pi_queue_delete_task(task, task_manager);
            }
            else {
                task->runtime_data.state = TASK_AWAITING_EXECUTION;
                task->runtime_data.
            }
            break;
        case TASK_CREATED:

            break;
    }
}