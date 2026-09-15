/*
 * Memory Manager Assignment
 * Computer Science XII - Computer Systems
 *
 * This program implements a dynamic game inventory system to practice
 * manual memory management using malloc, calloc, realloc, and free.
 *
 * You'll experience memory leaks and dangling pointers firsthand,
 * then systematically fix each error.
 */

#include <stdio.h>
#include <stdlib.h>

// =============================================================================
// PART 1: CREATE INVENTORY
// =============================================================================
// Build a basic inventory system that stores item IDs and quantities.
// Use malloc to allocate memory for arrays that will hold this data.
void create_inventory() {
    printf("\n=== PART 1: CREATE INVENTORY ===\n");

    int inventory_size = 5;
    int *item_ids = NULL;
    int *quantities = NULL;

    // Allocate memory for item IDs.
    item_ids = malloc(inventory_size * sizeof(int));

    // Check whether allocation succeeded.
    if (item_ids == NULL) {
        printf("Failed to allocate item_ids\n");
        return;
    }

    // Allocate memory for quantities.
    quantities = malloc(inventory_size * sizeof(int));

    // Check whether allocation succeeded.
    if (quantities == NULL) {
        printf("Failed to allocate quantities\n");
        free(item_ids);
        return;
    }

    // Fill the inventory with starting items.
    printf("Starting inventory:\n");
    for (int i = 0; i < inventory_size; i++) {
        item_ids[i] = 100 + i;
        quantities[i] = (i + 1) * 10;
        printf("  Item %d: quantity %d\n", item_ids[i], quantities[i]);
    }

    // Free both dynamically allocated arrays.
    free(item_ids);
    free(quantities);

    printf("Memory freed successfully.\n");
}

// =============================================================================
// PART 2: EXPAND INVENTORY
// =============================================================================
// Demonstrate dynamic growth using realloc when the player acquires new items
// than the initial inventory can hold.
void expand_inventory() {
    printf("\n=== PART 2: EXPAND INVENTORY ===\n");

    int initial_size = 3;
    int expanded_size = 6;
    int *item_ids = NULL;
    int *quantities = NULL;

    // Allocate the initial arrays.
    item_ids = malloc(initial_size * sizeof(int));

    if (item_ids == NULL) {
        printf("Failed to allocate item_ids\n");
        return;
    }

    quantities = malloc(initial_size * sizeof(int));

    if (quantities == NULL) {
        printf("Failed to allocate quantities\n");
        free(item_ids);
        return;
    }

    // Fill initial inventory.
    printf("Initial inventory (size %d):\n", initial_size);
    for (int i = 0; i < initial_size; i++) {
        item_ids[i] = 200 + i;
        quantities[i] = 5 * (i + 1);
        printf("  Item %d: quantity %d\n", item_ids[i], quantities[i]);
    }

    printf("\nPlayer acquires more items! Expanding inventory...\n");

    // Use temporary pointers so a failed realloc does not lose the
    // original allocation.
    int *new_item_ids = realloc(item_ids, expanded_size * sizeof(int));

    if (new_item_ids == NULL) {
        printf("Failed to expand item_ids\n");
        free(item_ids);
        free(quantities);
        return;
    }
    item_ids = new_item_ids;

    int *new_quantities = realloc(quantities, expanded_size * sizeof(int));

    if (new_quantities == NULL) {
        printf("Failed to expand quantities\n");
        free(item_ids);
        free(quantities);
        return;
    }
    quantities = new_quantities;

    // Add new items to expanded inventory.
    for (int i = initial_size; i < expanded_size; i++) {
        item_ids[i] = 200 + i;
        quantities[i] = 5 * (i + 1);
    }

    // Print full expanded inventory.
    printf("Expanded inventory (size %d):\n", expanded_size);
    for (int i = 0; i < expanded_size; i++) {
        printf("  Item %d: quantity %d\n", item_ids[i], quantities[i]);
    }

    // Free both expanded arrays.
    free(item_ids);
    free(quantities);

    printf("Memory freed successfully.\n");
}

