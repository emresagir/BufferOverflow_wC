#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function prototypes
void secretFunction();
void vulnerable_function(char *input);
long get_file_size(FILE *fp);


void secretFunction() {
    printf("U are pwned by Chronox-sama\n");
    return;
}


void vulnerable_function(char *input) {
    char vul_arr[100]; 
    //This string copy doesn't have a bound so it will result in a buffer overflow
    strcpy(vul_arr, input);
    printf(vul_arr); 
}

//To get the file size of the payload.
long get_file_size(FILE *fp){
    if(fseek(fp, 0, SEEK_END) < 0){
        fclose(fp);
        return -1;
    }
    long return_val = ftell(fp);
    rewind(fp);
    return return_val;
}


int main(int argc, char *argv[]) {
    FILE* fp;
    long sizeBytes;

    //Checking the argument count, wanted argument is 1
    if( argc == 2) {

        printf("The argument is = %s\n", argv[1]);
        printf("Count is %d \n", argc);

        //Reading as binary
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
