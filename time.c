#include "time.h"

SDL_Surface* chargerImage(char* imagetemps)
{
    SDL_Surface* image;

    image = IMG_Load(imagetemps);
    if (!image) {
        printf("Failed to load \"%s\"\n", imagetemps);
        printf("IMG_Load: %s\n", IMG_GetError());
    }

    return image;
}

SDL_Surface* chargerImageBMP(char* imagetemps2)
{
    SDL_Surface *temp, *sprite;

    /* Load the sprite image */
    sprite = SDL_LoadBMP(imagetemps2);
    if (sprite == NULL) {
        fprintf(stderr, "Couldn't load %s: %s", imagetemps2, SDL_GetError());
        exit(1);
    }

    /* Set transparent pixel as the pixel at (0,0) */
    if (sprite->format->palette) {
        SDL_SetColorKey(sprite, (SDL_SRCCOLORKEY | SDL_RLEACCEL),
            *(Uint8*)sprite->pixels);
    }

    /* Convert sprite to video format */
    temp = SDL_DisplayFormat(sprite);
    SDL_FreeSurface(sprite);
    if (temp == NULL) {
        fprintf(stderr, "Couldn't convert background: %s\n",
            SDL_GetError());
        exit(1);
    }
    sprite = temp;
    return sprite;
}

Timer initTimer()
{
    Timer t;
    t.startTime = 0;
    t.pausedTime = 0;
    t.isPaused = false;
    t.isStarted = false;
    return t;
}

void startTimer(Timer* t)
{
    t->isStarted = true;
    t->isPaused = false;
    t->startTime = SDL_GetTicks();
    t->pausedTime = 0;
}

void stopTimer(Timer* t)
{
    t->isStarted = false;
    t->isPaused = false;
    t->startTime = 0;
    t->pausedTime = 0;
}

void pauseTimer(Timer* t)
{
    if (t->isStarted && !t->isPaused) {
        t->isPaused = true;

        t->pausedTime = SDL_GetTicks() - t->startTime;
        t->startTime = 0;
    }
}

void continueTimer(Timer* t)
{
    if (t->isStarted && t->isPaused) {
        t->isPaused = false;
        t->startTime = SDL_GetTicks() - t->pausedTime;
        t->pausedTime = 0;
    }
}

Uint32 getTime(Timer t)
{
    Uint32 time = 0;

    if (t.isStarted) {
        if (t.isPaused) {
            time = t.pausedTime;
        } else {
            time = SDL_GetTicks() - t.startTime;
        }
    }

    return time;
}
