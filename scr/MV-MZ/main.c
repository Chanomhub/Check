#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>

#define MAX_PATH_LENGTH 1024

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
    fprintf(file, "  \"%s\",\n", file_path); // Append the file path to the files array
    fclose(file);
}

int main() {
    char dir[MAX_PATH_LENGTH];
    DIR *d;
    struct dirent *entry;

    printf("Please specify the default folder location: ");
    fgets(dir, sizeof(dir), stdin);
    dir[strcspn(dir, "\n")] = '\0';

    for (int i = 0; i < strlen(dir); i++) {
        if (dir[i] == '\\') {
            dir[i] = '/';
        }
    }

    // Open JSON file to store all file paths
    create_json("file_paths.json", dir);

    // Try different subfolders if 'data' is not found
    const char *subfolders[] = {"data", "www/data"};
    int num_subfolders = sizeof(subfolders) / sizeof(subfolders[0]);
    int found = 0;
    for (int i = 0; i < num_subfolders; ++i) {
        char temp_path[MAX_PATH_LENGTH];
        snprintf(temp_path, sizeof(temp_path), "%s/%s", dir, subfolders[i]);
        if ((d = opendir(temp_path)) != NULL) {
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

    // Start scanning files in the selected folder
    d = opendir(dir);
    if (d == NULL) {
        printf("Unable to open folder: '%s'\n", dir);
        return 1;
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
            append_to_json("file_paths.json", file_path);
        }
    }

    // Close the files array and the JSON object
    FILE *file = fopen("file_paths.json", "a");
    if (file == NULL) {
        printf("Error appending to JSON file: file_paths.json\n");
        return 1;
    }
    fprintf(file, " ]\n}\n");
    fclose(file);

    closedir(d);

    return 0;
}

