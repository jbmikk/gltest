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
int context_init_window(Context *context);
void context_dispose(Context *context);

#endif //CONTEXT_H
