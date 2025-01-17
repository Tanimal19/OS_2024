#ifndef THREADS_H_
#define THREADS_H_
#define NULL_FUNC ((void (*)(int))-1)
// TODO: necessary includes, if any
#include "user/setjmp.h"
// TODO: necessary defines, if any

struct task {
    void (*fp)(void *arg);
    void *arg;
    void *stack;
    void *stack_p;
    jmp_buf env;
    int buf_set;
    struct task *previous;
    struct task *next;
};

struct thread {
    void (*fp)(void *arg);
    void *arg;
    void *stack;
    void *stack_p;
    jmp_buf env; // for thread function
    int buf_set; // 1: indicate jmp_buf (env) has been set, 0: indicate jmp_buf (env) not set
    int ID;
    struct thread *previous;
    struct thread *next;

    int hastask;
    struct task *cur_task; // task current executing
    struct task *prior_task; // next task to be execute
};

struct thread *thread_create(void (*f)(void *), void *arg);
void thread_add_runqueue(struct thread *t);
void thread_yield(void);
void dispatch(void);
void schedule(void);
void thread_exit(void);
void thread_start_threading(void);

// part 2
void thread_assign_task(struct thread *t, void (*f)(void *), void *arg);
void task_exit(void);
#endif // THREADS_H_
