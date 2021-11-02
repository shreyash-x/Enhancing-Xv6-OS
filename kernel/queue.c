#include "types.h"
#include "param.h"
#include "memlayout.h"
#include "riscv.h"
#include "spinlock.h"
#include "proc.h"
#include "defs.h"

void enqueue(struct queue *q, struct proc *p)
{
    if (q->size == NPROC)
    {
        panic("Maximum process limit attained");
    }

    q->q_array[q->end] = p;
    q->end = (q->end + 1) % (NPROC + 1);
    q->size++;
    // printf("added\n");
}

void dequeue(struct queue *q)
{
    if (q->size == 0)
    {
        panic("Empty queue");
    }

    // q->q_array[q->start] = 0;
    q->start = (q->start + 1) % (NPROC + 1);
    q->size--;
    // printf("removed\n");
}

void delete (struct queue *q, int pid)
{
    int i;
    struct proc *temp;
    for (i = q->start; i != q->end; i = (i + 1) % (NPROC + 1))
    {
        // if (q->q_array[i] == 0)
        // {
        //     continue;
        // }
        if (q->q_array[i]->pid == pid)
        {
            temp = q->q_array[i];
            q->q_array[i] = q->q_array[(q->start + 1) % (NPROC + 1)];
            q->q_array[(q->start + 1) % (NPROC + 1)] = temp;
            // break;
        }
    }
    q->end = (q->end - 1 + (NPROC + 1)) % (NPROC + 1);
    q->size--;
}

struct proc *get_start(struct queue *q)
{
    if (q->start == q->end)
    {
        return 0;
    }
    return q->q_array[q->start];
}