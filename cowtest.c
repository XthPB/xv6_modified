#include "types.h"
#include "user.h"

int main() {
    printf(1, "Starting cowtest\n");

    // Allocate a shared memory region
    int *shared = (int *)sbrk(4096);
    *shared = 123;

    // Record initial free pages
    int initial_free = getNumFreePages();

    // Fork a child process
    int pid = fork();

    if (pid == 0) {
        // Child process
        printf(1, "Child process: free pages before modifying = %d\n", getNumFreePages());
        *shared = 456; // Trigger CoW
        printf(1, "Child process: modified shared value to %d\n", *shared);
        printf(1, "Child process: free pages after modifying = %d\n", getNumFreePages());
        exit();
    } else {
        // Parent process
        wait(); // Wait for child to exit
        printf(1, "Parent process: shared value after child exit = %d\n", *shared);

        // Record final free pages
        int final_free = getNumFreePages();
        printf(1, "Parent process: initial free pages = %d, final free pages = %d\n", initial_free, final_free);

        if (final_free != initial_free)
            printf(1, "Memory leak detected\n");
        else
            printf(1, "No memory leaks\n");
    }

    exit();
}
