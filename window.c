#include "window.h"
#include <stdio.h>

int window_init(Window *window, int width, int height, char *name)
{
	window->width = width;
	window->height = height;

	// Window hints
	glfwWindowHint(GLFW_SAMPLES, 4);
	//Opengl 2.1
	//glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
	//glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	//Opengl 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // MacOS fix
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window->handle = glfwCreateWindow(width, height, name, NULL, NULL);

	if(!window->handle) {
		return -1;
	}
	return 0;
}

void window_set_input(Window *window)
{
	// Ensure we can capture the escape key being pressed below
	glfwSetInputMode(window->handle, GLFW_STICKY_KEYS, GL_TRUE);
}

void window_set_size(Window *window)
{
	glfwGetWindowSize(window->handle, &window->width, &window->height);
}

void window_swap_buffers(Window *window)
{
	glfwSwapBuffers(window->handle);
}

void window_set_size_callback(Window *window, GLFWwindowsizefun callback)
{
	glfwSetWindowSizeCallback(window->handle, callback);
}
