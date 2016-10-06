#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/sysctl.h>

#include "phonebook_opt.h"
#include "debug.h"

entry *findName(char lastname[], entry *pHead)
{
    size_t len = strlen(lastname);
    while (pHead != NULL) {
        if (strncasecmp(lastname, pHead->lastName, len) == 0
                && (pHead->lastName[len] == '\n' ||
                    pHead->lastName[len] == '\0')) {
            pHead->lastName = (char *) malloc(sizeof(char) *
                                              MAX_LAST_NAME_SIZE);
            memset(pHead->lastName, '\0', MAX_LAST_NAME_SIZE);
            strcpy(pHead->lastName, lastname);
            pHead->dtl = (pdetail) malloc(sizeof(detail));
            return pHead;
        }
        dprintf("find string = %s\n", pHead->lastName);
        pHead = pHead->pNext;
    }
    return NULL;
}

task_info *init_task_info(int i, entry *e)
{
    task_info *task = (task_info *) malloc(sizeof(task_info));
    task->pHead = (entry *) malloc(sizeof(entry));
    task->pHead->pNext = NULL;
    task->pLast = task->pHead;
    task->entry_start = e;

    return task;
}

void task_run(char *p, task_info *task)
{

    cr_start();

    while (1) {
        task->pLast->lastName = p;
        task->pLast->pNext = task->entry_start;
        task->pLast = task->pLast->pNext;
        task->pLast->pNext = NULL;

        task->entry_start++;

        cr_yield();
    }
    cr_finish();
}

void show_entry(entry *pHead)
{
    while (pHead != NULL) {
        printf("lastName = %s\n", pHead->lastName);
        pHead = pHead->pNext;
    }
}

int get_sysctl_threads_max()
{
    int mib[2], threads_max;
    size_t len;
    mib[0] = CTL_KERN;
    mib[1] = KERN_MAX_THREADS;
    len = sizeof(threads_max);
    sysctl(mib, 2, &threads_max, &len, NULL, 0);
    return threads_max;
}
