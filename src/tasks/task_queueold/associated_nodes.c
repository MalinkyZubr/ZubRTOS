#include "tasks.h"


TaskNode *t_node_create(Task *task, TaskQueue *task_queue) {
    TaskNode *new_node = (TaskNode*)malloc(sizeof(TaskNode));
    new_node->owned_task = task;

    a_nodes_append(task, new_node, task_queue);
}

void a_nodes_append(Task *task, TaskNode *task_node, TaskQueue *task_queue) {
    AssociatedNodeWrapper *new_wrapper = (AssociatedNodeWrapper*)malloc(sizeof(AssociatedNodeWrapper));
    new_wrapper->associated_node = task_node;
    new_wrapper->task_queue = task_queue;

    if(task->associated_node == NULL) {
        task->associated_node = new_wrapper;
    }
    else {
        AssociatedNodeWrapper *selected_wrapper = task->associated_nodes;

        while(selected_wrapper->next != NULL) {
            selected_wrapper = selected_wrapper->next;
        }
        selected_node->next = new_wrapper;
    }
}

void a_nodes_delete(Task *task, TaskNode *task_node) {
    AssociatedNodeWrapper *prior = NULL;
    AssociatedNodeWrapper *selected = task->associated_node;
    AssociatedNodeWrapper *next = selected->next;

    while(selected != NULL && selected->associated_node) {
        prior = selected;
        selected = selected->next;
        next = selected->next
    }
    if(selected != NULL) {
        prior->next = next;
        pi_queue_delete_task(task, selected->task_queue);
        free(selected);
    }
}

void a_nodes_delete_all(Task *task) {
    AssociatedNodeWrapper *selected_wrapper = task->associated_node;
    AssociatedNodeWrapper *next_wrapper = NULL;

    while(selected_wrapper != NULL) {
        next_wrapper = selected_wrapper->next;

        pi_queue_delete_task(task, selected_wrapper->task_queue);
        free(selected_wrapper);

        selected_wrapper = next_wrapper;
    }
}