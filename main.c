#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function prototypes
void secretFunction();
void vulnerable_function(char *input);
long get_file_size(FILE *fp);


// Recipe for completing the practice:

// 1. Define a "malicious" function that should not be called directly.
//    - Print a message indicating the function was executed.
//    - Exit the program after printing the message.
void secretFunction() {
    // Add your code here
    printf("U are pwned by Chronox-sama\n");
    return;
}

// 2. Define a function that is vulnerable to buffer overflow.
//    - Declare a fixed-size buffer inside the function.
//    - Copy the input into the buffer without proper bounds checking.
//    - Print the received input.
void vulnerable_function(char *input) {
    char vul_arr[100]; 
    //80 is seg fault, 81 is ok in case the input file 96 Bytes in size.
    strcpy(vul_arr, input);
    printf(vul_arr); 
}


long get_file_size(FILE *fp){
    if(fseek(fp, 0, SEEK_END) < 0){
        fclose(fp);
        return -1;
    }
    long return_val = ftell(fp);
    rewind(fp);
    return return_val;
}

// 3. In the main function:
//    - Check if the program is called with exactly one argument (input file).
//    - If not, print the correct usage and exit.
//    - Open the input file in binary read mode.
//    - If the file cannot be opened, print an error message and exit.
//    - Determine the size of the file.
//    - Allocate memory to store the file content.
//    - Read the file content into the allocated memory.
//    - Close the file after reading.
//    - Call the vulnerable function with the file content as input.
//    - Clean up: free the allocated memory and print a success message.
int main(int argc, char *argv[]) {
    // Add your code here
    FILE* fp;
    long sizeBytes;

    if( argc == 2) {

        printf("The argument is = %s\n", argv[1]);
        printf("Count is %d \n", argc);

        //File 
        fp = fopen(argv[1], "rb");
        if(fp == NULL){
            printf("File/argument bumbum\n");
            return 0;

        }
        //Get size
        sizeBytes = get_file_size(fp);
        if(sizeBytes == -1){
            printf("file is empty\n");
            return 0;
        }
        else{
            printf("Size of the file %ld\n", sizeBytes);
        }
        //MALLOC
        char *mem = (char*)malloc(sizeBytes+1);
        if (mem == NULL) {
            printf("Allocation Failed\n");
            exit(0);
        }
        //read into the memory
        fread(mem,1,sizeBytes,fp);
        //closing file
        fclose(fp);
        //calling the func with the mem (content in mem)
        vulnerable_function(mem);
        //freeing
        free(mem);
        printf("DONE!!\n");
    }

    else{
        printf("Entered arguments more than 1, or no arguments\n");
        return 0;
    }

    return 0;
}
