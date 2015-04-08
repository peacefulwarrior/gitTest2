#include "Engine.h"

Engine::Engine(const int screenH, const int screenW) 
{
	// initialize SDL
	if (SDL_Init(SDL_INIT_EVERYTHING | SDL_INIT_VIDEO) != 0) {
		std::cout << "SDL_Init() Error: " << SDL_GetError() << std::endl;
	}
	// allow for modern OpenGL to be used
	glewExperimental = GL_TRUE;
	if (!glewInit()) {
		std::cerr << "glewInit Error" << std::endl;
	}
	// set up SDL for opengl 3.2
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
	window = SDL_CreateWindow("Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screenH, screenW, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
	if (window == nullptr) {
		std::cout << "SDL_CreateWindow() Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
	}
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC | SDL_WINDOW_OPENGL);
	if (renderer == nullptr) {
		SDL_DestroyWindow(window);
		std::cout << "SDL_CreateRenderer() Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
	}
	// set the gl context to the window
	glContext = SDL_GL_CreateContext(window);
}

void Engine::quit()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_GL_DeleteContext(glContext);
	SDL_Quit();
}

std::string Engine::getResourcePath(const std::string &subDir = ""){
	//We need to choose the path separator properly based on which
	//platform we're running on, since Windows uses a different
	//separator than most systems
#ifdef _WIN32
	const char PATH_SEP = '\\';
#else
	const char PATH_SEP = '/';
#endif
	//This will hold the base resource path: Lessons/res/
	//We give it static lifetime so that we'll only need to call
	//SDL_GetBasePath once to get the executable path
	static std::string baseRes;
	if (baseRes.empty()){
		//SDL_GetBasePath will return NULL if something went wrong in retrieving the path
		char *basePath = SDL_GetBasePath();
		if (basePath){
			baseRes = basePath;
			SDL_free(basePath);
		}
		else {
			std::cerr << "Error getting resource path: " << SDL_GetError() << std::endl;
			return "";
		}
		//We replace the last bin/ with res/ to get the the resource path
		size_t pos = baseRes.rfind("bin");
		baseRes = baseRes.substr(0, pos) + "res" + PATH_SEP;
	}
	//If we want a specific subdirectory path in the resource directory
	//append it to the base path. This would be something like Lessons/res/Lesson0
	return subDir.empty() ? baseRes : baseRes + subDir + PATH_SEP;
}


SDL_Texture* Engine::loadTexture(const std::string &file)
{
	SDL_Texture *texture = IMG_LoadTexture(renderer, file.c_str());
	if (texture == nullptr){
		logSDLErr("LoadTexture");
	}
	return texture;
}


void Engine::logSDLErr(const std::string &msg)
{
	std::cout << msg << " Error: " << SDL_GetError() << std::endl;
}

void Engine::renderTexture(SDL_Texture *tex, int x, int y){
	//Setup the destination rectangle to be at the position we want
	SDL_Rect dst;
	dst.x = x;
	dst.y = y;
	//Query the texture to get its width and height to use
	SDL_QueryTexture(tex, NULL, NULL, &dst.w, &dst.h);
	SDL_RenderCopy(renderer, tex, NULL, &dst);
}

/*
void Engine::render()
{
	for (Sprite s : sprites) {
		renderTexture(s.getTexture(), s.x, s.y);
	}
}

void Engine::setSpriteRenderer(SDL_Renderer *ren)
{
	for (Sprite s : sprites) {
		s.setRenderer(ren);
	}
}
*/