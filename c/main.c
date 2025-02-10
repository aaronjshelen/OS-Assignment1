#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

#define MAX_CHAR_LIM 100

const char CD[] = "cd", DIR[] = "dir", TYPE[] = "type", DEL[] = "del",
        REN[] = "ren", COPY[] = "copy";

int processInput(char input[MAX_CHAR_LIM]);

int main(int argc, char* argv[]) {
    bool run = true;
    while (run) {
        printf("Type Ctrl+C to exit..\n");

        char input[MAX_CHAR_LIM] = "";
        fgets(input, sizeof(input), stdin);
        input[strlen(input) - 1] = '\0'; // remove newline char
        printf("Input: %s\n", input);
        if (strncmp(input, "exit", sizeof("exit")) == 0) {
            run = false;
        } else {
            processInput(input);
        }
    }
    printf("Exiting");
}

int processInput(char input[MAX_CHAR_LIM]) {
    const char delim[] = " ";
    char* token = strtok(input, delim);
    if (token == NULL) {
        printf("Error processing input\n");
        return -1;
    }

    while (token != NULL) {
        printf("Token: %s\n", token);
        token = strtok(NULL, delim);
    }

    return 1;
}