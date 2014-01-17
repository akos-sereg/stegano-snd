#ifndef _stegano_snd_h_included_
#define _stegano_snd_h_included_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <math.h>
#include <sndfile.h>

char program[256];
char chars6[64], chars8[256];

struct usr_defs
{
    char input[256];
    char output[256];
    char textfile[256];
    int decode;
    int encode;
    int stdout;
    
} usr_defs;


#include "misc.h"
#include "snd.h"
#include "key.h"
#include "io.h"


#endif
