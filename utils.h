#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>								// Needed for POSIX syscalls

// Prototypes
char * read_line(void);
void split_tokens(void);
char ** tokenize_line(char *);
int dash_launch(char **);
void command_print(char *);
char * lower_string(char *);
char * copy_string(char *, char *);


char * read_line() {
    /*  # TO READ A LINE FROM THE USER
    - Malloc used as we don't know how long the user input might be.    */

    int line_Size = 1024;                               // Initial buffer size
    int line_Pos = 0;                                   // Position of the line
    char * line = (char *) malloc(sizeof(char) * line_Size);     // Allocate memory for the line
    char c;                                             // Temp, char to be read at a time

    // If memory allocation fails
    if (!line) {                                        
        fprintf(stderr, "Memory Allocation Error\n");
        exit(EXIT_FAILURE);
    }

    while (1) {
        c = getchar();                                  // Read a character
        if (c == EOF || c == '\n') {                    // CHECK IF EOF or NEWLINE is encountered
            line[line_Pos] = '\0';                      // Terminate the line
            return line;                                // Return the line [Back to the main loop]
        } else {
            line[line_Pos] = c;                         // Add the character to the line
        }
        line_Pos += 1;                                  // Move the position cursor ahead
    
        // If the line would exceed the buffer size
        if (line_Pos >= line_Size) {
            line_Size += 1024;                          // Increase the buffer size
            line = realloc(line, line_Size);            // Reallocate memory for the line
        
            // If memory allocation fails
            if (!line) {
                fprintf(stderr, "Memory Allocation Error\n");
                exit(EXIT_FAILURE);                     // Exit the program with an ERROR CODE
            }
        }
    }
}


void split_tokens() {
    // TO BE IMPLEMENTED -- > REPLACE strtok with it
}


char ** tokenize_line(char * user_input_line) {         
    /*  # Tokenizes user input into processable arguments
    - Returns an array of strings (which are our TOKENS)
    - Every subsequent 
    */

    int TOKEN_SIZE = 1024;                              // Initial buffer size
    int token_Pos = 0;                                  // Position of the token

    char ** token_list = (char **) malloc(sizeof(char *) * TOKEN_SIZE);     // Allocate memory for the LIST OF TOKENS
    char * token = (char *) malloc(sizeof(char) * TOKEN_SIZE);          // Allocate memory for the first token
    
    if (!token_list || !token) {                        // If memory allocation fails
        fprintf(stderr, "Memory Allocation Error. Could not extend variable \"tokens\". \n");
        exit(EXIT_FAILURE);
    }

    token = strtok(user_input_line, TOKEN_DELIM);         // Tokenize the first word (https://www.geeksforgeeks.org/strtok-strtok_r-functions-c-examples/)

    // Driving Loop for this function  - tokenize the entire line
    while (token != NULL) {
        token_list[token_Pos] = token;                  // Add the token to the list of tokens
        token_Pos += 1;                                 // Move the position cursor ahead

        if (token_Pos >= TOKEN_SIZE) {
            TOKEN_SIZE += TOKEN_SIZE;                         // Increase the buffer size IF we reach the prev allocated length
            token_list = realloc(token_list, TOKEN_SIZE);    // Reallocate memory for the list of tokens

            // Handle Allocation Error
            if (!token_list) {
                fprintf(stderr, "Memory Allocation Error in allocating \"token_list\"");
                exit(EXIT_FAILURE);
            }
        }
        
        token = strtok(NULL, TOKEN_DELIM);                 // TOKEN stores the next seperated word. 
    }

    token_list[token_Pos] = NULL;                      // Last one becomes null to mark the end.
    return token_list;
}


int dash_launch(char ** args) {                         // Takes in the list of arguments to be processed
    pid_t cpid;
    int status;

    // If the user wants to exit
    if (strcmp(lower_string(args[0]), "exit") == 0)
        return 0;

    cpid = fork();

    if (cpid == 0) {
        if (execvp(args[0], args) < 0)
            printf("dash: command not found: %s\n", args[0]);
        exit(EXIT_FAILURE);
    }

    else if (cpid < 0)
        printf("Error Forking \n");
    
    else 
        waitpid(cpid, & status, WUNTRACED);
    
    return 1;
}


void command_print(char * input_text) {                       // PRINT Something to the prompt
    printf("%s", input_text);
}


char * lower_string(char * input_string) {                  // To get lowercase commands from mixed-case input
    char * output_string;
    for (int i = 0; input_string[i]; i++) {
        output_string[i] = tolower(input_string[i]);
    }
    return output_string;
}


char * copy_string(char * input_string, char * output_string) {     // Assign a string to another
    for (int i = 0; input_string[i]; i++)
        input_string[i] = output_string[i];
    
    return output_string;
}