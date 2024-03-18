#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "hex.h"

bool search_in_exe(const char *filename, const uint8_t *search_data, size_t search_data_size) {
    FILE *file = fopen(filename, "rb");
    if (!file) {
        printf("Failed to open file: %s\n", filename);
        return false;
    }

    uint8_t *buffer = (uint8_t *)malloc(search_data_size);
    if (!buffer) {
        printf("Memory allocation failed.\n");
        fclose(file);
        return false;
    }

    bool found = false;

    while (!feof(file)) {
        if (fread(buffer, 1, search_data_size, file) == search_data_size) {
            if (memcmp(buffer, search_data, search_data_size) == 0) {
                found = true;
                break;
            }
        }
    }

    fclose(file);
    free(buffer);
    return found;
}

int main() {
    char filename[100];
    printf("Enter the filename of the .exe program: ");
    fgets(filename, sizeof(filename), stdin);
    filename[strcspn(filename, "\n")] = 0; // Removing newline character

    bool found = search_in_exe(filename, data, sizeof(data));
    if (found) {
        printf("The data was found in the specified .exe program.\n");
    } else {
        printf("The data was not found in the specified .exe program.\n");
    }

    return 0;
}
