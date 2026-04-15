#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef char password[13];

void fill(password myPass);
void copyToClipboard(password myPass);

int main(void) {
    srand(time(NULL));

    password myPass;

    fill(myPass);
    printf("Generated password: %s\n", myPass);

    copyToClipboard(myPass);

    return 0;
}

void fill(password myPass) {
    char pool[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!@#$%^&*";
    char numbers[] = "0123456789";
    char symbols[] = "!@#$%^&*";


    myPass[0] = numbers[rand() % (sizeof(numbers) - 1)];
    myPass[1] = symbols[rand() % (sizeof(symbols) - 1)];

    for (int i = 2; i < 12; i++) {
        myPass[i] = pool[rand() % (sizeof(pool) - 1)];
    }

    for (int i = 11; i > 0; i--) {
        int j = rand() % (i + 1);
        char temp = myPass[i];
        myPass[i] = myPass[j];
        myPass[j] = temp;
    }

    myPass[12] = '\0';
}

void copyToClipboard(password myPass) {
    char command[200];
    char permission;

    do {
        printf("Do you want to copy it? (y or n)\n");
        scanf("%c", &permission);
    } while (permission != 'y' && permission != 'n');

    if (permission == 'y') {
        #ifdef __APPLE__  // macOS
            sprintf(command, "echo '%s' | pbcopy", myPass);
            system(command);
            printf("Password copied to clipboard (macOS)!\n");
        #elif __linux__  // Linux
            sprintf(command, "echo '%s' | xclip -selection clipboard", myPass);
            system(command);
            printf("Password copied to clipboard (Linux)!\n");
        #elif _WIN32     // Windows
            sprintf(command, "echo %s | clip", myPass);
            system(command);
            printf("Password copied to clipboard (Windows)!\n");
        #else
            printf("Clipboard copy not supported on this OS.\n");
        #endif
    }
}