// =============================================================================
// PART 3: MEMORY LEAK DEMONSTRATION
// =============================================================================
// This function demonstrates a memory leak by allocating memory without freeing it.
// Run this version first to see what happens when memory is never freed.
void memory_leak_demo() {
    printf("\n=== PART 3A: MEMORY LEAK DEMONSTRATION ===\n");
    printf("Allocating memory in a loop WITHOUT freeing...\n");

    for (int i = 0; i < 1000; i++) {
        // Allocate memory for a temporary item.
        int *temp_item = (int*)malloc(1000 * sizeof(int));

        if (temp_item == NULL) {
            printf("Allocation failed at iteration %d!\n", i);
            return;
        }

        // Use the memory.
        temp_item[0] = 300 + i;

        // NO FREE - Memory is intentionally leaked for demonstration.
        // Each iteration leaks 4000 bytes on a typical 4-byte-int system.
    }

    printf("Loop complete. Leaked approximately %zu KB of memory.\n",
           (1000 * 1000 * sizeof(int)) / 1024);
    printf("This memory cannot be reused until the program ends.\n");
}

// =============================================================================
// PART 3B: FIXED VERSION - NO MEMORY LEAK
// =============================================================================
// This function properly frees memory after each allocation.
// Compare the behavior of this version to the leaking version above.
void memory_leak_fixed() {
    printf("\n=== PART 3B: FIXED VERSION - NO MEMORY LEAK ===\n");
    printf("Allocating memory in a loop WITH proper freeing...\n");

    for (int i = 0; i < 1000; i++) {
        // Allocate memory for a temporary item.
        int *temp_item = (int*)malloc(1000 * sizeof(int));

        if (temp_item == NULL) {
            printf("Allocation failed at iteration %d!\n", i);
            return;
        }

        // Use the memory.
        temp_item[0] = 300 + i;

        // Free the memory after it is no longer needed.
        free(temp_item);
    }

    printf("Loop complete. Memory properly freed after each use.\n");
    printf("Total memory allocated and freed: %zu KB\n",
           (1000 * 1000 * sizeof(int)) / 1024);
}

// =============================================================================
// PART 4: SAFE POINTER HANDLING
// =============================================================================
// This function demonstrates dangling pointer issues and how to handle
// pointers safely after freeing memory.
void safe_pointer_handling() {
    printf("\n=== PART 4: SAFE POINTER HANDLING ===\n");

    // Allocate memory for player health.
    int *player_health = (int*)malloc(sizeof(int));

    if (player_health == NULL) {
        printf("Allocation failed!\n");
        return;
    }

    *player_health = 100;
    printf("Player health: %d\n", *player_health);

    // Free the memory.
    free(player_health);
    printf("Health memory freed.\n");

    // Set the freed pointer to NULL so it cannot accidentally
    // be used as a dangling pointer.
    player_health = NULL;

    // Check the pointer before dereferencing it.
    if (player_health != NULL) {
        printf("Player health: %d\n", *player_health);
    } else {
        printf("Health data not available\n");
    }

    printf("Safe pointer handling complete.\n");
}

// =============================================================================
// MAIN FUNCTION
// =============================================================================
int main() {
    printf("=============================================================\n");
    printf("      MEMORY MANAGER: Dynamic Inventory System\n");
    printf("=============================================================\n");

    // Part 1: Basic memory allocation with malloc.
    create_inventory();

    // Part 2: Dynamic growth with realloc.
    expand_inventory();

    // Part 3: Memory leak demonstration and fix.
    printf("\n--- First, observe the memory leak ---\n");
    memory_leak_demo();

    printf("\n--- Now, see the properly managed version ---\n");
    memory_leak_fixed();

    // Part 4: Handle pointers safely after freeing.
    safe_pointer_handling();

    printf("\n=============================================================\n");
    printf("Memory management complete!\n");
    printf("Review your code for proper malloc/free pairing and NULL checks.\n");
    printf("=============================================================\n");

    return 0;
}
