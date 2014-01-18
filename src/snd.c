#include "../include/stegano-snd.h"

#define DISPLAY		0
#define SHOW		4
#define CNTR		4
#define USEASCII	0
#define MAGIC_NUM	3
#define BUFFER_LEN	1024
#define HEADER_LEN	30
#define HEADER_START	4

FILE *out;
int headerstat;
int ch;
int c;
int maxlen=0;
int left,n[8];
char out_fp_name[256];

void hdr_check(char *hdr)
{
    int i=1;
    int fname_start=0;
    int len_start = 0;
    char length[32];
    
    if((strlen(hdr) < 10))
    {
	fprintf(stderr, "Error: invalid header\n");
	exit(0);
    }
    
    while(hdr[i] == ' ') 
    {
	i++;
	if(strlen(hdr) < i)
	{
	    fprintf(stderr, "Error: invalid header\n");
	    exit(0);
	}
    }
    
    fname_start = i;
    while(hdr[i] != ' ')
    {
	out_fp_name[i-fname_start] = hdr[i];
	i++;
    }
    out_fp_name[i-fname_start] = '\0';
    
    while(hdr[i] == ' ') 
    {
	i++;
	if(strlen(hdr) < i)
	{
	    fprintf(stderr, "Error: invalid header\n");
	    exit(0);
	}
    }
    
    len_start = i;
    while(hdr[i] != 0)
    {
	length[i-len_start] = hdr[i];
	if(strlen(hdr)<i)
	{
	    fprintf(stderr, "Error: invalid header\n");
	    exit(0);
	}
	i++;
    }
    
    length[i-len_start] = '\0';
    maxlen = atoi(length);

    headerstat = 1;
    return;
}

void wav_decode(char *insnd, char *output)
{
    FILE *out;
    SNDFILE *infile;
    SF_INFO sfinfo;
    short data[BUFFER_LEN];
    unsigned int	readcount, k, len;
    int bitstate = 0;
    char fname[300], header[50];    
    int end_header=0;
    int bitmode = 8, bit; 
    int ch, processed=0;

    headerstat = 0;    
    
    if(strlen(output)) out = fopen(output, "w");
    else out = stdout;
    
    if(!out)
    {
	fprintf(stderr, "Error: output channel is not defined\n");
	exit(0);
    }
    
    
    infile = sf_open(insnd, SFM_READ, &sfinfo);
    if(!infile) return;
    len = BUFFER_LEN/sfinfo.channels;

    readcount = len ;
    ch='c';
    bit=0;

    while (readcount == len){
	
        readcount = sf_read_short(infile, data, len);
	
        for (k = 0 ; k < readcount ; k++) 
	{
	    if(bit == 8)
	    {
		/* Building header */
		if(!headerstat && (ch!=0)) 
		{
		    if(strlen(header) > 42) 
		    {
			fprintf(stderr, "Error: invalid header\n");
			exit(0);
		    }
		    sprintf(header, "%s%c", header, ch);
		} else if(!headerstat && (ch==0)) 
		{
		    /* Processing header */
		    headerstat = 1;
		    hdr_check(header);
		}
		
		/* End of processing header, processing body */
		if(headerstat)
		{
		    if(processed > maxlen) 
		    {
			fclose(out);
			sf_close(infile);
			return;
		    }
		    if(processed != 0) fprintf(out, "%c", ch);
		    processed++;
		}
		
		ch=0;
		bit = 0;
	    }
	    
	    if(abs(data[k] % 2) == 1) ch += bit_to_dec(bit, 8);
	    
	    bit++;
	} 
	
    }
    fclose(out);
    return;
    
}



int *toBits(char c)
{
    int left = toascii(c);
			if(left > 127){ n[0] = 1; left = left % 128; } else n[0] = 0;
	    		if(left > 63){ n[1] = 1; left = left % 64; } else n[1] = 0;
	    		if(left > 31){ n[2] = 1; left = left % 32; } else n[2] = 0;
	    		if(left > 15){ n[3] = 1; left = left % 16; } else n[3] = 0;
	    		if(left > 7){ n[4] = 1; left = left % 8; } else n[4] = 0;
	    		if(left > 3){ n[5] = 1; left = left % 4; } else n[5] = 0;
	    		if(left > 1){ n[6] = 1; left = left % 2; } else n[6] = 0;
	    		if(left > 0){ n[7] = 1; } else n[7] = 0;		
			
    return n;		
}		    


