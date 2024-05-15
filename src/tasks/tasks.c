#include "tasks.h"


uint8_t calculate_task_ticks_execution(uint8_t priority) {
    uint8_t tick_per_execution = ((64 * priority) / 255);
    return ticks_per_execution;
}

TaskRuntimeData generate_runtime_data(int execution_count, int current_execution_ticks, int ticks_from_last_execution, ReturnFlag return_flag) {
    TaskRuntimeData runtime_data;
    runtime_data.execution_count = execution_count;
    runtime_data.current_execution_ticks = current_execution_ticks;
    runtime_data.ticks_from_last_execution = ticks_from_last_execution;
    runtime_data.state = TASK_CREATED;
}

Task *generate_task(const uint8_t priority, const int tick_interval, const Operation task_opt, const int max_executions) {
    Task *to_return = (Task*)malloc(sizeof(Task));
    to_return->priority = priority;
    to_return->tick_interval = tick_interval;
    to_return->task_opt = task_opt;
    to_return->max_executions = max_executions;
    to_return->ticks_per_execution = calculate_ticks_execution(priority);

    to_return->runtime_data = generate_runtime_data(0, 0, 0, TASK_CREATED);
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

int check_task_previous_state(Task *task) {

}

void pi_tree_run_task(TaskManager *task_manager) {
    Task *root_task = task_manager->root_task;

    if(root_task != NULL) {
        Task *selected_task = root_task;
        while(selected_task->higher_priority != NULL) {
            
        }
        ReturnFlag return_flag = selected_task->task_opt(task_manager, selected_task);

    }
}

void pi_tree_add_task(Task *task, TaskManager *task_manager);

void pi_tree_delete_task(Task *task, TaskManager *task_manager)