#include "tasks.h"


void pi_queue_sort(TaskQueue *task_queue) { // what about if the next has to be null?
    if(selected_task->lowest_priority != NULL) {
        Task *selected_task = task_queue->lowest_priority;
        Task *minimum_priority_task = selected_task;
        Task *maximum_priority_task = selected_task;
        Task *former_higher_priority;

        while(selected_task != NULL) {
            selected_task = selected_task->higher_priority;

            while(selected_task->higher_priority != NULL && selected_task->runtime_data.adjusted_priority > selected_task->higher_priority->runtime_data.adjusted_priority) {// must append to the start of the linked list queue
                former_higher_priority = selected_task->higher_priority;

                selected_task->lower_priority->higher_priority = former_higher_priority;
                former_higher_priority->lower_priority = selected_task->lower_priority;
        
                selected_task->lower_priority = former_higher_priority;
                selected_task->higher_priority = former_higher_priority->higher_priority;

                former_higher_priority->higher_priority = selected_task;
            }

            if(selected_task->runtime_data.adjusted_priority > maximum_priority_task->runtime_data.adjusted_priority) {
                maximum_priority_task = selected_task;
            }
            else if(selected_task->runtime_data.adjusted_priority < minimum_priority_task->runtime_data.adjusted_priority) {
                minimum_priority_task = selected_task;
            }
        }

        task_queue->highest_priority = maximum_priority_task;
        task_queue->lowest_priority = minimum_priority_task
    }
}

void pi_queue_add_task(Task *task, TaskQueue *task_queue) {
    if(task_queue->lowest_priority == NULL) {
        task_queue->lowest_priority = task;
        task_queue->highest_priority = task;
    }
    else {
        task_queue->lowest_priority->lower_priority = task;
        task->higher_priority = task_queue->lowest_priority;
        task_queue->lowest_priority = task;

        task->lower_priority = NULL;
        pi_queue_sort(task_queue);
    }
}

void pi_queue_delete_task(Task *task, TaskQueue *task_queue) {
    if(task != NULL) {
        if(task == task_queue->lowest_priority) {
            task_queue->lowest_priority = NULL;
            task_queue->highest_priority = NULL;
        }
        else if(task == task_queue->highest_priority) {
            task_queue->highest_priority = task->lower_priority;
        }
        else {
            if(selected_task->higher_priority != NULL) {
                selected_task->higher_priority->lower_priority = selected_task->lower_priority;
            }
            if(selected_task->lower_priority != NULL) {
                selected_task->lower_priority->higher_priority = selected_task->higher_priority;
            }
        }
        free(task);
    }
}