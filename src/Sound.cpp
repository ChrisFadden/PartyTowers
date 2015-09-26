#include <iostream>
#include "Sound.h"

GameSound::GameSound() {
    int audio_rate = 22050;
    Uint16 audio_format = AUDIO_S16SYS;
    int audio_channels = 2;
    int audio_buffers = 4096;
    if (Mix_OpenAudio(audio_rate, audio_format, audio_channels,
                      audio_buffers) != 0) {
        printf("Unable to initialize audio: %s\n", Mix_GetError());
    }
}

void GameSound::PlaySound(char* songName) {
    Mix_Chunk* sound = NULL;
    int channel;

    sound = Mix_LoadWAV(songName);
    if (sound == NULL) {
        printf("Unable to load WAV file: %s\n", Mix_GetError());
    }

    channel = Mix_PlayChannel(-1, sound, 0);
    if (channel == -1) {
        printf("Unable to play WAV file: %s\n", Mix_GetError());
    }
    
    MixChunkVec.push_back(sound);
    channelVec.push_back(channel);
    
    return;
}

bool GameSound::IsPlaying(){
   for(auto &i : channelVec)
   {
       if(Mix_Playing(i) != 0)
           return true;
   }
   return false;
}

GameSound::~GameSound(){
    for(auto &i : MixChunkVec)
    {
        Mix_FreeChunk(i);
    }
    Mix_CloseAudio();
}
