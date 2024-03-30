#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CHAR_PER_LINE 1000

int main() {
    FILE *fp;
    char line[MAX_CHAR_PER_LINE];
    char *filename = "file_paths.json";
    char *tmp_filename = "tmp_file_paths.json";

    // Open the original file
    fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Error: Unable to open file %s\n", filename);
        return 1;
    }

    // Open a temporary file for writing
    FILE *tmp_fp = fopen(tmp_filename, "w");
    if (tmp_fp == NULL) {
        printf("Error: Unable to open temporary file\n");
        fclose(fp);
        return 1;
    }

    // Read line by line and check for the correct format
    int is_files_section = 0; // Flag to indicate if we are in the "files" section
    while (fgets(line, MAX_CHAR_PER_LINE, fp) != NULL) {
        if (strstr(line, "\"files\"")) {
            is_files_section = 1; // Found "files" section
            fputs(line, tmp_fp); // Write the line to temporary file
            continue;
        }

        if (is_files_section) {
            // Check for lines after "files" section
            if (line[0] == ',') {
                // Found a line with only ","
                printf("Warning: Found a line with only ',' after \"files\" section. Ignoring.\n");
                continue; // Skip writing this line to temporary file
            } else {
                is_files_section = 0; // End of "files" section
            }
        }

        // Write the line to temporary file
        fputs(line, tmp_fp);
    }

    // Close both files
    fclose(fp);
    fclose(tmp_fp);

    // Remove the original file
    if (remove(filename) != 0) {
        printf("Error: Unable to delete the original file\n");
        return 1;
    }

    // Rename the temporary file to the original filename
    if (rename(tmp_filename, filename) != 0) {
        printf("Error: Unable to rename the temporary file\n");
        return 1;
    }

    printf("File formatting check and correction completed successfully.\n");

    return 0;
}
