#ifndef _SOUND_H
#define _SOUND_H

#include "SDL.h"
#include "SDL_mixer.h"
#include <vector>
#include <tuple>

class GameSound
{
    public:
        GameSound(); 
        void PlaySound(char*); //Play .wav file
        bool IsPlaying(); 
        std::vector<Mix_Chunk*> MixChunkVec;
        std::vector<int> channelVec;
        ~GameSound();
};
#endif
