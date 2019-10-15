#include <stdio.h>

#include "context.h"

void print_error() 
{
	GLenum error;
	while((error = glGetError()) != GL_NO_ERROR) {
		printf("Error: %i\n", error);
	}
}

int context_init(Context *context)
{
	if(!glfwInit()) {
		printf("Could not init GLFW");
		return -1;
	}
	return 0;
}

void context_dispose(Context *context)
{
	glfwTerminate();
}

void context_set_window(Context *context, Window *window)
{
	glfwMakeContextCurrent(window->handle);
}

int context_init_extensions(Context *context)
{
	glewExperimental = GL_TRUE; // Needed for core profile
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		return -1;
	}

	//#clear errors GLEW may trigger
	print_error();
	return 0;
}

int context_set_clear_color(float r, float g, float b, float a)
{
	glClearColor(r, g, b, a);
}

void context_clear()
{
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
}

