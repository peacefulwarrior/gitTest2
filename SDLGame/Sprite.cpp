#include "Sprite.h"


Sprite::Sprite()
	: x(0),
	  y(0),
	  _texture(nullptr),
	  _ren(nullptr)
{
}

Sprite::Sprite(const std::string &path, int xCoord, int yCoord)
	: _texture(nullptr),
	x(xCoord),
	y(yCoord),
	  _ren(nullptr)
{
	_texture = IMG_LoadTexture(_ren, path.c_str());
	if (_texture == nullptr){
		Engine::logSDLErr("LoadTexture");
	}
}

Sprite::Sprite(SDL_Surface  *surface, int xCoord, int yCoord)
	: x(xCoord),
	y(yCoord),
	_ren(nullptr)
{
	if (surface == nullptr) {
		Engine::logSDLErr("Surface");
		return;
	}
	_texture = SDL_CreateTextureFromSurface(_ren, surface);
	if (_texture == nullptr) {
		Engine::logSDLErr("CreateTextureFromSurface");
	}
}

Sprite::Sprite(SDL_Texture *texture, int xCoord, int yCoord)
	: x(xCoord),
	y(yCoord),
	_ren(nullptr)
{
	if (texture == nullptr) {
		Engine::logSDLErr("Texture");
		return;
	}
	_texture = texture;
}

void Sprite::setRenderer(SDL_Renderer *ren)
{
	_ren = ren;
}