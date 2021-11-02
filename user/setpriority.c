#include "kernel/param.h"
#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[])
{

    if (argc != 3)
    {
        fprintf(1, "%s: Invalid Syntax\n", argv[0]);
        exit(1);
    }
    else
    {
        int new_priority = atoi(argv[1]);
        int pid = atoi(argv[2]);

        int prev_priority = set_priority(new_priority, pid);

        if (prev_priority == -1)
        {
            fprintf(1, "%s: Invalid Syntax, check values of new priority and pid\n", argv[0]);
            exit(1);
        }
        else
        {
            // fprintf(1, "Old priority: %d\n", prev_priority);
        }
    }
    exit(0);
}
