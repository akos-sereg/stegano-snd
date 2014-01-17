#include "../include/stegano-snd.h"

int inchars(int into){
    int fd_chars;
    char l = into;
    
    for(fd_chars=0; fd_chars!=64; fd_chars++){
	if(chars6[fd_chars] == l) return fd_chars;
    }
    
    return 1;
}

int get_char(int into){
    int fd_chars;
    char l = into;
    
    for(fd_chars=0; fd_chars!=256; fd_chars++){
	if(chars8[fd_chars] == l) return fd_chars;
    }
        
    return 1;
}



