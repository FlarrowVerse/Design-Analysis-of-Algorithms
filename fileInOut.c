#include <stdio.h>

int writeToFile(char *fielname) {

    FILE *file = fopen(fielname, "a"); // opens a file in append mode. if it doesn't exists creates a new

    char data[255]; // holds one line of input
    // error check block
    if(file == NULL) {
        fprintf(stderr, "cannot open file %s\n", fielname); // error message
        return 1; //exit status
    }

    fgetc(stdin); // first character is taken out to clear stdin stream
   
    while(data[0] != '\n') {                
        fgets(data, sizeof(data), stdin);
        fputs(data, file);
    }    

    fclose(file);

    return 0;
}

int readFromFile(char *fielname) {

    FILE *file = fopen(fielname, "r"); // opens a file in read mode.

    char data[255]; // holds one line of data
    // error check block
    if(file == NULL) {
        fprintf(stderr, "cannot open file %s\n", fielname); // error message
        return 1; //exit status
    }   
   
    while((fgets(data, 255, file)) != 0) {                
        fputs(data, stdout);
    }    

    fclose(file);

    return 0;
}

int main() {

    char filename[255];
    char mode[2];
    printf("Enter a filename: ");
    fscanf(stdin, "%s.%s", filename, filename);

    printf("Enter file opening mode: ");
    fscanf(stdin, " %c", mode);

    printf("File %s has been opened with mode %s\n\n", filename, mode);
    printf("Enter data for the file. Hit Enter twice to exit edit mode:\n");
    if(writeToFile(filename)) return 1;
    
    printf("Data written to file: ");
    if(readFromFile(filename)) return 1;

    return 0;
}