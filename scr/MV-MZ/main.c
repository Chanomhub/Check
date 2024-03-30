#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>

#define MAX_PATH_LENGTH 1024

// Function to replace backslashes with forward slashes in a string
void replace_backslashes_with_slashes(char *str) {
    for (int i = 0; i < strlen(str); i++) {
        if (str[i] == '\\') {
            str[i] = '/';
        }
    }
}

// Function to create a JSON file and write initial contents
void create_json(const char *filename, const char *path) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error creating JSON file: %s\n", filename);
        return;
    }
    fprintf(file, "{\n \"dir\": [\n");
    fprintf(file, "  \"%s\"\n", path); // Write the initial path
    fprintf(file, " ],\n \"files\": [\n"); // Open the files array
    fclose(file);
}

void append_to_json(const char *filename, const char *file_path) {
    FILE *file = fopen(filename, "a");
    if (file == NULL) {
        printf("Error appending to JSON file: %s\n", filename);
        return;
    }

    // Check if the file is empty
    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    fseek(file, 0, SEEK_SET);
    int empty = (size <= 0);

    // Open the file for appending with comma if not empty
    fprintf(file, "%s", empty ? "" : ",\n"); // Use empty string for first file

    // Append the file path
    fprintf(file, "  \"%s\"", file_path);

    fclose(file);
}




// Function to scan files in a directory and append qualifying ones to a JSON file
void scan_directory_and_append_to_json(const char *dir, const char *json_filename) {
    DIR *d;
    struct dirent *entry;

    // Open JSON file to store all file paths
    create_json(json_filename, dir);

    // Start scanning files in the selected folder
    d = opendir(dir);
    if (d == NULL) {
        printf("Unable to open folder: '%s'\n", dir);
        return;
    }

    while ((entry = readdir(d)) != NULL) {
        char filename[MAX_PATH_LENGTH];
        strncpy(filename, entry->d_name, sizeof(filename) - 1);
        filename[sizeof(filename) - 1] = '\0'; // Ensure null termination

        // Check if the file meets the criteria to include in the JSON
        if ((strcmp(filename, "Armors.json") == 0 ||
             strcmp(filename, "States.json") == 0 ||
             strcmp(filename, "Enemies.json") == 0 ||
             strcmp(filename, "MapInfos.json") == 0 ||
             strcmp(filename, "Actors.json") == 0 ||
             strcmp(filename, "Classes.json") == 0 ||
             strcmp(filename, "Weapons.json") == 0 ||
             strcmp(filename, "Items.json") == 0 ||
             strcmp(filename, "Skills.json") == 0) ||
            (strlen(filename) >= 3 && strncmp(filename, "Map", 3) == 0)) {

            // Append file path to the existing JSON file
            char file_path[MAX_PATH_LENGTH];
            snprintf(file_path, sizeof(file_path), "%s/%s", dir, filename);
            append_to_json(json_filename, file_path);
        }
    }

    // Close the files array and the JSON object
    FILE *file = fopen(json_filename, "a");
    if (file == NULL) {
        printf("Error appending to JSON file: %s\n", json_filename);
        return;
    }
    fprintf(file, " ]\n}\n");
    fclose(file);

    closedir(d);
}

int main() {
    char dir[MAX_PATH_LENGTH];

    printf("Please specify the default folder location: ");
    fgets(dir, sizeof(dir), stdin);
    dir[strcspn(dir, "\n")] = '\0';

    // Replace backslashes with slashes in the directory path
    replace_backslashes_with_slashes(dir);

    // Try different subfolders if 'data' is not found
    const char *subfolders[] = {"data", "www/data"};
    int num_subfolders = sizeof(subfolders) / sizeof(subfolders[0]);
    int found = 0;
    for (int i = 0; i < num_subfolders; ++i) {
        char temp_path[MAX_PATH_LENGTH];
        snprintf(temp_path, sizeof(temp_path), "%s/%s", dir, subfolders[i]);
        DIR *temp_dir = opendir(temp_path);
        if (temp_dir != NULL) {
            closedir(temp_dir);
            strcat(dir, "/");
            strcat(dir, subfolders[i]);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Unable to find the default subfolder.\n");
        return 1;
    }

    // Scan directory and append qualifying file paths to JSON
    scan_directory_and_append_to_json(dir, "file_paths.json");

    return 0;
}
