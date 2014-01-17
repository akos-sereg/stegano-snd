#include "../include/stegano-snd.h"

int file_len(char *fname)
{
    struct stat st;
    
    if(stat(fname, &st) == -1) return -1;
    else return st.st_size;

}

int file_exists(char *fname)
{
    struct stat st;
    
    if(stat(fname, &st) == -1) 
    {
	fprintf(stderr, "WARN: File does not exist: '%s'\n", fname);
	return 0;
    }
    else return 1;
}

