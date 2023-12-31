# A3:
dynamic linking: a dynamic linker is the part of an operating system that loads and links the shared libraries needed by an executable when 
it is executed (at "run time"), by copying the content of libraries from persistent storage to RAM, filling jump tables and relocating pointers. 

.a: static library. ".a" stands for "archive"
.so: shared libraries. If it is contained then it is "Static linking". ".so" stands for "shared object".
.o: object but yet "linked". They are interpreted to object files with certain filled in address pointer. They will be linked when the parameter that contained the pointer to the function.

# A4:
## Precondition:
    * Assert(//condtion);

## Postcondition
    The condition that the result of the section of code is supposed to satisfy.

## Undefined behavior:
    The case that causes wrong result :) 
    * Example: Buffer Overflow, Absolute MIN_INT is still MIN_INT

# A6, A7: 
```bash 
.──────────────────────.
|                      | Address 2^n - 1
| Kernel address space | (n is the number of address bits)
|                      |
+──────────────────────+
|                      |
| Stack                |
| (grows ↓)            |
|                      |
+──────────────────────+
|                      |
|                      |
+──────────────────────+
|                      |
| Memory mapping       |
| (grows ↓)            |
|                      |
+──────────────────────+
|                      |
|                      |
+──────────────────────+
|                      |
| Heap                 |
| (grows ↑)            |
|                      |
+──────────────────────+
|                      |
+──────────────────────+
|                      |
| BSS                  |
| (Uninitialized       |
|  global              |
|  or static data)     |
|                      |
+──────────────────────+ -----> 1 bytes separate
|                      |
| Data                 |
| (Initialized         |
|  global              |
|  or static data)     |
|                      |
+──────────────────────+
|                      |
| Text (Code)          |
|                      |
+──────────────────────+
|                      |
|                      |
|                      | Address 0
'──────────────────────'

```
![Linux Memory Visual](LinuxMemorySpace.txt)

Static array is on stack. Increment to get next item.

Dynamic array is not real. It is the free space that done by malloc. Indexing [] operator allow the increment based on datatype to access next element relatively based on the pointer to the array.

# A8

## Struct and Union padding
```c
struct as_struct {
  uint16_t l2b; // the lowest two bytes
  uint8_t n1b;  // the next one byte
  uint8_t h1b;  // the highest one byte
};
union as_union {
  uint16_t r2b; // reading two bytes
  uint32_t r4b; // reading four bytes
  uint8_t r1b;  // reading one byte
};
```
Memory diagram
```bash
                   (highest)                    (lowest)
As raw (four) bytes:   | 0xBE | 0xEF | 0xCA | 0xFE |

As `uint32_t`:         |------------ i ------------|

As `uint16_t`:         |-- ptr16[1] -|-- ptr16[0] -|

As `struct as_struct`: |- h1b-|- n1b-|---- l2b ----|

As `union as_union`:   |----------- r4b -----------|
                                     |---- r2b ----|
                                            |- r1b-|
```


## Default struct padding
Struct is default 4 bytes align
```c
#include <stdio.h>

struct align_example {
  char a;   // 1 byte
  int b;    // 4 bytes (requires 4-byte alignment)
  short c;  // 2 bytes (requires 2-byte alignemnt)
  double d; // 8 bytes (requires 8-byte alignment)
};

void align(void) {
  struct align_example ex = {'0', 0, 0, 0.1};

  printf("sizeof(char): %lu, sizeof(int): %lu, sizeof(short): %lu, "
         "sizeof(double): %lu\n",
         sizeof(char), sizeof(int), sizeof(short), sizeof(double));
  printf("ex.a address: %p\nex.b address: %p\nex.c address: %p\nex.d address: "
         "%p\n",
         (void *)&ex.a, (void *)&ex.b, (void *)&ex.c, (void *)&ex.d);
  printf("sizeof(struct align_example): %lu\n", sizeof(struct align_example));
}

int main(void) { align(); }
```
Output:
``` bash
    sizeof(char): 1, sizeof(int): 4, sizeof(short): 2, sizeof(double): 8
    ex.a address: 0xfffffa151cd0
    ex.b address: 0xfffffa151cd4
    ex.c address: 0xfffffa151cd8
    ex.d address: 0xfffffa151ce0
    sizeof(struct align_example): 24
```

## Add pragma(push, 1) padding
Align 1 bytes instead of 4 bytes by default.
``` c
#pragma pack(push, 1) // Push current packing setting and set packing to 1 byte alignment
struct pack_example {
  char a;   // 1 byte
  int b;    // 4 bytes (no padding now)
  short c;  // 2 bytes
  double d; // 8 bytes (no padding now)
};
#pragma pack(pop) // Restore previous packing setting

void pack(void) {
  struct pack_example ex = {'0', 0, 0, 0.1};

  printf("ex.a address: %p\nex.b address: %p\nex.c address: %p\nex.d address: "
         "%p\n",
         (void *)&ex.a, (void *)&ex.b, (void *)&ex.c, (void *)&ex.d);
  printf("sizeof(struct pack_example): %lu\n", sizeof(struct pack_example));
}
```
Output:
```bash
    ex.a address: 0xffffe25bbc60
    ex.b address: 0xffffe25bbc61
    ex.c address: 0xffffe25bbc65
    ex.d address: 0xffffe25bbc67
    sizeof(struct pack_example): 15
```

