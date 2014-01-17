#include "../include/stegano-snd.h"


int main(int argc, char **argv)
{
    int c,i;
    
    sprintf(program, "%s", argv[0]);
    if(argc < 2) help();
    
    
    herb_snd_init();

    for(i=0; i!=2; i++)
    {
	while((c = getopt(argc, argv, "e:d:t:o:hs"))  != EOF)
	{
	    switch(c)
	    {
		case 'e':
		    if(usr_defs.decode) help();
		    sprintf(usr_defs.input, "%s", optarg);
		    usr_defs.encode = 1;
		    break;
		case 'd':
		    if(usr_defs.encode) help();
		    sprintf(usr_defs.input, "%s", optarg);
		    usr_defs.decode = 1;
		    break;
		case 't':
		    if(usr_defs.encode) 
			sprintf(usr_defs.textfile, "%s", optarg);
		    break;
		case 'o':
		    sprintf(usr_defs.output, "%s", optarg);
		    break;
		case 'h':
		    help();
		    break;
		case 's':
		    usr_defs.stdout = 1;
		    break;
		default:
		    help();
		    break;
	    }
	}
    }
    
    hcore();
        
    return 1;
}

