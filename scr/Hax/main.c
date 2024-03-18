#include <stdio.h>
#include <ctype.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "hex.h"

bool is_valid_filename(const char *filename) {
    for (int i = 0; filename[i] != '\0'; i++) {
        if (!isalnum(filename[i]) && filename[i] != '.' && filename[i] != '_') {
            return false;
        }
    }
    return true;
}

bool search_in_exe(const char *filename, const uint8_t *search_data, size_t search_data_size) {
    FILE *file = fopen(filename, "rb");
    if (!file) {
        printf("Failed to open file: %s\n", filename);
        return false;
    }

    uint8_t *buffer = malloc(search_data_size);
    if (!buffer) {
        printf("Memory allocation failed.\n");
        fclose(file);
        return false;
    }

    bool found = false;

    while (!feof(file)) {
        if (fread(buffer, 1, search_data_size, file) == search_data_size && memcmp(buffer, search_data, search_data_size) == 0) {
            found = true;
            break;
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
    filename[strcspn(filename, "\n")] = 0; 

    if (!is_valid_filename(filename)) {
        printf("Invalid filename.\n");
        return 1; 
    }

    FILE *file = fopen(filename, "rb");
    if (!file) {
        printf("Failed to open file: %s\n", filename);
        return 1; 
    }

    bool found = search_in_exe(filename, data, sizeof(data));

    fclose(file); // Always close the file

    printf("The data was %s in the specified .exe program.\n", found ? "found" : "not found");

    return 0;
}