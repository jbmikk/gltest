#include "window.h"
#include <stdio.h>

int window_init(Window *window, int width, int height, char *name)
{
	window->width = width;
	window->height = height;

	window->handle = glfwCreateWindow(width, height, name, NULL, NULL);

	if(!window->handle) {
		return -1;
	}
	glfwMakeContextCurrent(window->handle);

	// Ensure we can capture the escape key being pressed below
	glfwSetInputMode(window->handle, GLFW_STICKY_KEYS, GL_TRUE);

	glfwGetWindowSize(window->handle, &window->width, &window->height);
	return 0;
}

void window_swap_buffers(Window *window)
{
	glfwSwapBuffers(window->handle);
}

void window_set_size_callback(Window *window, GLFWwindowsizefun callback)
{
	glfwSetWindowSizeCallback(window->handle, callback);
}
