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
void changeDir(char *directory);
void listDirectory(char *arg1, char *arg2); 
void type_cmd(const char *filename);
void copy_cmd(const char *filename, const char *dst);
void ren_cmd(const char *filename, const char *newname);
void del_cmd(const char *filename);

int main(int argc, char* argv[]) {

    bool run = true;

    while (run) {
        
        printf("Type Ctrl+C to exit.\n");

        char input[MAX_CHAR_LIM] = "";
        fgets(input, sizeof(input), stdin);
        input[strlen(input) - 1] = '\0'; // remove newline char

        processInput(input);


        

    }
    printf("Exiting");
}

// function that changes the directory
void changeDir(char *directory) {
    char command[200] = "cd ";
    strncat(command, directory, strlen(directory));
    system(command);
}

// Function to implement DIR (ls)
void listDirectory(char *arg1, char *arg2) {
    char command[200] = "dir";
    if (arg1 != NULL) {
        strcat(command, " ");
        strcat(command, arg1);
    }
    if (arg2 != NULL) {
        strcat(command, " ");
        strcat(command, arg2);
    }
    system(command);
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

void del_cmd(const char *filename) {
    char command[MAX_CHAR_LIM + 5] = "del ";
    strncat(command, filename, strlen(filename));
    system(command);
}

void ren_cmd(const char *filename, const char *newname) {
    char command[MAX_CHAR_LIM + 5] = "ren ";
    strncat(command, filename, strlen(filename));
    strncat(command, " ", 1);
    strncat(command, newname, strlen(newname));
    system(command);
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

    bool dirActivated = false;

    token = strtok(NULL, delim);
    arg1 = token;
    token = strtok(NULL, delim);
    arg2 = token;


    if (strcmp(command, DIR) == 0) {
        dirActivated = true;
    } else if  (strcmp(command, CD) == 0 || strcmp(command, TYPE) == 0 || strcmp(command, DEL) == 0) {
        num_args = 1;        
    } else if (strcmp(command, REN) == 0 || strcmp(command, COPY) == 0) {
        num_args = 2;
    }

    // printf("NUM: %d\n", num_args);
    // printf("ARG1: %s\n", arg1);
    // printf("ARG2: %s\n", arg2);

    if (dirActivated == false) {
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
    }

    if (strcmp(command, CD) == 0){
        changeDir(arg1);
    } else if (strcmp(command, DIR) == 0) {
        listDirectory(arg1, arg2);
        dirActivated = false;
    } else if (strcmp(command, TYPE) == 0) {
        type_cmd(arg1);
    } else if (strcmp(command, COPY) == 0) {
        copy_cmd(arg1, arg2);
    } else if (strcmp(command, DEL) == 0) {
        del_cmd(arg1);
    } else if (strcmp(command, REN) == 0) {
        ren_cmd(arg1, arg2);
    }




    return;
}