#ifndef SPRITE_H
#define SPRITE_H

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <string>
#include "Engine.h"

class Sprite
{
public:
	Sprite();
	Sprite(const std::string &path, int xCoord, int yCoord);
	Sprite(SDL_Surface *surface, int xCoord, int yCoord);
	Sprite(SDL_Texture *texture, int xCoord, int yCoord);
	
	void setRenderer(SDL_Renderer *ren);

	SDL_Texture *getTexture() const { return _texture; }
	void setTexture(SDL_Texture *texture) { _texture = texture; }

public:
	int x;
	int y;

private:
	SDL_Texture *_texture;
	SDL_Rect _boundingBox;
	SDL_Renderer *_ren;
};

#endif // SPRITE_H