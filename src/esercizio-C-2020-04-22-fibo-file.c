/*
 * esercizio-C-2020-04-22-fibo-file.c
 *
 *  Created on: 24 apr 2020
 *      Author: utente
 */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <limits.h>
#include <math.h>

#define _OPEN_SYS_ITOA_EXT

void * writing_function(int fd, char * file_name, unsigned long * num[]){
	char * text_to_write;
	int text_to_write_len;
    char * newline = "\n";
    int res;
    char buffer[20];
    for(int i = 0; i < 40; i++){
        sprintf(buffer, "%lld", num[i]);
        text_to_write = buffer;
	    text_to_write_len = strlen(text_to_write) + 1;
        res = write(fd, text_to_write, text_to_write_len);
        if(res == -1){
            perror("write()");
            exit(EXIT_FAILURE);
        }
        res = write(fd, text_to_write, text_to_write_len);
        if(res == -1){
            perror("write()");
            exit(EXIT_FAILURE);
        }
    }
    
}

unsigned long fibonacci(unsigned int n){
    unsigned long result;
    unsigned long arr[n+1];
    if(n == 0){
        result = 0;
    } else if(n == 1){
        result = 1;
    } else {
        arr[0] = 0;
        arr[1] = 1;
        for(unsigned int i = 2; i < n+1; i++){
            arr[i] = arr[i-2] + arr[i-1];
        }
        result = arr[n];
    }
    return result;
}

unsigned long * fibonacci_array(unsigned int n){
    unsigned long * arr;
    arr = malloc(sizeof(unsigned long) * (n+1));
	if (arr == NULL)
		return NULL;
    for(unsigned int i = 0; i < n+1; i++){
        arr[i] = fibonacci(i);
    }
    return arr;
}

int main(int argc, char * argv[]){
    unsigned long * fibonacci_result;
    char * file_name;
    if (argc == 1) {
		printf("Specificare come parametro il nome del file da creare e su cui scrivere!\n");
		exit(EXIT_FAILURE);
	}
    file_name = argv[1];
	printf("scrivo nel file %s\n", file_name);
    int fd = open(file_name, O_CREAT | O_TRUNC | O_WRONLY, S_IRUSR | S_IWUSR);
    if (fd == -1) {
		perror("open()");
		exit(EXIT_FAILURE);
	}
    fibonacci_result = fibonacci_array(39);
    writing_function(fd, file_name, &fibonacci_result);
    free(fibonacci_result);
    if (close(fd) == -1) {
		perror("close");
		exit(EXIT_FAILURE);
	}
    printf("bye\n");
    exit(EXIT_SUCCESS);
}
