#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_JSON_SIZE 10000 // ปรับขนาดตามความต้องการ

// ฟังก์ชันแทนคำว่า "null" ด้วยเลข 0
void replaceNullWithZero(char *json) {
    char *pos = json;
    while ((pos = strstr(pos, "\"null\"")) != NULL) {
        memcpy(pos, "0", 1);
        pos += 1;
    }
}

// ฟังก์ชันเพิ่มคำว่า "null" ใส่คำที่สอง
void addNullAtSecondPosition(char *json) {
    int countBrackets = 0;
    char *pos = json;

    while (*pos != '\0') {
        if (*pos == '[') {
            countBrackets++;
            if (countBrackets == 2) {
                int len = strlen(json);
                memmove(pos + 6, pos, len - (pos - json) + 1);
                memcpy(pos, "null,", 5);
                break;
            }
        }
        pos++;
    }
}

int main() {
    FILE *file;
    char json[MAX_JSON_SIZE];

    // อ่าน file_paths.json เพื่อดึงเส้นทางไฟล์
    FILE *file_paths_file = fopen("file_paths.json", "r");
    if (file_paths_file == NULL) {
        printf("ไม่สามารถเปิดไฟล์ file_paths.json\n");
        return 1;
    }

    char file_paths_json[MAX_JSON_SIZE];
    fgets(file_paths_json, MAX_JSON_SIZE, file_paths_file);
    fclose(file_paths_file);

    // Parse file_paths.json เพื่อดึงเส้นทางไฟล์
    char *file_path = strtok(file_paths_json, "\":,[ ]\n\t\r");
    while (file_path != NULL) {
        if (strstr(file_path, ".json") != NULL) {
            // อ่าน JSON จากไฟล์
            file = fopen(file_path, "r");
            if (file == NULL) {
                printf("ไม่สามารถเปิดไฟล์ %s\n", file_path);
                return 1;
            }

            fgets(json, MAX_JSON_SIZE, file);
            fclose(file);

            // แทนคำว่า "null" ด้วยเลข 0
            replaceNullWithZero(json);

            // เพิ่มคำว่า "null" ใส่คำที่สอง
            addNullAtSecondPosition(json);

            // พิมพ์ JSON หลังจากการแก้ไข
            printf("%s\n", json);
        }
        file_path = strtok(NULL, "\":,[ ]\n\t\r");
    }

    return 0;
}
