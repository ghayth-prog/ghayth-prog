#ifndef temps_H
#define temps_H
#include <SDL/SDL_image.h>
#include <stdbool.h>

typedef struct timer Timer;
struct timer {
    bool isStarted;
    bool isPaused;
    Uint32 startTime;
    Uint32 pausedTime;
};

SDL_Surface* chargerImage(char* imagetemps);
SDL_Surface* chargerImageBMP(char* imagetemps2);

Timer initTimer();
void startTimer(Timer*);
void stopTimer(Timer*);
void pauseTimer(Timer*);
void continueTimer(Timer*);
Uint32 getTime(Timer t);

#endif
