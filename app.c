#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include "config.h"
#include "auth.h"
#include "youtube_summarizer.h" 
#include "mindmap_generator.h"

char username[50];


void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void clearScreen() {
    system("cls");
}

void printBanner() {
    setColor(10); // Bright Green
    printf("\n");
    printf("    +==========================================+\n");
    printf("    |              StudyBuddyyy 📚          |\n");
    printf("    |        Your Personal Study Companion    |\n");
    printf("    +==========================================+\n\n");
    setColor(7); // White
}

void printAuthMenu() {
    setColor(14); // Yellow
    printf("\n    ╔════════════ Authentication ═════════════╗\n");
        printf("    ║                                         ║\n");
        printf("    ║  1. Login                              ║\n");
        printf("    ║  2. Register                           ║\n");
        printf("    ║  3. Exit                               ║\n");
        printf("    ║                                         ║\n");
        printf("    ╚═════════════════════════════════════════╝\n");
    setColor(7); // White
}
void printMenu(char *username) {
    clearScreen();
    printBanner();
    setColor(11); // Cyan
    printf("    Logged in as: %s\n", username);
    setColor(14); // Yellow
    printf("\n    ╔════════════════ MAIN MENU ═══════════════╗\n");
    printf("    ║                                          ║\n");
    printf("    ║  1. Generate Learning Content            ║\n");
    printf("    ║  2. Summarize YouTube Video             ║\n");
    printf("    ║  3. Create Mind Maps               ║\n");
    printf("    ║  4. Exit                                ║\n");
    printf("    ║                                          ║\n");
    printf("    ╚══════════════════════════════════════════╝\n");
    setColor(7); // White
    printf("\n    Choose an option (1-4): ");
}


void generate_content()
{
    char topic[100];
    char content_type[20];
    
    clearScreen();
    printBanner();
    
    setColor(14); // Yellow
    printf("\n    ╔═════════════ Generate Content ════════════╗\n");
    printf("    ║                                          ║\n");
    printf("    ║  Enter a topic to learn about:          ║\n");
    printf("    ╚══════════════════════════════════════════╝\n");
    setColor(7); // White
    
    printf("\n    Topic: ");
    scanf(" %99[^\n]", topic);
    
    clearScreen();
    printBanner();
    
    setColor(14); // Yellow
    printf("\n    ╔════════════ Select Content Type ══════════╗\n");
    printf("    ║                                          ║\n");
    printf("    ║  1. Study Notes                         ║\n");
    printf("    ║  2. Quiz                                ║\n");
    printf("    ║                                          ║\n");
    printf("    ╚══════════════════════════════════════════╝\n");
    setColor(7); // White
    
    printf("\n    Choice (1-2): ");
    int choice;
    if(scanf("%d", &choice) != 1 || choice < 1 || choice > 2) {
        while(getchar() != '\n');
        setColor(12); // Red
        printf("\n    Invalid choice! Returning to main menu.\n");
        setColor(7);
        Sleep(1500);
        return;
    }
    
    strcpy(content_type, choice == 1 ? "notes" : "quiz");
    
    setColor(11); // Cyan
    printf("\n    Generating %s for '%s'...\n", 
           choice == 1 ? "study notes" : "quiz", 
           topic);
    setColor(7);
    
    // Call Python script
    char cmd[512];
    snprintf(cmd, sizeof(cmd), "python api_handler.py \"%s\" %s", 
             topic, content_type);

    FILE *fp = _popen(cmd, "r");
    if (!fp)
    {
        printf("Error generating content\n");
        return;
    }

    char buffer[4096];
    char md_filename[100] = "";
    char pdf_filename[100] = "";

    while (fgets(buffer, sizeof(buffer), fp))
    {
        if (strncmp(buffer, "MARKDOWN:", 9) == 0)
        {
            strncpy(md_filename, buffer + 9, sizeof(md_filename));
            md_filename[strcspn(md_filename, "\n")] = 0;
        }
        else if (strncmp(buffer, "PDF:", 4) == 0)
        {
            strncpy(pdf_filename, buffer + 4, sizeof(pdf_filename));
            pdf_filename[strcspn(pdf_filename, "\n")] = 0;
        }
        else
        {
            printf("%s", buffer);
        }
        
        
    }
    _pclose(fp);

    if (md_filename[0] && pdf_filename[0])
    {
        printf("\nFiles saved:\n");
        printf("Markdown: %s\n", md_filename);
        printf("PDF: %s\n", pdf_filename);
    }
}

int main() {
    system("chcp 65001");
    int logged_in = 0;
    clearScreen();
    printBanner();

    while (!logged_in) {
        setColor(14); // Yellow
        printAuthMenu();
        setColor(7); // White

        printf("\n    Choose an option (1-3): ");
        int choice;
        if(scanf("%d", &choice) != 1) {
            while(getchar() != '\n'); // Clear input buffer
            setColor(12); // Red
            printf("\n    Invalid input! Please enter a number.\n");
            setColor(7);
            Sleep(1500);
            clearScreen();
            printBanner();
            continue;
        }

        switch(choice) {
            case 1:
                if(login_user(username)) {
                    logged_in = 1;
                    setColor(10); // Green
                    printf("\n    Login successful!\n");
                    setColor(7);
                }
                break;
            case 2:
                if(register_user()) {
                    setColor(10);
                    printf("\n    Please login with your new account.\n");
                    setColor(7);
                }
                break;
            case 3:
                setColor(10);
                printf("\n    Thank you for using Learning Assistant!\n\n");
                setColor(7);
                exit(0);
            default:
                setColor(12);
                printf("\n    Invalid choice! Please select 1-3.\n");
                setColor(7);
        }
        Sleep(1500);
        clearScreen();
        printBanner();
    }

    int running = 1;
    while (running) {
        clearScreen();
        printBanner();
        setColor(11); // Cyan
        printf("    Logged in as: %s\n", username);
        setColor(7);
        printMenu(username);

        int choice;
        printf("    Choose an option (1-4): ");
        if(scanf("%d", &choice) != 1) {
            while(getchar() != '\n');
            setColor(12);
            printf("\n    Invalid input! Please enter a number.\n");
            setColor(7);
            Sleep(1500);
            continue;
        }

        switch (choice) {
            case 1:
                generate_content();
                break;
            case 2:
                summarize_youtube_video(username);
                break;
            case 3:
                create_mindmap(username);
                break;
            case 4:
                setColor(10);
                printf("\n    Thank you for using Learning Assistant!\n");
                printf("    Goodbye %s!\n\n", username);
                setColor(7);
                running = 0;
                break;
            default:
                setColor(12);
                printf("\n    Invalid choice! Please select 1-4.\n");
                setColor(7);
                Sleep(1500);
        }

        if (running && choice >= 1 && choice <= 3) {
            printf("\n    Press Enter to continue...");
            while(getchar() != '\n');
            getchar();
        }
    }
    return 0;
}