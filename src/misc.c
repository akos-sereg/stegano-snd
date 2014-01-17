#include "../include/stegano-snd.h"

void hcore()
{
    if(usr_defs.encode) 
    {
	if(strlen(usr_defs.input) == 0) help();
	if((strlen(usr_defs.output) == 0) && (usr_defs.stdout==0)) help();
	if(strlen(usr_defs.textfile) == 0) help();
	
	if(!file_exists(usr_defs.input)) die("Exit");
	if(strlen(usr_defs.output)) 
	    if(file_exists(usr_defs.output)) die("Output file exists (-o <filename>).\nWe do not want to overwrite it, please provide a different filename.");
	if(!file_exists(usr_defs.textfile)) die("Exit");
	
	wav_encode(usr_defs.input, usr_defs.output, usr_defs.textfile);	
    } 
    else if(usr_defs.decode)
    {
	if(strlen(usr_defs.input) == 0) help();
	if((strlen(usr_defs.output) == 0) && (!usr_defs.stdout)) help();
	
	if(!file_exists(usr_defs.input)) die("Exit");
	
	wav_decode(usr_defs.input, usr_defs.output);
    }
}

void herb_snd_init()
{
    sprintf(usr_defs.input, "");
    sprintf(usr_defs.output, "");
    sprintf(usr_defs.textfile, "");
    usr_defs.encode=0;
    usr_defs.decode=0;
    usr_defs.stdout=0;
    
}

void die(char *str)
{
    fprintf(stderr, "%s", str);
    exit(0);
}

void help()
{
    fprintf(stdout, "Usage: %s [OPTION]...\n", program);
    fprintf(stdout, "	-e <file>	.wav file, encode data into this sound file\n");
    fprintf(stdout, "	-d <file>	.wav file, decode data from this sound file\n");
    fprintf(stdout, "	-t <file>	Data file to be encoded\n");
    fprintf(stdout, "	-o <file>	Encoded output file: in case of encoding, this is the encoded \n");
    fprintf(stdout, "			sound file. In case of decoding, this is the data file.\n");
    fprintf(stdout, "	-s		Print data file content to stdout.\n");
    fprintf(stdout, "	-h		Help\n\n");
    fprintf(stdout, " ---- Example ----\n");
    fprintf(stdout, "> %s -e track-01.wav -t secret-email.txt -o track-01_secret.wav\n", program);
    fprintf(stdout, "> %s -d track-01_secret.wav -s > secret-decoded.txt\n", program);
    
    exit(0);
}

int bit_to_dec(int num, int bit_mode){
    if(bit_mode == 6){
	if(num == 0) return 32;
	if(num == 1) return 16;
	if(num == 2) return 8;
	if(num == 3) return 4;
	if(num == 4) return 2;
	if(num == 5) return 1;
    }
    if(bit_mode == 8){
	if(num == 0) return 128;
	if(num == 1) return 64;
	if(num == 2) return 32;
	if(num == 3) return 16;
	if(num == 4) return 8;
	if(num == 5) return 4;
	if(num == 6) return 2;
        if(num == 7) return 1;
    }
    return 0;
}
