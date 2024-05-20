#include "tasks.h"


task_manager_main_isr(TaskManager *task_manager) {
    task_manager->ticks_from_resort++;
    
}