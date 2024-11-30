#include "types.h"
#include "stat.h"
#include "user.h"

int main(int argc, char *argv[])
{
    int vpages = numvp(); // Call to system call
    printf(1, "Number of virtual pages: %d\n", vpages);
    exit();
}
