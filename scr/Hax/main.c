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

// Function to sanitize file path by removing invalid characters
void sanitize_filepath(char *path) {
    int i, j = 0;
    char sanitized[100]; // Assuming maximum path length of 100 characters
    
    for (i = 0; path[i] != '\0'; i++) {
        if (isalnum(path[i]) || path[i] == '.' || path[i] == '/' || path[i] == '_' || path[i] == '-') {
            sanitized[j++] = path[i];
        }
    }
    sanitized[j] = '\0';
    
    strcpy(path, sanitized);
}

int main() {
    char filename[100];
    printf("Enter the filename of the .exe program: ");
    fgets(filename, sizeof(filename), stdin);
    filename[strcspn(filename, "\n")] = 0; // Removing newline character
    
    // Sanitize file path
    sanitize_filepath(filename);

    bool found = search_in_exe(filename, data, sizeof(data));
    if (found) {
        printf("The data was found in the specified .exe program.\n");
    } else {
        printf("The data was not found in the specified .exe program.\n");
    }

    return 0;
}
