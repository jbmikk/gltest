#ifndef CONTEXT_H
#define CONTEXT_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define GLEW_STATIC 1

#include "window.h"


typedef struct Context {
} Context;

int context_init(Context *context);
void context_set_window(Context *context, Window *window);
int context_init_extensions(Context *context);
int context_set_clear_color(float r, float g, float b, float a);
void context_clear();
void context_dispose(Context *context);

#endif //CONTEXT_H
