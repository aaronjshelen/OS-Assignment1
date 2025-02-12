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
int changeDir(char *directory);


int main(int argc, char* argv[]) {

    bool run = true;

    while (run) {

        printf("Type Ctrl+C to exit..\n");

        char input[MAX_CHAR_LIM] = "";
        fgets(input, sizeof(input), stdin);
        input[strlen(input) - 1] = '\0'; // remove newline char
        printf("Input: %s\n", input);

        processInput(input);


        // if (strncmp(input, "exit", sizeof("exit")) == 0) {
        // run = false;
        

    }
    printf("Exiting");
}

// function that changes the directory
int changeDir(char *directory) {

    if (_chdir(directory) == 0) {
        printf("Directory changed to: %s\n", directory);
    } else {
        printf("The system cannot find the path specified.\n");
    }

    return 1;
}





void processInput(char input[MAX_CHAR_LIM]) {
    
    const char delim[] = " ";
    char* token = strtok(input, delim);
    if (token == NULL) {
        // printf("Error processing input\n");
        return;
    }


    int num_args = 0;
    int arg_counter = 0;
    char *command = token;
    char *arg1, *arg2;

    token = strtok(NULL, delim);
    arg1 = token;
    token = strtok(NULL, delim);
    arg2 = token;



    if (strcmp(command, CD) == 0){
        num_args = 1;
    } else if (strcmp(command, DIR) == 0) {
        num_args = 0;
    }

    printf("NUM: %d\n", num_args);
    printf("ARG1: %s\n", arg1);
    printf("ARG2: %s\n", arg2);

    if (num_args == 0) {
        if (arg1 != NULL) {
            printf("Too many\n");
            return;
        }
    } else if (num_args == 1) {
        if (arg1 == NULL) {
            printf("too few\n");
            return;
        } else if (arg2 != NULL) {
            printf("too many\n");
            return;
        } 
    } else { // num_args is 2
        if (arg1 == NULL || arg2 == NULL) {
            printf("too few\n");
            return;
        } else if (strtok(NULL, delim) != NULL) {
            printf("too many\n");
            return;
        }
    }

    if (strcmp(command, CD) == 0){
        changeDir(arg1);
    }




    return;
}