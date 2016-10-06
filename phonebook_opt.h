#ifndef _PHONEBOOK_H
#define _PHONEBOOK_H

#include <pthread.h>
#include <time.h>

#define MAX_LAST_NAME_SIZE 16

#define OPT 1

#define cr_start()		   	\
		static int __s = 0;	\
		switch (__s) { 		\
			case 0:

#define cr_yield() 			\
		do { 				\
			__s = __LINE__; 	\
			return; 		\
			case __LINE__:; \
		} while (0)

#define cr_finish() \
		} 			\
		__s = 0

typedef struct _detail {
    char firstName[16];
    char email[16];
    char phone[10];
    char cell[10];
    char addr1[16];
    char addr2[16];
    char city[16];
    char state[2];
    char zip[5];
} detail;

typedef detail *pdetail;

typedef struct __PHONE_BOOK_ENTRY {
    char *lastName;
    struct __PHONE_BOOK_ENTRY *pNext;
    pdetail dtl;
} entry;

entry *findName(char lastname[], entry *pHead);

typedef struct _TASK_INFO {
    entry *entry_start;
    entry *pHead;
    entry *pLast;
} task_info;

task_info *init_task_info(int i, entry *e);

void task_run(char *p, task_info *task);

void show_entry(entry *pHead);

int get_sysctl_threads_max();

#endif
