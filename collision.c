#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <stdbool.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include "def.h"
#include "background.h"
#include "perssonage.h"
#include "jouer.h"
#include "mouvement.h"
#include "collision.h"
#include "coin.h"
#include "coeur.h"
#include "enemi.h"




#define gravity 9.81;
#define GRAVITY_SPEED 0.6
#define MAX_FALL_SPEED 5
#define JUMP_HEIGHT 14.5
#define SPEED 2
#define MAX_SPEED 7
/*void get_pixel(perssonage *p,background *b,SDL_Color *Color)
{
//  Declaring col value
Uint32 col=0;
//  Declaring the pos variable to get the position of the wanted pixel
char *pos=(char*) b->background_tile->pixels;
//  Following the Y axe position of the main caracter
pos+= (b->background_tile->pitch * (p->rect.y+70));
//  Following the X axe position of the main caracter
pos+= (b->background_tile->format->BytesPerPixel * (b->camera.x));
//  Copying the data of the result pixel
memcpy(&col,pos,b->background_tile->format->BytesPerPixel);
//  Converting the copyied pixel to an RGB value using the SDL_GetRGB function
SDL_GetRGB(col,b->background_tile->format,&Color->r,&Color->g,&Color->b);
//  End of the get pixel function


}*/


bool collision(SDL_Rect* rec1,SDL_Rect* rec2)
{
if(rec1->y >= rec2->y + rec2->h)
return 0;
if(rec1->x >= rec2->x + rec2->w)
return 0;
if(rec1->y + rec1->h <= rec2->y)
return 0;
if(rec1->x + rec1->w <= rec2->x)
return 0;
return 1;
}
/*************************************************************************************************************/
/*************************************************************************************************************/
Uint32 getpixel(SDL_Surface *surface, int x, int y)
{
int bpp = surface->format->BytesPerPixel;
/* Here p is the address to the pixel we want to retrieve */
Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;
switch(bpp) {
case 1:
return *p;
case 2:
return *(Uint16 *)p;
case 3:
if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
return p[0] << 16 | p[1] << 8 | p[2];
else
return p[0] | p[1] << 8 | p[2] << 16;
case 4:
return *(Uint32 *)p;
default:
return 0;
			}
}
/*************************************************************************************************************/
/*************************************************************************************************************/
void GetPixelColor(SDL_Surface * surface,int x,int y,SDL_Color *Color)
{
    SDL_GetRGB(getpixel(surface,x,y),surface->format,&Color->r,&Color->g,&Color->b);
}
/*************************************************************************************************************/
/*************************************************************************************************************/
bool collision1(SDL_Surface *screen,int x,int y)
{
Uint32 blanc=SDL_MapRGB(screen->format,255,255,255);
if(getpixel(screen,x,y)==blanc)
return true;
return false ;
}
/*************************************************************************************************************/
/*************************************************************************************************************/
bool collision2(SDL_Surface *screen,int x,int y)
{
Uint32 noir=SDL_MapRGB(screen->format,0,0,0);
if(getpixel(screen,x,y)==noir)
{
return true;
}else
return false ;
}
/*************************************************************************************************************/
/*************************************************************************************************************/
int collisiongravite (SDL_Surface *screen,SDL_Rect *rect)
{
if (collision1(screen,rect->x+40,rect->y+90))
	return 1;
if (collision1(screen,rect->x+60,rect->y+90))
	return 1;
if (collision1(screen,rect->x+80,rect->y+90))
	return 1;


return 0;
}
/*************************************************************************************************************/
/*************************************************************************************************************/
int collisionright (SDL_Surface *screen,SDL_Rect *rect)
{
	if (collision1(screen,rect->x+85,rect->y))
	return 1;
if (collision1(screen,rect->x+85,rect->y+20))
	return 1;
if (collision1(screen,rect->x+85,rect->y+40))
	return 1;
if (collision1(screen,rect->x+85,rect->y+60))
	return 1;
if (collision1(screen,rect->x+85,rect->y+80))
	return 1;
if (collision1(screen,rect->x+85,rect->y+85))
	return 1;


return 0;
}
/*************************************************************************************************************/
/*************************************************************************************************************/
int collisionleft (SDL_Surface *screen,SDL_Rect *rect)
{
	if (collision1(screen,rect->x,rect->y))
	return 1;
	if (collision1(screen,rect->x,rect->y+20))
	return 1;
	if (collision1(screen,rect->x,rect->y+40))
	return 1;
		if (collision1(screen,rect->x,rect->y+60))
	return 1;
	if (collision1(screen,rect->x,rect->y+80))
	return 1;
		if (collision1(screen,rect->x,rect->y+85))
	return 1;

return 0;
}
/*************************************************************************************************************/
/*************************************************************************************************************/
void gravite (SDL_Surface *screen,perssonage*p,Input *I)
{
if (collisiongravite (screen,&p->rect)==1)
	p->onground=1;
else
	p->onground=0;

if (p->onground==0)
{
		p->one_jump=0;
		p->yvelocity+=GRAVITY_SPEED;
		if (p->yvelocity>=MAX_FALL_SPEED)
			p->yvelocity=MAX_FALL_SPEED;
		//p->rect.y=p->rect.y+p->yvelocity*p->delta_time;
}else
p->one_jump=1;

}
/*************************************************************************************************************/
/*************************************************************************************************************/
void gravite_enemi (SDL_Surface *screen,enemie *p)
{
if (collisiongravite (screen,&p->rect)==1)
	p->onground=1;
else
	p->onground=0;

if (p->onground==0)
{
		p->rect.y+=GRAVITY_SPEED;
		//p->rect.y=p->rect.y+p->yvelocity*p->delta_time;
}

}
