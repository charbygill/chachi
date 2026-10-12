#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <errno.h>   

#include "parser.h"
#include "error.h"

static bool has_extension(const char* path, const char* ext){
    size_t p_len = strlen(path); 
    size_t e_len = strlen(ext);

    if (p_len < e_len) return false;

    return strcmp(path + (p_len - e_len), ext) == 0;
}

static char* read_file(const char* path){
    FILE *f = fopen(path, "rb");
    
    if (f == NULL) {
	erxit(1, "Error opening \"%s\": %s", path, strerror(errno));
    }

    //Measure the length of the file in bytes
    if (fseek(f, 0, SEEK_END) != 0){
	erxit(1, "Failed to seek to the end of \"%s\": %s", path, strerror(errno));
    }
    long size = ftell(f);
    if (size < 0){
	erxit(1, "Could not determine size of \"%s\": %s", path, strerror(errno));
    }
    rewind(f);

    //Create buffer
    char *buf = malloc(size + 1);
    if (buf == NULL) {
	erxit(1, "Failed to allocate buffer for file \"%s\"", path);
    }

    //Read file into the buffer
    long read = fread(buf, 1, size, f);
    if (read != size){
	erxit(1, "Failed to read \"%s\"", path);
    } 

    //Terminate (needs a zero byte for prints to recognize the end of the buffer)
    buf[read] = '\0';


    fclose(f);
    return buf;
}

int main(int argc, char* argv[]){
    if (argc != 2) erxit(1, "Usage: chachi <file_path>");
    if (!has_extension(argv[1], ".chi")) erxit(1, "\'%s\' has the wrong file extension", argv[1]);

    char *buf = read_file(argv[1]); 

    Ast* a = parse(buf);
    ast_print(a); printf("\n");
    ast_free(a);

    free(buf);
    return 0;
}
