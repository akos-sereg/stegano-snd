stegano-snd
===========

This is an experimental project from my university years.   
The program is written in **C**, using **libsndfile1-dev** library. You can embed secret data (encode) into a sound file, with minimal loss of sound quality (you can not even recognize by listening). After that, you are able to retrieve (decode) the secret content from the encoded file.   

**Install**   

Prerequisites:   

    $ apt-get install libsndfile1-dev
    $ cd stegano-snd
    $ make

Usage:

    $ ./stegano-snd -e song.wav -t secret.txt -o song-encoded.wav
    $ ./stegano-snd -d song-encoded.wav -o
    
