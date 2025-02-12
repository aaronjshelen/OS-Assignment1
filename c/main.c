#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <direct.h>


#define MAX_CHAR_LIM 100
#define MAX_TOKENS 4

const char CD[] = "cd", DIR[] = "dir", TYPE[] = "type", DEL[] = "del",
        REN[] = "ren", COPY[] = "copy";


void processInput(char input[MAX_CHAR_LIM]);
int changeDir(const char *directory);
void type_cmd(const char *filename);
void copy_cmd(const char *filename, const char *dst);

int main(void) {

    while (true) {
        printf("Type Ctrl+C to exit..\n");
        char input[MAX_CHAR_LIM] = "";
        fgets(input, sizeof(input), stdin);
        input[strlen(input) - 1] = '\0'; // remove newline char
        // printf("Input: %s\n", input);

        if (strncmp(input, "Ctrl+C", sizeof("Ctrl+C")) == 0) {
            return 0;
        }
        processInput(input);
    }
}

// function that changes the directory
int changeDir(const char *directory) {

    if (_chdir(directory) == 0) {
        printf("Directory changed to: %s\n", directory);
    } else {
        printf("The system cannot find the path specified.\n");
    }

    return 1;
}

// type (cat) filename: view file contents of filename
void type_cmd(const char *filename) {
    char command[MAX_CHAR_LIM + 6] = "type "; // strlen("type ") + 1 = 6
    strncat(command, filename, strlen(filename));
    // printf("Command: %s\n", command);
    system(command);
    printf("\n");
}

// copy (cp) filename dest: copies filename to dest (e.g. copy file.txt directory/
void copy_cmd(const char *filename, const char *dst) {
    char command[MAX_CHAR_LIM + 6] = "copy "; // strlen("type ") + 1 = 6
    strncat(command, filename, strlen(filename));
    strncat(command, " ", 1);
    strncat(command, dst, strlen(dst));
    // printf("%s\n", command);
    system(command);
}

void processInput(char input[MAX_CHAR_LIM]) {
    const char delim[] = " ";
    const char* token = strtok(input, delim);
    if (token == NULL) {
        // printf("Error processing input\n");
        return;
    }

    int num_args = 0;
    const char *command = token;

    token = strtok(NULL, delim);
    char const *arg1 = token;
    token = strtok(NULL, delim);
    const char *arg2 = token;

    if (strcmp(command, DIR) == 0){
        num_args = 0;
    } else if (strcmp(command, CD) == 0 || strcmp(command, TYPE) == 0 || strcmp(command, DEL) == 0) {
        num_args = 1;
    } else if (strcmp(command, REN) == 0 || strcmp(command, COPY) == 0) {
        num_args = 2;
    }

    // printf("NUM: %d\n", num_args);
    // printf("ARG1: %s\n", arg1);
    // printf("ARG2: %s\n", arg2);

    if (num_args == 0) {
        if (arg1 != NULL) {
            printf("Too many\n");
            return;
        }
    } else if (num_args == 1) {
        if (arg1 == NULL) {
            printf("too few\n");
            return;
        }
        if (arg2 != NULL) {
            printf("too many\n");
            return;
        }
    } else {
        // num_args is 2
        if (arg1 == NULL || arg2 == NULL) {
            printf("too few\n");
            return;
        }
        if (strtok(NULL, delim) != NULL) {
            printf("too many\n");
            return;
        }
    }

    if (strcmp(command, CD) == 0){
        changeDir(arg1);
    } else if (strcmp(command, TYPE) == 0) {
        type_cmd(arg1);
    } else if (strcmp(command, COPY) == 0) {
        copy_cmd(arg1, arg2);
    }
}