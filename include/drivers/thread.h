#ifndef THREAD_H
#define THREAD_H

#include <stdint.h>
#include <stddef.h>

typedef uint32_t tid_t;

typedef enum {
    THREAD_READY,
    THREAD_RUNNING,
    THREAD_ZOMBIE,
    THREAD_SLEEPING
} thread_state_t;

typedef void (*thread_fn_t)(void*);

typedef struct thread {
    uint32_t esp;
    tid_t id;
    uint32_t *stack;
    size_t stack_size;
    thread_state_t state;
    struct thread *next;
} thread_t;

typedef struct {
    int locked;
    thread_t *wait_head;
    thread_t *wait_tail;
} mutex_t;

typedef struct {
    int count;
    thread_t *wait_head;
    thread_t *wait_tail;
} semaphore_t;

int thread_system_init(void);
tid_t thread_create(thread_fn_t fn, void *arg, size_t stack_size);
void thread_yield(void);
void thread_exit(void);

void mutex_init(mutex_t *mut);
void mutex_lock(mutex_t *mut);
void mutex_unlock(mutex_t *mut);

void sem_init(semaphore_t *sem, int count);
void sem_wait(semaphore_t *sem);
void sem_post(semaphore_t *sem);

#endif
