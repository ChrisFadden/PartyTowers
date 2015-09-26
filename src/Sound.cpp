#include <iostream>
#include "Sound.h"

void PlaySound(char* songName)
{
    SDL_AudioSpec wav_spec;
    Uint32 wav_length;
    Uint8 *wav_buffer;

    if(SDL_LoadWAV(songName,&wav_spec, &wav_buffer,&wav_length) == NULL)
        std::cout << "Could not load wav file: " << SDL_GetError() << std::endl;
    
    SDL_FreeWAV(wav_buffer);
}


