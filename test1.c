// #include "types.h"
// #include "stat.h"
// #include "user.h"

// int main(void)
// {
//     int numFreePagesInitial = getNumFreePages(); // Get the initial number of free pages
//     int numVirtPagesInitial = numvp();    // Get the initial number of virtual pages
//     int numPhysPagesInitial = numpp();    // Get the initial number of physical pages

//     printf(1, "Initial: Free Pages=%d, Virtual Pages=%d, Physical Pages=%d\n",
//            numFreePagesInitial, numVirtPagesInitial, numPhysPagesInitial);

//     // Allocate a page
//     sbrk(4096);

//     int numFreePagesFinal = getNumFreePages();  // Get the final number of free pages
//     int numVirtPagesFinal = numvp();      // Get the final number of virtual pages
//     int numPhysPagesFinal = numpp();      // Get the final number of physical pages

//     printf(1, "Final: Free Pages=%d, Virtual Pages=%d, Physical Pages=%d\n",
//            numFreePagesFinal, numVirtPagesFinal, numPhysPagesFinal);

//     exit();
// }

#include "types.h"
#include "stat.h"
#include "user.h"

int main(void) {
    // Initial counts
    printf(1, "Initial: Free=%d, Virt=%d, Phys=%d\n", getNumFreePages(), numvp(), numpp());

    // Test sbrk
    sbrk(4096);
    printf(1, "After sbrk: Free=%d, Virt=%d, Phys=%d\n", getNumFreePages(), numvp(), numpp());

    // Test mmap
    char *mmap_region = (char*)mmap(4096);
    printf(1, "After mmap: Free=%d, Virt=%d, Phys=%d\n", getNumFreePages(), numvp(), numpp());

    // Access mmap'd memory
    mmap_region[0] = 'x';
    printf(1, "After mmap access: Free=%d, Virt=%d, Phys=%d\n", getNumFreePages(), numvp(), numpp());

    exit();
}