# A9
fork() make exact copy of current state of the execution

# Scheduling
## First Come, First Served (FCFS)

* Run in the order of arrival.
* Non-preemptive
* Example
    * P1 takes 24 time units. P2: 3. P3: 3.
    * Suppose 3 processes arrive around the same time but gets added to the ready queue in the order
      of P1, P2, P3.
    * What is the waiting time?
        * P1 = 0; P2  = 24; P3 = 27
    * What is the average waiting time?
        * (0 + 24 + 27) / 3 = 17
    * Calculating the waiting time and the average waiting time evaluates your understanding.
    * Drawing a diagram like the following is a good idea to understand various scheduling
      algorithms.

      ```bash
      +------------------+
      | P1     | P2 | P3 |
      +------------------+
      0        24   27   30
      ```
* Problem?
    * A long process can sabotage all other processes.
  
## Shortest Job First (SJF)

* Let's try something where a long process doesn't sabotage all other processes.
* Among the remaining processes, pick the process with the shortest execution time.
* Assume for the sake of discussion, we know how long each process takes.
* Non-preemptive
* Example
    * Execution times
        * P1: 7, P2: 4, P3: 1, P4: 4
    * Arrival times
        * P1: 0, P2: 2, P3: 4, P4: 5
    * Steps
        * (Draw a timeline diagram yourself to better understand the steps.)
        * P1 runs until time 7.
        * P3 is the shorted job, so P3 runs next until it's done (time 8).
        * P2 and P4 are the next shorted jobs (tie). The scheduler can pick any one of them. Let's
          assume the scheduler picks P2. So P2 runs until it's done (time 12).
        * P4 is the next shorted job and runs until it's done (time 16).
    * Average waiting time?
        * (0 + 6 + 3 + 7) / 4  = 4

  ## Shortest Remaining Time First
  * Let's try something where a long process doesn't sabotage all other processes.
  * Among the remaining processes, pick the process with the shortest execution time.
  * Assume for the sake of discussion, we know how long each process takes.
  * Non-preemptive
  * Example
      * Execution times
          * P1: 7, P2: 4, P3: 1, P4: 4
      * Arrival times
          * P1: 0, P2: 2, P3: 4, P4: 5
      * Steps
          * (Draw a timeline diagram yourself to better understand the steps.)
          * P1 runs until time 7.
          * P3 is the shorted job, so P3 runs next until it's done (time 8).
          * P2 and P4 are the next shorted jobs (tie). The scheduler can pick any one of them. Let's
            assume the scheduler picks P2. So P2 runs until it's done (time 12).
          * P4 is the next shorted job and runs until it's done (time 16).
      * Average waiting time?
          * (0 + 6 + 3 + 7) / 4  = 4
  ## Round Robin

  ## Priority Scheduling (Same as heuristic)

  ## Multilevel Queue Scheduling

  ## Multilevel Feedback Queue Scheduling
    * Use multiple queues but move a process to lower priority queues if it takes too much CPU time.
    * Example

    ``` bash
  
          Q0
          +-------------+
      --> | quantum: 8  | --+
          +-------------+   |
                            |
      +---------------------+
      |
      |   Q1
      |   +-------------+
      +-> | quantum: 16 | --+
          +-------------+   |
                            |
      +---------------------+
      |
      |   Q2
      |   +-------------+
      +-> | FCFS        | -->
          +-------------+
    
    ```

      * Q0 and Q1 use RR. Q2 uses FCFS.
      * `Process A` enters Q0, and gets 8 ms (RR).
      * If it does not finish, move it to Q1.
      * Run all other processes in Q0.
      * When there is no more processes left in Q0, run processes in Q1 (e.g., `Process A`).
      * `Process A` gets 16 ms (RR).
      * If `Process A` is still not done, move it to Q2.
      * Run all other processes in Q0 and Q1.
      * When there is no more processes left in Q0 and Q1, run processes in Q2 (e.g., `Process A`).
      * Run `Process A` until it's done (FCFS).
      * This is one example, and one can use other scheduling algorithms for the queues. The key is
        lowering priority by moving to a lower priority queue if a process runs for too long. This is
        called process *aging*.
  





# Virtual Memory
  ## First In First Out
  ## Least Recent Used
  ## Second Chance 

* This algorithm is an approximation of LRU.
    * Each page has a reference bit (ref_bit), initially = 0
    * When a page is accessed, we set ref_bit to 1.
    * We maintain a moving pointer to the next (candidate) victim.
    * When choosing a page to replace, check ref_bit of victim:
        * If ref_bit == 0, replace it.
        * Else set ref_bit to 0.
            * Leave page in memory (give it another chance).
            * Move pointer to next page.
            * Repeat till a victim is found.

  ## Thrashing