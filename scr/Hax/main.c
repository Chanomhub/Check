#include <stdio.h>
#include <ctype.h> 
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include "hex.h"  // Assuming 'data' is defined here

bool is_valid_filename(const char *filename) {
    while (*filename) { 
        if (!isalnum(*filename) && *filename != '.' && *filename != '_') {
            return false;
        }
        filename++;
    }
    return true; 
}

bool search_in_exe(const char *filename, const uint8_t *data, size_t data_size) {
    FILE *file = fopen(filename, "rb");
    if (!file) {
        fprintf(stderr, "Failed to open file: %s\n", filename);
        return false; 
    }

    uint8_t *buffer = malloc(data_size);
    if (!buffer) {
        fprintf(stderr, "Memory allocation failed.\n");
        fclose(file);
        return false;
    }

    while (fread(buffer, 1, data_size, file) == data_size) {
        if (memcmp(buffer, data, data_size) == 0) {
            fclose(file);
            free(buffer);
            return true; 
        }
    }

    fclose(file);
    free(buffer);
    return false; 
}

int main() {
    char filename[100];

    printf("Enter the filename of the .exe program: ");
    if (fgets(filename, sizeof(filename), stdin)) {
        filename[strcspn(filename, "\n")] = 0; // Remove newline

        if (is_valid_filename(filename) && search_in_exe(filename, data, sizeof(data))) {
            printf("The data was found in the specified .exe program.\n");
        } else {
            printf("The data was not found or filename is invalid.\n");
        }
    }

    return 0; 
}
