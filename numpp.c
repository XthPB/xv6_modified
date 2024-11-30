#include "types.h"
#include "stat.h"
#include "user.h"

int main(int argc, char *argv[])
{
    int ppages = numpp(); // Call to system call
    printf(1, "Number of physical pages: %d\n", ppages);
    exit();
}
