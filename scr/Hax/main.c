#include <ctype.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "hex.h"


bool is_valid_filename(const char *filename) {
    if (strspn(filename, "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789._") != strlen(filename)) {
        return false;
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
  filename[strcspn(filename, "\n")] = 0;

  if (is_valid_filename(filename)) {
  bool found = search_in_exe(filename, data, sizeof(data));
  if (found) {
    printf("The data was found in the specified .exe program.\n");
  } else {
    printf("The data was not found in the specified .exe program.\n");
  }
  }

  return 0;
}
