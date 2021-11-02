# Assignment 4 : Modifying XV6-riscv

## Features Added:

---

### 1. Tracing

---

-   For this we implemented a syscall trace and a user program strace.
-   It intercepts and records the system calls which are called by a process during its execution.

```sh
strace mask command [args]
```

### 2. Scheduling

---

Each scheduler has its own part in scheduler function and the trap funciton.

### FCFS

-   First come first serve scheduling
-   Process creation time stored in proc.c/allocproc()
-   We check and compare the creation time in scheduler function and schedule the process accordingly
-   Yielding is disabled for the timer interrupt in trap function.

```sh
make qemu SCHEDULER=FCFS
```

### PBS

-   Priority Based Scheduling
-   Static priority alloted as 60 and niceness as 5 in proc.c/allocproc()
-   Sleep time calculated by making changes in sleep and wakeup functions when state chages to and from SLEEP respectively.
-   Scheduler function checks the conditions and sets dynamic priority according to formula and then selects process to be scheduled.

```sh
make qemu SCHEDULER=PBS
```

### MLFQ

-   Multi-Level Feedback Queue Scheduling
-   Initially each process is added to queue level 0 and according to its time slice it is shifted to required queue level
-   Ageging is added to prevent starvation.
-   Scheduling based on Round-Robin

```sh
make qemu SCHEDULER=MLFQ
```

### 3. Procdump

---

-   Modified procdump() in kernel/proc.c to display various values for MLFQ and PBS scheduling when ctrl+p is pressed.
-   MLFQ : PID Priority State rtime wtime nrun q0 q1 q2 q3 q4
-   PBS : PID Priority State rtime wtime nrun

where:

-   rtime: Total ticks for which the process ran on the CPU till now.
-   wtime: This corresponds to the total waiting time for the process. However,
    In the case of the MLFQ scheduler, this is the wait time in the current
    queue.
-   nrun: Number of times the process was picked by the scheduler.
-   q0,q1,q2,q3,q4: Number of ticks the process has spent in each of the 5
    queues.

## Testing

---

On running `schedulertest` we obtain following results:

### ROUND ROBIN

-   wtime = 200
-   rtime = 25

### FCFS

-   wtime = 236
-   rtime = 53

### PBS

-   wtime = 153
-   rtime = 26

### MLFQ

-   wtime = 303
-   rtime = 29

### Explain in the README how could this be exploited by a process

The programmer can take use of MLFQ by adding a tiny I/O burst with a frequency lower than the queue's time slice. This will result in the process being removed from the queue and then re-added to the same queue with highest priority. As a result, that procedure will be placed in the same queue over and over again, and it will be completed with the highest priority ( in queue 0 ).
