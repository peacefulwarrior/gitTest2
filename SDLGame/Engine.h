#ifndef ENGINE_H
#define ENGINE_H

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <glew.h>
#include <glm.hpp>
#include <string>
#include <vector>

class Engine
{
public:
	Engine();
	Engine(const int screenH = 640, const int screenW = 480);
	void quit();

	SDL_Window *getWindow() const { return window; }
	SDL_Renderer *getRenderer() const { return renderer; }
	std::string  getResourcePath(const std::string &subDir);

	/**
	* Loads a texture to the specified renderer
	* @param path The file path of the texture
	*/
	SDL_Texture *loadTexture(std::string &path);

	/**
	* Prints an error message along with
	* SDL's error code to standard output
	* @param msg Message to print
	*/
	static void logSDLErr(const std::string &msg);

	/**
	* Draws the texture to the renderer at position (x, y)
	* while preserving the texture's width and height
	* at the specified renderer
	* @param tex The texture to draw
	* @param x The x coordinate to draw to
	* @param y The y coordinate to draw to
	*/
	void renderTexture(SDL_Texture *tex, int x, int y);

	/**
	* Loads an image into a texture on the rendering device
	* @param file The image file to load
	* @param ren The renderer to load the texture onto
	* @return the loaded texture, or nullptr if something went wrong.
	*/
	SDL_Texture* loadTexture(const std::string &file);

	/**
	* Renders all sprites in the sprites vector
	* in the order they were loaded
	*/
	void render();

	/**
	* Sets the renderer all of the sprites in the Sprites vector
	* Used for rendering and creating many sprites without
	* having to set and render them individually
	*/
	void setSpriteRenderer(SDL_Renderer *ren);

	// Sprites caused many compile errors so i removed them
	// because i most likely wont be using them with opengl

	//std::vector<Sprite> sprites;
	//Sprite *player;

private:
	SDL_Window *window;
	SDL_Renderer *renderer;
	SDL_GLContext glContext;
};

#endif ENGINE_H