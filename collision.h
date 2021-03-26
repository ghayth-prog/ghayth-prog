#ifndef DS4_H_INCLUDED
#define DS4_H_INCLUDED







//void get_pixel(perssonage *p,background *b,SDL_Color *Color);
void GetPixelColor(SDL_Surface * surface,int x,int y,SDL_Color *color);
bool collision(SDL_Rect* rec1,SDL_Rect* rec2);
Uint32 getpixel(SDL_Surface *surface, int x, int y);
bool collision1(SDL_Surface *screen,int x,int y);
bool collision2(SDL_Surface *screen,int x,int y);
int collisiongravite (SDL_Surface *screen,SDL_Rect *rect);
int collisionright (SDL_Surface *screen,SDL_Rect *rect);
int collisionleft (SDL_Surface *screen,SDL_Rect *rect);
void gravite_enemi (SDL_Surface *screen,enemie *p);








  #endif // DS_H_INCLUDED
