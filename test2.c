// #include "types.h"
// #include "stat.h"
// #include "user.h"

// int i = 3;

// int main(void) {
//     int pid;

//     // Get the initial number of free pages for the parent
//     int numInitialFreePageParent = getNumFreePages();

//     pid = fork();
//     if (pid == 0) {
//         // Child process
//         int numInitialFreePageChild = getNumFreePages();

//         // Modify shared variable to trigger CoW
//         i = 4;

//         // Check the number of free pages after modification
//         int numFinalFreePageChild = getNumFreePages();
//         if ((numInitialFreePageChild - numFinalFreePageChild) > 0)
//             printf(1, "Child: Number of free pages decreased\n");
//         else
//             printf(1, "Child: Error: No decrease in number of free pages\n");

//         exit();
//     } else {
//         // Parent process
//         wait();

//         // Calculate the change in number of free pages after child process exits
//         printf(1, "Parent: Change in number of free pages after reaping child process: %d\n",getNumFreePages() - numInitialFreePageParent);

//         exit();
//     }
// }

#include "types.h"
#include "stat.h"
#include "user.h"

int i = 3;

int main(void) {
    int pid;

    // Get the initial number of free pages for the parent
    int numInitialFreePageParent = getNumFreePages();

    printf(1, "Parent: Initial free pages: %d\n", numInitialFreePageParent);

    pid = fork();
    if (pid == 0) {
        // Child process
        int numInitialFreePageChild = getNumFreePages();
        printf(1, "Child: Initial free pages: %d\n", numInitialFreePageChild);

        // Allocate additional memory
        int *array = (int*)sbrk(2 * 4096); // Allocate two additional pages
        array[0] = 42; // Access first new page
        array[1024] = 84; // Access second new page

        int numAfterAllocChild = getNumFreePages();
        printf(1, "Child: Free pages after allocating memory: %d\n", numAfterAllocChild);

        // Modify shared variable to trigger CoW
        i = 4;
        int numFinalFreePageChild = getNumFreePages();

        if ((numInitialFreePageChild - numFinalFreePageChild) > 0)
            printf(1, "Child: Number of free pages decreased after CoW\n");
        else
            printf(1, "Child: Error: No decrease in number of free pages after CoW\n");

        printf(1, "Child: Final free pages: %d\n", numFinalFreePageChild);
        exit();
    } else {
        // Parent process
        wait();

        // Check free pages after child exits
        int numFinalFreePageParent = getNumFreePages();
        printf(1, "Parent: Final free pages after child exit: %d\n", numFinalFreePageParent);

        printf(1, "Parent: Change in free pages after child exit: %d\n",
               numFinalFreePageParent - numInitialFreePageParent);

        exit();
    }
}
