#ifndef WINDOW_H
#define WINDOW_H

#include <GLFW/glfw3.h>


typedef struct Window {
	GLFWwindow* handle;
	int width;
	int height;
} Window;

int window_init(Window *window, int width, int height, char *name);
void window_set_input(Window *window);
void window_set_size(Window *window);
void window_swap_buffers(Window *window);
void window_set_size_callback(Window *window, GLFWwindowsizefun callback);

#endif //WINDOW_H
