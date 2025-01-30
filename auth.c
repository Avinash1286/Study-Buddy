#include <stdio.h>
#include <string.h>
#include "config.h"

typedef struct {
    char username[50];
    char password[256]; // SHA-256 hashed
} User;

// Add new function to check if user exists
int user_exists(const char* username) {
    FILE *fp = fopen(USER_DB, "rb");
    if(!fp) return 0;
    
    User user;
    while(fread(&user, sizeof(User), 1, fp)) {
        if(strcmp(user.username, username) == 0) {
            fclose(fp);
            return 1;
        }
    }
    fclose(fp);
    return 0;
}

int register_user() {
    User new_user;
    char password[50];
    
    printf("Enter username: ");
    scanf("%49s", new_user.username);

        // Check if user already exists
      if(user_exists(new_user.username)) {
        printf(COLOR_ERROR "Username already exists!\n" COLOR_RESET);
        return 0;
    }

    printf("Enter password: ");
    scanf("%49s", password);
    
    // Add password hashing (using crypt() or OpenSSL)
    // Simplified for example:
    strncpy(new_user.password, password, sizeof(new_user.password));
    
    FILE *fp = fopen(USER_DB, "ab");
    if(!fp) {
        printf(COLOR_ERROR "Error creating user database!\n" COLOR_RESET);
        return 0;
    }
    
    fwrite(&new_user, sizeof(User), 1, fp);
    fclose(fp);
    printf(COLOR_SUCCESS "Registration successful!\n" COLOR_RESET);
    return 1;
}

int login_user(char *username) {
    User user;
    char password[50];
    
    printf("Username: ");
    scanf("%49s", username);
    // Check if user exists first
    if(!user_exists(username)) {
        printf(COLOR_ERROR "User not found! Please register first.\n" COLOR_RESET);
        return 0;
    }
    printf("Password: ");
    scanf("%49s", password);
    
    FILE *fp = fopen(USER_DB, "rb");
    if(!fp) {
        printf(COLOR_ERROR "Error accessing user database!\n" COLOR_RESET);
        return 0;
    }
    
    while(fread(&user, sizeof(User), 1, fp)) {
        if(strcmp(user.username, username) == 0 && 
           strcmp(user.password, password) == 0) {
            fclose(fp);
            printf(COLOR_SUCCESS "Login successful!\n" COLOR_RESET);
            return 1;
        }
    }
    
    fclose(fp);
    printf(COLOR_ERROR "Invalid password!\n" COLOR_RESET);
    return 0;
}