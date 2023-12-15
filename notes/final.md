# Memory
* sbrk()  -- add the offset to the current memory break address
* brk() -- move current memory break to a specific address 

# Thread
* Threads share same address space: text, data, bss, and heap segments.
* Each threads gets its own stack.
```C
thread_t 
pthread_create()
pthread_exit()
pthread_self()
pthread_join()
pthread_detach()
```

# Synchorization

## Locks (Mutex)
* The central guarantee of a lock is that only a single thread can hold a lock.
    * Example, thread A grabs the lock, so that any thread call lock should wait until it is available. 
    * thread B should wait until thread A release the lock by using "unlock"


```C
pthread_mutex_t *mutex = PTHREAD_MUTEX_INITIALIZER;
int pthread_mutex_lock(pthread_mutex_t *mutex);
int pthread_mutex_unlock(pthread_mutex_t *mutex);
```

## Lock Usage 

## Deadlock and Livelock
* Deadlock:
    * Deadlock hold the lock and make timeout bug.
    * Circular wait
    * Mutual exclusion: threads hold resources exclusively.
    * No preemption: resource released only voluntarily by the thread holding it

* Livelock:
    * Example: 2 threads: A and B, A aquires B, B aquires A (recursion).
    * Because in lock in A haven't been releases. 
    * T0 acquires R0 and T1 acquires R1. T0 then tries to acquire R1 and T1 tries to acquire R0. However, since R0 and R1 are not available, T0 releases R0 and tries again, and T1 releases R1 and tries again. T0 and T1 repeats this sequence forever.

## Conditional Variables
```C
pthread_cond_wait(pthread_cond_t \*cond, pthread_mutex_t \*mutex);
pthread_cond_broadcast(pthread_cond_t \*cond);
// lock-safe sleep
```

## Semphamores
* A lock with a count
```C
sem_init(sem_t \*sem, int pshared, unsigned int value);
// value for number of max lock 
// pshared for threads (0) or process (1).
sem_wait(sem_t \*sem);
sem_post(sem_t \*sem);
// sem_init(&sem, 0, 1) is the same as a mutex
```

## Read-Write Lock
* Either write or read.
```C
pthread_rwlock_t *rwlock = PTHREAD_RWLOCK_INITIALIZER;
pthread_rwlock_rdlock(pthread_rwlock_t *rwlock);
thread_rwlock_wrlock(pthread_rwlock_t *rwlock);
``` 


