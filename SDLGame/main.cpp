#include <iostream>
#include <string>
#include <SDL.h>
#include <glew.h>
#include <GL/GL.h>
#include <SDL_opengl.h>
#include "Engine.h"
#include <SDL_image.h>

float vertices[] = {
	0.0f, 0.5f, // Vertex 1 (X, Y)
	0.5f, -0.5f, // Vertex 2 (X, Y)
	-0.5f, -0.5f  // Vertex 3 (X, Y)
};

const GLchar *vertexShaderSource =
"#version 150 \n"
"in vec2 position;"
"void main()"
"{"
"	gl_Position = vec4(position, 0.0, 1.0);"
"}";

const GLchar *fragmentShaderSource =
"#version 150 \n"
"out vec4 outColor;"
"void main()"
"{"
"	outColor = vec4(1.0, 1.0, 1.0, 1.0);"
"}";

int main(int argc, char **argv)
{	
	Engine engine(640, 480);
	SDL_Renderer *ren = engine.getRenderer();
	SDL_Texture *tex = engine.loadTexture(engine.getResourcePath("") + "test.png");

	GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	GLuint fragShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragShader);

	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragShader);

	glBindFragDataLocation(shaderProgram, 0, "outColor");
	glLinkProgram(shaderProgram);
	glUseProgram(shaderProgram);

	GLuint posAttrib = glGetAttribLocation(shaderProgram, "position");
	glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(posAttrib);

	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	int x = 0;
	int y = 0;
	const int velocity = 12;

	SDL_Event event;
	bool quit = false;
	while (!quit)
	{
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT) {
				quit = true;
			}
			if (event.type == SDL_KEYDOWN) {
				if (event.key.keysym.sym == SDLK_w) {
					// up
				}
				if (event.key.keysym.sym == SDLK_s) {
					// down
				}
				if (event.key.keysym.sym == SDLK_a) {
					// left
				}
				if (event.key.keysym.sym == SDLK_d) {
					// right
				}
				else if (event.key.keysym.sym == SDLK_ESCAPE) { // might remove this 
					quit = true;
				}
			}
		}
		SDL_GL_SwapWindow(engine.getWindow());
	}

	SDL_DestroyTexture(tex);
	engine.quit();
	return 0;
}