#include <stdio.h>
#include <string.h>
#include "config.h"
#include "mindmap_generator.h"
#include "utils.h"
#include <windows.h>

void create_mindmap(char *username) {
    char topic[200];
    printf("\nEnter topic for mind map: ");
    scanf(" %199[^\n]", topic);
   
    printf("\nGenerating Mind Map for '%s'...\n", topic);
    
    char cmd[512];
    snprintf(cmd, sizeof(cmd), "python api_handler.py \"%s\" mindmap", topic);

    FILE *fp = _popen(cmd, "r");
    if (!fp) {
        printf("Error generating mind map\n");
        return;
    }

    char buffer[4096];
    char mindmap_file[256] = "";
    int error_occurred = 0;

    while (fgets(buffer, sizeof(buffer), fp)) {
        if (strncmp(buffer, "Error:", 6) == 0) {
            setColor(12); // Red
            printf("\n%s", buffer);
            setColor(7); // White
            error_occurred = 1;
            break;
        }
        
        if (strncmp(buffer, "MINDMAP:", 8) == 0) {
            strncpy(mindmap_file, buffer + 8, sizeof(mindmap_file));
            mindmap_file[strcspn(mindmap_file, "\n")] = 0;
        } else {
            printf("%s", buffer);
        }
    }
    _pclose(fp);

    if (!error_occurred && mindmap_file[0]) {
        setColor(10); // Green
        printf("\nMind map saved as: %s\n", mindmap_file);
        setColor(7); // White
    }
}