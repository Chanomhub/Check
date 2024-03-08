#include <stdio.h>
#include <dirent.h>
#include <string.h>

int main() {
  char dir[1024];
  DIR *d;
  struct dirent *entry;

  printf("Pls specify the default folder location: ");
  scanf("%s", dir);

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
    strcpy(filename, entry->d_name);

    if (strcmp(filename, "Armors.json") == 0 ||
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

  printf("Found %d map files\n", num_map_files);

  closedir(d);

  return 0;
}
