#include <stdio.h>
#include <dirent.h>
#include <string.h>

int main() {
    char dir[1024];
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

    chdir(dir);
    strcat(dir, "/Data");
    d = opendir(dir);
    
    if (d == NULL) {
        printf("Unable to open folder: '%s' \n", dir);
        return 1;
    }

    int num_map_files = 0;
    
    while ((entry = readdir(d)) != NULL) {
        char filename[1024];
        strncpy(filename, entry->d_name, sizeof(filename));
        filename[sizeof(filename) - 1] = '\0'; // Ensure null-termination
        
        if (strcmp(filename, "Actors.rvdata2") == 0 ||
            strcmp(filename, "Animations.rvdata2") == 0 ||
            strcmp(filename, "Armors.rvdata2") == 0 ||
            strcmp(filename, "Classes.rvdata2") == 0 ||
            strcmp(filename, "CommonEvents.rvdata2") == 0 ||
            strcmp(filename, "Enemies.rvdata2") == 0 ||
            strcmp(filename, "Items.rvdata2") == 0 ||
            strcmp(filename, "MapInfos.rvdata2") == 0 ||
            strcmp(filename, "Skills.rvdata2") == 0) {
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
