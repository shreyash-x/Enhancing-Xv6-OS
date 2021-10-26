#include "kernel/param.h"
#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[])
{
    char *temp_args[MAXARG];

    if (argc < 3)
    {
        fprintf(2, "%s: Invalid Syntax\n", argv[0]);
        exit(1);
    }
    else
    {
        for (int i = 0; argv[1][i] != '\0'; i++)
        {
            if (argv[1][i] < '0' || argv[1][i] > '9')
            {
                fprintf(2, "%s: Invalid value for mask (%s) - Must be an integer\n", argv[0], argv[1]);
                exit(1);
            }
        }
    }

    if (trace(atoi(argv[1])) == -1)
    {
        fprintf(2, "%s: Some Error Occured\n", argv[0]);
    }

    int k = 0;
    for (int i = 2; i < argc && i < MAXARG; i++)
    {
        temp_args[k] = argv[i];
        k++;
    }

    exec(temp_args[0], temp_args);
    exit(0);
}