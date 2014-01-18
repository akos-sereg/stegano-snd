stegano-snd
===========

This is an experimental project from my university years.   
The program was written in **C**, using **libsndfile1-dev** library. You can embed secret data (encode) into a sound file, with minimal loss of sound quality (you can not even recognize by listening). After that, you are able to retrieve (decode) the secret content from the encoded file.   

![Screenshot](https://raw.github.com/akos-sereg/stegano-snd/master/doc/encoding.png "Encoding")

**Usage**   

Prerequisites:   

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
