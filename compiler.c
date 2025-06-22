#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <ctype.h>

// pl0 possible token types
#define TOK_IDENT       'I'
#define TOK_NUMBER	    'N'
#define TOK_CONST	    'C'
#define TOK_VAR		    'V'
#define TOK_PROCEDURE	'P'
#define TOK_CALL	    'c'
#define TOK_BEGIN	    'B'
#define TOK_END		    'E'
#define TOK_IF		    'i'
#define TOK_THEN	    'T'
#define TOK_WHILE	    'W'
#define TOK_DO		    'D'
#define TOK_ODD		    'O'
#define TOK_DOT		    '.'
#define TOK_EQUAL	    '='
#define TOK_COMMA	    ','
#define TOK_SEMICOLON	';'
#define TOK_ASSIGN	    ':' // Assignment is :=, but here it's one char for convention
#define TOK_HASH	    '#'
#define TOK_LESSTHAN	'<'
#define TOK_GREATERTHAN	'>'
#define TOK_PLUS        '+'
#define TOK_MINUS	    '-'
#define TOK_MULTIPLY    '*'
#define TOK_DIVIDE	    '/'
#define TOK_LPAREN	    '('
#define TOK_RPAREN	    ')'
#define TOK_LCOMM       '{'
#define TOK_RCOMM       '{'


char *raw_file_data;  // supposed to contain the .pl0 file raw data as string
int raw_file_data_len = 0;
int *curr_index = 0;
int curr_row = 0;

void print_error(char *error_msg) {
    printf(error_msg);
    exit(1);
}

static void read_file(char *file_path) {
    /*
    Stages:
    1. check file is valid plo file
    2. open the file
    3. check for its size
    4. allocate memory for the file data
    5. read into the allocated memory
    */
    int fd; 
    struct stat st;
    if (strlen(file_path) < 4 || strcmp(file_path + strlen(file_path) - 4, ".pl0") != 0)
        print_error("File must have .pl0 suffix");
    
    if ((fd = open(file_path, O_RDONLY)) == -1)
        print_error("Could not open file");

    if (fstat(fd, &st) == -1)
        print_error("Could not stat file");

    if ((raw_file_data = malloc(st.st_size + 1)) == NULL)
        print_error("Failed allocating memory for file data");
    
    if (read(fd, raw_file_data, st.st_size) != st.st_size)
        print_error("Failed reading file data");

    raw_file_data[st.st_size] = '\0';  // Add null terminator. without it, the program will just keep reading and random chars will appear
    raw_file_data_len = st.st_size;
    
    close(fd);
}

int skip_comment() {
    for (int i = curr_index; i < raw_file_data_len; i++) {
        if (raw_file_data[i] == TOK_RCOMM)
            curr_index = i;
            return 0;
    }
    print_error("Could not find end of comment");
}

char* get_function_name() {
    char *function_name[100];
    int function_index = 0;
    char current_char;
    for (int i = curr_index; i < raw_file_data_len; i++) {
        current_char = raw_file_data[i];
        if (isalpha(current_char)) {
            function_name[function_index] = current_char;
        }
        else { 
            if (current_char == ";") {
                function_name[i] = "/0";
                curr_index = i;
                return function_name;
            }
            else {
                print_error("A non alphabetic char inserted in procedure name");
            }
        }
    }
    print_error("Non-terminated procedure name.");
}

int main(int argc, char *argv[]) {
    if(argc != 2) {
        printf("Usage: compiler FILE_NAME_TO_COMPILE\n");
        return 1;
    }
    
    printf("Reading file content...\n");
    printf("%s\n", argv[1]);

    read_file(argv[1]);

    printf("Finish read_file function\n");
    printf("%s", raw_file_data);

    return 0;
}
