#ifndef _snd_h_included_
#define _snd_h_included_

int feltolt(void);
char *outfp(char *header);
//void wav_decodol(SNDFILE *in, unsigned int len, int bitmode, int iscd);
void wav_decodol(char *insnd, char *output);
//void wav_codol(SNDFILE *out, SNDFILE *in, unsigned int len, FILE *text, int bitmode, SF_INFO sfinfo, char *key_fname);
void wav_codol(char *insnd, char *outsnd, char *key_fname);

#endif
