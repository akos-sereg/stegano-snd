stegano-snd
===========

This is an experimental project from my university years.   
The program was written in **C**, using **libsndfile1-dev** library. Stegano-snd command line tool allows you to encode secret data file into a .wav sound file with minimal loss of quality, and then you can restore the secret content back from the .wav stream. 

**Use-case**
 * Encode secret data into soundtracks (44.1 khz, stereo)
 * Write soundtracks to CD
 * Listen to the music: there is secret data in the background which you can not "hear" at all
 * Use any CD grabber to extract .wav files back (44.1 khz, stereo again)
 * Restore secret data by decoding .wav files

In theory, you should be able to encode **50.46 MB** of secret data into a 80 min CD by using this technique.

**Usage**   

Prerequisites and Install:   

    $ apt-get install libsndfile1-dev
    $ cd stegano-snd
    $ make

Usage:

    $ ./stegano-snd -e song.wav -t secret.txt -o song-encoded.wav
    $ ./stegano-snd -d song-encoded.wav -o
    

**The way it works**

CD-quality .wav sound consists of 44100 frame (16 bit each) every second, multiplied with 2 because it is stereo: 88200 frames per second = 88200 * 16 bit sound data. When we are encoding secret data to the sound file, we take the least significant bit from each frame to hold secret data. Having secret data encoded into song-encoded.wav, only 15 bits/frame will be used to hold the original sound-wave, and one bit/frame for the secret data.    
As a result, we can encode **10.76 kbyte** data for every second in the sound file.

![Screenshot](https://raw.github.com/akos-sereg/stegano-snd/master/doc/sound.png "Stegano-SND")
