#include <stdio.h>
#include <stdlib.h>

int main(void) {

    // PART 1: CREATE INVENTORY
    printf("PART 1: CREATE INVENTORY\n");

    int inventory_size = 3;

    int *item_ids = malloc(inventory_size * sizeof(int));
    int *item_quantities = malloc(inventory_size * sizeof(int));

    if (item_ids == NULL || item_quantities == NULL) {
        printf("Memory allocation failed.\n");
        free(item_ids);
        free(item_quantities);
        return 1;
    }

    item_ids[0] = 101;
    item_ids[1] = 102;
    item_ids[2] = 103;

    item_quantities[0] = 2;
    item_quantities[1] = 5;
    item_quantities[2] = 1;

    for (int i = 0; i < inventory_size; i++) {
        printf("Item ID: %d, Quantity: %d\n",
               item_ids[i], item_quantities[i]);
    }


    // PART 2: EXPAND INVENTORY
    printf("\nPART 2: EXPAND INVENTORY\n");

    int new_size = 5;

    int *temp_ids = realloc(item_ids, new_size * sizeof(int));
    if (temp_ids == NULL) {
        printf("Could not expand item IDs.\n");
        free(item_ids);
        free(item_quantities);
        return 1;
    }
    item_ids = temp_ids;

    int *temp_quantities = realloc(
        item_quantities,
        new_size * sizeof(int)
    );

    if (temp_quantities == NULL) {
        printf("Could not expand quantities.\n");
        free(item_ids);
        free(item_quantities);
        return 1;
    }
    item_quantities = temp_quantities;

    inventory_size = new_size;

    item_ids[3] = 104;
    item_ids[4] = 105;

    item_quantities[3] = 4;
    item_quantities[4] = 3;

    for (int i = 0; i < inventory_size; i++) {
        printf("Item ID: %d, Quantity: %d\n",
               item_ids[i], item_quantities[i]);
    }


    // PART 3: FIX MEMORY LEAKS
    printf("\nPART 3: FIX MEMORY LEAKS\n");

    free(item_ids);
    free(item_quantities);

    printf("Inventory memory has been freed.\n");


    // PART 4: SAFE POINTER HANDLING
    printf("\nPART 4: SAFE POINTER HANDLING\n");

    item_ids = NULL;
    item_quantities = NULL;

    if (item_ids != NULL) {
        printf("Item ID pointer is still valid.\n");
    } else {
        printf("Item ID pointer is NULL and will not be used.\n");
    }

    if (item_quantities != NULL) {
        printf("Quantity pointer is still valid.\n");
    } else {
        printf("Quantity pointer is NULL and will not be used.\n");
    }

    printf("Program completed safely.\n");

    return 0;
}