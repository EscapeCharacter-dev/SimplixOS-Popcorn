#include "shell_unix.h"

static void echo(const char* message)
{
    printk(message);
}

int system(const char* command)
{

}
