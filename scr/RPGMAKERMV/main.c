#include <stdio.h>
#include <dirent.h>
#include <string.h>

int main() {
    char dir[1024];
    DIR *d;
    struct dirent *entry;

    printf("Pls specify the default folder location: ");
    fgets(dir, sizeof(dir), stdin);
    dir[strcspn(dir, "\n")] = '\0'; // Removing trailing newline if any

    for (int i = 0; i < strlen(dir); i++) {
        if (dir[i] == '\\') {
            dir[i] = '/';
        }
    }

    chdir(dir);
    strcat(dir, "/www/data");

    d = opendir(dir);
    if (d == NULL) {
        printf("Unable to open folder: '%s' \n", dir);
        return 1;
    }

    int num_map_files = 0;

    while ((entry = readdir(d)) != NULL) {
        char filename[1024];
        strncpy(filename, entry->d_name, sizeof(filename) - 1);
        filename[sizeof(filename) - 1] = '\0'; // Ensuring null termination

        if (strcmp(filename, "Armors.json") == 0 ||
            strcmp(filename, "States.json") == 0 ||
            strcmp(filename, "Enemies.json") == 0 ||
            strcmp(filename, "MapInfos.json") == 0 ||
            strcmp(filename, "Actors.json") == 0 ||
            strcmp(filename, "Classes.json") == 0 ||
            strcmp(filename, "Weapons.json") == 0 ||
            strcmp(filename, "Items.json") == 0 ||
            strcmp(filename, "Skills.json") == 0) {
            printf("found: '%s'\n", filename);
        }

        if (strlen(filename) >= 3 && strncmp(filename, "Map", 3) == 0) {
            num_map_files++;
            printf("found: '%s'\n", filename);
        }
    }

    closedir(d);

    return 0;
}
