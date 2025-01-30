#include <stdio.h>
#include <string.h>
#include "config.h"
#include "youtube_summarizer.h"
#include <windows.h>



void summarize_youtube_video(char *username) {
    char url[200];
    printf("\nEnter YouTube video URL: ");
    scanf(" %199[^\n]", url);
   
    
    printf("\nGenerating Summary for Youtube Video'%s'...\n", url);
    
    
    char cmd[512];
    snprintf(cmd, sizeof(cmd), "python api_handler.py \"%s\" youtube_summary", url);

    FILE *fp = _popen(cmd, "r");
    if (!fp) {
        printf("Error generating summary\n");
        return;
    }

    char buffer[4096];
    char md_filename[100] = "";
    char pdf_filename[100] = "";

    while (fgets(buffer, sizeof(buffer), fp)) {
        if (strncmp(buffer, "MARKDOWN:", 9) == 0) {
            strncpy(md_filename, buffer + 9, sizeof(md_filename));
            md_filename[strcspn(md_filename, "\n")] = 0;
        }
        else if (strncmp(buffer, "PDF:", 4) == 0) {
            strncpy(pdf_filename, buffer + 4, sizeof(pdf_filename));
            pdf_filename[strcspn(pdf_filename, "\n")] = 0;
        }
        else {
            printf("%s", buffer);
        }
    }
    _pclose(fp);

    if (md_filename[0] && pdf_filename[0]) {
        printf("\nFiles saved:\n");
        printf("Markdown: %s\n", md_filename);
        printf("PDF: %s\n", pdf_filename);
    }
}