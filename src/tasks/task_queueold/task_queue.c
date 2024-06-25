#include "tasks.h"


void pi_queue_sort(TaskQueue *task_queue) { // what about if the next has to be null?
    if(selected_task->lowest_priority != NULL) {
        TaskNode *selected_task = task_queue->lowest_priority;
        TaskNode *minimum_priority_task = selected_task;
        TaskNode *maximum_priority_task = selected_task;
        TaskNode *former_higher_priority;

        while(selected_task != NULL) {
            selected_task = selected_task->higher_priority;

            while(selected_task->higher_priority != NULL && selected_task->owned_task->runtime_data.adjusted_priority > selected_task->owned_task->higher_priority->runtime_data.adjusted_priority) {// must append to the start of the linked list queue
                former_higher_priority = selected_task->higher_priority;

                selected_task->lower_priority->higher_priority = former_higher_priority;
                former_higher_priority->lower_priority = selected_task->lower_priority;
        
                selected_task->lower_priority = former_higher_priority;
                selected_task->higher_priority = former_higher_priority->higher_priority;

                former_higher_priority->higher_priority = selected_task;
            }

            if(selected_task->owned_task->runtime_data.adjusted_priority > maximum_priority_task->owned_task->runtime_data.adjusted_priority) {
                maximum_priority_task = selected_task;
            }
            else if(selected_task->owned_task->runtime_data.adjusted_priority < minimum_priority_task->owned_task->runtime_data.adjusted_priority) {
                minimum_priority_task = selected_task;
            }
        }

        task_queue->highest_priority = maximum_priority_task;
        task_queue->lowest_priority = minimum_priority_task
    }
}

void pi_queue_add_task(TaskNode *task, TaskQueue *task_queue) {
    TaskNode *new_node = (TaskNode*)malloc(sizeof(TaskNode));
    new_node->owned_task = task;

    if(task_queue->lowest_priority == NULL) {
        task_queue->lowest_priority = new_node;
        task_queue->highest_priority = new_node;
    } 
    else {
        task_queue->lowest_priority->lower_priority = new_node;
        new_node->higher_priority = task_queue->lowest_priority;
        task_queue->lowest_priority = new_node;

        new_node->lower_priority = NULL;
        pi_queue_sort(task_queue);
    }
}

void pi_queue_delete_task(TaskNode *task_node, TaskQueue *task_queue) {
    if(task_node != NULL) {
        if(task_node == task_queue->lowest_priority) {
            task_queue->lowest_priority = NULL;
            task_queue->highest_priority = NULL;
        }
        else if(task_node == task_queue->highest_priority) {
            task_queue->highest_priority = task_node->lower_priority;
        }
        else {
            if(task_node->higher_priority != NULL) {
                task_node->higher_priority->lower_priority = task_node->lower_priority;
            }
            if(task_node->lower_priority != NULL) {
                task_node->lower_priority->higher_priority = task_node->higher_priority;
            }
        }
        free(task_node->owned_task);
        free(task_node);
    }
}

TaskNode *pi_queue_find_node(Task *task, TaskQueue *task_queue) {
    TaskNode *selected_node = NULL;

    if(task != NULL) {
        selected_node = task_queue->lowest_priority;

        while(selected_node != NULL && selected_node->owned_task) {
            selected_node = selected_node->higher_priority;
        }
    }

    return selected_node;
}

void pi_queue_destructor(TaskQueue *task_queue) {
    TaskNode *selected_node = task_queue->lowest_priority;

    while(selected_)
}