void wav_analysis(char *insnd)
{
    SNDFILE *infile;
    SF_INFO sfinfo;

    infile = sf_open(insnd, SFM_READ, &sfinfo);
    long capacityBit = (int)(sfinfo.frames * sfinfo.channels);
    double capacityByte = capacityBit / 8;
    double capacityKb = capacityBit / 8 / 1024;
    double capacityMb = capacityBit / 8 / 1024 / 1024;
    
    printf("Frames: %d\n", (int)sfinfo.frames);
    printf("Channels: %d\n", (int)sfinfo.channels);
    printf("Capacity: %d bit\n", (int)(sfinfo.frames * sfinfo.channels));
    printf("  => %.2f bytes\n", capacityByte);
    printf("  => %.2f Kb\n", capacityKb);
    printf("  => %.2f MB\n", capacityMb);
    
    return;
}


void wav_encode(char *insnd, char *outsnd, char *key_fname)
{
    SNDFILE *outfile, *infile;
    SF_INFO sfinfo, sfinfo_out;
    FILE *fd_text;
    short data[BUFFER_LEN];
    unsigned int	readcount, k ;
    unsigned int len = 0;
    int n[8], bitmode=8;
    int flen;
    char header[40], ch;
    int pt, bit;
    int *bitstream;
    int wrote=0;
    int max=0,min=999999;
    int cnt=0;

    infile = sf_open(insnd, SFM_READ, &sfinfo);
    sfinfo_out = sfinfo;
    
    outfile = sf_open(outsnd, SFM_WRITE, &sfinfo_out);
    
    len = BUFFER_LEN/sfinfo.channels;
    printf("len: %d channels: %d\n", len, sfinfo.channels);
    flen = file_len(key_fname);
    fd_text = fopen(key_fname, "r");
    if(!fd_text) return;
    
    if(((flen*bitmode) + ((strlen(key_fname)*8) + 5  ) ) > sfinfo.frames * sfinfo.channels) {
	
	printf("Length of input data exceeds WAV capacity. Exiting ...\n");
	printf("Capacity: %d bit\n", (int)(sfinfo.frames * sfinfo.channels));
	printf("Needed: %d\n", flen*8);
	return;
    
    }
    
    if(strlen(key_fname) > 32) key_fname[32] = '\0';
    sprintf(header, "%32s%8d", key_fname, flen);

    readcount = len ;
    pt=0;
    bit=0;
    ch = header[0];
    bitstream = toBits(ch);
    
    while (readcount == len)
    {
        readcount = sf_read_short(infile, data, len);
	for (k=0; k<readcount; k++) 
	{
	    
	    if(bit == 8)
	    {
		bit=0;
		wrote++;
		if(wrote > strlen(header)) 
		{
		    if(!feof(fd_text)) ch = fgetc(fd_text);
		    else ch = 'a';
		} else ch = header[wrote];
		bitstream = toBits(ch);
	    }
	    
	    
	    if(data[k] > max) max = data[k];
	    if(data[k] < min) min = data[k];
	    
	    cnt++;
	    
	    if(bitstream[bit])
	    {
	    
		if((data[k] % 2) == 0 ) 
		{
		    
		    if(data[k] < 10) data[k]++;
		    else data[k]--;
		} 
	    } else { 
		if(((data[k] % 2) == 1) || (data[k]%2 == -1)) 
		{
		    if(data[k] < 10) data[k]++;
		    else data[k]--; 
		}
	    }
	    	    
	    bit++;
	}
		
	sf_write_short(outfile, data, readcount);
    }
    
    printf("min: %d -> %d\n", min, max);

    sf_close(outfile);
    sf_close(infile);
    return ;
    
}

